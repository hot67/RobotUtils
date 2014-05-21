#include "SmartPIDController.h"

SmartPIDController::SmartPIDController(float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
    : PIDController(p, 0.0, d, source, output, period)
{
    i_type = kDynamic;
    m_Ki = i;
    m_iT = 0;

    m_pid = new PIDController (p, 0.0, d, source, output, period);
}

SmartPIDController::SmartPIDController(float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
    : PIDController(p, 0.0, d, f, source, output, period)
{
    i_type = kDynamic;
    m_i = i;
    m_iT = 0;

    m_pid = new PIDController (p, 0.0, d, f, source, output, period);
}

SmartPIDController::SmartPIDController(float p, float i, float d, iType nI, PIDSource *source, PIDOutput *output, float period)
    : PIDController(p, 0.0, d, source, output, period)
{
    i_type = nI;
    m_i = i;
    m_iT = 0;

    if (i_type == kStatic)
        m_pid = new PIDController (p, i, d, source, output, period);
    else
        m_pid = new PIDController (p, 0.0, d, source, output, period);
}

SmartPIDController::SmartPIDController(float p, float i, float d, float f, iType nI, PIDSource *source, PIDOutput *output, float period)
{
    i_type = nI;
    m_i = i;
    m_iT = 0;

    if (i_type == kStatic)
        m_pid = new PIDController (p, i, d, f, source, output, period);
    else
        m_pid = new PIDController (p, 0.0, d, f, source, output, period);
}

SmartPIDController::SetI(float i)
{
    m_i = i;

    if (i_type == kStatic)
        SetPID(GetP(),m_i,GetD());
}

SmartPIDController::SetPID(float p, float i, float d)
{
    SetPID(p,i,d,GetF());
}

SmartPIDController::SetPID(float p, float i, float d, float f)
{
    m_i = i;

    if (i_type == kStatic)
        m_pid->SetPID(p,i,d,f);
    else
        m_pid->SetPID(p,GetInstantaneousI(),d,f);
}
