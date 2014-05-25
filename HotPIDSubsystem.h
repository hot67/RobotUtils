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
	
private:
	HotPIDController* m_pid;
};

#endif
