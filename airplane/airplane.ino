#include <Servo.h>
#include <RF24.h>
#include "nRF24L01.h"

byte x;
int y;
Servo motor;
RF24 radio(9,10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

void setup() {
   //INIT MOTOR
  motor.attach(A2);
  motor.writeMicroseconds(2300);
  delay(2000);
  myservo.writeMicroseconds(2000);
  delay(6000);

  // INIT RADIO
  radio.begin();
  delay(3000);
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate (RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  radio.startListening();

 

  //INIT SERVO
}

struct Plane{
  uint16_t throttle;    // Газ
  uint16_t roll;        // Крен
  uint16_t pitch;       // Тангаж
  uint16_t yaw;         // Рысканье
}
Plane plane;


void loop() {
  while(radio.available()){
    radio.read(&plane, sizeof(plane));
  }
   motor.write(plane.throttle);
  

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