
#include "HotPIDController.h"

/******************************
 * 	Constructors
 ******************************/
HotPIDController::HotPIDController(HotLogger* parent, std::string name,
		float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, source, output, period), HotLogger(parent, name) {
	m_source = source;
	DefineLogSchema();
}

HotPIDController::HotPIDController(HotLogger* parent, std::string name,
		float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, f, source, output, period), HotLogger(parent, name) {
	m_source = source;
	DefineLogSchema();
}

HotPIDController::HotPIDController(HotLogger* parent,
		float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, source, output, period), HotLogger(parent, "PID") {
	m_source = source;
	DefineLogSchema();
}

HotPIDController::HotPIDController(HotLogger* parent,
		float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, f, source, output, period), HotLogger(parent, "PID") {
	m_source = source;
	DefineLogSchema();
}

/******************************
 * 	Configuration
 ******************************/
void HotPIDController::SetContinuous(bool continuous) {
	m_continuous = continuous;
	PIDController::SetContinuous(continuous);
}

void HotPIDController::SetInputRange(float inMin, float inMax) {
	m_inMin = inMin;
	m_inMax = inMax;
	PIDController::SetInputRange(inMin, inMax);
}

void HotPIDController::SetOutputRange(float outMin, float outMax) {
	m_outMin = outMin;
	m_outMax = outMax;
	PIDController::SetOutputRange(outMin, outMax);
}

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
 * 	Get Status
 ******************************/
float HotPIDController::GetInputMin() const {
	return m_inMin;
}

float HotPIDController::GetInputMax() const {
	return m_inMax;
}

float HotPIDController::GetOutputMin() const {
	return m_outMin;
}

float HotPIDController::GetOutputMax() const {
	return m_outMax;
}

bool HotPIDController::IsContinuous() const {
	return m_continuous;
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

/******************************
 * 	Log Period
 ******************************/
void HotPIDController::LogPeriod() {
	WriteLog("PCoef", GetP());
	WriteLog("ICoef", GetI());
	WriteLog("DCoef", GetD());
	WriteLog("Input", GetInput());
	WriteLog("Output", GetOutput());
	WriteLog("Setpoint", GetSetpoint());
	WriteLog("Enabled", IsEnabled());
	WriteLog("OnTarget", OnTarget());
}

/******************************
 * 	Define Log Schema
 ******************************/
void HotPIDController::DefineLogSchema() {
	/**
	 *	Coefficients
	 */
	DoubleSchema("PCoef", 0.0, 1.0, 0.01);
	DoubleSchema("ICoef", 0.0, 1.0, 0.01);
	DoubleSchema("DCoef", 0.0, 1.0, 0.01);

	/**
	 * 	Input/Output
	 */
	DoubleSchema("Input", GetInputMin(), GetInputMax(),
			(GetInputMax() - GetInputMin()) / 100);
	DoubleSchema("Output", GetOutputMin(), GetOutputMax(),
			(GetOutputMax() - GetOutputMin()) / 100);

	/**
	 * 	Set Point
	 */
	DoubleSchema("Setpoint", GetInputMin(), GetInputMax(),
			(GetInputMax() - GetInputMin()) / 100);


	/**
	 * 	Enabled
	 */
	BooleanSchema("Enabled");

	/**
	 * 	On Target
	 */
	BooleanSchema("OnTarget");
}
