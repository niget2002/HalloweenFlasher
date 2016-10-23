/* HalloweenStrobe
Bought a little $20 strobe and decided it sucked.
Decided I could do better.
Spent $30 on hardware to make white Christmas lights act like a strobe
*/
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial BT(10,11);

#define aInput  A0
#define LED  13

int dOutput[3] = {2, 3, 4};
int sleepTime[3] = {100, 500, 500};  //Default sleep time equates to half a second
int onTime[3] = {100, 500, 500};
int maxSleep = 1000;  //Max sleep time = 1 second
int minSleep = 10;   //Min sleep time = 1/10 of a second

int sleepAddress = 0;
int onAddress = 10;
int potAddress = 20;
unsigned long previousMillis[3] = {0, 0, 0};

void flicker();

void setup() {
  pinMode(dOutput[0], OUTPUT);
  pinMode(dOutput[1], OUTPUT);
  pinMode(dOutput[2], OUTPUT);
  pinMode(aInput, INPUT);
  Serial.begin(9600);
  BT.begin(115200);
  Serial.println("Hello");
}

void loop(){
  String t;
  int i;
  unsigned long currentMillis = 0;

  while(1){
    currentMillis = millis();
    for(i=0; i <= 3; i++){
      if(!digitalRead(dOutput[i])){
        if(currentMillis - previousMillis[i] >= sleepTime[i]){
          digitalWrite(dOutput[i], HIGH);
          previousMillis[i] = currentMillis;
        }
      } else {
        if(currentMillis - previousMillis[i] >= onTime[i]){
          digitalWrite(dOutput[i], LOW);
          previousMillis[i] = currentMillis;
          if(i==1){
            flicker();
          }
        }
      }
    }
  }
}

void flicker(){
  sleepTime[1]=500;
  onTime[1]=random(3000,20000);
  Serial.println(onTime[1]);
}
