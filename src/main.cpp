/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       hezek                                                     */
/*    Created:      1/23/2025, 12:34:30 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

bool airOn;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int firstCheck = 1;
void autonomous(void) {
  // ..........................................................................
    airFist.set(false);
    leftBackM.spinFor(reverse,355,degrees,10,velocityUnits::pct,false);
    leftFrontM.spinFor(reverse,355,degrees,10,velocityUnits::pct,false);
    rightBackM.spinFor(reverse,355,degrees,10,velocityUnits::pct,false);
    rightFrontM.spinFor(reverse,355,degrees,10,velocityUnits::pct,false);
    //clamp goal
    airFist.set(true);
    //Put ring on goal
    IntakeMotor.setVelocity(100,percent);
    IntakeMotor.spin(reverse);
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int airPump()
{
  while (1)
  {
    if (Controller1.ButtonR2.pressing())
    {
      if(airOn)
      {
        wait(0.2,sec);
        airFist.set(true);
        airOn = false;
        wait(0.1,seconds);
      }
      
      else
      {
        wait(0.2,sec);
        airFist.set(false);
        airOn = true;
        wait(0.1,seconds);
      }
    }
  }

  return 0;
}

int joysticks()
{
  while(1)
  {
    leftFrontM.spin(fwd,(Controller1.Axis3.position()),velocityUnits::pct);
    leftBackM.spin(fwd,(Controller1.Axis3.position()),velocityUnits::pct);
    
    rightFrontM.spin(fwd,(Controller1.Axis2.position()),velocityUnits::pct); 
    rightBackM.spin(fwd,(Controller1.Axis2.position()),velocityUnits::pct); 
  }
  
  return 0;
}

int IntakeUp()
{
  while(1)
  {
    if (Controller1.ButtonL1.pressing())
    {
      IntakeMotor.spin(forward,100,velocityUnits::pct);
    }

    else if (Controller1.ButtonL2.pressing())
    {
      IntakeMotor.spin(reverse,100,velocityUnits::pct);
    }

    else 
    {
      IntakeMotor.stop();
    }
  }
  return 0;
}

int wallStake() 
{
  
  stakeMotor.resetPosition();

  while (1) 
  {
    int currentPosistion = stakeMotor.position(degrees);
    if (Controller1.ButtonX.pressing() && currentPosistion < 145) {
      stakeMotor.spin(forward, 100, velocityUnits::pct);
      // stakeMotor.stop(brake);
    } 

    else if (Controller1.ButtonB.pressing() && currentPosistion > -145) 
    {
      stakeMotor.spin(reverse, 100, velocityUnits::pct);
      // stakeMotor.stop(brake);
    } 

    else 
    {
      stakeMotor.stop(hold);
    }

    // std::cout << stakeMotor.position(deg) << std::endl;
  }

  return 0;
}


void usercontrol(void) {
  // User control code here, inside the loop
  task MyTask1 = task(joysticks);
  task Mytask2 = task(IntakeUp);
  task MyTask3 = task(airPump);
  task MyTask5 = task(wallStake);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
