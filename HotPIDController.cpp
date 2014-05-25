#include "HotPIDController.h"

HotPIDController::HotPIDController(float p, float i, float d,
		PIDSource* source, PIDOutput* output,
		float period
		)
	: PIDController(p, i, d, source, output, period) 
{
	m_pidSource = source;
}

HotPIDController::HotPIDController(float p, float i, float d, float f,
		PIDSource* source, PIDOutput* output,
		float period
		)
	: PIDController(p, i, d, f, source, output, period)
{
	m_pidSource = source;
}

/********** PID Control **********/
void HotPIDController::SetP(float p)
{
	PIDController::SetPID(p, PIDController::GetI(), PIDController::GetD());
}
void HotPIDController::SetI(float i)
{
	PIDController::SetPID(PIDController::GetP(), i, PIDController::GetD());
}
void HotPIDController::SetD(float d)
{
	PIDController::SetPID(PIDController::GetP(), PIDController::GetI(), d);
}
/********** New Dynamic PID **********/
void HotPIDController::SetDynamicPID(float range, float p, float i, float d)
{
	PIDValues pidValues(p, i, d);
	
	/***** Insert the dynamic PID *****/
	m_dynamicPIDs.insert(std::map<float, PIDValues>::value_type(0.0, pidValues));
}

/********** Update Dynamic PID **********/
void HotPIDController::Update()
{
	std::map<float, PIDValues>::iterator it = m_dynamicPIDs.begin();
		
	while(it != m_dynamicPIDs.end())
	{
		if ((*it).first < fabs(PIDController::GetSetpoint() - m_pidSource->PIDGet()))
		{
			PIDController::SetPID((*it).second.m_p, (*it).second.m_i, (*it).second.m_d);
		}
		++it;
	}
}
