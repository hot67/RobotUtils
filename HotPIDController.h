
#ifndef SRC_HOTPIDCONTROLLER_H_
#define SRC_HOTPIDCONTROLLER_H_

#include "HotLog.h"
#include <PIDController.h>

class HotPIDController: public PIDController, public HotLog {
public:
	HotPIDController(HotLog* parent, std::string name,
			float p, float i, float d, PIDSource *source, PIDOutput *output, float period = 0.05);
	HotPIDController(HotLog* parent, std::string name,
			float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period = 0.05);
	HotPIDController(HotLog* parent,
			float p, float i, float d, PIDSource *source, PIDOutput *output, float period = 0.05);
	HotPIDController(HotLog* parent,
			float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period = 0.05);

	/******************************
	 * 	Configuration
	 ******************************/
	/**
	 * 	Set IO Range
	 */
	void SetInputRange(float minimumInput, float maximumInput);
	void SetOutputRange(float minimumOutput, float maximumOutput);

	/**
	 * 	Set Continuous;
	 */
	void SetContinuous(bool continuous = true);

	/******************************
	 * 	Get Status
	 ******************************/
	/**
	 * 	Read IO Range
	 */
	float GetInputMin() const;
	float GetInputMax() const;
	float GetOutputMin() const;
	float GetOutputMax() const;

	/**
	 * 	Read Continuous
	 */
	bool IsContinuous() const;

	/******************************
	 * 	Get Input/Output Value
	 ******************************/
	double GetInput() const;
	double GetOutput() const;

	/******************************
	 * 	Control P/I/D
	 ******************************/
	void SetP(float p);
	void SetI(float i);
	void SetD(float d);

	/******************************
	 * 	Log Period
	 ******************************/
	void LogPeriod();

private:
	/**
	 * 	Define Log Schema
	 */
	void DefineLogSchema();

	/**
	 * 	IO Range
	 */
	float m_inMin = 0.0, m_inMax = 0.0, m_outMin = 0.0, m_outMax = 0.0;

	/**
	 * 	Continuous
	 */
	bool m_continuous = false;

	/**
	 * 	PIDSource
	 */
	PIDSource* m_source;
};

#endif /* SRC_HOTPIDCONTROLLER_H_ */
