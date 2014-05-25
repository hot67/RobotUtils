#ifndef HOTPIDCONTROLLER_H
#define HOTPIDCONTROLLER_H

#include "WPILib.h"
#include <cmath>
#include <map>

class HotPIDController : public PIDController
{
public:
	/********** Constructor **********/
	HotPIDController(float p, float i, float d,
			PIDSource* source, PIDOutput* output,
			float period = 0.05);

	HotPIDController(float p, float i, float d, float f,
			PIDSource* source, PIDOutput* output,
			float period = 0.05);
	
	/********** Config **********/
	void SetP(float p);
	void SetI(float i);
	void SetD(float d);
	void SetDynamicPID(float range, float p, float i, float d);
	
	/********** Dynamic PID Updater **********/
	void Update();
	
private:
	class PIDValues {
	public:
		PIDValues(float p, float i, float d) {
			m_p = p;
			m_i = i;
			m_d = d;
		}
		float m_p, m_i, m_d;
	};
	
	std::map<float, PIDValues> m_dynamicPIDs;
	
	PIDSource* m_pidSource;
};

#endif
