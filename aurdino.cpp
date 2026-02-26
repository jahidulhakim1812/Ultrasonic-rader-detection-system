#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int buzzer = 8;
const int led = 9;
const int servoPin = 12;

long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  // Sweep from 15 to 165 degrees
  for(int i=15; i<=165; i++){  
    rotateAndScan(i);
  }
  // Sweep back
  for(int i=165; i>15; i--){  
    rotateAndScan(i);
  }
}

void rotateAndScan(int angle) {
  myServo.write(angle); // Move physical servo
  delay(30);            // Give servo time to reach position
  
  // Calculate distance
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // 5-inch Alert (13 cm)
  if (distance > 0 && distance < 13) {
    digitalWrite(led, HIGH);
    tone(buzzer, 1000); 
  } else {
    digitalWrite(led, LOW);
    noTone(buzzer);
  }

  // Send angle to Processing to rotate the visual line
  Serial.print(angle); 
  Serial.print(","); 
  Serial.print(distance); 
  Serial.print("."); 
}