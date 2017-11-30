#define trigPin1 3 //right edge detection
#define echoPin1 24 
#define trigPin2 11 //left edge detection
#define echoPin2 25
#define trigPin3 45
#define echoPin3 26
#define trigPin4 46
#define echoPin4 27
#define tapeSenseRight 44 // ir sensors
#define tapeSenseLeft 10

#define flameSense A0
#define fan 12

#define motorRForward 4
#define motorRBackward 5
#define motorLPower 6
#define motorLBackward 7
#define motorLForward 8
#define motorRPower 9

long leftEdgeSonarSensor, rightEdgeSonarSensor;

void setup() {
  Serial.begin (9600);        // serial number to start at

  pinMode(tapeSenseRight,INPUT);
  pinMode(tapeSenseLeft,INPUT);

  pinMode(trigPin1, OUTPUT);  
  pinMode(echoPin1, INPUT);   
  
  pinMode(trigPin2, OUTPUT);  
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  pinMode(flameSense, INPUT_PULLUP);

  pinMode(fan, OUTPUT);
}

void loop() {
  leftEdgeSonarSensor = sonarSensorMicros(trigPin1, echoPin1);
  rightEdgeSonarSensor = sonarSensorMicros(trigPin2, echoPin2);

  digitalWrite(fan, LOW);

  checkForFire();
  if (sonarSensorMicros(trigPin3, echoPin3) <= 18) // right sonar sensor is 45
  {
    turnLeft();
    delay(200);
  }
  else if (sonarSensorMicros(trigPin4, echoPin4) <= 18) // left sonar sensor is 46
  {
    turnRight();
    delay(200);
  }
  else if (rightEdgeSonarSensor >= 6 && leftEdgeSonarSensor <= 6) //right edge sensor is off table
  {
    turnLeft();
  }
  else if (rightEdgeSonarSensor <= 6 && leftEdgeSonarSensor >= 6) //left edge sensor is off table
  {
    turnRight();
  }
  else if (rightEdgeSonarSensor <= 6 && leftEdgeSonarSensor <= 6) {//if both sensors are on the table,
    if (digitalRead(tapeSenseRight) == HIGH) {
      while (digitalRead(tapeSenseLeft) == LOW) {
        shortTurnRight();
      }
      checkForFire();
      shortTurnLeft();
      delay(500);
      goStraight();
      delay(20);
      while (digitalRead(tapeSenseLeft) == LOW && digitalRead(tapeSenseRight) == LOW) {
        shortTurnRight();
      }
    }
    else if (digitalRead(tapeSenseLeft) == HIGH) {
      int count = 0;
      while (digitalRead(tapeSenseRight) == LOW) {
        shortTurnLeft();
      }
      checkForFire();
      shortTurnRight();
      delay(500);
      goStraight();
      delay(20);
      while (digitalRead(tapeSenseRight) == LOW && digitalRead(tapeSenseLeft) == LOW) {
        shortTurnLeft();
      }
    }
    else {
      goStraight();
    }
  }
  else {
    reverseTurn();
  }
}

void checkForFire() {
  if (analogRead(flameSense) <= 750) {
    analogWrite(motorRPower,0);
    analogWrite(motorLPower,0);
    digitalWrite(fan, HIGH);
    delay(5000);
    digitalWrite(fan, LOW);
    while (true) {
      // do nothing
    }
  }
}

void goStraight(){
  digitalWrite(motorRForward, HIGH);  
  digitalWrite(motorRBackward, LOW);   
  analogWrite(motorRPower,80);

  digitalWrite(motorLForward, HIGH);  
  digitalWrite(motorLBackward, LOW);   
  analogWrite(motorLPower,80);
}

void turnRight(){
  digitalWrite(motorRForward, LOW);  
  digitalWrite(motorRBackward, HIGH);   
  analogWrite(motorRPower,80);

  digitalWrite(motorLForward, HIGH);  
  digitalWrite(motorLBackward, LOW);   
  analogWrite(motorLPower,80);
}

void shortTurnRight() {
  digitalWrite(motorRForward, LOW);  
  digitalWrite(motorRBackward, HIGH);   
  analogWrite(motorRPower,80);
  
  digitalWrite(motorLForward, HIGH);  
  digitalWrite(motorLBackward, LOW);   
  analogWrite(motorLPower,80);
}
void shortTurnLeft() {
  digitalWrite(motorRForward, HIGH);  
  digitalWrite(motorRBackward, LOW);   
  analogWrite(motorRPower,80);
  
  digitalWrite(motorLForward, LOW);  
  digitalWrite(motorLBackward, HIGH);   
  analogWrite(motorLPower,80);
}


void reverseTurn(){
  reverse();
  digitalWrite(motorRForward, LOW);  
  digitalWrite(motorRBackward, HIGH);   
  analogWrite(motorRPower,70);
  digitalWrite(motorLForward, HIGH);  
  digitalWrite(motorLBackward, LOW);   
  analogWrite(motorLPower,70);
  delay(1000); 
}

void reverse() {
  digitalWrite(motorRForward, LOW);  
  digitalWrite(motorRBackward, HIGH);   
  analogWrite(motorRPower,70);
  digitalWrite(motorLForward, LOW);  
  digitalWrite(motorLBackward, HIGH);   
  analogWrite(motorLPower,70);
  delay(500);
}

void turnLeft(){
  digitalWrite(motorRForward, HIGH);  
  digitalWrite(motorRBackward, LOW);   
  analogWrite(motorRPower,80);
  
  digitalWrite(motorLForward, LOW);  
  digitalWrite(motorLBackward, HIGH);   
  analogWrite(motorLPower,80);
  delay(100);
}

double sonarSensorMicros(int trigPin, int echoPin) 
{
  digitalWrite(trigPin, LOW);
  myDelayMicros(2);
  digitalWrite(trigPin, HIGH);
  myDelayMicros(10);
  digitalWrite(trigPin, LOW);
  float sonarDuration = pulseIn(echoPin, HIGH);
  float sonarDistance = (sonarDuration / 2) / 29.1;
  return sonarDistance;
}

double myDelayMicros(unsigned long n) {
  unsigned long curTime = micros();
  while (micros() < curTime + n) {
    /* wait */
  }
}

double sonarSensor(int trigPin,int echoPin) //read sensor 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);//2
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);//10
  digitalWrite(trigPin, LOW);
  float sonarDuration = pulseIn(echoPin, HIGH);
  float sonarDistance = (sonarDuration/2) / 29.1;
  return sonarDistance;
}
