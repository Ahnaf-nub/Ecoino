void controlSolar()
{
  int val1 = analogRead(ldr1); // read the value of ldr 1
  int val2 = analogRead(ldr2); // read the value of ldr 2

  if ((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance))
  {
    //no servo motor horizontal movement will take place if the ldr value is within the allowable tolerance
  }
  else
  {
    if (val1 > val2) // if ldr1 senses more light than ldr2
    {
      pos = pos + 1; // decrement the 90 degree poistion of the horizontal servo motor - this will move the panel position Eastward
    }
    if (val1 < val2) // if ldr2 senses more light than ldr1
    {
      pos = pos - 1; // increment the 90 degree position of the horizontal motor - this will move the panel position Westward
    }
  }

  if (pos > 180) {
    pos = 180; // reset the horizontal postion of the motor to 180 if it tries to move past this point
  }
  if (pos < 0) 
  {
    pos = 0; // reset the horizontal position of the motor to 0 if it tries to move past this point
  }
  solarServo.write(pos); // write the starting position to the horizontal motor
  delay(50);
}
