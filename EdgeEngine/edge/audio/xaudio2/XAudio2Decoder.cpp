// cpp文件

#include "XAudio2Decoder.h"
#include "lib-xaudio2.h"
#include <utils/FileUtils.h>

USING_NS_EDGE;

AudioData* XAudio2Decoder::getMp3DataFromFile(const std::string& filename)
{
	AudioData* audioData = NULL;

	int err = 0;
	mpg123_handle* mpg123Handle = NULL;
	err = mpg123_init();
	if (err != MPG123_OK) { return NULL; }
	mpg123Handle = mpg123_new(NULL, &err);
	if (err != MPG123_OK) { return NULL; }
	err = mpg123_open(mpg123Handle, filename.c_str());
	if (err != MPG123_OK) { return NULL; }
	long samplerate;
	int channels, encod;
	err = mpg123_getformat(mpg123Handle, &samplerate, &channels, &encod);
	if (err != MPG123_OK) { return NULL; }

	Byte* pcmdata = NULL;
	UInt length = 0;
	std::size_t done;
	off_t samples = mpg123_length(mpg123Handle);
	if (samples > 0)
	{
		length = (UInt)(channels * 2 * samples);
		pcmdata = new Byte[length];
		ZeroMemory(pcmdata, length);
	}
	else
	{
		return NULL;
	}
	err = mpg123_read(mpg123Handle, pcmdata, length, &done);
	if (err != MPG123_OK)
	{
		if (err == MPG123_NEED_MORE)
		{
			//err = mpg123_feed(mpg123Handle, pcmdata, length);
			err = MPG123_OK;
		}
	}
	if (err != MPG123_OK)
	{
		delete[] pcmdata;
		return NULL;
	}

	audioData = new AudioData();
	audioData->Filename = filename;
	audioData->AudioFormat = WAVE_FORMAT_PCM;
	audioData->BitsPerSample = 16;
	audioData->BlockAlign = 2 * channels; // 16 bits / 8 (to bytes) * numchannels (2)
	audioData->ByteRate = samplerate*channels * 2;
	audioData->NumberOfChannels = channels;
	audioData->SampleRate = samplerate;
	audioData->data.setValue(pcmdata, length);
	delete[] pcmdata;

	audioData->SoundLength = audioData->data.size / audioData->BlockAlign;
	audioData->TotalTime = (UInt)(audioData->data.size /
		(double)audioData->SampleRate /
		(double)audioData->NumberOfChannels /
		((double)audioData->BitsPerSample / 8.0));

	return audioData;
}

AudioData* XAudio2Decoder::getOggDataFromFile(const std::string& filename)
{
	AudioData* audioData = NULL;

	char pcmout[4096]; // ogg decoding buffer
	OggVorbis_File vf;
	int eof = 0;
	int current_section = 0;

	if (ov_fopen(filename.c_str(), &vf) < 0)
	{
		assert(!"XA2OggSound::load: Input does not appear to be an Ogg bitstream.");
		return NULL;
	}

	/* Throw the comments plus a few lines about the bitstream we're
	decoding */
	vorbis_info *vi = ov_info(&vf, -1);

	// resize the pcmdata vector to the size of the ogg file
	// two bytes per channel per sample
	ogg_int64_t samples = ov_pcm_total(&vf, -1);
	int channels = vi->channels;
	int samplerate = vi->rate;

	//std::vector<unsigned char> pcmdata;
	Byte* pcmdata = NULL;
	UInt length = 0;
	if (samples > 0)
	{
		//pcmdata.reserve((UInt)(channels * 2 * samples));
		length = (UInt)(channels * 2 * samples);
		pcmdata = new Byte[length];
		ZeroMemory(pcmdata, length);
	}
	else
	{
		return NULL;
	}

	UInt index = 0;
	while (!eof)
	{
		long ret = ov_read(&vf, pcmout, sizeof(pcmout), 0, 2, 1, &current_section);
		if (ret == 0)
		{
			/* EOF */
			eof = 1;
		}
		else if (ret < 0)
		{
			/* error in the stream.  Not a problem, just reporting it in
			case we (the app) cares.  In this case, we don't. */
		}
		else
		{
			/* we don't bother dealing with sample rate changes, etc, but
			you'll have to*/
			// transfer the data out of the ogg buffer and into ours.
			if (index + ret > length)
			{
				ret = length;
			}
			for (int q = 0; q < ret; q++) {
				//pcmdata.push_back(pcmout[q]);
				pcmdata[index] = pcmout[q];
				++index;
			}
		}
	}

	/* cleanup */
	ov_clear(&vf);

	// now that we have the PCM data in memory, convert it to a WAV file
	// and handoff to DirectMusic for loading into a segment.
	audioData = new AudioData();
	audioData->Filename = filename;
	audioData->AudioFormat = WAVE_FORMAT_PCM;
	audioData->BitsPerSample = 16;
	audioData->BlockAlign = 2 * channels; // 16 bits / 8 (to bytes) * numchannels (2)
	audioData->ByteRate = samplerate*channels * 2;
	audioData->NumberOfChannels = channels;
	audioData->SampleRate = samplerate;
	audioData->data.setValue(pcmdata, length);
	delete[] pcmdata;

	audioData->SoundLength = audioData->data.size / audioData->BlockAlign;
	audioData->TotalTime = (UInt)(audioData->data.size / (double)audioData->SampleRate / (double)audioData->NumberOfChannels / ((double)audioData->BitsPerSample / 8.0));

	return audioData;
}

AudioData* XAudio2Decoder::getWavDataFromFile(const std::string& filename)
{
	AudioData* audioData = NULL;
	Data data = FileUtils::readBinaryFromFile(filename);

	if (!data.bin || !data.size) { return NULL; }

	FOURCC riff, wave, fmt, datacc;

	// check for RIFF ChunkID
	memcpy(&riff, &data[0], sizeof(FOURCC));
	if (riff != mmioFOURCC('R', 'I', 'F', 'F'))
	{
		assert(!"XA2WaveSound::load: invalid WAV file data (missing RIFF header).");
		return false;
	}

	// check for WAVE format
	memcpy(&wave, &data[8], sizeof(FOURCC));
	if (wave != mmioFOURCC('W', 'A', 'V', 'E'))
	{
		assert(!"XA2WaveSound::load: invalid WAV file data (not WAVE format).");
		return false;
	}

	// check for FMT ChunkID
	memcpy(&fmt, &data[12], sizeof(FOURCC));
	if (fmt != mmioFOURCC('f', 'm', 't', ' '))
	{
		assert(!"XA2WaveSound::load: invalid WAV file data (FMT subchunk not found).");
		return false;
	}

	// check for DATA ChunkID
	memcpy(&datacc, &data[36], sizeof(FOURCC));
	if (datacc != mmioFOURCC('d', 'a', 't', 'a'))
	{
		assert(!"XA2WaveSound::load: invalid WAV file data (DATA subchunk not found).");
		return false;
	}

	// if we get here, we're pretty sure it's a WAV file.
	audioData = new AudioData();

	// load in data members
	audioData->Filename = filename;
	memcpy(&audioData->AudioFormat, &data[20], sizeof(short int));
	memcpy(&audioData->NumberOfChannels, &data[22], sizeof(short int));
	memcpy(&audioData->SampleRate, &data[24], sizeof(short int));
	memcpy(&audioData->ByteRate, &data[28], sizeof(int));
	memcpy(&audioData->BlockAlign, &data[32], sizeof(short int));
	memcpy(&audioData->BitsPerSample, &data[34], sizeof(short int));

	UInt datasize = 0;
	memcpy(&datasize, &data[40], sizeof(int));
	audioData->data.setValue(&data[44], datasize);
	audioData->SoundLength = datasize / audioData->BlockAlign;
	audioData->TotalTime = (UInt)(datasize / (double)audioData->SampleRate / (double)audioData->NumberOfChannels / ((double)audioData->BitsPerSample / 8.0));

	return audioData;
}
