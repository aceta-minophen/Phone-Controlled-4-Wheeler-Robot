#include <Wire.h>

//motors
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

int speed9 = 40;
int speed10 = 40;

int slider;
int valx;
int valy;

void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  analogWrite(9,speed9); //left
  analogWrite(10, speed10);//Right

  //anticlockwise
  digitalWrite(motor1pin1, HIGH); //right motor going front
  digitalWrite(motor1pin2, LOW); //right motor going front
  digitalWrite(motor2pin1, LOW); //left motor going front
  digitalWrite(motor2pin2, HIGH); //left motor going front

  /*temporary setup code*/
  analogWrite(9, 60);
  analogWrite(10, 60);
}

void loop() {

}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    byte low = Wire.read();
    byte high = Wire.read();
    int val = word(high, low);
    
    
    if(val>200 && val<=400){
      //Serial.print("Y: ");
      valy = 400 - val;
      //Serial.println(valy);
      if(valy<=100){
        digitalWrite(motor1pin1, HIGH); //right motor going front
        digitalWrite(motor1pin2, LOW); //right motor going front
        digitalWrite(motor2pin1, LOW); //left motor going front
        digitalWrite(motor2pin2, HIGH); //left motor going front
        Serial.print("Moving Forward");
       
      }
      else if(valy>100){
        digitalWrite(motor1pin1, LOW); //right motor going front
        digitalWrite(motor1pin2, HIGH); //right motor going front
        digitalWrite(motor2pin1, HIGH); //left motor going front
        digitalWrite(motor2pin2, LOW); //left motor going front
        Serial.print("Moving Backward");
      }
    }
    if(val>1000){
      //Serial.print("Speed: ");
      slider = val - 1000;
      speed10 = slider/5;
      speed9 = slider/5;
      //Serial.println(slider);
      analogWrite(10, speed10);//right
      analogWrite(9, speed9);//left
      Serial.print("Left speed: ");
      Serial.println(speed9);
      Serial.print("Right speed: ");
      Serial.println(speed10);
    }
    if(val<=200){
      //Serial.print("X: ");
      valx = 200-val;
      //Serial.println(valx);
      if(valx<100){
        speed9 = speed9 - ((100-valx)/10);
        speed10 = speed10 + ((100-valx)/10);
        analogWrite(9, speed9);
        analogWrite(10, speed10);
        if(speed9<0){
          speed9 = 0;
          speed10 = 100;
          analogWrite(9, speed9);
          analogWrite(10, speed10);
        }
        Serial.print("Left speed: ");
        Serial.println(speed9);
        Serial.print("Right speed: ");
        Serial.println(speed10);
      }
      else if(valx>100){
        speed9 = speed9 + ((valx-100)/10);
        speed10 = speed10 - ((valx-100)/10);
        analogWrite(9, speed9);
        analogWrite(10, speed10);
        if(speed10<0){
          speed9 = 100;
          speed10 = 0;
          analogWrite(9, speed9);
          analogWrite(10, speed10);
        }
        Serial.print("Left speed: ");
        Serial.println(speed9);
        Serial.print("Right speed: ");
        Serial.println(speed10);
      }
      else if(valx==100){
        speed9 = 40;
        speed10 = 40;
        analogWrite(9, speed9);
        analogWrite(10, speed10);
        Serial.print("Left speed: ");
        Serial.println(speed9);
        Serial.print("Right speed: ");
        Serial.println(speed10);
      }
    }
 Serial.println();             /* to newline */
}
}
