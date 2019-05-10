#include <Wire.h>

#define SLAVE_ADDRESS 0x04

bool flag = true;

int start1_pin = 5;
int finish1_pin = 6;
int start1_ind = 6;
int finish1_ind = 23;

int start2_pin = 7;
int finish2_pin = 8;
int start2_ind = 10;
int finish2_ind = 18;

byte board[] = {1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 1, 1, 
               0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0,
               1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 1, 1};

int number = 0;
int state = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  Serial.println("Ready!");
}

void loop() {
  delay(100);
}

// callback for received data
void receiveData(int byteCount){
  int counter = 0;
  int start_index = 0;
  int finish_index = 0;
  while(Wire.available()) {
    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);

    if (counter == 1){
      start_index = number;
    }else if (counter == 2){
      finish_index = number;
    }
    counter++;
  }

  //Call motors
}

// callback for sending data
void sendData(){

  board[start1_ind] = (byte)(digitalRead(start1_pin)+1)%2;
  board[finish1_ind] = (byte)(digitalRead(finish1_pin)+1)%2;

  board[start2_ind] = (byte)(digitalRead(start2_pin)+1)%2;
  board[finish2_ind] = (byte)(digitalRead(finish2_pin)+1)%2;

 
 if (flag){
   for(int i = 0; i < 32; i++){
    Wire.write(board[i]);
   }
 }else{
   for(int i = 32; i < 64; i++){
    Wire.write(board[i]);
   }
 }

 flag = !flag;
}
