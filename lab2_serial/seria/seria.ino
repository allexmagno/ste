//int n = 0;
int incomingByte = 0; // for incoming serial data
int led = 13;
int err = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SERIAL_8N1;
  pinMode(led, OUTPUT);
  pinMode(err, OUTPUT);
  
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }*/
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.write(1);
  delay(1000);
  Serial.write(0);
  delay(1000);

}


//incomingByte = Serial.read();
/*
void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if (incomingByte == 1){
     digitalWrite(led, HIGH);
     digitalWrite(err, LOW);
     
    }else if (incomingByte == 0){
      digitalWrite(led,LOW);
    }
  }
  digitalWrite(err, HIGH);

}*/
