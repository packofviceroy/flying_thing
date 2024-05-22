#include <Servo.h>
#include <RF24.h>
#include "nRF24L01.h"

byte x;
int y;
Servo motor;
RF24 radio(9,10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб
struct Plane{
  uint16_t throttle;    // Газ
  uint16_t roll;        // Крен
  uint16_t pitch;       // Тангаж
  uint16_t yaw;         // Рысканье
};
Plane plane;


void setup() {
  Serial.begin(9600);
   //INIT MOTOR
  motor.attach(A2);
  motor.writeMicroseconds(2300);
  delay(2000);
  motor.writeMicroseconds(800);
  delay(6000);
  motor.writeMicroseconds(800);

  // INIT RADIO
  radio.begin();
  delay(3000);
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setRetries(10, 30);    // (время между попыткой достучаться, число попыток)
  radio.setPayloadSize(sizeof(Plane));
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate (RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  radio.openReadingPipe(1, address[0]);   // хотим слушать трубу 0
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  radio.startListening();
  //INIT SERVO
}




void loop() {
  while(radio.available()){
    radio.read(&plane, sizeof(plane));
    Serial.print("throttle:");
    Serial.println(plane.throttle);
    // Serial.print("roll:");
    // Serial.println(plane.roll);
    // Serial.print("pitch:");
    // Serial.println(plane.pitch);
    // Serial.print("yaw:");
    // Serial.println(plane.yaw);
  }
  if (plane.throttle <= 2250 || plane.throttle >= 800)
    motor.write(plane.throttle);
  delay(100);
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