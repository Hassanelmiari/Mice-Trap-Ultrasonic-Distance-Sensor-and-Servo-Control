#include <Servo.h>

#define trigPin 9 // Pin connected to the trigger pin on the ultrasonic sensor
#define echoPin 8 // Pin connected to the echo pin on the ultrasonic sensor
#define servoPin 7 // Pin connected to the servo
#define led 5
#define piezo 6

Servo myServo;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  pinMode(trigPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT); // Set echo pin as input
  myServo.attach(servoPin); // Attach the servo to its pin
}

void loop() {
  long duration, distance;
  
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond pulse to the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // If an object is within 20 cm, move the servo
  if (distance < 20) {
    myServo.write(90); // Move the servo to 90 degrees
    analogWrite(led,HIGH);
    tone(piezo,2000,1500);
  } else {
    myServo.write(0);
    analogWrite(led,LOW);
  }
  
  delay(100); // Wait for 100 milliseconds before the next reading
}
