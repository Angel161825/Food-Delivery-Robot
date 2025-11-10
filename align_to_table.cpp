void alignTable()
{
  float distanceTol = 5.00; // Change after experimentation
  
  // If the bumper is pressed first, the opposite side's wheel moves forward until the  distance sensor distance ~ 0
  if (Bumper7.pressing())
  {
    MotorLeft.spin(forward);
    while (distance4.objectDistance(mm) > distanceTol){} 
    MotorLeft.stop();
  }
    
  // If the distance sensor ~ 0 first, the opposite side's wheel moves forward until the bumper is pressed.
  else if (Distance4.objectDistance(mm) < distanceTol)
  {
    MotorRight.spin(forward);
    while (!Bumper7.pressing()){}
    MotorRight.stop();
  }
}
