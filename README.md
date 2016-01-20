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

Base class that extends IterativeRobot.
Main robot class should inherit this class

`HotBot : public IterativeRobot, public HotLog`

### HotSubsystem

Base class for subsystem.
As soon as this class is instantiated, this subsystem is set as subsystem of parent HotBot class.
With no configuration, all periodic / initializaction functions, including `RobotInit`, `TeleopInit`, `AutonPeriod`, etc... should run when it should run.

`HotSubsystem : public HotLog`

### HotLog

Abstruct class that has any data to be logged.
`HotBot`, `HotSubsystem`, `HotJoystick`, `HotPIDController` inherits this class.
If you define new class that have logging data, you should inherit this class.

`HotLog`

### HotJoystick

Wrapper of Joystick specified for xbox controller.
This class extends functionality of Joystick including, easy access to each button and axis, simple button pressed function.
All control are logged.

`HotJoystick : public Joystick, public HotLog`

### HotPIDController

Wrapper of PIDController.
Easy access to PID coefficients.
Log input and output value of PID, coefficients, setpoints, etc...

`HotPIDController : public Joystick, public PIDController`

## How to use

## Changes
