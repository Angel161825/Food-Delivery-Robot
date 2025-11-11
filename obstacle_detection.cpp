// Let rotations be a variable for now that indicates the # of degrees the motors must turn from the start to get to the current table
void obstacleDetection(float rotations) 
{
  float objectTol = 10.00; // Arbitrary # of how close something has to be to be considered an obstacle
  float rotationsTol = rotations - (360)*5; // Basically making sure the obstacle isn't actually the table 
                                          // (in this case, it needs to be more than 5 turns away from the table)

  // "If the distance sensor detects something equal or closer to it than the tolerance and the robot is far enough from the table"
  if ( (Distance5.objectDistance(mm) <= objectTol) && (MotorLeft.position(degrees) < rotationsTol) )
  {
    MotorLeft.stop();
    MotorRight.stop();
    while(Distance5.objectDistance(mm) <= objectTol){} // waiting until object leaves
    //call movement function again here
  }

}

