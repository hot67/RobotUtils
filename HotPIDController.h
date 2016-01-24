
#ifndef SRC_HOTPIDCONTROLLER_H_
#define SRC_HOTPIDCONTROLLER_H_

#include "WPILib.h"

class HotPIDController: public PIDController {
public:
	HotPIDController(float p, float i, float d, PIDSource *source, PIDOutput *output, float period = 0.05);
	HotPIDController(float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period = 0.05);

	/******************************
	 * 	Configuration
	 ******************************/

	/******************************
	 * 	Enable/Disable
	 ******************************/
	/**
	 * 	Enable PID if it is not enabled
	 */
	void Enable();

	/**
	 * 	Disabled PID if it is enabled
	 */
	void Disable();

	/******************************
	 * 	Set Set Point
	 ******************************/
	void SetSetpoint(float setpoint, bool enable=false);

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

private:
	/**
	 * 	PIDSource
	 */
	PIDSource* m_source;
};

#endif /* SRC_HOTPIDCONTROLLER_H_ */
