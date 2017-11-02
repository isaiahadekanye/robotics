#define trigPin1 3 //right edge detection
#define echoPin1 24 
#define trigPin2 11 //left edge detection
#define echoPin2 25
#define trigPin3 12 //front obstacle detection
#define echoPin3 27
#define trigPin4 46 //back obstacle detection
#define echoPin4 23 
#define trigPin5 45 //right obstacle detection
#define echoPin5 22 
#define trigPin6 2 //left obstacle detection
#define echoPin6 26
#define tapeSense1 44
#define tapeSense2 10
#define motorRForward 4
#define motorRBackward 5
#define motorLPower 6
#define motorLBackward 7
#define motorLForward 8
#define motorRPower 9

long sonarDuration,sonarDistance,leftSonarSensor,rightSonarSensor,frontSonarSensor,backSonarSensor,rightEdgeSonarSensor,leftEdgeSonarSensor;
long obsticaleRangeDistance = 26;
int tapeSensorRight,tapeSensorLeft;

void setup() {
  Serial.begin (9600);        // serial number to start at

  pinMode(tapeSense1,INPUT);
  pinMode(tapeSense2,INPUT);
  
  pinMode(trigPin1, OUTPUT);  
  pinMode(echoPin1, INPUT);   
  
  pinMode(trigPin2, OUTPUT);  
  pinMode(echoPin2, INPUT);   
  
  pinMode(trigPin3, OUTPUT); 
  pinMode(echoPin3, INPUT);   
 
  pinMode(trigPin4, OUTPUT);  
  pinMode(echoPin4, INPUT);  
 
  pinMode(trigPin5, OUTPUT);  
  pinMode(echoPin5, INPUT);   
  
  pinMode(trigPin6, OUTPUT);  
  pinMode(echoPin6, INPUT); 
  
}


void loop() {

  sonarSensor(trigPin1, echoPin1);
  rightEdgeSonarSensor = sonarDistance;
  sonarSensor(trigPin2, echoPin2);
  leftEdgeSonarSensor = sonarDistance;
  sonarSensor(trigPin3, echoPin3);
  frontSonarSensor = sonarDistance; //distance ahead is 26
  sonarSensor(trigPin4, echoPin4);
  backSonarSensor = sonarDistance;
  sonarSensor(trigPin5, echoPin5);
  rightSonarSensor = sonarDistance;
  sonarSensor(trigPin6, echoPin6);
  leftSonarSensor = sonarDistance;
  
  tapeSensorRight = digitalRead(tapeSense1);
  tapeSensorLeft = digitalRead(tapeSense2);

  if (tapeSensorLeft == HIGH)
	turnRight();
  else if (tapeSensorRight == High)
	turnLeft();
  
  if (rightSonarSensor <= obsticaleRangeDistance && leftSonarSensor <= obsticaleRangeDistance && frontSonarSensor <= obsticaleRangeDistance)
    reverseTurn();
  else if (frontSonarSensor <= obsticaleRangeDistance)
    reverseTurn();
  else if ((rightEdgeSonarSensor >= 6 && leftEdgeSonarSensor <= 6) || rightSonarSensor <= obsticaleRangeDistance) //right edge sensor is off table
    turnLeft();
  else if ((rightEdgeSonarSensor <= 6 && leftEdgeSonarSensor >= 6) || leftSonarSensor <= obsticaleRangeDistance) //left edge sensor is off table
    turnRight();
  else if (rightEdgeSonarSensor <= 6 && leftEdgeSonarSensor <= 6) //if both sensors are on the table,
    goStraight();
  else
    reverseTurn();

}
void goStraight(){
  digitalWrite(motorRForward, HIGH);  
  digitalWrite(motorRBackward, LOW);   
  analogWrite(motorRPower,70);

  digitalWrite(motorLForward, HIGH);  
  digitalWrite(motorLBackward, LOW);   
  analogWrite(motorLPower,70);
}

void turnRight(){
  digitalWrite(motorRForward, LOW);  
  digitalWrite(motorRBackward, HIGH);   
  analogWrite(motorRPower,80);
  
  digitalWrite(motorLForward, HIGH);  
  digitalWrite(motorLBackward, LOW);   
  analogWrite(motorLPower,80);
  delay(100);
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

void reverseTurn(){
  if (backSonarSensor >= obsticaleRangeDistance) {
    goStraight();
  }
  else {
    digitalWrite(motorRForward, LOW);  
    digitalWrite(motorRBackward, HIGH);   
    analogWrite(motorRPower,70);
    digitalWrite(motorLForward, LOW);  
    digitalWrite(motorLBackward, HIGH);   
    analogWrite(motorLPower,70);
    delay(500);
  }

  digitalWrite(motorRForward, LOW);  
  digitalWrite(motorRBackward, HIGH);   
  analogWrite(motorRPower,70);
  digitalWrite(motorLForward, HIGH);  
  digitalWrite(motorLBackward, LOW);   
  analogWrite(motorLPower,70);
  delay(1000); 
}

void sonarSensor(int trigPin,int echoPin) //read sensor 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sonarDuration = pulseIn(echoPin, HIGH);
  sonarDistance = (sonarDuration/2) / 29.1;
}     
