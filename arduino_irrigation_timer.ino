// Inputs
#define waterLevel 2

// Outputs
#define sensor 8
#define waterLevelAlarm 9
#define pump 10
#define pumpLed 13

long min = 0;
long hour = 0;


static long previousMillis;

void setup() {
  pinMode(pump, OUTPUT);
  pinMode(pumpLed, OUTPUT);
  pinMode(waterLevelAlarm, OUTPUT);
  pinMode(waterLevel, INPUT);
}

void loop() {
  if (digitalRead(waterLevel) == HIGH) {
    //OnOffBlink(15000, 14400000); //OnOffBlink(tOn, tOff);
    OnOffBlink(10000, 30000); //OnOffBlink(tOn, tOff);
    digitalWrite(waterLevelAlarm, LOW);
  } else {
    digitalWrite(pump, LOW);
    digitalWrite(pumpLed, LOW);
    digitalWrite(waterLevelAlarm, HIGH);
    previousMillis = millis();
  }
}

void OnOffBlink(long tOn, long tOff) {

  static int timer = tOn;

  if ((millis() - previousMillis) >= timer) {

    if (digitalRead(pump) == HIGH ) {
      timer = tOff;
    } else {
      timer = tOn;
    }
    digitalWrite(pump, !digitalRead(pump));
    digitalWrite(pumpLed, !digitalRead(pumpLed));
    previousMillis = millis();
  }

}
