#include <Servo.h>

// servo object
Servo servo;

// pins
#define SENSOR_TRIG 8
#define SENSOR_ECHO 12
#define VOLUME 0
#define SERVO 9

void setup() {
  Serial.begin(9600);

  // setup pins
  pinMode(SENSOR_TRIG, OUTPUT);
  pinMode(SENSOR_ECHO, INPUT);
  servo.attach(SERVO);

  // set initial value
  digitalWrite(SENSOR_TRIG,LOW);
  digitalWrite(SENSOR_ECHO,LOW);
  servo.write(0);
}

void loop() {
  // start emitting ultra sound
  digitalWrite(SENSOR_TRIG, LOW);
  delayMicroseconds(1);
  digitalWrite(SENSOR_TRIG, HIGH);
  delayMicroseconds(11);

  // stop emitting ultra sound
  digitalWrite(SENSOR_TRIG, LOW);

  // measure echo time and calculate distance
  int t = pulseIn(SENSOR_ECHO, HIGH, 60000);
  float distance = t * 0.017;

  // output distance for debug
  Serial.print(distance);
  Serial.println(" cm");

  // if proximity detected, operate servo
  if (distance > 0 && distance < 10) {
    // get volume ratio
    float volumeRatio = analogRead(VOLUME) / 1024.0;
    // output volume ratio for debug
    Serial.print("volume ratio: ");
    Serial.println(volumeRatio);

    // play sound
    tone(10, 2093, 50);
    delay(100);
    tone(10, 2093, 500);

    // wait user moving hands to sanitizer
    delay(1000);

    // move servo depending on volume
    servo.write(180.0 * volumeRatio);
    // wait serve to get there
    delay(500);
    // move servo to initial position
    servo.write(0);
    // wait serve to get there
    delay(500);
  }

  // ultra sound sensor needs some delay for repeating sensing
  delay(100);
}
