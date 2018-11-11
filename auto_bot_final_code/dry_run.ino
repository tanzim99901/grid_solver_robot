
void dry_run()
{
  base.detach();
  left.detach();
  right.detach();

  int i = 0;
  int j = 0;

  while (!dry)
  {

    while (digitalRead(FR) && digitalRead(FL))
    {
      linefollow();
    }
    //    wheel(-base_L, -base_R);
    //    wheel(0,0);
    //   delay(25);

    if (!digitalRead(FL) && !digitalRead(FR))
    {
      delay(20);
      //PID_reset();
      //wheel(0, 0);
      //delay(1000);
      if ((sRead(F6) || sRead(F7) || sRead(F8) || sRead(F9)) && (!sRead(F1) && !sRead(F2) && !sRead(F3)) && (!sRead(F12) && !sRead(F13) && !sRead(F14))) // box node
      {
        //wheel(0,0);
        //delay(1000);
        //found box ureka
        

        node_count++;
        if (!(i == 6 && j == 3))
        {
          digitalWrite(LED_green, HIGH);
          EEPROM.write(32, i * COL + j + 1);
        }
        grid[i][j] = 1;
        
        /* else
           EEPROM.write(33, i * COL + j + 1);
        */
        if (j % 2 == 0)
        {
          i++;
        }
        else
        {
          i--;
        }
      }
      else if (!sRead(F6) || !sRead(F7) || !sRead(F8) || !sRead(F9)) //black node
      {

        //middle black
        //wheel(0, 0);
        //delay(1000);

        // node will not pass
        digitalWrite(LED_red, HIGH);

        node_count++;
        if (i == 6 && j == 3)
        {
          grid[i][j] = 1;
        }
        else 
        {
          grid[i][j]=2;
        }
        if (j % 2 == 0)
        {
          i++;
        }
        else
        {
          i--;
        }
      }
      else if (sRead(F6) && sRead(F7) && sRead(F8) && sRead(F9)) //white node
      {

        //Middle White
        //wheel(0, 0);
        //delay(1000);

        // normal white
        digitalWrite(LED_blue, HIGH);

        node_count++;
        grid[i][j] = 1;
        if (j % 2 == 0)
        {

          i++;
        }
        else
        {
          i--;
        }
      }

      //wheel(0,0);
      //delay(1000);

      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      wheel(-120, -120);
      delay(25);
      wheel(0, 0);
      delay(500);

      digitalWrite(LED_blue, LOW);
      digitalWrite(LED_green, LOW);
      digitalWrite(LED_red, LOW);

      fixposition();

      if (col == 1 && node_count == 1)
      {
        turn_right();
      }
      if (col == 2 && node_count == 1)
      {
        turn_left();
      }
      if (col == 3 && node_count == 1)
      {
        turn_right();
      }
      if (node_count == 8)
      {

        if (col == 1 )
        {
          turn_left();
          i++;
        }
        else if (col == 3)
        {
          wheel(0, 0);
          delay(2000);
          dry = 1;
          EEPROM.write(40, 1);
          for (i = 0; i < ROW; i++)
          {
            for (j = 0; j < COL; j++)
            {
              EEPROM.write(i * COL + j, grid[i][j]);
            }
          }
          digitalWrite(LED_blue, HIGH);

        }
        else if (col == 0 || col == 2 )
        {
          turn_right();
          i--;
        }
        col++;
        j++;
        node_count = 0;
      }
    }


  }
}


