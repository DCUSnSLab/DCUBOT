void setup() {
  Serial.begin(9600);  // Programming Port
  while (!Serial) { ; } // Native USB 연결 대기
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Serial.println(msg);  // 받은 메시지 그대로 출력
  }
}
