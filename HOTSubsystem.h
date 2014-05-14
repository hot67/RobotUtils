/* HOTSubsystem
 *
 * This is the base class for all
 * objects to be used with
 * SubsystemHandler. Note: All classes
 * that inherit this must be a friend
 * of the SubsystemHandler so it can call
 * the update() function.
 */

#ifndef HOTSUBSYSTEM_H
#define HOTSUBSYSTEM_H

class HOTSubsystem {

protected:
    virtual void update();
};

#endif // HOTSUBSYSTEM_H
