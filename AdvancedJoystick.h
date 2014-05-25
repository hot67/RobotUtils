#include "WPILib.h"
#include <cmath>
#include <vector>

/* AdvancedJoystick -- Enhancements for the Joystick class.
 *
 * Currently optimized for Xbox 360 controllers.
 *
 * Added -
 *
 * Builtin deadband control:
 * - Set the deadband width (SetDeadband)
 * - Turn the deadband into a quadratic, cubic, sinusoid ramp (SetDeadbandType)
 *
 * Treat the triggers like buttons in GetRawButton or GetButtonPress.
 *
 * Builtin timer for button presses. (GetButtonPress)
 *
 * Get the value from just one trigger in GetRawAxis.
 */

#ifndef ADVANCEDJOYSTICK_H
#define ADVANCEDJOYSTICK_H

#define M_PI_2 1.57079632679489661923

#define JOYSTICK_TIMEOUT 0.1
#define JOYSTICK_DEADBAND 0.2

class AdvancedJoystick {
public:

    // BUTTON AND AXIS ENUMS ----------
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
        kTriggerL = 11,
        kTriggerR = 12
    } button_t;

    typedef enum {
        kNone,
        kFlat,
        kQuad,
        kCube,
        kSine
    } deadband_t;

    typedef enum {
        kLeftX = 1,
        kLeftY = 2,
        kRawTrigger = 3,
        kRightX = 4,
        kRightY = 5,
        kLeftTrigger = 6,
        kRightTrigger = 7
    } axis_t;

    //CONSTRUCTORS --------------
    /* Default values:
     *
     * deadbandType: None, unless a deadband is provided, then flat
     * deadband: JOYSTICK_DEADBAND
     * timeout: JOYSTICK_TIMEOUT
     */
    AdvancedJoystick (std::string id, Joystick* gamepad);
    AdvancedJoystick (std::string id, Joystick* gamepad, deadband_t deadbandType, float deadband, float timeout);
    AdvancedJoystick (std::string id, Joystick* gamepad, deadband_t deadbandType);
    AdvancedJoystick (std::string id, Joystick* gamepad, float deadband, float timeout);

    AdvancedJoystick (std::string id, int channel);
    AdvancedJoystick (std::string id, int channel, deadband_t deadbandType, float deadband, float timeout);
    AdvancedJoystick (std::string id, int channel, deadband_t deadbandType);
    AdvancedJoystick (std::string id, int channel, float deadband, float timeout);

    //JOYSTICK ACCESS FUNCTIONS ---
    /* You can pass the enum values
     * to these functions, they're
     * typecast to ints.
     */
    bool GetRawButton (button_t);
    bool GetButtonPress (button_t);
    float GetRawAxis (axis_t);

    Joystick* GetJoystick() { return m_gamepad; }

    //WARNING! Experimental
    // bool GetButtonPress_new(int);

    //CONFIGURATION FUNCTIONS --------
    void SetPressTimeout (float timeout) { m_buttonTimeout = timeout; }
    void SetDeadband (float dWidth) { m_deadband = dWidth; }
    void SetDeadbandType (deadband_t dType) { m_deadbandType = dType; }

protected:
    void update ();

private:
    // INTERNAL FUNCTIONS ------
    //Deadband
    float applyDeadband (float input);
    float applyDeadbandFlat (float input);
    float applyDeadbandQuad (float input);
    float applyDeadbandCube (float input);
    float applyDeadbandSine (float input);

    void trackTimer();

    //WARNING - Experimental
    void trackPresses();
    bool isPressed (button_t button);

    // MEMBER OBJECTS --------
    Joystick* m_gamepad;
    Timer* m_timer;
    float m_buttonTimeout;
    float m_deadband;
    deadband_t m_deadbandType;

    // FLAGS -----------------
    vector<button_t> f_pressedButtons;
};

#endif //ADVANCEDJOYSTICK_H
