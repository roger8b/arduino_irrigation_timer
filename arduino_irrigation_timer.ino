// Inputs
#define waterLevel 2

// Outputs
#define sensor 8
#define waterLevelAlarm 9
#define pump 10
#define pumpLed 13


static long previousMillis;
static long minuteAcc;
static long hourAcc;

static long pumpTimeInverval = 3;
static long timePumpOn = 15000;

void setup() {
  pinMode(pump, OUTPUT);
  pinMode(pumpLed, OUTPUT);
  pinMode(waterLevelAlarm, OUTPUT);
  pinMode(waterLevel, INPUT);
}

void loop() {
  minuteCounter();
  hourCounter();
  if (digitalRead(waterLevel) == HIGH) {
    if (hourAcc >= pumpTimeInverval) {
      digitalWrite(pump, HIGH);
      delay(timePumpOn);
      digitalWrite(pump, LOW);
      hourAcc = 0;
    }
    digitalWrite(waterLevelAlarm, LOW);
  } else {
    digitalWrite(pump, LOW);
    digitalWrite(pumpLed, LOW);
    digitalWrite(waterLevelAlarm, HIGH);
    previousMillis = millis();
  }
}

void minuteCounter() {
  if ((millis() - previousMillis) >= 60000) {
    previousMillis = millis();
    minuteAcc = minuteAcc + 1;
    digitalWrite(pumpLed, !digitalRead(pumpLed));

  }
}

void hourCounter() {
  if (minuteAcc >= 60) {
    hourAcc = hourAcc + 1;
    minuteAcc = 0;
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
