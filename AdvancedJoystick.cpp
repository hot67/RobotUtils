#include "AdvancedJoystick.h"

/**** CONSTRUCTORS ****/
AdvancedJoystick::AdvancedJoystick (Joystick* gamepad) {
	m_gamepad = gamepad;
	m_timer = new Timer;

    m_deadband = JOYSTICK_DEADBAND;
    m_deadbandType = kNone;

    m_buttonTimeout = JOYSTICK_TIMEOUT;
	
	m_timer->Reset();
}

AdvancedJoystick::AdvancedJoystick (Joystick* gamepad, deadband_t deadbandType, float deadband, float timeout) {
    m_gamepad = gamepad;
    m_timer = new Timer;

    m_deadband = deadband;
    m_deadbandType = deadbandType;

    m_buttonTimeout = timeout;

    m_timer->Reset();
}

AdvancedJoystick::AdvancedJoystick (Joystick* gamepad, deadband_t deadbandType) {
    m_gamepad = gamepad;
    m_timer = new Timer;

    m_deadband = JOYSTICK_DEADBAND;
    m_deadbandType = deadbandType;

    m_buttonTimeout = JOYSTICK_TIMEOUT;

    m_timer->Reset();
}

AdvancedJoystick::AdvancedJoystick (Joystick* gamepad, float deadband, float timeout) {
    m_gamepad = gamepad;
    m_timer = new Timer;

    m_deadband = deadband;

    if (m_deadband != 0)
        m_deadbandType = kFlat;
    else
        m_deadbandType = kNone;

    m_buttonTimeout = timeout;

    m_timer->Reset();
}

AdvancedJoystick::AdvancedJoystick (int gamepad) {
	m_gamepad = new Joystick (gamepad);
	m_timer = new Timer;

    m_deadband = JOYSTICK_DEADBAND;
    m_deadbandType = kNone;

    m_buttonTimeout = JOYSTICK_TIMEOUT;
	
	m_timer->Reset();
}

AdvancedJoystick::AdvancedJoystick (int gamepad, deadband_t deadbandType, float deadband, float timeout) {
    m_gamepad = new Joystick (gamepad);
    m_timer = new Timer;

    m_deadband = deadband;
    m_deadbandType = deadbandType;

    m_buttonTimeout = timeout;

    m_timer->Reset();
}

AdvancedJoystick::AdvancedJoystick (int gamepad, deadband_t deadbandType) {
    m_gamepad = new Joystick (gamepad);
    m_timer = new Timer;

    m_deadband = JOYSTICK_DEADBAND;
    m_deadbandType = deadbandType;

    m_buttonTimeout = JOYSTICK_TIMEOUT;

    m_timer->Reset();
}

AdvancedJoystick::AdvancedJoystick (int gamepad, float deadband, float timeout) {
    m_gamepad = new Joystick (gamepad);
    m_timer = new Timer;

    m_deadband = deadband;

    if (m_deadband != 0)
        m_deadbandType = kFlat;
    else
        m_deadbandType = kNone;

    m_buttonTimeout = timeout;

    m_timer->Reset();
}

/**** JOYSTICK ACCESS FUNCTIONS ****/

bool AdvancedJoystick::GetRawButton (int channel) {
    if (channel < 11)
        return m_gamepad->GetRawButton(channel);
    else
    {
        if (channel == AdvancedJoystick::kTriggerL)
        {
            return GetRawAxis(AdvancedJoystick::kLeftTrigger) > 0.4;
        }
        else
        {
            return GetRawAxis(AdvancedJoystick::kRightTrigger) > 0.4;
        }
    }
}

bool AdvancedJoystick::GetButtonPress (int channel) {
    trackTimer();

    if (m_gamepad->GetRawButton(channel) && (m_timer->Get() == 0.0))
    {
        m_timer->Start();
        return true;
    }
    else
        return false;
}

float AdvancedJoystick::GetRawAxis (int channel) {
    if ((channel < 6) && (channel != 3))
        return applyDeadband(m_gamepad->GetRawAxis(channel));
    else if (channel == 3)
        return m_gamepad->GetRawAxis(3);
    else
    {
        if (channel == AdvancedJoystick::kLeftTrigger)
        {
            if (m_gamepad->GetRawAxis(3) < 0)
                m_gamepad->GetRawAxis(3);
            else
                return 0.0;
        }
        else
        {
            if (m_gamepad->GetRawAxis(3) > 0)
                return fabs(m_gamepad->GetRawAxis(3));
            else
                return 0.0;
        }
    }
}

/**** INTERNAL FUNCTIONS ****/

float AdvancedJoystick::applyDeadband (float input) {
    if (m_deadbandType == kFlat)
        return applyDeadbandFlat(input);
    else if (m_deadbandType == kQuad)
        return applyDeadbandQuad(input);
    else if (m_deadbandType == kCube)
        return applyDeadbandQuad(input);
    else if (m_deadbandType == kSine)
        return applyDeadbandSine(input);
    else
        return input;
}

float AdvancedJoystick::applyDeadbandFlat (float input)
{
    if (input < -m_deadband) {
        return input;
    } else if (input < m_deadband) {
        return 0.0;
    } else {
        return input;
    }
}

float AdvancedJoystick::applyDeadbandQuad (float input)
{
    if (fabs(input) < m_deadband)
    {
        if (input > 0)
            return pow((input/m_deadband),2.0);
        else if (input < 0)
            return -pow((input/m_deadband),2.0);
        else
            return 0.0;
    }
    else
        return input;
}

float AdvancedJoystick::applyDeadbandCube (float input)
{
    if (fabs(input) < m_deadband)
    {
        if (input != 0)
            return pow((input/m_deadband),3.0);
        else
            return 0.0;
    }
    else
        return input;
}

float AdvancedJoystick::applyDeadbandSine (float input)
{
    if (fabs(input) < m_deadband)
    {
        if (input != 0)
            return sin(M_PI_2*(input/m_deadband));
        else
            return 0.0;
    }
    else
        return input;
}

void AdvancedJoystick::trackTimer () {
    if (m_timer->HasPeriodPassed(m_buttonTimeout))
	{
		m_timer->Stop();
		m_timer->Reset();
	}
}

void AdvancedJoystick::update ()
{
    trackTimer();
}
