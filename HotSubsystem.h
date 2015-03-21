#ifndef HOTSUBSYSTEM_H
#define HOTSUBSYSTEM_H

#include "WPILib.h"
#include "HotThread.h"
#include <vector>
//#include <string>

enum data_send_t {
    kPrintData,
    kGetData,
    kNone
};

class HotSubsystem
{
public:
	/********** Constructor **********/
	HotSubsystem(std::string id) { m_id = id; }
	virtual ~HotSubsystem();
	
    /********** Constants **********/
	virtual void Update() {}
	virtual void PrintData() {}
    virtual void GetData() {}
	
	/********** Internal Functions **********/
	void Print (std::string id, float value);
	void Print (std::string id, bool value);
	
private:
	std::string m_id;
};


class HotSubsystemHandler : public HotThread
{
public:
	/********** Constructor **********/
	HotSubsystemHandler();
	~HotSubsystemHandler();
	
	/********** Add New Subsystem to Handler **********/
	void Add(HotSubsystem* subsystem);
	
	/********** Flag Control **********/
	void SetUpdate(bool on) { f_runUpdate = on; }
    void SetDataSender(data_send_t on) { f_dataSend = on; }
	bool GetUpdate() { return f_runUpdate; }
    data_send_t GetDataSender() { return f_dataSend; }
	
private:
	std::vector<HotSubsystem*> m_subsystems;
	
	/********** Main Function **********/
	void Run();
	
	/********** Flags **********/
	bool f_runUpdate;
    data_send_t f_dataSend;
};


#endif
