// quad-tic-timer.ino - ATtiny85 4-channel ratio tic generator with single-pot global tempo
// Board: ATtiny85 @ 8MHz internal (ATTinyCore). Programmer: USBasp / Arduino-as-ISP.
// Pins: PB3/A3 <- 10k 10-turn precision pot wiper (Bourns 3590S-1-103L or 3296W trimmer),
//        PB0=o1, PB1=o2, PB2=o3, PB4=o4
//
// Nominal (pot centered): o1=1.00s, o2=0.75s, o3=0.50s, o4=0.25s per tic.
// Range: o1 = 0.2s (full CCW) .. 5.0s (full CW), others track by fixed ratio.
// Mapping is exponential: k = 5^((pot-512)/512), so mid detent = 1.0x.
// Output: 10ms active-HIGH pulse, non-blocking, phase-accurate (no drift accumulation).
#include <avr/wdt.h>

const uint8_t OUT_PINS[4] = {0, 1, 2, 4};
const uint8_t POT_PIN = A3;
const uint32_t NOM_US[4] = {1000000UL, 750000UL, 500000UL, 250000UL};
const uint32_t TIC_US = 10000UL;

uint32_t chNext[4] = {0, 0, 0, 0};
uint32_t chOff[4] = {0, 0, 0, 0};
uint32_t chPeriod[4] = {1000000UL, 750000UL, 500000UL, 250000UL};
uint16_t potFilt = 512;

uint16_t readPot() {
  uint16_t s = 0;
  for (uint8_t i = 0; i < 16; i++) s += analogRead(POT_PIN);
  return s >> 4;
}

void setup() {
  wdt_enable(WDTO_500MS);
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(OUT_PINS[i], OUTPUT);
    digitalWrite(OUT_PINS[i], LOW);
    chNext[i] = micros() + NOM_US[i];
  }
}

void loop() {
  wdt_reset();
  static uint32_t lastPot = 0;
  uint32_t now = micros();

  if (millis() - lastPot > 50) {
    lastPot = millis();
    uint16_t raw = readPot();
    if (abs((int)raw - (int)potFilt) > 2) {
      potFilt = constrain(raw, 0, 1023);
      float k = pow(5.0, ((float)potFilt - 512.0) / 512.0);
      for (uint8_t i = 0; i < 4; i++)
        chPeriod[i] = (uint32_t)(NOM_US[i] * k);
    }
  }

  for (uint8_t i = 0; i < 4; i++) {
    if ((int32_t)(now - chNext[i]) >= 0) {
      digitalWrite(OUT_PINS[i], HIGH);
      chOff[i] = now + TIC_US;
      chNext[i] += chPeriod[i];
      if ((int32_t)(now - chNext[i]) >= 0) chNext[i] = now + chPeriod[i];
    }
    if (digitalRead(OUT_PINS[i]) && (int32_t)(now - chOff[i]) >= 0)
      digitalWrite(OUT_PINS[i], LOW);
  }
}
