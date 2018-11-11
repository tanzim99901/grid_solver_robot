void calcPath(int source, int target)
{
  int i, j, w, ch, co;
  for (i = 0; i < N; i++)
  {
    path[i] = 48;
    nav[i] = 0;
  }

  char cost[N][N];
  int x, y;
  for (i = 1; i < N; i++)
  {
    for (j = 1; j < N; j++)
    {
      cost[i][j] = IN;
    }

  }

  int asd = 1;
  for (x = 1; x < N; x++)
  {
    if (!(grid[x / COL][(x % COL) - 1] == 2))
    {
      for (y = x + 1; y < N; y++)
      {
        if (((y == x + 1) && (x % COL) != 0) || (y == x + COL))
        {
          if (!(grid[y / COL][(y % COL) - 1] == 2))
            cost [x][y] = cost[y][x] = asd;
        }
      }
    }
  }
  co = dijsktra(cost, source, target);
  // Serial.println("\nThe Shortest Path:");
  //Serial.println(co);
  i = 0;
  while (path[i] != 48)
  {
    Serial.print (path[i]);
    nav[i] = path[i];
    i++;
  }
  nav[i - 1] = 0;
}

int gotoNode(int start, int end, int curDir, boolean flag_box)
{
  calcPath(start, end);
  int i = 0, diff[N];
  while (nav[i] != 0)
  {
    Serial.println(nav[i]);
    i++;
  }
  if (!flag_box)
  {
    return nav[i - 2];
  }
  i = 0;
  while (nav[i] != 0)
  {
    diff[i] = nav[i + 1] - nav[i];
    Serial.println(diff[i]);
    i++;
    //Serial.println(nav[i]);
  }

  diff[i] = '\0';
  i = 0;
  while (diff[i + 1] != '\0' )
  {


    switch (diff[i])
    {
      case 1:
        Serial.println("east");
        curDir = change_Dir(curDir, east);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);

        PID_reset();
        break;
      case -1:
        Serial.println("west");
        curDir = change_Dir(curDir, west);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);
        PID_reset();
        break;
      case COL:
        Serial.println("north");
        curDir = change_Dir(curDir, north);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);
        PID_reset();
        break;
      case -COL:
        Serial.println("south");
        curDir = change_Dir(curDir, south);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);
        PID_reset();
        break;
      default:
        Serial.println("FU");
        break;
    }

  }

  return curDir;
}

int gotoNodeOr(int start, int end, int curDir, boolean flag_box)
{
  calcPath(start, end);
  int i = 0, diff[N];
  while (nav[i] != 0)
  {
    Serial.println(nav[i]);
    i++;
  }
  if (!flag_box)
  {
    return nav[i - 2];
  }
  i = 0;
  while (nav[i] != 0)
  {
    diff[i] = nav[i + 1] - nav[i];
    Serial.println(diff[i]);
    i++;
    //Serial.println(nav[i]);
  }

  diff[i] = '\0';
  i = 0;
  while (diff[i + 1] != '\0' )
  {


    switch (diff[i])
    {
      case 1:
        Serial.println("east");
        curDir = change_Dir(curDir, east);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);

        PID_reset();
        break;
      case -1:
        Serial.println("west");
        curDir = change_Dir(curDir, west);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);
        PID_reset();
        break;
      case COL:
        Serial.println("north");
        curDir = change_Dir(curDir, north);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);
        PID_reset();
        break;
      case -COL:
        Serial.println("south");
        curDir = change_Dir(curDir, south);
        do
        {

          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while (sRead(F0) && sRead(F1) && sRead(F2) && !sRead(F13) && !sRead(F14) && !sRead(F15))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(FL) && digitalRead(FR)))
          {
            linefollow();
          }
          delay(25);
          while ((digitalRead(BL) && digitalRead(BR)))
          {
            linefollow();
          }
          delay(25);
          i++;
        }
        while ((diff[i - 1] == diff[i]) && diff[i + 1] != '\0');
        wheel(0, 0);
        PID_reset();
        break;
      default:
        Serial.println("FU");
        break;
    }

  }

  return curDir;
}
int dijsktra(char cost[][N], int source, int target)
{
  int dist[N], prev[N], selected[N] = {0}, i, m, min, start, d, j;
  for (i = 1; i < N; i++)
  {
    dist[i] = IN;
    prev[i] = -1;
  }
  start = source;
  selected[start] = 1;
  dist[start] = 0;
  while (selected[target] == 0)
  {
    min = IN;
    m = 0;
    for (i = 1; i < N; i++)
    {
      d = dist[start] + cost[start][i];
      if (d < dist[i] && selected[i] == 0)
      {
        dist[i] = d;
        prev[i] = start;
      }
      if (min > dist[i] && selected[i] == 0)
      {
        min = dist[i];
        m = i;
      }
    }
    start = m;
    selected[start] = 1;
  }
  start = target;
  j = 0;
  while (start != -1)
  {
    path[j++] = start ;
    start = prev[start];
  }
  path[j] = '\0';
  strrev(path);
  //Serial.println(path);
  return dist[target];
}




int change_Dir (int my_Dir, int next_dir)
{
  if (my_Dir == north)
  {
    ////////////////////////////
    switch (next_dir)
    {
      case (east):
        turn_right();
        my_Dir = next_dir; // update current Dir

        break;
      case (south):


        turn_left();
        delay(100);
        fixposition();
        turn_left();
        my_Dir = next_dir; // update current Dir

        break;
      case (west):
        turn_left();
        my_Dir = next_dir; // update current Dir

        break;
      default: break;
    }
  }
  ////////////////////////////
  if (my_Dir == east)
  {
    switch (next_dir)
    {
      case (south):
        turn_right();
        my_Dir = next_dir; // update current Dir

        break;
      case (west):

        turn_right();
        delay(100);
        fixposition();
        turn_right();
        my_Dir = next_dir; // update current Dir

        break;
      case (north):
        turn_left();
        my_Dir = next_dir; // update current Dir

        break;
      default: break;
    }
  }
  ////////////////////////////
  if (my_Dir == south)
  {
    switch (next_dir)
    {
      case (west):
        turn_right();
        my_Dir = next_dir; // update current Dir

        break;
      case (north):

        turn_left();
        delay(100);
        fixposition();
        turn_left();
        my_Dir = next_dir; // update current Dir

        break;
      case (east):
        turn_left();
        my_Dir = next_dir; // update current Dir

        break;
      default: break;
    }
  }
  ////////////////////////////
  if (my_Dir == west)
  {
    switch (next_dir)
    {
      case (north):
        turn_right();
        my_Dir = next_dir; // update current Dir

        break;
      case (east):

        turn_left();
        delay(100);
        fixposition();
        turn_left();
        my_Dir = next_dir; // update current Dir

        break;
      case (south):
        turn_left();
        my_Dir = next_dir; // update current Dir

        break;
      default: break;
    }
  }
  return (my_Dir); // return updated direction to calling function
}

