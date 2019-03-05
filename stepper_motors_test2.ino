#include <Stepper.h>

#define STEP 100

Stepper s1(STEP, 8, 9, 10, 11);
Stepper s2(STEP, 4, 5, 6, 7);

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
  Serial.println("Stepper test!");
  // set the speed of the motor to 30 RPMs
  s1.setSpeed(60);
  s2.setSpeed(60);
}

void loop() {
  for (int i = 0; i < (sizeof(testArray) / sizeof(testArray[0])); i++){
    moveMotors(testArray[i]);
  }
}

void moveMotors(tuple t){
  start_x = t.start % 8
  start_y = (int) t.start / 8

  finish_x = t.finish % 8
  finish.y = (int) t.finish / 8  
  
  s1.step(STEP * start_x);
  s2.step(STEP * start_y);

  //Activate magnet

  s1.step(STEP * (finish_x - start_x ));
  s2.step(STEP * (finish_y - start_y));

  //Deactivate magnet
  
  s1.step(-STEP * finish_x);
  s2.step(-STEP * finish_y);
}
