#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t IR_PIN = D5; // Pin modul IR
IRrecv irrecv(IR_PIN);
decode_results results;

uint64_t lastCode = 0;
unsigned long pressCount = 0;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  Serial.println("\n=== IR Receiver Siap ===\n");
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFFFFFFFFFF) {
      lastCode = results.value;
      pressCount++;

      Serial.println();
      Serial.println(F("========================================"));
      Serial.print(F(">>> #"));
      Serial.print(pressCount);
      Serial.print(F(" | Waktu: "));
      Serial.print(millis() / 1000.0, 2);
      Serial.println(F("s <<<"));

      Serial.print(F("Protokol : "));
      Serial.println(typeToString(results.decode_type).c_str());

      Serial.print(F("HEX      : 0x"));
      Serial.println(uint64ToString(results.value, HEX));

      Serial.print(F("DEC      : "));
      Serial.println(uint64ToString(results.value, DEC));

      Serial.println(F("========================================"));
    }
    irrecv.resume();
  }
}
