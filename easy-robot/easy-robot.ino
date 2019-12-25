// Include all library for easy-robot 
#include <Ultrasonic.h>

//PINs for HC-SR04
int trig = 6;
int echo = 9;
// PINs for L298N
int in1 = 2;
int in2 = 4;
int in3 = 7;
int in4 = 8;
int ena = 3;
int enb = 5;
// Other variables
bool autoMode = true;
bool bluetooth = true; // ignore, if autoMode == true

//Initialization
Ultrasonic ultrasonic(trig, echo);

void setup(){
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop(){
  if(autoMode){
    int d = checkDist(); // Get distance 
    Serial.println(d);
    if(d >= 20 && d <= 30){ // Back and right 
      setEngine(LOW, HIGH, LOW, HIGH, 255, 255);
      delay(500);
      setEngine(HIGH, LOW, HIGH, LOW, 255, 50);
    }else if(d <= 10){ // Back and right (long)
      setEngine(LOW, HIGH, LOW, HIGH, 255, 255);
      delay(1000);  
      setEngine(HIGH, LOW, HIGH, LOW, 255, 50);
    }else{  // Forward
      Serial.println("FORWARD");
      setEngine(HIGH, LOW, HIGH, LOW, 255, 255);
    }
  }else{
    if(bluetooth){
      while(Serial.available() > 0){
        char command = Serial.read();
        Serial.println(command);
        if(command == 'f'){
          setEngine(HIGH, LOW, HIGH, LOW, 255, 255);
        }else if(command == 'b'){
          setEngine(LOW, HIGH, LOW, HIGH, 255, 255);
        }else if(command == 'l'){
          setEngine(HIGH, LOW, HIGH, LOW, 255, 150);
        }else if(command == 'r'){
          setEngine(HIGH, LOW, HIGH, LOW, 150, 255);
        }else if(command == 's'){
          setEngine(HIGH, LOW, HIGH, LOW, 0, 0);
        }
      }
    }else{ // radio
      // None
    }
  }
}

int checkDist(){
  return ultrasonic.read();
}
void setEngine(int n1, int n2, int n3, int n4, int s1, int s2){
  digitalWrite(in1, n1);
  digitalWrite(in2, n2);
  digitalWrite(in3, n3);
  digitalWrite(in4, n4);
  analogWrite(ena, s1);
  analogWrite(enb, s2);
}
