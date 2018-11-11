
void pick_box()
{
  wheel(-100, -100);
  delay(20);
  wheel(0, 0);
  delay(50);
  digitalWrite(LED_blue, HIGH);
  left.write(L_OPEN);
  right.write(R_OPEN);
  delay(500);
  base.write(75);
  delay(1000);
  fixposition();
  wheel(base_L, base_R);
  delay(255);
  wheel(-100, -100);
  delay(20);
  wheel(0, 0);
  delay(50);
  
  gripcode();
  delay(500);
  for(int i=75; i>=UP_ANGLE; i--)
  {
    base.write(i);
    delay(15);
  }
  
  delay(1000);
//  left.write(L_OPEN);
//  right.write(R_OPEN);
//  delay(500);
//  left.write(L_CLOSE);
//  right.write(R_CLOSE);
  boxflag = 1;
  digitalWrite(43, LOW);
}


void box_deposit()
{
  base.write(DOWN_ANGLE2);
  delay(500);
  base_L = 90; base_R = 70;  
  wheel(-base_L,-base_R);
  delay(550);
  wheel(80,80);
  delay(20);
  wheel(0,0);
  delay(500);

  wheel(100,-100);
  delay(100);
  wheel(0,0);
  delay(500);

  wheel(-100,100);
  delay(200);
  wheel(0,0);
  delay(500);

  wheel(100,-100);
  delay(100);
  wheel(0,0);
  delay(500);
  
  left.write(L_OPEN);
  right.write(R_OPEN);
  delay(500);

  wheel(-80,-70);
  delay(500);
  wheel(80,80);
  delay(20);
  wheel(0,0);
  delay(50);

  
  base.write(UP_ANGLE);
  delay(500);
  left.write(130);
  right.write(60);
  delay(100);
}

void gripcode()
{
  left.write(10);
  for(int i=0; i<=90; i++)
  {
    right.write(R_OPEN-i);
    left.write(10+i);
    delay(6);
  }
  
}


