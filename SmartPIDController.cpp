#include "SmartPIDController.h"

SmartPIDController::SmartPIDController(float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
    : PIDController(p, 0.0, d, source, output, period)
{
    m_iType = kDynamic;
    m_Ki = i;
    m_iT = 0;

    m_pid = new PIDController (p, 0.0, d, source, output, period);
}

SmartPIDController::SmartPIDController(float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
    : PIDController(p, 0.0, d, f, source, output, period)
{
    m_iType = kDynamic;
    m_i = i;
    m_iT = 0;

    m_pid = new PIDController (p, 0.0, d, f, source, output, period);
}

SmartPIDController::SmartPIDController(float p, float i, float d, iType nI, PIDSource *source, PIDOutput *output, float period)
    : PIDController(p, 0.0, d, source, output, period)
{
    m_iType = nI;
    m_i = i;
    m_iT = 0;

    if (m_iType == kStatic)
        m_pid = new PIDController (p, i, d, source, output, period);
    else
        m_pid = new PIDController (p, 0.0, d, source, output, period);
}

SmartPIDController::SmartPIDController(float p, float i, float d, float f, iType nI, PIDSource *source, PIDOutput *output, float period)
{
    m_iType = nI;
    m_i = i;
    m_iT = 0;

    if (m_iType == kStatic)
        m_pid = new PIDController (p, i, d, f, source, output, period);
    else
        m_pid = new PIDController (p, 0.0, d, f, source, output, period);
}

void SmartPIDController::SetI(float i)
{
    m_i = i;

    if (m_iType == kStatic)
        SetPID(GetP(),m_i,GetD());
}

void SmartPIDController::SetPID(float p, float i, float d)
{
    SetPID(p,i,d,GetF());
}

void SmartPIDController::SetPID(float p, float i, float d, float f)
{
    m_i = i;

    if (m_iType == kStatic)
        m_pid->SetPID(p,i,d,f);
    else
        m_pid->SetPID(p,GetInstantaneousI(),d,f);
}

void SmartPIDController::update()
{
    manageI();
}

void SmartPIDController::manageI()
{
    if (m_iType == kDynamic)
    {
        if (fabs(GetError()) < m_iW)
            m_pid->SetPID(GetP(),m_i,GetD());
        else
            m_pid->SetPID(GetP(),0.0,GetD());
    }
}

void SmartPIDController::TurnOnDynamicI (bool on, bool zero)
{
    if (on)
        m_iType = kDynamic;
    else
    {
        m_iType = kStatic;
        if (zero)
            m_pid->SetPID(GetP(),0.0,GetD());
    }
}
