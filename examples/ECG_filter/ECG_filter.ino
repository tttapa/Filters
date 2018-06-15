#include <FIRFilter.h>
#include <IIRFilter.h>

const double ECG_samplefreq  = 360;
const uint8_t ECG_pin = A0;
const int16_t DC_offset = 511;

// 50 Hz notch
const double b_notch[] = { 1.39972748302835,  -1.79945496605670, 1.39972748302835 };

// 35 Hz Butterworth low-pass
const double b_lp[] = { 0.00113722762905776, 0.00568613814528881, 0.0113722762905776,  0.0113722762905776,  0.00568613814528881, 0.00113722762905776 };
const double a_lp[] = { 1, -3.03124451613593, 3.92924380774061,  -2.65660499035499, 0.928185738776705, -0.133188755896548 };

// 0.3 Hz high-pass
const double b_hp[] = { 1, -1 };
const double a_hp[] = { 1, -0.995 };

FIRFilter notch(b_notch);
IIRFilter lp(b_lp, a_lp);
IIRFilter hp(b_hp, a_hp);

void setup() {
  Serial.begin(115200);
}

void loop() {
  const static unsigned long ECG_interval  = round(1e6 / ECG_samplefreq);
  static unsigned long ECG_prevmicros = micros();
  
  if (!Serial) {
    ECG_prevmicros = micros();
  } else if (micros() - ECG_prevmicros >= ECG_interval) {
    measureECGAndSend();
    ECG_prevmicros += ECG_interval;
  }
}

void measureECGAndSend() {
  int16_t value = analogRead(ECG_pin);
  double filtered = notch.filter(
                      lp.filter(
                      hp.filter(value - DC_offset)));
  value = round(filtered) + DC_offset;
  Serial.println(value);
}
