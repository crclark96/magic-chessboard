void setup() {
  Serial.begin(9600);
}

void loop() {
  int hall1 = analogRead(0);
  int hall2 = analogRead(1);

  if (hall1 == 0){
    Serial.print("AHH! A magnet!");
  }else{
    Serial.print("Phew, no magnets.");
  }
  Serial.print("\t\t\t");
  if (hall2 == 0){
    Serial.println("AHH! A magnet!");
  }else{
    Serial.println("Phew, no magnets.");
  }
}
