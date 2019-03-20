/********************************************
名称:
说明:
1.
********************************************/

#ifndef __SCHEDULE_H_H__
#define __SCHEDULE_H_H__

#include "Object.h"

NS_EDGE_BEGIN

class EDGE_DLL Schedule final : public Object
{
private:
	class EDGE_DLL ScheduleState
	{
	public:
		virtual void update(double dt) = 0;
		Schedule* _scheduleObj;
	};

	class EDGE_DLL DelayState final : public ScheduleState
	{
	public:
		DelayState();
		void update(double dt);
	private:
		double m_dCurrentDelay;
	};
	class EDGE_DLL CountsState final : public ScheduleState
	{
	public:
		CountsState();
		void update(double dt);
	private:
		int m_iCurrentCounts;
		double m_dCurrentInterval;
	};
	class EDGE_DLL IntervalState final : public ScheduleState
	{
	public:
		void update(double dt);
	private:
		double m_dCurrentInterval;
	};
	class EDGE_DLL NormalState final : public ScheduleState
	{
	public:
		void update(double dt);
	};

public:
	typedef std::function<void(double)> ScheduleFunc;

	static Schedule* create();
	static Schedule* create(const ScheduleFunc& func);

	~Schedule();
	void update(double dt);

	void setUpdateFunc(const ScheduleFunc& func);

	void setDelay(double delay);
	double getDelay() const;
	void setInterval(double interval);
	double getInterval() const;
	void setCounts(int counts);
	int getCounts() const;
	void setZOrder(int zOrder);
	int getZOrder() const;

	void setStop(bool b);
	void setPause(bool b);
	bool isStop() const;
	bool isPause() const;

public:
	void changeState(ScheduleState* state);
	void _callbackFunc(double dt);

private:
	Schedule();

private:
	ScheduleFunc _updateFunc;
	double m_dDelay;
	double m_dInterval;
	int m_iCounts;
	int m_iZOrder;

	ScheduleState* _state;

	bool m_bStop;
	bool m_bPause;
};

NS_EDGE_END

#endif // __SCHEDULE_H_H__