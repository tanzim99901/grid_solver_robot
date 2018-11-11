void fixposition()
{
  readSensor();
  if((avgSensor<9) && (avgSensor>8));
  else if(avgSensor>9)
  {
    while(avgSensor>9)
    {
      readSensor();
      wheel(100,-100);
    }
    wheel(-100,100);
    delay(20);
    wheel(0,0);
    delay(50);
  }
  else if(avgSensor<8)
  {
    while(avgSensor<8)
    {
      readSensor();
      wheel(-100,100);
    }
    wheel(100,-100);
    delay(20);
    wheel(0,0);
    delay(100);
  }
}


void brake()
{
  wheel(-150, -150);
  delay(20);
  wheel(0, 0);
  delay(500);

  
}

