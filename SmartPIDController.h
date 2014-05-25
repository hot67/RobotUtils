#ifndef SMARTPIDCONTROLLER_H
#define SMARTPIDCONTROLLER_H

#include "WPILib.h"
#include <cmath>

class SmartPIDController
{
public:
    typedef enum {
        kStatic,
        kDynamic
    } iType;

    SmartPIDController(float p, float i, float d, PIDSource* source, PIDOutput* output, float period = 0.05);
    SmartPIDController(float p, float i, float d, float f, PIDSource* source, PIDOutput* output, float period = 0.05);
    SmartPIDController(float p, float i, float d, iType nI, PIDSource* source, PIDOutput* output, float period = 0.05);
    SmartPIDController(float p, float i, float d, float f, iType nI, PIDSource* source, PIDOutput* output, float period = 0.05);

    //P, I ,D access functions
    void SetP (float p) { m_pid->SetPID(p, GetInstantaneousI(), GetD()); }
    void SetI (float i);
    void SetD (float d) { m_pid->SetPID(GetP(), GetInstantaneousI(), d); }
    void SetF (float f) { m_pid->SetPID(GetP(), GetInstantaneousI(), GetD(), f); }
    void SetPID (float p, float i, float d);
    void SetPID (float p, float i, float d, float f);

    float GetP () { return m_pid->GetP(); }
    float GetI () { return m_i; }
    float GetInstantaneousI() { return m_pid->GetI(); }
    float GetD () { return m_pid->GetD(); }
    float GetF () { return m_pid->GetF(); }

    bool GetIType () { return m_iType; }

    //Controller functions
    void SetSetpoint (float setpoint) { m_pid->SetSetpoint(setpoint); }
    float GetSetpoint () { return m_pid->GetSetpoint(); }

    float Get () { return m_pid->Get(); }

    float GetError () { return m_pid->GetError(); }

    void Enable () { m_pid->Enable(); }
    void Disable () { m_pid->Disable(); }
    bool IsEnabled () { m_pid->IsEnabled(); }

    void Reset () { m_pid->Reset(); }

    void SetTolerance (float percent) { m_pid->SetTolerance(percent); }
    void SetAbsoluteTolerance (float tolerance) { m_pid->SetAbsoluteTolerance(tolerance); }
    void SetPercentTolerance (float percent) { m_pid->SetPercentTolerance(percent); }

    bool OnTarget () { return m_pid->OnTarget(); }
    bool AtSetpoint () { return fabs(GetError()) < m_width; }

    //Configuration
    void SetIWidth (float iT) { m_iW = iT; }
    void SetIType (iType nI) { m_iType = nI; }

    void TurnOnDynamicI (bool on, bool zero=true);

    void SetContinuous (bool continuous = true) { m_pid->SetContinuous(continuous); }
    void SetInputRange (float minInput, float maxInput) { m_pid->SetInputRange(minInput, maxInput); }
    void SetOutputRange (float minOutput, float maxOutput) { m_pid->SetOutputRange(minOutput, maxOutput); }

    void SetSetpointWidth (float width) { m_width = width; }

    //Dynamic I updater
    void update ();

    void InitTable (ITable* table) { m_pid->InitTable(table); }
private:
    void manageI();

    PIDController* m_pid;

    float m_width;
    float m_i;
    float m_iW;
    iType m_iType;
};

#endif // SMARTPIDCONTROLLER_H
