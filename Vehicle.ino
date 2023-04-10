#define RIGHT_PWM_PIN 11
#define RIGHT_DIR_PIN 4

#define LEFT_PWM_PIN 10
#define LEFT_DIR_PIN 2

#define TRIG_PIN 13
#define ECHO_PIN 12

#define STOP_SIGNAL A1
#define LEFT_SIGNAL 7
#define RIGHT_SIGNAL 8

// 디버깅용 버튼들
#define LEFT_BTN 7
#define RIGHT_BTN 8
#define UP_BTN A0
#define DOWN_BTN A1

#define IRL A6
#define IRR A7

#define LR_RATE 1.0
#define DISTANCE 7.0
#define SPEED 70
#define TURNSPEED 50
#define TURNTIME 30

bool do_move = false;
int _centerValue;
float getDistance();
void go_left();
void go_right();
void MoveJellibi();

void setup() {
    pinMode(RIGHT_PWM_PIN, OUTPUT);
    pinMode(RIGHT_DIR_PIN, OUTPUT);
    pinMode(LEFT_PWM_PIN, OUTPUT);
    pinMode(LEFT_DIR_PIN, OUTPUT);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.begin(115200);
    _centerValue = (analogRead(IRR)-analogRead(IRL));
    stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(LEFT_BTN)==LOW) {
    // (여기에 필요하다면 직진조금만 더 하는 부분 필요)
    go_left();
    do_move = true;
    Serial.println(do_move);
  }
  if (digitalRead(RIGHT_BTN)==LOW) {
    // (여기에 필요하다면 직진조금만 더 하는 부분 필요)
    go_right();
    do_move = true;
    Serial.println(do_move);
  }
  if (digitalRead(UP_BTN)==LOW) {
    do_move = true;
    Serial.println(do_move);
  }
  if (digitalRead(DOWN_BTN)==LOW && do_move==true) {
    do_move = false;
    Serial.println(do_move);
  }
  else if (digitalRead(DOWN_BTN)==HIGH) {
    do_move = true;
  }
  if (do_move==true && getDistance()>DISTANCE) {
    MoveJellibi();
  }
  else {
    stop();
  }
  delay(10);
}

void stop() {  //정지
  analogWrite(RIGHT_PWM_PIN, 0);
  analogWrite(LEFT_PWM_PIN, 0);
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

void go_right()
{
  double leftSpeed = SPEED + TURNSPEED;
  double rightSpeed = SPEED - TURNSPEED;
  for (int cnt=0; cnt<TURNTIME; cnt++) {
    if (getDistance() < DISTANCE) {
      stop();      
      cnt--;
    } else {
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
      analogWrite(LEFT_PWM_PIN, round(abs(leftSpeed)));
      analogWrite(RIGHT_PWM_PIN, round(abs(rightSpeed/LR_RATE)));
    }

  }
}

void go_left()
{
  double leftSpeed = SPEED - TURNSPEED;
  double rightSpeed = SPEED + TURNSPEED;
  for (int cnt=0; cnt<TURNTIME; cnt++) {
    if (getDistance() < DISTANCE) {
      stop();    
      cnt--;  
    } else {
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
      analogWrite(LEFT_PWM_PIN, round(abs(leftSpeed)));
      analogWrite(RIGHT_PWM_PIN, round(abs(rightSpeed/LR_RATE)));
    }

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
  analogWrite( RIGHT_PWM_PIN, round(abs(rightSpeed/LR_RATE)));
}