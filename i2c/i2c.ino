#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;

int flag = 0;

int board[] = {1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 1, 1, 
               0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0,
               1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 1, 1};

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
  Serial.print("start and finish: ");
  Serial.print(start_index);
  Serial.print(" ");
  Serial.println(finish_index);

  //Call motors

  board[start_index] = 0;
  board[finish_index] = 1;
}

// callback for sending data
void sendData(){
  Serial.print("SEND: ");
  Serial.println(board[flag]);
  Wire.write(board[flag]);
  flag = (flag+1)%64;
}
