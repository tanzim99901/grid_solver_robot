void retriveGrid()
{
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      grid[i][j] = EEPROM.read(i * COL + j);
    }
  }
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      Serial.print(grid[i][j]);
    }
    Serial.println();
  }

}

void gridCorrectForLowRun()
{
  for (int i = 4; i < ROW; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      grid[i][j] = 2;
    }
  }
}

void gridCorrectForHighRun()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      grid[i][j] = 2;
    }
  }
}
