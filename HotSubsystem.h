#ifndef HOTSUBSYSTEM_H
#define HOTSUBSYSTEM_H

#include "WPILib.h"
#include "HotThread.h"
#include <vector>
#include <string>


class HotSubsystem
{
	friend class HotSubsystemHandler;
	
public:
	/********** Constructor **********/
	HotSubsystem(std::string id) { m_id = id; }
	virtual ~HotSubsystem();
	
protected:
	/********** Constents **********/
	virtual void Init() {}
	virtual void Periodic() {}
	virtual void PrintData() {}
	
	/********** Internal Functions **********/
	void Print (std::string id, float value);
	void Print (std::string id, bool value);
	
private:
	std::string m_id;
};


class HotSubsystemHandler : public HotThread
{
	friend class HotSubsystem;
	
public:
	/********** Constructor **********/
	HotSubsystemHandler();
	~HotSubsystemHandler();
	
	/********** Add New Subsystem to Handler **********/
	void Add(HotSubsystem* subsystem);
	
	/********** Flag Control **********/
	void SetPeriodic(bool on) { f_runPeriodic = on; }
	void SetPrintData(bool on) { f_runPeriodic = on; }
	bool GetPeriodic() { return f_runPeriodic; }
	bool GetPrintData() { return f_runPrintData; }
	
private:
	std::vector<HotSubsystem*> m_subsystems;
	
	/********** Main Function **********/
	void Run();
	
	/********** Flags **********/
	bool f_runPeriodic;
	bool f_runPrintData;
};


#endif
