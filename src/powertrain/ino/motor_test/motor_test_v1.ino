#include <Scheduler.h>

const int SPD_PIN = DAC1;   // AOUT: 모터 회전 속도(0-255)
const int BRK_PIN = 10;     // DOUT: 모터 브레이크 신호(LOW: 모터 작동 | HIGH: 모터 정지)
const int DIR_PIN = 8;      // DOUT: 모터 회전 방향(LOW: 전진 | HIGH: 후진)

const int MIN_VAL = 200; // 정지 전압
const float PULSES_PER_REV = 87.0; 
const float WHEEL_DIAMETER_M = 0.1397; 
const float WHEEL_CIRCUM = WHEEL_DIAMETER_M * 3.14159;

// [중요] 노이즈를 줄이기 위해 센서 1개만 씁니다. (H1만 사용)
const int H1 = 3;

volatile long hallCount = 0;
volatile int targetSpeed = MIN_VAL;
volatile int targetDir = 1;

unsigned long lastTime = 0;
long lastHallCount = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  analogWriteResolution(10);

  pinMode(SPD_PIN, OUTPUT);
  pinMode(BRK_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  // [수정 1] 3, 4, 5번 중 3번 하나만 씁니다.
  pinMode(H1, INPUT_PULLUP);
  
  // [수정 2] CHANGE(오르락내리락) 말고 RISING(올라갈 때)만 체크 -> 노이즈 절반 감소
  attachInterrupt(digitalPinToInterrupt(H1), countHall, RISING);

  analogWrite(SPD_PIN, MIN_VAL);
  delay(500);

  Serial.println("=== [Noise Filtered Speedometer] ===");
  Scheduler.startLoop(loopMotor);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.length() == 0) return;
    input.toUpperCase();

    if (input == "STOP") targetSpeed = MIN_VAL;
    else if (input.startsWith("L") && !input.startsWith("LD")) {
      int val = input.substring(1).toInt();
      if (val < MIN_VAL) val = MIN_VAL;
      targetSpeed = constrain(val, 0, 1023);
    }
  }

  // 1초마다 속도 계산
  if (millis() - lastTime > 1000) {
    unsigned long currentTime = millis();
    long currentCount = hallCount;
    long pulsesPerSec = (currentCount - lastHallCount); 
    
    // RISING만 체크하므로 펄스 수 기준을 절반(또는 측정값)으로 보정해야 할 수 있음
    // 일단 기존 로직대로 계산
    float rpm = (pulsesPerSec * 60.0) / PULSES_PER_REV;
    float kmh = (rpm * WHEEL_CIRCUM * 60.0) / 1000.0;

    Serial.print("PWM: "); Serial.print(targetSpeed);
    Serial.print(" | Speed: "); Serial.print(kmh, 1);
    Serial.println(" km/h");
    Serial.println(digitalRead(10));

    lastTime = currentTime;
    lastHallCount = currentCount;
  }
  yield();
}

void loopMotor() {
  analogWrite(SPD_PIN, targetSpeed);
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  delay(5000);
  digitalWrite(10, LOW);
  delay(5000);
  yield();
}

// =================================================
// [핵심 수정] 소프트웨어 노이즈 필터 (Debounce)
// =================================================
void countHall() {
  // static 변수는 함수가 끝나도 값을 기억합니다.
  static unsigned long last_micros = 0;
  unsigned long current_micros = micros();
  
  // [필터 설정] 
  // 600 마이크로초(0.0006초) 이내에 다시 들어온 신호는 무조건 노이즈로 간주하고 무시함.
  // 이 값(600)을 조절해서 노이즈를 잡습니다.
  if (current_micros - last_micros > 600) {
    hallCount++;
    last_micros = current_micros;
  }
}

void spin_forward() {
  digitalWrite(DIR_PIN, LOW);
  delay(delay_sec * 1000);
}

void spin_back_and_forth(int delay_sec) {
  digitalWrite(DIR_PIN, LOW);
  analogWrite(SPD_PIN, 200);
  Serial.println("GO");
  delay(delay_sec * 1000);

  digitalWrite(DIR_PIN, HIGH);
  analogWrite(SPD_PIN, 200);
  Serial.println("BACK");
  delay(delay_sec * 1000);
}

// 회전은 모터 드라이버 2개 필요함. PIN 변수도 따로 선언하기 바람.
void turn_left() {
    
}