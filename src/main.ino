/* HalloweenStrobe
  Bought a little $20 strobe and decided it sucked.
  Decided I could do better.
  Spent $30 on hardware to make white Christmas lights act like a strobe
  */

  #define aInput  A0
  #define LED  13

  int sleepTime = 500;  //Default sleep time equates to half a second
  int maxSleep = 1000;  //Max sleep time = 1 second
  int minSleep = 10;   //Min sleep time = 1/10 of a second

  void setup() {
    pinMode(LED, OUTPUT);
    pinMode(aInput, INPUT);
  }

  void loop(){
    int sleepTime = map(analogRead(aInput), 0, 1023, minSleep, maxSleep);
    digitalWrite(LED, HIGH);
    delay(sleepTime);
    digitalWrite(LED, LOW);
    delay(sleepTime);
  }
