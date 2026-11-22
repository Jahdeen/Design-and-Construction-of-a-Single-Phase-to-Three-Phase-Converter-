/*
 ============================================================
   3-PHASE INVERTER
   50 Hz
   120 DEGREE PHASE SHIFT
   7-STEP WAVEFORM
   DEAD TIME INCLUDED
 ============================================================
 PHASE A:
   D5 -> HIN
   D6 -> LIN
 PHASE B:
   D7 -> HIN
   D8 -> LIN
 PHASE C:
   D9 -> HIN
   D10 -> LIN
 Phase displacement:
   A =   0 degrees
   B = 120 degrees
   C = 240 degrees
 Frequency:
   50 Hz
 IMPORTANT:
   This code keeps both inputs of each bridge LOW
   during a polarity change before the opposite
   input is activated.
 ============================================================
*/
// ============================================================
// PIN DEFINITIONS
// ============================================================
const byte A_H = 5;
const byte A_L = 6;
const byte B_H = 7;
const byte B_L = 8;
const byte C_H = 9;
const byte C_L = 10;
// ============================================================
// BASIC TIMING
// ============================================================
const unsigned long PERIOD_US = 20000UL;
const unsigned long HALF_PERIOD_US = 10000UL;
const unsigned long PHASE_120_US = 6667UL;
const unsigned long PHASE_240_US = 13333UL;
const unsigned long DEAD_TIME_US = 20UL;
const unsigned long STEP_WIDTH[7] = { 500, 750, 1250, 2000, 1250, 750, 500 };
const unsigned long GAP_US = 500;
void bridgeOff(byte highPin, byte lowPin) {
  digitalWrite(highPin, LOW);
  digitalWrite(lowPin, LOW);
}
int getWaveState(unsigned long t) {
  bool negative = false;
  if (t >= HALF_PERIOD_US) {
    negative = true;
    t = t - HALF_PERIOD_US;
  }
  unsigned long position = 0;
  for (byte i = 0; i < 7; i++) {
    if (t >= position && t < position + STEP_WIDTH[i]) {
      if (negative) return -1;
      else return 1;
    }
    position += STEP_WIDTH[i];
    if (i < 6) {
      if (t >= position && t < position + GAP_US) {
        return 0;
      }
      position += GAP_US;
    }
  }
  return 0;
}

void applyPhase(byte highPin, byte lowPin, int state) {
  if (state == 1) {
    digitalWrite(lowPin, LOW);
    delayMicroseconds(DEAD_TIME_US);
    digitalWrite(highPin, HIGH);
  }
  else if (state == -1) {
    digitalWrite(highPin, LOW);
    delayMicroseconds(DEAD_TIME_US);
    digitalWrite(lowPin, HIGH);
  }
  else {
    digitalWrite(highPin, LOW);
    digitalWrite(lowPin, LOW);
  }
}

void setup() {
  pinMode(A_H, OUTPUT);
  pinMode(A_L, OUTPUT);
  pinMode(B_H, OUTPUT);
  pinMode(B_L, OUTPUT);
  pinMode(C_H, OUTPUT);
  pinMode(C_L, OUTPUT);

  bridgeOff(A_H, A_L);
  bridgeOff(B_H, B_L);
  bridgeOff(C_H, C_L);
  delay(1000);
}
void loop() {
  unsigned long masterTime = micros() % PERIOD_US;
  unsigned long timeA = masterTime;
  int stateA = getWaveState(timeA);

  unsigned long timeB = (masterTime + PERIOD_US - PHASE_120_US) % PERIOD_US;
  int stateB = getWaveState(timeB);

  unsigned long timeC = (masterTime + PERIOD_US - PHASE_240_US) % PERIOD_US;
  int stateC = getWaveState(timeC);

  applyPhase(A_H, A_L, stateA);
  applyPhase(B_H, B_L, stateB);
  applyPhase(C_H, C_L, stateC);
}
