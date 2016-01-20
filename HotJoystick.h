#ifndef SRC_HOTJOYSTICK_H_
#define SRC_HOTJOYSTICK_H_

#include "WPILib.h"
#include "HotLog.h"

class HotJoystick: public Joystick, public HotLog {
public:
	/******************************
	 * 	Access Selector
	 ******************************/
	typedef enum {
		kButtonA = 1,
		kButtonB = 2,
		kButtonX = 3,
		kButtonY = 4,
		kButtonLB = 5,
		kButtonRB = 6,
		kButtonBack = 7,
		kButtonStart = 8,
		kButtonL3 = 9,
		kButtonR3 = 10,

		/**
		 * 	Next Two:
		 * 		Using triggers as buttons (good for shooting)
		 * 		These buttons are on if the triggers are pressed more than 40%
		 */
		kButtonLT = 11,
		kButtonRT = 12
	} kButton;

	typedef enum {
		kAxisLX = 1,
		kAxisLY = 2,
		kAxisLT = 3,	//	Left Trigger
		kAxisRT = 4,	//	Right Trigger
		kAxisRX = 5,
		kAxisRY = 6
	} kAxis;

	/******************************
	 * 	Constructor
	 ******************************/
	HotJoystick(HotLog* bot, std::string name, unsigned int port);

	/******************************
	 * 	Access with Access Selector
	 ******************************/
	/**
	 * 	Simply Access Button with Access Selector
	 */
	bool Button(kButton btn);

	/**
	 * 	Simply Access Axis With Access Selector
	 */
	float Axis(kAxis axis);


	/**
	 * 	Access Button Press
	 * 		This function only return true when a button is newly pressed
	 * 		Whole the button is pressed, this function returns false
	 */
	bool ButtonPressed(kButton btn);

	/******************************
	 * 	Access Individual
	 ******************************/
	/**
	 * 	Button
	 */
	bool ButtonA() { return Button(kButtonA); }
	bool ButtonB() { return Button(kButtonB); }
	bool ButtonX() { return Button(kButtonX); }
	bool ButtonY() { return Button(kButtonY); }
	bool ButtonLB() { return Button(kButtonLB); }
	bool ButtonRB() { return Button(kButtonRB); }
	bool ButtonBack() { return Button(kButtonBack); }
	bool ButtonStart() { return Button(kButtonStart); }
	bool ButtonL3() { return Button(kButtonL3); }
	bool ButtonR3() { return Button(kButtonR3); }
	bool ButtonLT() { return Button(kButtonLT); }
	bool ButtonRT() { return Button(kButtonRT); }

	/**
	 * 	Button Pressed
	 */
	bool ButtonPressedA() { return ButtonPressed(kButtonA); }

	/**
	 * 	Axis
	 */
	float AxisLX() { return Axis(kAxisLX); }
	float AxisLY() { return Axis(kAxisLY); }
	float AxisRX() { return Axis(kAxisRX); }
	float AxisRY() { return Axis(kAxisRY); }
	float AxisLT() { return Axis(kAxisLT); }
	float AxisRT() { return Axis(kAxisRT); }

	/******************************
	 * 	Period
	 ******************************/
	void GeneralPeriod();
	void LogPeriod();

private:
	struct ButtonStatus {
		ButtonStatus () {
			A = false;
			B = false;
			X = false;
			Y = false;
			LB = false;
			RB = false;
			Back = false;
			Start = false;
			L3 = false;
			R3 = false;
		}
		bool A, B, X, Y, LB, RB, Back, Start, L3, R3;
	};

	ButtonStatus f_status;
};

#endif /* SRC_HOTJOYSTICK_H_ */
