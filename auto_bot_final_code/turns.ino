
void turn_test_right()
{
  while (digitalRead(FR) || digitalRead(FL)) //FR FL black
  {
    linefollow();
  }
  while (digitalRead(BR) || digitalRead(BL))  //BR BL black
  {
    linefollow();
  }

  wheel(-150, -150);
  delay(20);
  wheel(0, 0);
  delay(500);

  wheel(120, -120);

  while (1)
  {
    if ((sRead(F6) == 0) && (sRead(F7) == 0) && (sRead(F8) == 0) && (sRead(F9) == 0)) break;
  }

  while (1)
  {
    if ((sRead(F6) == 1) || (sRead(F7) == 1) || (sRead(F8) == 1) || (sRead(F9) == 1)) break;
  }

  wheel(-120, 120);
  delay(20);
  wheel(0, 0);
  delay(100);
}


void turn_test_left()
{
  while (digitalRead(FR) || digitalRead(FL)) //FR FL black
  {
    linefollow();
  }
  while (digitalRead(BR) || digitalRead(BL))  //BR BL black
  {
    linefollow();
  }

  wheel(-150, -150);
  delay(20);
  wheel(0, 0);
  delay(500);

  wheel(-120, 120);

  while (1)
  {
    if ((sRead(F6) == 0) && (sRead(F7) == 0) && (sRead(F8) == 0) && (sRead(F9) == 0)) break;
  }

  while (1)
  {
    if ((sRead(F6) == 1) || (sRead(F7) == 1) || (sRead(F8) == 1) || (sRead(F9) == 1)) break;
  }

  wheel(120, -120);
  delay(20);
  wheel(0, 0);
  delay(100);
}


void turn_right()
{

  wheel(-150, -150);
  delay(20);
  wheel(0, 0);
  delay(50);

  wheel(120, -120);

  while (1)
  {
    if ((sRead(F6) == 0) && (sRead(F7) == 0) && (sRead(F8) == 0) && (sRead(F9) == 0)) break;
  }

  while (1)
  {
    if ((sRead(F6) == 1) || (sRead(F7) == 1) || (sRead(F8) == 1) || (sRead(F9) == 1)) break;
  }

  wheel(-120, 120);
  delay(20);
  wheel(0, 0);
  delay(20);

 // fixposition();
}


void turn_left()
{

  wheel(-150, -150);
  delay(20);
  wheel(0, 0);
  delay(50);

  wheel(-120, 120);

  while (1)
  {
    if ((sRead(F6) == 0) && (sRead(F7) == 0) && (sRead(F8) == 0) && (sRead(F9) == 0)) break;
  }

  while (1)
  {
    if ((sRead(F6) == 1) || (sRead(F7) == 1) || (sRead(F8) == 1) || (sRead(F9) == 1)) break;
  }

  wheel(120, -120);
  delay(20);
  wheel(0, 0);
  delay(20);
  //fixposition();
}

