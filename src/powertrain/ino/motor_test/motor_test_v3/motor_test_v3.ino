const int SPD_PIN = DAC1;   // AOUT: 모터 회전 속도(0-1023)
const int BRK_PIN = 37;     // DOUT: 모터 브레이크 신호(LOW: 모터 작동 | HIGH: 모터 정지)
const int DIR_PIN = 8;      // DOUT: 모터 회전 방향(LOW: 전진 | HIGH: 후진)
const int SWAP_PIN = 9;     // DOUT: 좌우회전(LOW: 전진 | HIGH: 회전)