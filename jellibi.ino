#define RIGHT_PWM_PIN 11
#define RIGHT_DIR_PIN 4

#define LEFT_PWM_PIN 10
#define LEFT_DIR_PIN 2

#define MAX_PWM 255
#define HIGH_PWM 120
#define LOW_PWM 60
#define MIN_PWM 0

#define STOP_SIGNAL 8
#define LEFT_SIGNAL 13
#define RIGHT_SIGNAL 9

#define IRL A6
#define IRR A7

#define TRIG_PIN 13
#define ECHO_PIN 12

#define DISTANCE 7.0
#define SPEED 70

void lowSpeed();
void highSpeed();
void turnRight();
void turnLeft();
void Forward();
void Backward();
void stop();
float getDistance();
int _centerValue;
void setup() {
  Serial.begin(115200);

  pinMode(RIGHT_PWM_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(LEFT_PWM_PIN, OUTPUT);
  pinMode(LEFT_DIR_PIN, OUTPUT);

  pinMode(STOP_SIGNAL, INPUT);
  pinMode(LEFT_SIGNAL, INPUT);
  pinMode(RIGHT_SIGNAL, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  _centerValue = (analogRead(IRR)-analogRead(IRL));
}

void loop() {
  int stop_signal = digitalRead(STOP_SIGNAL);
  Serial.println(stop_signal);
  if(getDistance() < DISTANCE || stop_signal == LOW) {
    stop();
  }
  else{
    Serial.println(stop_signal);
    MoveJellibi();
  }
}

void MoveJellibi()
{
  double turnSpeed = ((analogRead(IRR)-analogRead(IRL)) - _centerValue )/4;
  double leftSpeed = SPEED + turnSpeed;
  double rightSpeed = SPEED - turnSpeed;

  if (leftSpeed > 0) {
    digitalWrite(LEFT_DIR_PIN, 1);
  } else {
    digitalWrite(LEFT_DIR_PIN, 0);
  }
  if (rightSpeed > 0 ) {
    digitalWrite(RIGHT_DIR_PIN, 0);
  } else {
    digitalWrite(RIGHT_DIR_PIN, 1);
  }

  analogWrite( LEFT_PWM_PIN, round(abs(leftSpeed)));
  analogWrite( RIGHT_PWM_PIN, round(abs(rightSpeed)));
}

void stop() {  //정지
  analogWrite(RIGHT_PWM_PIN, MIN_PWM);
  analogWrite(LEFT_PWM_PIN, MIN_PWM);
}

float getDistance() {
  float duration, distance;
  digitalWrite(TRIG_PIN, HIGH);
  delay(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = ((float)(340*duration)/1000/10)/2;
  Serial.print("distance : ");
  Serial.print(distance);
  Serial.println("cm");
  return distance;
}