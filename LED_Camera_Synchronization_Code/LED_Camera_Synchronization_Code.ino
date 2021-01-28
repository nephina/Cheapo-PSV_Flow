#include <SPI.h>


long deltaT_between_flashes = 10000;

// pins for the mosfet gates for each LED color
int red_led = 0;
int green_led = 1;
int blue_led = 3;

// digital potentiometer stuff
byte address = 0x00;
int CS= 10;

void setup() {
  pinMode(red_led,OUTPUT);
  pinMode(green_led,OUTPUT);
  pinMode(blue_led,OUTPUT);
  pinMode (CS, OUTPUT);
  //digitalPotWrite(255);
  SPI.begin();
}

void loop() {

  // Phone camera is triggered with "volume down" keypress
  // which is initiated by a resistance change from mic to gnd
  // to a specific ohm value. We acheive this by setting a
  // digital potentiometer to that resistance for a bit, then
  // turning the resistance back up to max
  digitalPotWrite(2); // Signal the phone camera to take a picture
  delay(100); // The phone won't recognize very very short clicks
  digitalPotWrite(255); 

  // Wait for the phone to begin capturing
  delay(600);

  // Flash red, then green, then blue leds
  digitalWrite(red_led,HIGH);
  delayMicroseconds(0.05*deltaT_between_flashes);
  digitalWrite(red_led,LOW);
  delayMicroseconds(0.95*deltaT_between_flashes);
  digitalWrite(green_led,HIGH);
  delayMicroseconds(0.05*deltaT_between_flashes);
  digitalWrite(green_led,LOW);
  delayMicroseconds(0.95*deltaT_between_flashes);
  digitalWrite(blue_led,HIGH);
  delayMicroseconds(0.05*deltaT_between_flashes);
  digitalWrite(blue_led,LOW);
  delayMicroseconds(0.95*deltaT_between_flashes);

  // Give the camera time to save the file to drive
  delay(3000);
}

int digitalPotWrite(int value) {
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
