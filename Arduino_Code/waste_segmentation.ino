#include <Servo.h>

#define IR_SENSOR 5
#define METAL_SENSOR 6
#define MOISTURE_SENSOR A0

Servo binServo;

int dryCount = 0;
int wetCount = 0;
int metalCount = 0;

void setup() {
  Serial.begin(9600);

  pinMode(IR_SENSOR, INPUT);
  pinMode(METAL_SENSOR, INPUT);

  binServo.attach(3);
}

void loop() {

  if (digitalRead(IR_SENSOR) == LOW) {

    if (digitalRead(METAL_SENSOR) == LOW) {
      metalCount++;
      binServo.write(120);
    }
    else {
      int moisture = analogRead(MOISTURE_SENSOR);

      if (moisture > 500) {
        wetCount++;
        binServo.write(60);
      }
      else {
        dryCount++;
        binServo.write(0);
      }
    }

    Serial.print("DRY:");
    Serial.print(dryCount);
    Serial.print(",WET:");
    Serial.print(wetCount);
    Serial.print(",METAL:");
    Serial.println(metalCount);

    delay(2000);
  }
}
