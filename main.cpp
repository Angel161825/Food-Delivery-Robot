int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  float tableCoords[3][2] = {{200.0, 0.0}, {200.0, -200.0}, {0.0, -200.0}}; // Coordinates in cm, each row represents a table
  float avgCount = 0.0;
  float deliveryTimeAvg = 0.0;
// While the close program button hasnt been pressed
  while(!Controller.ButtonFDown.pressing())
  {
    Brain.Timer.reset()
    float currentCoords [2] = {0,0};

    int table = controllerUsage();
    // Move forward x cm and reset robot's current coords
    moveForward([table, 0]);
    currentCoords[0] = table;

    // If it hasn't reach the right y coordinate, turn 90 degrees
    if(currentCoords[1] != tableCoords[table,1])
    {
      rotateRobot(90, 50);
    }
    // Move forward y cm
    moveForward([table,1]);
    alignTable();
    conveyorMove();
    feedback();
    
    // Going back to kitchen
    if (table == 0)
    {
      rotateRobot(180,50);
    }
    else if (table == 1 || table == 2)
    {
      rotateRobot(-180,50);
    }
    // Move back in same y amount, then x amount
    moveForward([table,1]);
    moveForward([table, 0]);
    if (table == 2)
    {
      rotateRobot(-90,50);
    }
    else
    {
      rotateRobot(180,50);
    }
    deliveryTimeAvg += Brain.Timer.value();
    avgCount ++;
  }
  deliveryTimeAvg = deliveryTimeAvg/avgCount;
  Brain.Screen.print("%f", deliveryTimeAvg);
  Brain.programStop();
  
}

