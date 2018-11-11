
void box_test()
{
  while (!digitalRead(sonar_pin))
  {
    linefollow();
  }
  wheel(0, 0);
  delay(25);
  if (digitalRead(sonar_pin) && !boxflag)
  {
    fixposition();
    pick_box();
    boxflag = 1;
  }
  delay(25);
  while (digitalRead(FR) && digitalRead(FL))
  {
    linefollow();
  }
  wheel(0, 0);
  delay(25);
  while (digitalRead(BR) && digitalRead(BL))
  {
    linefollow();
  }
  wheel(0, 0);
  delay(25);
  
}
