
#include "HotPIDController.h"

/******************************
 * 	Constructors
 ******************************/

HotPIDController::HotPIDController(float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, source, output, period) {
	m_source = source;
}

HotPIDController::HotPIDController(float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, f, source, output, period) {
	m_source = source;
}

/******************************
 * 	Configuration
 ******************************/

/******************************
 * 	Enable/Disable
 ******************************/
void HotPIDController::Enable() {
	if (!IsEnabled()) {
		PIDController::Enable();
	}
}

void HotPIDController::Disable() {
	if (IsEnabled()) {
		PIDController::Disable();
	}
}

/******************************
 * 	Set PID set point
 ******************************/
void HotPIDController::SetSetpoint(float setpoint, bool enable) {
	PIDController::SetSetpoint(setpoint);
	if (enable) {
		Enable();
	}
}

/******************************
 * 	Get Input/Output Value
 ******************************/
double HotPIDController::GetInput() const {
	return m_source->PIDGet();
}

double HotPIDController::GetOutput() const {
	return Get();
}
/******************************
 * 	Control PID
 ******************************/
void HotPIDController::SetP(float p) {
	SetPID(p, GetI(), GetD());
}
void HotPIDController::SetI(float i) {
	SetPID(GetP(), i, GetD());
}
void HotPIDController::SetD(float d) {
	SetPID(GetP(), GetI(), GetD());
}
