#include <Wire.h>

#define SLAVE_ADDRESS 0x04

int flag = 0;

int start1_pin = 5;
int finish1_pin = 6;
int start1_ind = 6;
int finish1_ind = 23;

int start2_pin = 7;
int finish2_pin = 8;
int start2_ind = 10;
int finish2_ind = 18;

int board[] = {1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 1, 1, 
               0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0,
               1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 1, 1, 1, 1};

int number = 0;
int state = 0;

typedef struct{
  int start;
  int finish;
} tuple;

//Delete after BS
tuple moves[] = {
    {11, 19},
    {2, 38}
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
  delay(100);
}

void printBoard(){
  for(int i = 0; i < 64; i++){
    if ((i!=0) && (i%8 == 0)){
      Serial.print("\n");
    }
    Serial.print(board[i]);
  }
  Serial.println();
}

// callback for received data
void receiveData(int byteCount){
  int counter = 0;
  int start_index = 0;
  int finish_index = 0;
  while(Wire.available()) {
    number = Wire.read();
    if (counter == 1){
      start_index = number;
    }else if (counter == 2){
      finish_index = number;
    }
    counter++;
  }
  if (counter > 1){
    Serial.print("RECEIVED: start ");
    Serial.print(start_index);
    Serial.print(" finish ");
    Serial.println(finish_index);
    board[start_index] = 0;
    board[finish_index] = 1;
  
    //Call motors
  
    Serial.println("RECEIVE");
    printBoard();
  }
}

// callback for sending data
void sendData(){
 Wire.write(1);
 flag = (flag+1)%64;
  
  //board[start1_ind] = (byte)(digitalRead(start1_pin)+1)%2;
  //board[finish1_ind] = (byte)(digitalRead(finish1_pin)+1)%2;
  
  //board[start2_ind] = (byte)(digitalRead(start2_pin)+1)%2;
  //board[finish2_ind] = (byte)(digitalRead(finish2_pin)+1)%2;
 
 //board[moves[turn].start] = 0;
 //board[moves[turn].finish] = 1;
  
 //turn++;

 Serial.println("SEND");
 printBoard();
}
