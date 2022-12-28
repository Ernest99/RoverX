#include <AFMotor.h>

//motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


//ultrasonic sensors
//middle
#define midTrig A1
#define midEcho A0

//left
#define leftTrig A5
#define leftEcho A4

//right
#define rightTrig A3
#define rightEcho A2




void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Moving Motors");
  pinMode(midTrig, OUTPUT); // middle ultrasonic
  pinMode(midEcho, INPUT); // middle ultrasonic
  pinMode(leftTrig, OUTPUT); // left ultrasonic
  pinMode(leftEcho, INPUT); // left ultrasonic
  pinMode(rightTrig, OUTPUT); // right ultrasonic
  pinMode(rightEcho, INPUT); // right ultrasonic
}


void loop() {



  //Middle Ultrasonic
  long duration, distance;
  digitalWrite(midTrig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(midTrig, LOW);
  duration = pulseIn(midEcho, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print(distance);
  Serial.println(" CM");
  delay(10);

  //left Ultrasonic
  long left_duration, left_distance;
  digitalWrite(leftTrig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(leftTrig, LOW);
  left_duration = pulseIn(leftEcho, HIGH);
  left_distance = (left_duration / 2) / 29.1;
  Serial.print(left_distance);
  Serial.println(" CM Left");
  delay(10);


  //right Ultrasonic
  long right_duration, right_distance;
  digitalWrite(rightTrig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(rightTrig, LOW);
  right_duration = pulseIn(rightEcho, HIGH);
  right_distance = (right_duration / 2) / 29.1;
  Serial.print(right_distance);
  Serial.println(" CM Right");
  delay(10);

  motor1.setSpeed(speed(25)); //set speed for motor 1 at 50%
  motor2.setSpeed(speed (25));
  motor3.setSpeed(speed (25));
  motor4.setSpeed(speed (25));
  motor1.run(FORWARD); // first motor
  motor2.run(FORWARD); // second motor
  motor3.run(FORWARD); // third motor
  motor4.run(FORWARD); // fourth motor


  if (left_distance < 20) {

    motor1.run(FORWARD); //first motor
    motor2.run(FORWARD); // second motor
    motor3.run(BACKWARD); // third motor
    motor4.run(BACKWARD); //fourth motor

  }
  else if (right_distance < 20) {

    motor1.run(BACKWARD); //first motor
    motor2.run(BACKWARD); // second motor
    motor3.run(FORWARD); // third motor
    motor4.run(FORWARD); //fourth motor

  }

  else if (distance < 30) {

    motor1.run(BACKWARD); //first motor
    motor2.run(BACKWARD); // second motor
    motor3.run(BACKWARD); // third motor
    motor4.run(BACKWARD); //fourth motor
     delay(500);
    motor1.run(BACKWARD); //first motor
    motor2.run(BACKWARD); // second motor
    motor3.run(FORWARD); // third motor
    motor4.run(FORWARD); //fourth motor
    motor1.run(FORWARD); //first motor
    motor2.run(FORWARD); // second motor
    motor3.run(BACKWARD); // third motor
    motor4.run(BACKWARD); //fourth motor
    if (right_distance < 20) {
      motor1.run(BACKWARD); //first motor
      motor2.run(BACKWARD); // second motor
      motor3.run(FORWARD); // third motor
      motor4.run(FORWARD); //fourth motor

    }
    else if (left_distance < 20) {

      motor1.run(FORWARD); //first motor
      motor2.run(FORWARD); // second motor
      motor3.run(BACKWARD); // third motor
      motor4.run(BACKWARD); //fourth motor

    }

  }

  else {
    motor1.run(FORWARD); //first motor
    motor2.run(FORWARD); // second motor
    motor3.run(FORWARD); // third motor
    motor4.run(FORWARD); //fourth motor
  }


}



int  speed(int percent)
{
  return map(percent, 0, 100, 0, 255);
}
