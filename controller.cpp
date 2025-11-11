int controllerUsage()
{
  int buttonPressed = 0;
  // Waits until a button is pressed
  while (!(Controller.ButtonEDown.pressing() || Controller.ButtonEUp.pressing()|| Controller.ButtonFDown.pressing() || Controller.ButtonFUp.pressing())){}
  // E up = table 1, E down = table 2, F up = table 3
  // Stores what button is being pressed
  if (Controller.ButtonEDown.pressing())
  {
    buttonPressed = 1;
  }
  else if (Controller.ButtonEUp.pressing())
  {
    buttonPressed = 0;
  }
  else if (Controller.ButtonFUp.pressing())
  {
    buttonPressed = 2;
  }
  // Waits until the button is done being pressed
  while (Controller.ButtonEDown.pressing() || Controller.ButtonEUp.pressing()|| Controller.ButtonFDown.pressing() || Controller.ButtonFUp.pressing()){}
  return buttonPressed;

}

