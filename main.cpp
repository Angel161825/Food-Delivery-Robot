int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  configureAllSensors();

  float tableCoords[3][2] = {{20000, 0}, {20000, -20000}, {0, -20000}}; // Coordinates in mm, each row represents a table
  float avgCount = 0;
  float deliveryTimeAvg = 0;
  float feedbackAvg = 0;

  while(!Controller.ButtonFDown.pressing())
  {
    Brain.Timer.reset();
    float currentCoords [2] = {0,0};

    int table = controllerUsage();
    // Move forward x cm and reset robot's current coords

    moveForward((tableCoords[table][0]), 0);
    currentCoords[0] = table;

    // If it hasn't reach the right y coordinate, turn 90 degrees
    if(currentCoords[1] != tableCoords[table][1])
    {
      rotateRobot(90, 50);
    }
    // Move forward y cm
    moveForward(tableCoords[table][1], 0);

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


