void unload(double distance, double CIRCUMFERENCE) // Motors are reverse
{
  double turn = distance/CIRCUMFERENCE + 0.1 // Experimental value should be used
  Motor1.spinFor(forward, turn, turns);
  Motor2.spinFor(forward, turn, turns);
}
