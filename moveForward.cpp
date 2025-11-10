void moveForward(float distance)
{
  MotorLeft.setPosition(0, degrees);
  MotorLeft.setVelocity(70, percent);
  MotorRight.setVelocity(70, percent);
  MotorLeft.spin(forward);
  MotorRight.spin(forward);
  while (MotorLeft.position(degrees) < ((distance/200.00)*360))
  {
    obstacleDetection(MotorLeft.position(degrees));
    wait(2, seconds); // check for obstacles every 2 seconds
  }
  MotorLeft.stop;
  MotorRight.stop;
}
