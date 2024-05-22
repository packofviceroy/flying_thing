#include <Servo.h>
#include <RF24.h>
#include "nRF24L01.h"

byte x;
int y;
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
  // INIT RADIO
  radio.begin();
  delay(3000);
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(10, 30);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate (RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS

  radio.stopListening();
  radio.openWritingPipe(address[0]);
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  if (radio.write(&plane,sizeof(Plane))){
    Serial.println("Successfully connected");
    delay(3000);
  }else{
    Serial.println("Not connected !");
    delay(5000);
  }
    
  radio.setPayloadSize(sizeof(Plane));
  radio.openWritingPipe(address[0]);

}

void loop() {
    // plane.throttle = constrain(map(analogRead(A1),525,1023,800,2250),800,2250);
    plane.throttle = analogRead(A0);
    plane.roll = 0;
    plane.pitch = 0;
    plane.yaw = 0;
    // radio.write(&plane, sizeof(Plane));
    Serial.print("throttle:");
    Serial.println(plane.throttle);
    delay(100);
    
}