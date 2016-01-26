#include "HotJoystick.h"

HotJoystick::HotJoystick(HotBot* bot, std::string name, unsigned int port)
: Joystick(port) {
	f_A = f_B = f_X = f_Y = f_LB = f_RB = f_Back = f_Start = f_L3 = f_R3 = f_LT = f_RT = false;
	db_LX = db_LY = db_LT = db_RT = db_RX = db_RY = 0.0;
}

/**
 * 	Configuration
 */
void HotJoystick::SetDeadband(int channels, float value) {
	if (channels & kAxisLX) {
		db_LX = value;
	}
	if (channels & kAxisLY) {
		db_LY = value;
	}
	if (channels & kAxisLT) {
		db_LT = value;
	}
	if (channels & kAxisRT) {
		db_LX = value;
	}
	if (channels & kAxisRX) {
		db_RX = value;
	}
	if (channels & kAxisRY) {
		db_RY = value;
	}
}

float HotJoystick::GetDeadband(kAxis axis) {
	switch(axis) {
	case kAxisLX:
		return db_LX;
	case kAxisLY:
		return db_LY;
	case kAxisLT:
		return db_LT;
	case kAxisRT:
		return db_RT;
	case kAxisRX:
		return db_RX;
	case kAxisRY:
		return db_RY;
	default:
		return 0.0;
	}
}

/**
 * 	Simple Button Access
 */
bool HotJoystick::Button(kButton btn) {
	switch (btn) {
	case kButtonA:
		return GetRawButton(1);
	case kButtonB:
		return GetRawButton(2);
	case kButtonX:
		return GetRawButton(3);
	case kButtonY:
		return GetRawButton(4);
	case kButtonLB:
		return GetRawButton(5);
	case kButtonRB:
		return GetRawButton(6);
	case kButtonLT:
		return GetRawAxis(2) > 0.4;
	case kButtonRT:
		return GetRawAxis(3) > 0.4;
	default:
		return false;
	}
}
bool HotJoystick::Button(int btn) {
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
	} else if ((btn & kButtonRT) && (GetRawAxis(3) < 0.4)) {
		return false;
	}

	return true;
}

bool HotJoystick::ButtonPressed(kButton btn) {
	switch (btn) {
	case kButtonA:
		if (Button(btn)) {
			return (f_A) ? false : f_A = true;
		} else {
			return f_A = false;
		}
	case kButtonB:
		if (Button(btn)) {
			return (f_B) ? false : f_B = true;
		} else {
			return f_B = false;
		}
	case kButtonX:
		if (Button(btn)) {
			return (f_X) ? false : f_X = true;
		} else {
			return f_X = false;
		}
	case kButtonY:
		if (Button(btn)) {
			return (f_Y) ? false : f_Y = true;
		} else {
			return f_Y = false;
		}
	case kButtonLB:
		if (Button(btn)) {
			return (f_LB) ? false : f_LB = true;
		} else {
			return f_LB = false;
		}
	case kButtonRB:
		if (Button(btn)) {
			return (f_RB) ? false : f_RB = true;
		} else {
			return f_RB = false;
		}
	case kButtonBack:
		if (Button(btn)) {
			return (f_Back) ? false : f_Back = true;
		} else {
			return f_Back = false;
		}
	case kButtonStart:
		if (Button(btn)) {
			return (f_Start) ? false : f_Start = true;
		} else {
			return f_Start = false;
		}
	case kButtonL3:
		if (Button(btn)) {
			return (f_L3) ? false : f_L3 = true;
		} else {
			return f_L3 = false;
		}
	case kButtonR3:
		if (Button(btn)) {
			return (f_R3) ? false : f_R3 = true;
		} else {
			return f_R3 = false;
		}
	case kButtonLT:
		if (Button(btn)) {
			return (f_LT) ? false : f_LT = true;
		} else {
			return f_LT = false;
		}
	case kButtonRT:
		if (Button(btn)) {
			return (f_RT) ? false : f_RT = true;
		} else {
			return f_RT = false;
		}
	default:
		return false;
	}
}
bool HotJoystick::ButtonPressed(int btn) {
	if ((btn & kButtonA) && !ButtonPressed(kButtonA)) {
		return false;
	} else if ((btn & kButtonB) && !ButtonPressed(kButtonB)) {
		return false;
	} else if ((btn & kButtonX) && !ButtonPressed(kButtonX)) {
		return false;
	} else if ((btn & kButtonY) && !ButtonPressed(kButtonY)) {
		return false;
	} else if ((btn & kButtonLB) && !ButtonPressed(kButtonLB)) {
		return false;
	} else if ((btn & kButtonRB) && !ButtonPressed(kButtonRB)) {
		return false;
	} else if ((btn & kButtonLT) && !ButtonPressed(kButtonLT)) {
		return false;
	} else if ((btn & kButtonRT) && !ButtonPressed(kButtonRT)) {
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
