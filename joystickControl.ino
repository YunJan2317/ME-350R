/*
  ME 350R: First Build
*/

#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7


int xAxis, yAxis, xMapped, yMapped, rightVelocity, leftVelocity;


void wheelControl(int rightVelocity, int leftVelocity) {

  int rightDir, leftDir, rightSpeed, leftSpeed;

  rightDir = (rightVelocity > 0) ? HIGH : LOW;
  leftDir = (leftVelocity > 0) ? HIGH : LOW;

  rightSpeed = abs(rightVelocity);
  leftSpeed = abs(leftVelocity);

  digitalWrite(in1, rightDir);
  digitalWrite(in2, 1 - rightDir);
  digitalWrite(in3, leftDir);
  digitalWrite(in4, 1 - leftDir);
  analogWrite(enA, rightSpeed);
  analogWrite(enB, leftSpeed);
}

int sign(int x) {
    return (x > 0) - (x < 0);
}


void setup() {
	Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void loop() {
  xAxis = analogRead(A0)/2 - 255; // Read Joysticks X-axis.
  yAxis = analogRead(A1)/2 - 255; // Read Joysticks Y-axis.

  rightVelocity = (abs(yAxis - xAxis) < 255) ? yAxis - xAxis : sign(yMapped - xAxis)*255;
  leftVelocity = (abs(yAxis + xAxis) < 255) ? yAxis + xAxis : sign(yMapped + xAxis)*255;

  rightVelocity = abs(rightVelocity) < 16 ? 0 : rightVelocity;
  leftVelocity = abs(leftVelocity) < 16 ? 0 : leftVelocity;

  Serial.println(rightVelocity);
  Serial.println(leftVelocity);

  wheelControl(rightVelocity, leftVelocity);
}
