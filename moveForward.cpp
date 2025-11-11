void moveForward(float distance, int reverse)
{
  MotorLeft.setPosition(0, degrees);
  MotorLeft.setVelocity(70, percent);
  MotorRight.setVelocity(70, percent);

  if (reverse = 1)
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
    obstacleDetection(MotorLeft.position(degrees));
    wait(2, seconds); // check for obstacles every 2 seconds
  }
  MotorLeft.stop();
  MotorRight.stop();
}
