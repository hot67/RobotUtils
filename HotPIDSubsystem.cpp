#include "HotPIDSubsystem.h"

HotPIDSubsystem::HotPIDSubsystem(std::string id, float p, float i, float d)
	: HotSubsystem("HotPIDSubsystem")
{
	m_pid = new HotPIDController(p, i, d, this, this);
}

HotPIDSubsystem::HotPIDSubsystem(std::string id, float p, float i, float d, float f)
	: HotSubsystem(id)
{
	m_pid = new HotPIDController(p, i, d, f, this, this);
}
