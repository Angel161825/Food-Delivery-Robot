#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START IQ MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END IQ MACROS


// Robot configuration code.
inertial BrainInertial = inertial();
motor MotorLeft = motor(PORT1, false);
motor MotorRight = motor(PORT6, true);
bumper Bumper2 = bumper(PORT2);
touchled TouchLED12 = touchled(PORT12);
controller Controller = controller();
motor MotorConveyorLeft = motor(PORT3, false);
motor MotorConveyorRight = motor(PORT4, false);
distance Distance5 = distance(PORT5);


// generating and setting random seed
void initializeRandomSeed(){
  wait(100,msec);
  double xAxis = BrainInertial.acceleration(xaxis) * 1000;
  double yAxis = BrainInertial.acceleration(yaxis) * 1000;
  double zAxis = BrainInertial.acceleration(zaxis) * 1000;
  // Combine these values into a single integer
  int seed = int(
    xAxis + yAxis + zAxis
  );
  // Set the seed
  srand(seed); 
}



void vexcodeInit() {

  // Initializing random seed.
  initializeRandomSeed(); 
}


// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

//----------------------------------------------------------------------------
//                                                                            
//    Module:       main.cpp                                                  
//    Author:       {author}                                                  
//    Created:      {date}                                                    
//    Description:  IQ project                                                
//                                                                            
//----------------------------------------------------------------------------

// Include the IQ Library
#include "iq_cpp.h"

// Allows for easier use of the VEX Library
using namespace vex;

void configureAllSensors()
{
  BrainInertial.calibrate();
  wait(2,seconds);
  BrainInertial.setHeading(0,degrees);
  BrainInertial.setRotation(0,degrees);
  MotorLeft.setPosition(0,turns);
  MotorRight.setPosition(0,turns);
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono15);
}

//rotate robot to a certain angle at a given power
void rotateRobot (int angle, int motorPower){
  BrainInertial.setRotation(0,degrees);
  wait(50, msec);

  MotorLeft.setVelocity(motorPower,percent);
  MotorRight.setVelocity(motorPower,percent);
  //for positive angle, rotates clockwise
  if (angle>0) {
    MotorLeft.spin(forward);
    MotorRight.spin(reverse); 
  }
  //for negative angle, rotates counterclockwise
  else {
    MotorLeft.spin(reverse);
    MotorRight.spin(forward);
  }
  while (abs(BrainInertial.rotation(degrees))<abs(angle)) {
  }
  MotorLeft.stop();
  MotorRight.stop();
}

void alignTable()
{
  Brain.Screen.print("align");
  float distanceTol = 5.00; // Change after experimentation

  MotorLeft.setVelocity(30, percent);
  MotorRight.setVelocity(30, percent);
  MotorLeft.spin(forward);
  MotorRight.spin(forward);
  // Keep moving forward while the bumper is not pressed and the distance sensor isn't close
  while (!(Bumper2.pressing() || Distance5.objectDistance(mm) < distanceTol)){}
  MotorLeft.stop();
  MotorRight.stop();
  
  // If the bumper is pressed first, the opposite side's wheel moves forward until the  distance sensor distance ~ 0
  if (Bumper2.pressing())
  {
    MotorLeft.spin(forward);
    while (Distance5.objectDistance(mm) > distanceTol){} 
    MotorLeft.stop();
  }
    
  // If the distance sensor ~ 0 first, the opposite side's wheel moves forward until the bumper is pressed.
  else if (Distance5.objectDistance(mm) < distanceTol)
  {
    MotorRight.spin(forward);
    while (!Bumper2.pressing()){}
    MotorRight.stop();
  }
}

int controllerUsage()
{
  int buttonPressed = 0;
  // Waits until a button is pressed
  while (!(Controller.ButtonEDown.pressing()) && !(Controller.ButtonEUp.pressing()) && !(Controller.ButtonFDown.pressing()) && !(Controller.ButtonFUp.pressing())){}
  // E up = table 1, E down = table 2, F up = table 3
  // Stores what button is being pressed
  if (Controller.ButtonEDown.pressing())
  {
    buttonPressed = 1;
  }
  else if (Controller.ButtonEUp.pressing())
  {
    buttonPressed = 0;
  }
  else if (Controller.ButtonFUp.pressing())
  {
    buttonPressed = 2;
  }
  // Waits until the button is done being pressed
  //while (Controller.ButtonEDown.pressing() || Controller.ButtonEUp.pressing()|| Controller.ButtonFDown.pressing() || Controller.ButtonFUp.pressing()){}
  return buttonPressed;

}


void obstacleDetection(float rotations) 
{
  Brain.Screen.print("object detection function");
  float objectTol = 50.00; // Arbitrary # of how close something has to be to be considered an obstacle
  float rotationsTol = rotations - (360)*0.5; // Basically making sure the obstacle isn't actually the table 
                                          // (in this case, it needs to be more than 5 turns away from the table)

  // "If the distance sensor detects something equal or closer to it than the tolerance and the robot is far enough from the table"
  if ( (Distance5.objectDistance(mm) <= objectTol) && (MotorLeft.position(degrees) < rotationsTol) )
  {
    Brain.Screen.print("object detected");
    MotorLeft.setVelocity(0, percent);
    MotorRight.setVelocity(0, percent);
    while(Distance5.objectDistance(mm) <= objectTol){} // waiting until object leaves
    MotorLeft.setVelocity(70, percent);
    MotorRight.setVelocity(70, percent);
  }

}

void moveForward(float distance, int direction)
{
  MotorLeft.setPosition(0, degrees);
  MotorLeft.setVelocity(70, percent);
  MotorRight.setVelocity(70, percent);

  if (direction == 1)
  {
    MotorLeft.spin(reverse);
    MotorRight.spin(reverse);
  }
  else
  {
    MotorLeft.spin(forward);
    MotorRight.spin(forward);
  }
  
  while (MotorLeft.position(degrees) < ((distance/200.00)*360))
  {
    obstacleDetection((distance/200.00)*360);
    //wait(2, seconds); // check for obstacles every 2 seconds
  }
  MotorLeft.stop();
  MotorRight.stop();
}

int feedback ( )
{
  double time = Brain.Timer.value();
  Brain.Screen.print("It took %d", time, "seconds to deliver the food");
  Brain.Screen.newLine();
  Brain.Screen.print("Your feedback would be greatly appreciated!");
  int rating = -1;
  while (rating == -1)
  {
    Brain.Timer.reset();
    while (TouchLED12.pressing())
    {
    }
    double secondsPressed = Brain.Timer.value();
    if (secondsPressed < 2.00)
    {
      rating = 3;
    }
    else if (secondsPressed < 5.00)
    {
      rating = 2;
    }
    else if (secondsPressed < 10.00)
    {
      rating = 1;
    }
    Brain.Screen.print("You have given us %d", rating, "stars out of 3! If you want to change your rating please tap the touch LED");
    Brain.Screen.newLine();
    double resetRating = Brain.Timer.value();
    while (Brain.Timer.value() < resetRating + 500)
    {
      if (TouchLED12.pressing())
      {
        rating = -1;
        Brain.Screen.print("Please renter the feedback");
        Brain.Screen.newLine();
      }
    }
  }
  return rating;
}

void unload(double distance, double CIRCUMFERENCE) // Motors are reverse
{
  double turn = distance/CIRCUMFERENCE + 0.1; // Experimental value should be used
  MotorConveyorLeft.spinFor(forward, turn, turns);
  MotorConveyorRight.spinFor(forward, turn, turns);
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  configureAllSensors();

  float tableCoords[3][2] = {{2000, 0}, {2000, -2000}, {0, -2000}}; // Coordinates in mm, each row represents a table
  float avgCount = 0;
  float deliveryTimeAvg = 0;
  float feedbackAvg = 0;

  while(!Controller.ButtonFDown.pressing())
  {
    Brain.Timer.reset();
    float currentCoords [2] = {0,0};

    int table = controllerUsage();
    Brain.Screen.print("working");
    // Move forward x cm and reset robot's current coords

    moveForward((tableCoords[table][0]), 0);
    currentCoords[0] = table;

    // If it hasn't reach the right y coordinate, turn 90 degrees
    if(currentCoords[1] != tableCoords[table][1])
    {
      rotateRobot(90, 50);
    }
    // Move forward y cm
    moveForward(abs(tableCoords[table][1]), 0);

    // At the table
    alignTable();
    unload(1000.0, 200.0);
    feedbackAvg += feedback();
    
    // Going back to kitchen

    // Move back in same y amount, then x amount
    moveForward(tableCoords[table][1],1);
    moveForward(tableCoords[table][0],1);

    deliveryTimeAvg += Brain.Timer.value();
    avgCount ++;
  }

  deliveryTimeAvg = deliveryTimeAvg/avgCount;
  feedbackAvg = feedbackAvg/avgCount;
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Delivery Time Avg: %f", deliveryTimeAvg);
  Brain.Screen.setCursor(4, 1);
  Brain.Screen.print("Rating avg: %f", feedbackAvg);
  wait(10, seconds);
  Brain.programStop();
}
