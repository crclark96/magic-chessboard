#include <Stepper.h>
 
// change this to the number of steps on your motor
#define STEPS 200
 
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper1(STEPS, 8, 9, 10, 11);
Stepper stepper2(STEPS, 4, 5, 6, 7);
 
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Stepper test!");
  // set the speed of the motor to 30 RPMs
  stepper1.setSpeed(60);
  stepper2.setSpeed(60);
}
 
void loop()
{
  stepper1.step(STEPS);
  stepper2.step(-STEPS);
  
  stepper1.step(-STEPS);
  stepper2.step(STEPS);
}
