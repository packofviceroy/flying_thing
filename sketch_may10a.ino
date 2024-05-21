#include <Servo.h>



byte x;
int y;
Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(A2);
  myservo.writeMicroseconds(2300);
  delay(2000);
  myservo.writeMicroseconds(2000);
  delay(6000);
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse){
  val = constrain(val, lower, upper);
  if ( val < middle ){
    val = map(val, lower, middle, 0, 128);
  }else{
    val = map(val, middle, upper, 128, 255);
  }
  return ( reverse ? 255 - val : val );
} 


void loop() {
  //  x = mapJoystickValues(analogRead(A0), 0, 1023, , false);
   y =  map(analogRead(A1),500,1023,800,2200);
  //  y = mapJoystickValues(analogRead(A1), 500, 1024, 800, 2300);
  //  y = analogRead(A1);
   myservo.write(y);
   x = analogRead(A0);
   
  //  Serial.print("x:");
  //  Serial.print(x);
  //  Serial.print(",");
   Serial.print("y:");
   Serial.println(y);
}
