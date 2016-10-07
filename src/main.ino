/* HalloweenStrobe
  Bought a little $20 strobe and decided it sucked.
  Decided I could do better.
  Spent $30 on hardware to make white Christmas lights act like a strobe
  */

  #include <SoftwareSerial.h>

  SoftwareSerial BT(10,11);

  #define aInput  A0
  #define LED  13
  #define dOutput 8

  int sleepTime = 500;  //Default sleep time equates to half a second
  int maxSleep = 1000;  //Max sleep time = 1 second
  int minSleep = 10;   //Min sleep time = 1/10 of a second

  void outLow();
  void outHigh();

  void setup() {
    pinMode(LED, OUTPUT);
    pinMode(dOutput, OUTPUT);
    pinMode(aInput, INPUT);
    Serial.begin(9600);
    BT.begin(9600);
  }

  void loop(){

    String t;
    int on=1;
    int sleepTime=1000;
    int potOn=1;

    if(potOn){
      sleepTime = map(analogRead(aInput), 0, 1023, minSleep, maxSleep);
    }
    if(BT.available()){
      while(BT.available() > 0){
        t += (char)BT.read();
      }
      if(t == "on"){
        on=1;
      }
      if(t == "off"){
        outLow();
        on=0;
      }
      if(t == "potOn"){
        potOn=1;
      }
      if(t == "potOff"){
        potOn=0;
      }
      else {
        sleepTime = t.toInt();
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

  void outHigh(){
    digitalWrite(LED, HIGH);
    digitalWrite(dOutput, HIGH);
  }

  void outLow(){
    digitalWrite(LED, LOW);
    digitalWrite(dOutput, LOW);
  }
