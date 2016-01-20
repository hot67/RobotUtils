/*
 * HotPIDController.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Jin
 */

#include "HotPIDController.h"

/******************************
 * 	Constructors
 ******************************/
HotPIDController::HotPIDController(HotLog* parent, std::string name,
		float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, source, output, period), HotLog(parent, name) {
	m_source = source;
	DefineLogSchema();
}

HotPIDController::HotPIDController(HotLog* parent, std::string name,
		float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, f, source, output, period), HotLog(parent, name) {
	m_source = source;
	DefineLogSchema();
}

HotPIDController::HotPIDController(HotLog* parent,
		float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, source, output, period), HotLog(parent, "PID") {
	m_source = source;
	DefineLogSchema();
}

HotPIDController::HotPIDController(HotLog* parent,
		float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, f, source, output, period), HotLog(parent, "PID") {
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
	Log("PCoef", GetP());
	Log("ICoef", GetI());
	Log("DCoef", GetD());
	Log("Input", GetInput());
	Log("Output", GetOutput());
	Log("Setpoint", GetSetpoint());
	Log("Enabled", IsEnabled());
	Log("OnTarget", OnTarget());
}

/******************************
 * 	Define Log Schema
 ******************************/
void HotPIDController::DefineLogSchema() {
	/**
	 *	Coefficients
	 */
	DefineDoubleLog("PCoef", 0.0, 1.0, 0.01);
	DefineDoubleLog("ICoef", 0.0, 1.0, 0.01);
	DefineDoubleLog("DCoef", 0.0, 1.0, 0.01);

	/**
	 * 	Input/Output
	 */
	DefineDoubleLog("Input", GetInputMin(), GetInputMax(),
			(GetInputMax() - GetInputMin()) / 100);
	DefineDoubleLog("Output", GetOutputMin(), GetOutputMax(),
			(GetOutputMax() - GetOutputMin()) / 100);

	/**
	 * 	Set Point
	 */
	DefineDoubleLog("Setpoint", GetInputMin(), GetInputMax(),
			(GetInputMax() - GetInputMin()) / 100);


	/**
	 * 	Enabled
	 */
	DefineBoolLog("Enabled");

	/**
	 * 	On Target
	 */
	DefineBoolLog("OnTarget");
}
