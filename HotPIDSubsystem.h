#ifndef HOTPIDSUBSYSTEM_H
#define HOTPIDSUBSYSTEM_H

#include "WPILib.h"
#include "HotSubsystem.h"
#include "HotPIDController.h"

class HotPIDSubsystem : public HotSubsystem, public PIDSource, public PIDOutput
{
public:
	/********** Constructor **********/
	HotPIDSubsystem(std::string id, float p, float i, float d);
	HotPIDSubsystem(std::string id, float p, float i, float d, float f);
	
	/********** Control **********/
	void SetPID(float p, float i, float d) { m_pid->SetPID(p, i, d); }
	void SetP(float p) { m_pid->SetP(p); }
	void SetI(float i) { m_pid->SetI(i); }
	void SetD(float d) { m_pid->SetD(d); }
	void GetP() { return m_pid->GetP(); }
	void GetI() { return m_pid->GetI(); }
	void GetD() { return m_pid->GetD(); }
	
	void SetDynamicPID(float range, float p, float i, float d) {
		m_pid->SetDynamicPID(range, p, i, d);
	}
	
	void SetSetpoint(float point) { m_pid->SetSetpoint; }
	void Enable() { m_pid->Enable(); }
	void Diable() { m_pid->Diable(); }
	bool IsEnabled() { m_pid->ISEnabled(); }
	
private:
	HotPIDController* m_pid;
};

#endif
