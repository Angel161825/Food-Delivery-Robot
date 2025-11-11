void unload(double distance, double CIRCUMFERENCE) // Motors are reverse
{
  double turn = distance/CIRCUMFERENCE + 0.1; // Experimental value should be used
  MotorConveyorLeft.spinFor(forward, turn, turns);
  MotorConveyorRight.spinFor(forward, turn, turns);
}
