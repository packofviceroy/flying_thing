#include <Servo.h>
#include <RF24.h>
#include "nRF24L01.h"

byte x;
int y;
RF24 radio(9,10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

void setup() {
  Serial.begin(9600);
  // INIT RADIO
  radio.begin();
  delay(3000);
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  radio.openWritingPipe(address[0]);
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  if (radio.write("123",3)){
    Serial.write("Successfully connected");
  }else{
    Serial.write("Not connected !");
  }
    
  radio.setPayloadSize(sizeof(Plane));
  radio.openWritingPipe();

}
struct Plane{
  uint16_t throttle;    // Газ
  uint16_t roll;        // Крен
  uint16_t pitch;       // Тангаж
  uint16_t yaw;         // Рысканье
}
Plane plane;

void loop() {
    plane.throttle = constrain(map(analogRead(A1),500,1023,800,2200),800,2250);
    plane.roll = 0;
    plane.pitch = 0;
    plane.yaw = 0;
    radio.write(plane, sizeof(Plane));
    Serial.print("throttle:");
    Serial.println(plane.throttle);
}