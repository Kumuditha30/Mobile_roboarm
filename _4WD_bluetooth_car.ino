#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(2, 3); // RX | TX 
Servo servo1, servo2, servo3, servo4; 

// Motor driver pins
int leftForward  = 13;
int leftBackward = 12;
int rightForward = 11;
int rightBackward = 10;

// Servo positions
int angle1 = 90;
int angle2 = 90;
int angle3 = 90;
int angle4 = 90;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Bluetooth Car + 4 Servo Control Ready!");

  // Motor pin setup 
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  // Servo setup
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);

  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);
}

void loop() {
  if (mySerial.available()) {
    char command = mySerial.read();
    Serial.print("Received: ");
    Serial.println(command);

    // ------------------ CAR CONTROL ------------------
    if (command == 'R') { // Forward
      Serial.println("Forward");
      digitalWrite(leftForward, HIGH);
      digitalWrite(leftBackward, LOW);
      digitalWrite(rightForward, LOW);
      digitalWrite(rightBackward, HIGH);
    }
    else if (command == 'Q') { // Reverse
      Serial.println("Reverse");
      digitalWrite(leftForward, LOW);
      digitalWrite(leftBackward, HIGH);
      digitalWrite(rightForward, HIGH);
      digitalWrite(rightBackward, LOW);
    }
    else if (command == 'O') { // Left
      Serial.println("Left");
      digitalWrite(leftForward, LOW);
      digitalWrite(leftBackward, HIGH);
      digitalWrite(rightForward, LOW);
      digitalWrite(rightBackward, HIGH);
    }
    else if (command == 'P') { // Right
      Serial.println("Right");
      digitalWrite(leftForward, HIGH);
      digitalWrite(leftBackward, LOW);
      digitalWrite(rightForward, HIGH);
      digitalWrite(rightBackward, LOW);
    }
     else if (command == 'S') { // Stop
      Serial.println("Stop");
      digitalWrite(leftForward, LOW);
      digitalWrite(leftBackward, LOW);
      digitalWrite(rightForward, LOW);
      digitalWrite(rightBackward, LOW);
    }

    // ------------------ SERVO 1 CONTROL ------------------
    else if (command == 'A') { angle1 -= 5; }
    else if (command == 'B') { angle1 += 5; }
 

    // ------------------ SERVO 2 CONTROL ------------------
    else if (command == 'C') { angle2 -= 5; }
    else if (command == 'D') { angle2 += 5; }
  
    // ------------------ SERVO 3 CONTROL ------------------
    else if (command == 'E') { angle3 -= 5; }
    else if (command == 'F') { angle3 += 5; }


    // ------------------ SERVO 4 CONTROL ------------------
    else if (command == 'G') { angle4 -= 5; }
    else if (command == 'H') { angle4 += 5; }


    // Constrain and update servos
    angle1 = constrain(angle1, 0, 180);
    angle2 = constrain(angle2, 0, 180);
    angle3 = constrain(angle3, 0, 180);
    angle4 = constrain(angle4, 0, 180);

    servo1.write(angle1);
    servo2.write(angle2);
    servo3.write(angle3);
    servo4.write(angle4);

    delay(50); // smooth update
 
 
}
}
