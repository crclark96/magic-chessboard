#include <Stepper.h>

#define STEP 100
#define E_MAGNET_PIN 2

Stepper s1(STEP, 4, 5, 6, 7);
Stepper s2(STEP, 8, 9, 10, 11);

typedef struct{
  int start;
  int finish;
} tuple;

tuple testArray[4] = {
  {0, 25},
  {23, 60},
  {45, 11},
  {54, 8}
};

void setup() {
  Serial.begin(9600);
  // set the speed of the motor to 30 RPMs
  s1.setSpeed(60);
  s2.setSpeed(60);
  pinMode(E_MAGNET_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < (sizeof(testArray) / sizeof(testArray[0])); i++){
    moveMotors(testArray[i]);
  }
}

/* 
The board is represented like this...

8  | 56 57 58 59 60 61 62 63
7  | 48 49 50 51 52 53 54 55
6  | 40 41 42 43 44 45 46 47
5  | 32 33 34 35 36 37 38 39
4  | 24 25 26 27 28 29 30 31
3  | 16 17 18 19 20 21 22 23
2  | 08 09 10 11 12 13 14 15
1  | 00 01 02 03 04 05 06 07
   +------------------------
      a  b  c  d  e  f  g  h
      
*/


void moveMotors(tuple t){
  int start_x = t.start % 8;
  int start_y = (int) t.start / 8;

  int finish_x = t.finish % 8;
  int finish_y = (int) t.finish / 8;

  Serial.print("Moving x_axis to ");
  Serial.println(t.start);
  s1.step(STEP * start_x);
  Serial.print("Moving y_axis to ");
  Serial.println(t.start);
  s2.step(STEP * start_y);

  digitalWrite(E_MAGNET_PIN, HIGH);

  Serial.print("Moving x_axis to ");
  Serial.println(t.finish);
  s1.step(STEP * (finish_x - start_x ));
  Serial.print("Moving y_axis to ");
  Serial.println(t.finish);
  s2.step(STEP * (finish_y - start_y));

  digitalWrite(E_MAGNET_PIN, LOW);
  
  s1.step(-STEP * finish_x);
  s2.step(-STEP * finish_y);
}
