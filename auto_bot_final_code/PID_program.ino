
int sRead(int pin)
{
  if (analogRead(pin) >= sT)
  {
    return 0;
  }
  else return 1;
}

void readSensor(void)
{
  int sensorReading[16];
  activeSensor = 0; totalSensor = 0;

  sensorReading[0] = sRead(F0);
  sensorReading[1] = sRead(F1);
  sensorReading[2] = sRead(F2);
  sensorReading[3] = sRead(F3);
  sensorReading[4] = sRead(F4);
  sensorReading[5] = sRead(F5);
  sensorReading[6] = sRead(F6);
  sensorReading[7] = sRead(F7);
  sensorReading[8] = sRead(F8);
  sensorReading[9] = sRead(F9);
  sensorReading[10] = sRead(F10);
  sensorReading[11] = sRead(F11);
  sensorReading[12] = sRead(F12);
  sensorReading[13] = sRead(F13);
  sensorReading[14] = sRead(F14);
  sensorReading[15] = sRead(F15);

  for (int i = 0; i < 16; i++)
  {
    if (sensorReading[i] == 1)
    {
      activeSensor = activeSensor + 1;
    }
    totalSensor = totalSensor + (sensorReading[i] * (i + 1));
  }
   for (int i = 0; i < 16; i++)
    {
      //Serial.print(sensorReading[i]);
     // Serial.print(" ");
  }

 if(activeSensor==0 )  avgSensor=8.5;
 else  avgSensor = totalSensor / activeSensor;

}


void PID_program()
{
  readSensor();
  previousError = error; // save previous error for differential
  error = avgSensor - 8.5; // Count how much robot deviate from center
  //Serial.println(error);

  if (!sRead(F0) && !sRead(F1) && !sRead(F2) && !sRead(F3) && !sRead(F4) && !sRead(F5) && !sRead(F6) && !sRead(F7) && !sRead(F8) && !sRead(F9) && !sRead(F10) && !sRead(F11) && !sRead(F12) && !sRead(F13) && !sRead(F14) && !sRead(F15))
  {
    error = 0;
    totalError = 0;
    PID_reset();
    /*while (1)
    {
      wheel(base_L, base_R);
      if (sRead(F0) || sRead(F1) || sRead(F2) || sRead(F3) || sRead(F4) || sRead(F5) || sRead(F6) || sRead(F7) || sRead(F8) || sRead(F9) || sRead(F10) || sRead(F11) || sRead(F12) || sRead(F13) || sRead(F14) || sRead(F15)) break;
    }*/
  }
  else totalError += error; // Accumulate error for integral
  if (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15) )
  {
    error = 0;
    totalError = 0;
    PID_reset();
    /*while (1)
    {
      wheel(base_L, base_R);
      if (!sRead(F0) && !sRead(F15)) break;
    }*/
  }
  else totalError += error;
  power = (Kp * error) + (Kd * (error - previousError)) + (Ki * totalError);

  if ( power > 255 ) {
    power = 255.0;
  }
  if ( power < -255.0 ) {
    power = -255.0;
  }

  if (power < 0) // Turn left
  {
    PWM_Right = base_R;
    PWM_Left = base_L - abs(int(power));
  }

  else // Turn right
  {
    PWM_Right = base_R - abs(int(power));
    PWM_Left = base_L;
  }
}




