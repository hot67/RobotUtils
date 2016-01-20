#include "HotJoystick.h"

HotJoystick::HotJoystick(HotLog* bot, std::string name, unsigned int port)
: Joystick(port), HotLog(bot, name)  {
	/**
	 * 	Define Log Schema
	 */
	//	For Buttons
	DefineBoolLog("ButtonA");
	DefineBoolLog("ButtonB");
	DefineBoolLog("ButtonX");
	DefineBoolLog("ButtonY");
	DefineBoolLog("ButtonLB");
	DefineBoolLog("ButtonRB");
	DefineBoolLog("ButtonBack");
	DefineBoolLog("ButtonStart");
	DefineBoolLog("ButtonL3");
	DefineBoolLog("ButtonR3");
	DefineBoolLog("ButtonLT");
	DefineBoolLog("ButtonRT");

	//	For axis
	DefineDoubleLog("AxisLX", 0.0, 1.0, 0.01);
	DefineDoubleLog("AxisLY", 0.0, 1.0, 0.01);
	DefineDoubleLog("AxisRX", 0.0, 1.0, 0.01);
	DefineDoubleLog("AxisRY", 0.0, 1.0, 0.01);
	DefineDoubleLog("AxisLT", 0.0, 1.0, 0.01);
	DefineDoubleLog("AxisRT", 0.0, 1.0, 0.01);
}

/**
 * 	Simple Button Access
 */
bool HotJoystick::Button(kButton btn) {
	switch (btn) {
	case kButtonA:
		return GetRawButton(1);
		break;
	case kButtonB:
		return GetRawButton(2);
		break;
	case kButtonX:
		return GetRawButton(3);
		break;
	case kButtonY:
		return GetRawButton(4);
		break;
	case kButtonLB:
		return GetRawButton(5);
		break;
	case kButtonRB:
		return GetRawButton(6);
		break;
	case kButtonLT:
		return (GetRawAxis(2) > 0.4);
		break;
	case kButtonRT:
		return (GetRawAxis(3) > 0.4);
		break;
	default:
		return false;
	}
}

/**
 * 	Simple Axis Access
 */
float HotJoystick::Axis(kAxis axis) {
	switch(axis) {
	case kAxisLX:
		return GetRawAxis(1);
		break;
	case kAxisLY:
		return GetRawAxis(2);
		break;
	case kAxisLT:
		return GetRawAxis(3);
		break;
	case kAxisRT:
		return GetRawAxis(4);
		break;
	case kAxisRX:
		return GetRawAxis(5);
		break;
	case kAxisRY:
		return GetRawAxis(6);
		break;
	default:
		return 0.0;
	}
}

void HotJoystick::GeneralPeriod() {
	f_status.A = ButtonA();
	f_status.B = ButtonB();
	f_status.X = ButtonX();
	f_status.Y = ButtonY();
	f_status.LB = ButtonLB();
	f_status.RB = ButtonRB();
	f_status.Back = ButtonBack();
	f_status.Start = ButtonStart();
	f_status.L3 = ButtonL3();
	f_status.R3 = ButtonR3();
}

void HotJoystick::LogPeriod() {
	Log("ButtonA", ButtonA());
	Log("ButtonB", ButtonB());
	Log("ButtonX", ButtonX());
	Log("ButtonY", ButtonY());
	Log("ButtonLB", ButtonLB());
	Log("ButtonRB", ButtonRB());
	Log("ButtonBack", ButtonBack());
	Log("ButtonStart", ButtonStart());
	Log("ButtonL3", ButtonL3());
	Log("ButtonR3", ButtonR3());
	Log("ButtonLT", ButtonLT());
	Log("ButtonRT", ButtonRT());

	//	For axis
	Log("AxisLX", AxisLX());
	Log("AxisLY", AxisLY());
	Log("AxisRX", AxisRX());
	Log("AxisRY", AxisRY());
	Log("AxisLT", AxisLT());
	Log("AxisRT", AxisRT());
}
