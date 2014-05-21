# RobotUtils

This is a series of classes written by Team 67 that enhance the functionality of WPILib.

This library is unfinished as of yet. This list will be updated as new functionality is added to it, and once everything is present, the wiki will be updated with reference on the library.

## Features

  * AdvancedJoystick (only for xbox controllers):
    * Button press detection
      * Variable timeout (this might go away...)
      * Experimental: Button-specific button press detection
    * Treat triggers like buttons
    * Advanced deadband handling for joysticks that don't zero properly
      * Turn deadband into a quadratic, cubic, or sinusoid ramp
    * Side-conscious trigger handling
    * All indices are wrapped up in nice little enums
  * Subsystems (Not the type from the command-based template)
    * Infrastructure for a subsystem-based code model
      * Keep internal variables up-to-date with the HotSubsystemHandler
      * Updating is run on a separate thread
    * Semi-automatic data printouts
  * Smart PID Controller
    * Set I to a nonzero value when within a specific range of the setpoint
  * More to come...
  
## Get RobotUtils

_Note: Until we finish the library, there will be no official release. If you really, really want the library, follow the directions for Unstable._

### Stable

Go to the [Releases page](https://github.com/hot67/RobotUtils/releases/) and download either the zip or the tar.gz of the latest release. Unpack it into your project's folder and rename the folder it extracted into to "RobotUtils". Include "RobotUtils/RobotUtils.h" in your project's main file (or wherever else you need it), and you're set!

### Unstable

_WARNING: This is **NOT** recommended. This method gets you the latest commit to our repository, which may break the library. We cannot guarantee that the unstable version will work. Proceed at your own risk._

Make sure that you are on the master branch, and click the "Download ZIP" button on the right. Unpack it into your project folder, rename the extraction folder to "RobotUtils" and include "RobotUtils/RobotUtils.h" in whatever files you need it in.

## Help us out!

Find a bug? Post it to our issue tracker, and we'll take care of it.

Is there a feature you want that isn't here? Either post it in the issue tracker (with the 'enhancement' label), or fork & pull request us!

_Please note that in order for your feature to be added, it must be either relevant to an existing class or have enough related enhancements to warrant creating a new class._
