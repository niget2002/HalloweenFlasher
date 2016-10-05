/* HalloweenStrobe
  Bought a little $20 strobe and decided it sucked.
  Decided I could do better.
  Spent $30 on hardware to make white Christmas lights act like a strobe
  */

  #define aInput  A0
  #define dOutput 02
  #define LED  13

  int sleepTime = 500;  //Default sleep time equates to half a second
  int maxSleep = 1000;  //Max sleep time = 1 second
  int minSleep = 100;   //Min sleep time = 1/10 of a second
  int maxVoltage = 5;   //vRef
  int minVoltage = 0;   //Gnd

  void calSleep();
  void high();
  void low();

  void setup() {
    pinMode(LED, OUTPUT);
    pinMode(dOutput, OUTPUT);
    pinMode(aInput, INPUT);
  }

  void loop(){
    calSleep();
    high();
    delay(sleepTime);
    low();
    delay(sleepTime);
  }

  void calSleep(){    //Calculate sleep time based on analog input, max, and min values
    float voltage = analogRead(aInput);
    sleepTime=((maxSleep-minSleep)/(maxVoltage-minVoltage))*voltage+minSleep; //this assumes minVoltage is Gnd
  }

  void high(){
    digitalWrite(LED, HIGH);
    digitalWrite(dOutput, HIGH);
  }

  void low(){
    digitalWrite(LED, LOW);
    digitalWrite(dOutput, LOW);
  }
