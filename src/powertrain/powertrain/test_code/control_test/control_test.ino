// const int SPD_PIN = DAC1;   // AOUT: 모터 회전 속도(0-1023)
// const int BRK_PIN = 37;     // DOUT: 모터 브레이크 신호(LOW: 모터 작동 | HIGH: 모터 정지)
// const int DIR_PIN = 8;      // DOUT: 모터 회전 방향(LOW: 전진 | HIGH: 후진)
// const int SWAP_PIN = 9;     // DOUT: 좌우회전(LOW: 전진 | HIGH: 회전)

// void setup() {
//   Serial.begin(9600);
//   Serial.setTimeout(10);
//   analogWriteResolution(10);

//   pinMode(SPD_PIN, OUTPUT);
//   pinMode(BRK_PIN, OUTPUT);
//   pinMode(DIR_PIN, OUTPUT);
// }

// void loop() {
//   int k = Serial.read();
//   if(k == 1) {
//     digitalWrite(DIR_PIN, LOW);
//     analogWrite(SPD_PIN, 200);
//     digitalWrite(BRK_PIN, LOW);
//   }
//   else if(k == 0) {
//     digitalWrite(DIR_PIN, LOW);
//     analogWrite(SPD_PIN, 0);
//     digitalWrite(BRK_PIN, HIGH);
//   }
//   else if(k == -1) {
//     Serial.write("READ ERROR\n");
//     digitalWrite(BRK_PIN, HIGH);
//   }
//   else {
//     Serial.write("KEY ERROR\n");
//     digitalWrite(BRK_PIN, HIGH);
//   }
// }

const int SPD_PIN = DAC1;   // AOUT: 모터 회전 속도(0-1023)
const int BRK_PIN = 37;     // DOUT: 브레이크 (LOW: 작동 | HIGH: 정지)
const int DIR_PIN = 8;      // DOUT: 방향 (LOW: 전진 | HIGH: 후진)

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  analogWriteResolution(10);

  pinMode(SPD_PIN, OUTPUT);
  pinMode(BRK_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  // 안전 초기 상태
  digitalWrite(BRK_PIN, HIGH);
  analogWrite(SPD_PIN, 0);
  digitalWrite(DIR_PIN, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char k = Serial.read();   // 문자로 받기
    Serial.write(k);

    if (k == '1') {
      // GO
      digitalWrite(DIR_PIN, LOW);
      analogWrite(SPD_PIN, 200);
      digitalWrite(BRK_PIN, LOW);
    }
    else if (k == '0') {
      // STOP
      analogWrite(SPD_PIN, 0);
      digitalWrite(BRK_PIN, HIGH);
    }
    else {
      // 알 수 없는 값 → 안전 정지
      analogWrite(SPD_PIN, 0);
      digitalWrite(BRK_PIN, HIGH);
      Serial.println("KEY ERROR");
    }
  }
}
