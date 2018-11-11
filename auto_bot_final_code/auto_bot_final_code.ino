#include  <StandardCplusplus.h>
#include  <iostream>     // std::cout
#include  <algorithm>
#include  <stdio.h>
#include  <string.h>
#include  <math.h>
#include  <EEPROM.h>
#include  <Servo.h>

#define DRY_RUN   0
#define FULL_RUN  1
#define RES_1     0
#define RES_2     0

#define switch_1 21   // for dry run
#define switch_2 20   // for 1st restart
#define switch_3 17   // for 2nd restart

#define UP_ANGLE    0
#define DOWN_ANGLE  80
#define DOWN_ANGLE2  90
#define R_OPEN      180
#define R_CLOSE     90
#define L_OPEN      0
#define L_CLOSE     100

#define F0 A15
#define F1 A14
#define F2 A13
#define F3 A12
#define F4 A11
#define F5 A10
#define F6 A9
#define F7 A8
#define F8 A7
#define F9 A6
#define F10 A5
#define F11 A4
#define F12 A3
#define F13 A2
#define F14 A1
#define F15 A0

#define FR 28
#define FL 26
#define BR 30
#define BL 24
#define HR 31
#define HL 32

#define in1 53
#define in2 51
#define in3 49
#define in4 47
#define ena 11
#define enb 12

#define LED_red 37
#define LED_green 39
#define LED_yellow 41
#define LED_blue 43
#define LED_white 45

#define sonar_pin 42
#define bridge_pin 40

#define servo_base 52
#define servo_right 50
#define servo_left 48
//.........GLOBAL FOR DIJKSTRAS......//
#define IN 99
#define N 33
#define ROW 8
#define COL 4

#define north  0
#define east   1
#define south  2
#define west   3

byte incomingByte;
boolean boxflag = 0;

char path[N];
int nav[N];
int pCount = 0;

int grid[ROW][COL] = { 0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                     };



//.......................//
int node_count = 0, col = 0;
boolean dry = 0;
int Box_go = 0;
int Box_Con = 0;
int Dir = 0;
int sT = 200;

int base_L = 107, turn_L_Rturn = 120, turn_L_Lturn = 120;
int base_R = 110, turn_R_Rturn = 120, turn_R_Lturn = 120;
float activeSensor = 0; // Count active sensors
float totalSensor = 0; // Total sensor readings
float avgSensor = 0; // Average sensor reading

float Kp = 30;   // Max deviation = 6-3.5 = 2.5 ||  100/2.5 = 40
//float Ki = 0.5;
float Ki = 0;
//float Kd = 0.7;
float Kd = 3;
int negedge = 15;

Servo base;
Servo right;
Servo left;

//const long delay_time = 200;

float error = 0;
float previousError = 0;
float totalError = 0;

float power = 0;

int PWM_Right, PWM_Left;


void setup()
{
  //Serial1.begin(9600);
  Serial.begin(9600);
  base.attach(servo_base);
  left.attach(servo_left);
  right.attach(servo_right);
  left.write(L_CLOSE);
  right.write(R_CLOSE);
  base.write(UP_ANGLE);
  // put your setup code here, to run once:
  pinMode(F0, INPUT);
  pinMode(F1, INPUT);
  pinMode(F2, INPUT);
  pinMode(F3, INPUT);
  pinMode(F4, INPUT);
  pinMode(F5, INPUT);
  pinMode(F6, INPUT);
  pinMode(F7, INPUT);
  pinMode(F8, INPUT);
  pinMode(F9, INPUT);
  pinMode(F10, INPUT);
  pinMode(F11, INPUT);
  pinMode(F12, INPUT);
  pinMode(F13, INPUT);
  pinMode(F14, INPUT);
  pinMode(F15, INPUT);
  pinMode(FL, INPUT);
  pinMode(FR, INPUT);
  pinMode(BL, INPUT);
  pinMode(BR, INPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(LED_blue, OUTPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(LED_yellow, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_white, OUTPUT);

  pinMode(sonar_pin, INPUT);
  pinMode(bridge_pin, INPUT);

  pinMode(switch_1, INPUT);
  pinMode(switch_2, INPUT);
  pinMode(switch_3, INPUT);

  digitalWrite(switch_1, LOW);
  digitalWrite(switch_2, LOW);
  digitalWrite(switch_3, LOW);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);

  digitalWrite(LED_blue, LOW);
  digitalWrite(LED_red, LOW);
  digitalWrite(LED_yellow, LOW);
  digitalWrite(LED_green, LOW);
  digitalWrite(LED_white, LOW);


  digitalWrite(sonar_pin, LOW);
  digitalWrite(bridge_pin, LOW);

  if (digitalRead(switch_1) && !digitalRead(switch_2) && !digitalRead(switch_3))
  {
    dry_run();
    delay(5000);
  }


  // ..........................................full run................................. ////
  if (!digitalRead(switch_1) && !digitalRead(switch_2) && !digitalRead(switch_3))
  {
    retriveGrid();
    gridCorrectForLowRun();
    while (digitalRead(FR) && digitalRead(FL))
    {
      linefollow();
    }
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    Box_go = gotoNode(1, EEPROM.read(32), north, 0);
    Dir = gotoNode(1, Box_go, north, 1);
    Box_Con = Box_go - EEPROM.read(32);
    switch (Box_Con)
    {
      case (-1):
        Dir = change_Dir(Dir, east);
        break;
      case (4):
        Dir = change_Dir(Dir, south);
        break;
      case (-4):
        Dir = change_Dir(Dir, north);
        break;
      case (1):
        Dir = change_Dir(Dir, west);
        break;
      default:
        Serial.print(Dir);
    }
    delay(25);
    fixposition();

    delay(25);
    box_test();
    /////..........................Grabs BOX............................//////
    Dir = gotoNode(EEPROM.read(32), 8, Dir, 1);
    if (Dir == north)
    {
      turn_right();
    }
    else if (Dir == south)
    {
      turn_left();
    }
    fixposition();
    wheel (0, 0);
    digitalWrite(LED_blue, LOW);
    while (1)
    {

      if (digitalRead(bridge_pin))
      {
        digitalWrite(LED_blue, HIGH);
        break;
      }
    }
    delay(1000);
    while (1)
    {
      if (!digitalRead(bridge_pin))
      {
        digitalWrite(LED_blue, LOW);
        break;
      }
    }
    delay(1000);
    while (1)
    {

      if (digitalRead(bridge_pin))
      {
        digitalWrite(LED_blue, HIGH);
        break;
      }
    }
    delay(1000);
    while (1)
    {
      if (!digitalRead(bridge_pin))
      {
        digitalWrite(LED_blue, LOW);
        break;
      }
    }
    delay(3000);
    while (digitalRead(FR) && digitalRead(FL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    turn_left();


    fixposition();
    base_L = 180;
    base_R = 200;
    int bridge_up = 0;
    while (1)
    {
      linefollow();
      if (!sRead(F0) && !sRead(F1) && !sRead(F2) && !sRead(F3) && !sRead(F4) && !sRead(F5) && !sRead(F6) && !sRead(F7) && !sRead(F8) && !sRead(F9) && !sRead(F10) && !sRead(F11) && !sRead(F12) && !sRead(F13) && !sRead(F14) && !sRead(F15))
      {
        wheel(base_L, base_R);
        delay(500);
        break;
      }
    }
    base_L = 80; base_R = 90;
    while (1)
    {
      linefollow();
      if (!sRead(F0) && !sRead(F1) && !sRead(F2) && !sRead(F3) && !sRead(F4) && !sRead(F5) && !sRead(F6) && !sRead(F7) && !sRead(F8) && !sRead(F9) && !sRead(F10) && !sRead(F11) && !sRead(F12) && !sRead(F13) && !sRead(F14) && !sRead(F15))
      {
        brake();
        break;
      }
    }

    box_deposit();
    base_L = 107;
    base_R = 110;
    while (digitalRead(FR) && digitalRead(FL))
    {
      linefollow();
    }
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    turn_left();
    delay(25);
    fixposition();
    base_L = 80;
    base_R = 90;
    while (1)
    {
      linefollow();
      if (!sRead(F0) && !sRead(F1) && !sRead(F2) && !sRead(F3) && !sRead(F4) && !sRead(F5) && !sRead(F6) && !sRead(F7) && !sRead(F8) && !sRead(F9) && !sRead(F10) && !sRead(F11) && !sRead(F12) && !sRead(F13) && !sRead(F14) && !sRead(F15))
      {
        wheel(base_L, base_R);
        delay(500);
        break;
      }
    }
    while (digitalRead(FR) && digitalRead(FL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(50);
    wheel(0, 0);
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);

    retriveGrid();
    gridCorrectForHighRun();
    base_L = 107;
    base_R = 110;
    if (grid[5][3] == 1)
    {
      turn_right();
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      wheel(-120, -120);
      delay(25);
      wheel(0, 0);
      turn_left();
      fixposition();
    }
    else
    {
      turn_left();
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      wheel(-120, -120);
      delay(25);
      wheel(0, 0);
      //turn_left();
      Dir = gotoNode(20, 28, south, 1);
      Dir = change_Dir(Dir, west);
    }
    digitalWrite(LED_blue, LOW);
    while (1)
    {
      if (!digitalRead(FL) || !digitalRead(FR))
      {
        digitalWrite(LED_blue, HIGH);
        break;
      }
    }
    delay(3000);
    digitalWrite(LED_blue, LOW);
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    fixposition();
    delay(100);
    Dir = gotoNodeOr(27, 29, west, 1);
    wheel(0, 0);
  }
  /////// ............................................... Restart #1..............................   /////////
  if (digitalRead(switch_2) && !digitalRead(switch_1) && !digitalRead(switch_3))
  {
    base.write(UP_ANGLE);
    delay(100);
    left.write(L_OPEN);
    right.write(R_OPEN);
    delay(2000);
    gripcode();
    delay(1500);
    fixposition();
    base_L = 180;
    base_R = 200;
    int bridge_up = 0;
    while (1)
    {
      linefollow();
      if (!sRead(F0) && !sRead(F1) && !sRead(F2) && !sRead(F3) && !sRead(F4) && !sRead(F5) && !sRead(F6) && !sRead(F7) && !sRead(F8) && !sRead(F9) && !sRead(F10) && !sRead(F11) && !sRead(F12) && !sRead(F13) && !sRead(F14) && !sRead(F15))
      {
        wheel(base_L, base_R);
        delay(500);
        break;
      }
    }
    base_L = 80; base_R = 90;
    while (1)
    {
      linefollow();
      if (!sRead(F0) && !sRead(F1) && !sRead(F2) && !sRead(F3) && !sRead(F4) && !sRead(F5) && !sRead(F6) && !sRead(F7) && !sRead(F8) && !sRead(F9) && !sRead(F10) && !sRead(F11) && !sRead(F12) && !sRead(F13) && !sRead(F14) && !sRead(F15))
      {
        brake();
        break;
      }
    }

    box_deposit();
    base_L = 107;
    base_R = 110;
    while (digitalRead(FR) && digitalRead(FL))
    {
      linefollow();
    }
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    turn_left();
    delay(25);
    fixposition();
    base_L = 80;
    base_R = 90;
    while (1)
    {
      linefollow();
      if (!sRead(F0) && !sRead(F1) && !sRead(F2) && !sRead(F3) && !sRead(F4) && !sRead(F5) && !sRead(F6) && !sRead(F7) && !sRead(F8) && !sRead(F9) && !sRead(F10) && !sRead(F11) && !sRead(F12) && !sRead(F13) && !sRead(F14) && !sRead(F15))
      {
        wheel(base_L, base_R);
        delay(500);
        break;
      }
    }
    while (digitalRead(FR) && digitalRead(FL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(50);
    wheel(0, 0);
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);

    retriveGrid();
    gridCorrectForLowRun();
    base_L = 107;
    base_R = 110;
    if (grid[5][3] == 1)
    {
      turn_right();
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      wheel(-120, -120);
      delay(25);
      wheel(0, 0);
      turn_left();
      fixposition();
    }
    else
    {
      turn_left();
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      wheel(-120, -120);
      delay(25);
      wheel(0, 0);
      //turn_left();
      Dir = gotoNode(20, 28, south, 1);
      Dir = change_Dir(Dir, west);
    }
    while (1)
    {
      if (!digitalRead(FL) || !digitalRead(FR)) break;
    }
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    fixposition();
    delay(100);
    Dir = gotoNodeOr(27, 29, west, 1);
    wheel(0, 0);
  }
  //..................................RESTART 2......................................//
  if (digitalRead(switch_3) && !digitalRead(switch_1) && !digitalRead(switch_2))
  {
    base_L = 107;
    base_R = 110;
    if (grid[5][3] == 1)
    {
      turn_right();
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      wheel(-120, -120);
      delay(25);
      wheel(0, 0);
      turn_left();
      fixposition();
    }
    else
    {
      turn_left();
      while (digitalRead(FR) && digitalRead(FL))
      {
        linefollow();
      }
      while (digitalRead(BR) && digitalRead(BL))
      {
        linefollow();
      }
      wheel(-120, -120);
      delay(25);
      wheel(0, 0);
      //turn_left();
      Dir = gotoNode(20, 28, south, 1);
      Dir = change_Dir(Dir, west);
    }
    while (1)
    {
      if (!digitalRead(FL) || !digitalRead(FR)) break;
    }
    while (digitalRead(BR) && digitalRead(BL))
    {
      linefollow();
    }
    wheel(-120, -120);
    delay(25);
    wheel(0, 0);
    fixposition();
    delay(100);
    Dir = gotoNodeOr(27, 29, west, 1);
    wheel(0, 0);
  }
}


void loop()
{
  //Serial.println(digitalRead(bridge_pin));
}

void wheel(int lm, int rm)
{
  if (lm == 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  else if (lm > 0)
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  else if (lm < 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }



  if (rm == 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  else if (rm > 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  else if (rm < 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  if (lm > 254) lm = 254;
  if (lm < -254) lm = -254;
  if (rm > 254) rm = 254;
  if (rm < -254) rm = -254;

  analogWrite(ena, abs(rm));
  analogWrite(enb, abs(lm));

}


void PID_reset()
{
  error = 0;
  previousError = 0;
  totalError = 0;
}


void linefollow()
{
  PID_program();


  if (PWM_Left < -negedge)
  {
    PWM_Left = -negedge;
  }
  else if (PWM_Right < -negedge)
  {
    PWM_Right = -negedge;
  }
  wheel(PWM_Left, PWM_Right);

}


void Mfor ()
{
  wheel (base_L, base_R);
}

void Mback ()
{
  wheel (-base_L, -base_R);
}







// Single Turn Left
void Single_Left()
{
  if (digitalRead(FR) && digitalRead(FL))
  {
    wheel(0, turn_R_Lturn);
    while (sRead(F7) && sRead(F8));
  }
}


