void unload(double distance, double CIRCUMFERENCE) // Motors are reverse
{
  double turn = distance/CIRCUMFERENCE + 0.1; // Experimental value should be used
  MotorLeft.spinFor(forward, turn, turns);
  MotorRight.spinFor(forward, turn, turns);
}
