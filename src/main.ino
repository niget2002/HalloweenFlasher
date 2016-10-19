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
#define dOutput0 2
#define dOutput1 3
#define dOutput2 4

int sleepTime = 500;  //Default sleep time equates to half a second
int maxSleep = 1000;  //Max sleep time = 1 second
int minSleep = 10;   //Min sleep time = 1/10 of a second

int sleepAddress = 0;
int onAddress = 10;
int potAddress = 20;


void outLow();
void outHigh();

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(dOutput0, OUTPUT);
  pinMode(dOutput1, OUTPUT);
  pinMode(dOutput2, OUTPUT);
  pinMode(aInput, INPUT);
  Serial.begin(9600);
  BT.begin(115200);
  Serial.println("Hello");
}

void loop(){
  String t;
  int on;
  EEPROM.get(onAddress,on);
  int sleepTime;
  EEPROM.get(sleepAddress,sleepTime);
  int potOn;
  EEPROM.get(potAddress,potOn);
  Serial.println(on);
  Serial.println(potOn);
  Serial.println(sleepTime);

  while(1){
    if(potOn){
      sleepTime = map(analogRead(aInput), 0, 1023, minSleep, maxSleep);
    }
    if(BT.available()){
      while(BT.available()){
        t += (char)BT.read();
      }
      if(t == "on"){
        on=1;
        Serial.println("LED ON");
        EEPROM.put(onAddress,on);
      }
      if(t == "off"){
        outLow();
        Serial.println("LED Off");
        on=0;
        EEPROM.put(onAddress,on);
      }
      if(t == "po"){
        potOn=1;
        Serial.println("POT On");
        EEPROM.put(potAddress,potOn);
      }
      if(t == "pf"){
        potOn=0;
        Serial.println("POT Off");
        EEPROM.put(potAddress,potOn);
      }
      else {
        sleepTime = t.toInt();
        Serial.println(sleepTime);
        EEPROM.put(sleepAddress,sleepTime);
      }
      t = "";
    }
    if(on){
      outHigh();
      delay(sleepTime);
      outLow();
      delay(sleepTime);
    }
  }
}

void outHigh(){
  digitalWrite(LED, HIGH);
  digitalWrite(dOutput0, HIGH);
  digitalWrite(dOutput1, HIGH);
  digitalWrite(dOutput2, HIGH);
}

void outLow(){
  digitalWrite(LED, LOW);
  digitalWrite(dOutput0, LOW);
  digitalWrite(dOutput1, LOW);
  digitalWrite(dOutput2, LOW);
}
