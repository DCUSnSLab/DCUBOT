const int SPD_PIN = DAC1;
const int BRK_PIN = 37;
const int DIR_PIN = 8;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  analogWriteResolution(10);

  pinMode(SPD_PIN, OUTPUT);
  pinMode(BRK_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(BRK_PIN, HIGH);
  analogWrite(SPD_PIN, 0);
  digitalWrite(DIR_PIN, LOW);
}

void loop() {

  if (Serial.available() >= 2) {

    char dir = Serial.read();   // 첫 자리 (방향)
    char run = Serial.read();   // 두 번째 자리 (동작)

    if ((dir == '0' || dir == '1') && (run == '0' || run == '1')) {

      // 방향 설정
      if (dir == '0') {
        digitalWrite(DIR_PIN, LOW);   // 전진
      } else {
        digitalWrite(DIR_PIN, HIGH);  // 후진
      }

      // 동작 설정
      if (run == '1') {
        analogWrite(SPD_PIN, 200);
        digitalWrite(BRK_PIN, LOW);
      } else {
        analogWrite(SPD_PIN, 0);
        digitalWrite(BRK_PIN, HIGH);
      }
    }
    else {
      // 이상한 값이면 안전 정지
      analogWrite(SPD_PIN, 0);
      digitalWrite(BRK_PIN, HIGH);
    }
  }
}
