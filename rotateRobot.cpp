// Taken from class
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
