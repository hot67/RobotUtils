# RobotUtils

This is a series of classes written by Team 67 that enhance the functionality of WPILib.

This library is unfinished as of yet. This list will be updated as new functionality is added to it, and once everything is present, the wiki will be updated with reference on the library.

## Features

* HotBot
  * Base class of robot
  * Instead of inheriting IterativeRobot, inherit this class
* HotSubsystem
  * Base class of subsystem of robot
  * Contain periodic/init functions such as `InitRobot`, `TeleopPeriod`
* HotLog
  * This is a class that handles logging
  * As long as you set what values to save in constructor of each subsystems, you most likely don't need to care about this feature.  Everything is handled automatically.
  * Details are describe in below in section "HotLog"
* HotJoystick
  * Wrapper class of Joystick
  * Specialized for xbox controller
  * Detect button press
  * Trigger as button
* HotPIDController
  * Wrapper for PIDController
  * Log basic data automatically, including input/output value, PID coefficients, setpoints, etc...


## Details
### HotBot
`HotBot : public IterativeRobot, public HotLog`
### HotSubsyste
`HotSubsystem : public HotLog`
### HotLog
`HotLog`
### HotJoystick
`HotJoystick : public Joystick, public HotLog`
### HotPIDController
`HotPIDController : public Joystick, public PIDController`

## How to use

## Changes
