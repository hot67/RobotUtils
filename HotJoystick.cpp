#include "HotJoystick.h"

HotJoystick::HotJoystick(HotLogger* bot, std::string name, unsigned int port)
: Joystick(port), HotLogger(bot, name)  {
	/**
	 * 	Define Log Schema
	 */
	//	For Buttons
	BooleanSchema("ButtonA");
	BooleanSchema("ButtonB");
	BooleanSchema("ButtonX");
	BooleanSchema("ButtonY");
	BooleanSchema("ButtonLB");
	BooleanSchema("ButtonRB");
	BooleanSchema("ButtonBack");
	BooleanSchema("ButtonStart");
	BooleanSchema("ButtonL3");
	BooleanSchema("ButtonR3");
	BooleanSchema("ButtonLT");
	BooleanSchema("ButtonRT");

	//	For axis
	DoubleSchema("AxisLX", 0.0, 1.0, 0.01);
	DoubleSchema("AxisLY", 0.0, 1.0, 0.01);
	DoubleSchema("AxisRX", 0.0, 1.0, 0.01);
	DoubleSchema("AxisRY", 0.0, 1.0, 0.01);
	DoubleSchema("AxisLT", 0.0, 1.0, 0.01);
	DoubleSchema("AxisRT", 0.0, 1.0, 0.01);
}

/**
 * 	Simple Button Access
 */
bool HotJoystick::Button(kButton btn) {
	if ((btn & kButtonA) && !GetRawButton(1)) {
		return false;
	} else if ((btn & kButtonB) && !GetRawButton(2)) {
		return false;
	} else if ((btn & kButtonX) && !GetRawButton(3)) {
		return false;
	} else if ((btn & kButtonY) && !GetRawButton(4)) {
		return false;
	} else if ((btn & kButtonLB) && !GetRawButton(5)) {
		return false;
	} else if ((btn & kButtonRB) && !GetRawButton(6)) {
		return false;
	} else if ((btn & kButtonLT) && (GetRawAxis(2) < 0.4)) {
		return false;
	} else if ((btn & kButtonLT) && (GetRawAxis(3) < 0.4)) {
		return false;
	}

	return true;
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
	WriteLog("ButtonA", ButtonA());
	WriteLog("ButtonB", ButtonB());
	WriteLog("ButtonX", ButtonX());
	WriteLog("ButtonY", ButtonY());
	WriteLog("ButtonLB", ButtonLB());
	WriteLog("ButtonRB", ButtonRB());
	WriteLog("ButtonBack", ButtonBack());
	WriteLog("ButtonStart", ButtonStart());
	WriteLog("ButtonL3", ButtonL3());
	WriteLog("ButtonR3", ButtonR3());
	WriteLog("ButtonLT", ButtonLT());
	WriteLog("ButtonRT", ButtonRT());

	//	For axis
	WriteLog("AxisLX", AxisLX());
	WriteLog("AxisLY", AxisLY());
	WriteLog("AxisRX", AxisRX());
	WriteLog("AxisRY", AxisRY());
	WriteLog("AxisLT", AxisLT());
	WriteLog("AxisRT", AxisRT());
}
