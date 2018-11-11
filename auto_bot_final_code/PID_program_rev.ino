
void PID_program_rev()
{
  readSensor();
  previousError = error; // save previous error for differential
  error = avgSensor - 8.5; // Count how much robot deviate from center
  Serial.println(error);
  /*if(error >= 2.00)
  {
    wheel(0,0);
    while(1)
    {
      wheel(turn_L_Rturn, -turn_R_Rturn);
      if(sRead(F6) && sRead(F7) && sRead(F8) && sRead(F9)) break;
    }
  }
  else if(error <= -2.00)
  {
    wheel(0,0);
    while(1)
    {
      wheel(-turn_L_Lturn, turn_R_Lturn);
      if(sRead(F6) && sRead(F7) && sRead(F8) && sRead(F9)) break;
    }

  }*/
  power = (Kp * error) + (Kd * (error - previousError)) + (Ki * totalError);

  if ( power > 255 ) {
    power = 255.0;
  }
  if ( power < -255.0 ) {
    power = -255.0;
  }

  if (power < 0) // Turn left
  {
    PWM_Right = -base_R + abs(int(power));
    PWM_Left = -base_L ;
  }

  else // Turn right
  {
    PWM_Right = -base_R ;
    PWM_Left = -base_L + abs(int(power));
  }


}

