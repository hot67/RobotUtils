#ifndef HOTSUBSYSTEM_H
#define HOTSUBSYSTEM_H

#include "WPILib.h"
#include <vector>


class HotSubsystem
{
public:
	/********** Constructor **********/
	HotSubsystem(const char* id) { m_id = id; }
	virtual ~HotSubsystem();
	
	/********** Constents **********/
	virtual void Init() {}
	virtual void Periodic() {}
	virtual void PrintData() {}
	
	/********** Accessor **********/
	const char* GetID() { return m_id; }
	
protected:
	void Print (const char* id, float value);
	void Print (const char* id, bool value);
	
private:
	const char* m_id;
};


class HotSubsystemHandler
{
public:
	/********** Constructor **********/
	HotSubsystemHandler();
	
	/********** Add New Subsystem to Handler **********/
	void Add(HotSubsystem subsystem);
	
	/********** Thread Control **********/
	void Enable() { f_enabled = true; }
	void Disable() { f_enabled = false; }
	void End() { f_running = false; }
	
	/********** Flag Access **********/
	bool IsRunning() { return f_running; }
	bool IsEnabled() { return f_enabled; }
	bool IsPeriodic() { return f_runPeriodic; }
	bool IsPrintData() { return f_runPrintData; }
	
	/********** Flag Control **********/
	void SetRunning (bool on = true) { f_running = on; }
	void SetEnabled (bool on = true) { f_enabled = on; }
	
	
	
private:
	Task* m_task;
	std::vector<HotSubsystem> m_subsystems;
	int Run();
	
	/********** Flags **********/
	bool f_running;
	bool f_enabled;
	bool f_runPeriodic;
	bool f_runPrintData;
};


#endif
