void alignTable()
{
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

