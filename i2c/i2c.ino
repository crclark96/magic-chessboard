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
struct tuple{
  int start;
  int finish;
};

typedef struct tuple Tuple;

Tuple moves[] = {
  {12, 28},
  {5, 26},
  {1, 16},
  {15, 23}  
};
int turn = 0;

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
  delay(50);
}

void printBoard(){
  for(int i = 56; i >= 0; i-=8){
    for(int j = 0; j < 8; j++){
      Serial.print(board[i+j]);
    }
    Serial.println();
  }
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

  board[start_index] = 0;
  board[finish_index] = 1;
}

// callback for sending data
void sendData(){  

  if (flag == 0){
    //printBoard();
    board[moves[turn].start] = 0;    
    board[moves[turn].finish] = 1;
    Serial.print("moving from: ");
    Serial.print(moves[turn].start);
    Serial.print(" to: ");
    Serial.println(moves[turn].finish);
    turn++;    
  } 
  
  Wire.write(board[flag]);
  flag = (flag+1)%64;
}
