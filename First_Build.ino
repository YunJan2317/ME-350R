/*
  ME 350R: First Build
*/

#define enA 9
#define in1 4
#define in2 5

#define enB 10
#define in3 6
#define in4 7

#define enIn 11
#define in5 12
#define in6 13


const int inputSpeed = 108;
const int driveSpeed = 75;
const int duration = 1000;

int xAxis, yAxis, xMapped, yMapped, rightVelocity, leftVelocity;
int buttonVal;


void setup() {
	Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enIn, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);

  pinMode(2, INPUT_PULLUP);

}


void loop() {

  buttonVal = digitalRead(2);

  // Serial.println(buttonVal);

  if (buttonVal == 0) {
    parallelParking(true);
  }

  xAxis = analogRead(A0)/2 - 255; // Read Joysticks X-axis.
  yAxis = analogRead(A1)/2 - 255; // Read Joysticks Y-axis.

  rightVelocity = (abs(yAxis - xAxis) < 255) ? yAxis - xAxis : sign(yMapped - xAxis)*255;
  leftVelocity = (abs(yAxis + xAxis) < 255) ? yAxis + xAxis : sign(yMapped + xAxis)*255;

  rightVelocity = abs(rightVelocity) < 16 ? 0 : rightVelocity;
  leftVelocity = abs(leftVelocity) < 16 ? 0 : leftVelocity;

  Serial.print("rightvel: ");
  Serial.print(rightVelocity);
  Serial.print(" | leftVel: ");
  Serial.println(leftVelocity);

  wheelControl(rightVelocity, leftVelocity);
}


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


void parallelParking(bool dir) {

  wheelControl(driveSpeed, driveSpeed);

  for (int i=0; i<19; i++) {
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    analogWrite(enIn, 255);
    delay(166);

    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    analogWrite(enIn, 192);
    delay(100);
  }

  wheelControl(-75, -90);
  analogWrite(enIn, 0);

  delay(1500);
  wheelControl(0, 0);

}
