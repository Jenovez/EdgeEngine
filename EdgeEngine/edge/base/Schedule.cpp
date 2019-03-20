// cpp文件

#include "Schedule.h"

USING_NS_EDGE;

Schedule* Schedule::create()
{
	auto sc = new Schedule();
	sc->autorelease();
	sc->changeState(new DelayState());
	return sc;
}
Schedule* Schedule::create(const ScheduleFunc& func)
{
	auto sc = new Schedule();
	sc->autorelease();
	sc->setUpdateFunc(func);
	sc->changeState(new DelayState());
	return sc;
}

Schedule::Schedule()
: _updateFunc(nullptr)
, m_dDelay(0)
, m_dInterval(0)
, m_iCounts(0)
, m_iZOrder(0)
, _state(NULL)
, m_bStop(false)
, m_bPause(false)
{}
Schedule::~Schedule()
{
	if (_state)
	{
		delete _state;
	}
}

void Schedule::update(double dt)
{
	if (m_bStop) { return; }
	if (m_bPause) { return; }
	if (!_state) { return; }
	_state->update(dt);
}

void Schedule::setUpdateFunc(const ScheduleFunc& func) { _updateFunc = func; }
void Schedule::setDelay(double delay) { m_dDelay = delay; }
double Schedule::getDelay() const { return m_dDelay; }
void Schedule::setInterval(double interval) { m_dInterval = interval; }
double Schedule::getInterval() const { return m_dInterval; }
void Schedule::setCounts(int counts) { m_iCounts = counts; }
int Schedule::getCounts() const { return m_iCounts; }
void Schedule::setZOrder(int zOrder) { m_iZOrder = zOrder; }
int Schedule::getZOrder() const { return m_iZOrder; }
void Schedule::setStop(bool b) { m_bStop = b; }
void Schedule::setPause(bool b) { m_bPause = b; }
bool Schedule::isStop() const { return m_bStop; }
bool Schedule::isPause() const { return m_bPause; }
void Schedule::changeState(ScheduleState* state)
{
	if (_state)
	{
		delete _state;
	}
	_state = state;
	if (_state)
	{
		_state->_scheduleObj = this;
	}
	else
	{
		setStop(true);
	}
}
void Schedule::_callbackFunc(double dt)
{
	if (!_updateFunc) { return; }
	_updateFunc(dt);
}

Schedule::DelayState::DelayState()
: m_dCurrentDelay(0)
{}
void Schedule::DelayState::update(double dt)
{
	if (m_dCurrentDelay < _scheduleObj->getDelay())
	{
		m_dCurrentDelay += dt;
		if (m_dCurrentDelay < _scheduleObj->getDelay()) { return; }
	}
	
	Schedule::ScheduleState* state = nullptr;
	if (_scheduleObj->getCounts() <= 0)
	{
		if (_scheduleObj->getInterval() > 0)
		{
			state = new Schedule::IntervalState();
		}
		else
		{
			state = new Schedule::NormalState();
		}
	}
	else
	{
		state = new Schedule::CountsState();
	}
	_scheduleObj->changeState(state);
	state->update(dt);
}
Schedule::CountsState::CountsState()
: m_iCurrentCounts(0)
, m_dCurrentInterval(0)
{}
void Schedule::CountsState::update(double dt)
{
	if (m_iCurrentCounts >= _scheduleObj->getCounts())
	{
		_scheduleObj->setStop(true);
		_scheduleObj->changeState(NULL);
		return;
	}

	if (_scheduleObj->getInterval() <= 0)
	{
		++m_iCurrentCounts;
		_scheduleObj->_callbackFunc(dt);
		return;
	}

	if (m_dCurrentInterval < _scheduleObj->getInterval())
	{
		m_dCurrentInterval += dt;
		if (m_dCurrentInterval < _scheduleObj->getInterval()) { return; }
		++m_iCurrentCounts;
		_scheduleObj->_callbackFunc(m_dCurrentInterval);
		m_dCurrentInterval -= _scheduleObj->getInterval();
	}
}
void Schedule::IntervalState::update(double dt)
{
	if (m_dCurrentInterval < _scheduleObj->getInterval())
	{
		m_dCurrentInterval += dt;
		if (m_dCurrentInterval < _scheduleObj->getInterval()) { return; }
		_scheduleObj->_callbackFunc(dt);
		m_dCurrentInterval -= _scheduleObj->getInterval();
	}
}
void Schedule::NormalState::update(double dt)
{
	_scheduleObj->_callbackFunc(dt);
}