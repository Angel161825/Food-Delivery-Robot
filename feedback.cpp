int feedback ( )
{
  double time = Brain.Timer.value();
  Brain.Screen.print("It took %d", time, "seconds to deliver the food");
  Brain.Screen.newLine();
  Brain.Screen.print("Your feedback would be greatly appreciated!");
  int rating = -1;
  while (rating == -1)
  {
    Brain.Timer.reset();
    while (TouchLED12.pressing())
    {
    }
    double secondsPressed = Brain.Timer.value();
    if (secondsPressed < 2.00)
    {
      rating = 3;
    }
    else if (secondsPressed < 5.00)
    {
      rating = 2;
    }
    else if (secondsPressed < 10.00)
    {
      rating = 1;
    }
    Brain.Screen.print("You have given us %d", rating, "stars out of 3! If you want to change your rating please tap the touch LED");
    Brain.Screen.newLine();
    double resetRating = Brain.Timer.value();
    while (Brain.Timer.value() < resetRating + 500)
    {
      if (TouchLED12.pressing())
      {
        rating = -1;
        Brain.Screen.print("Please renter the feedback");
        Brain.Screen.newLine();
      }
    }
  }
  return rating;
}

