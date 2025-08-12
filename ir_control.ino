#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t IR_PIN = D5; // Pin modul IR
const uint8_t LED_PIN = D4; // LED bawaan / relay, bisa kamu ganti terserah mau kontrol apa

#define LED_ON  LOW
#define LED_OFF HIGH

IRrecv irrecv(IR_PIN);
decode_results results;

uint64_t lastCode = 0;
unsigned long pressCount = 0;

// Ganti kode ini sesuai hasil pembacaan remote kamu
#define CODE_LED_ON  0xF7C03F  // Ganti sesuai hasil pembacaan
#define CODE_LED_OFF 0xF740BF  // Ganti sesuai hasil pembacaan

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_OFF);

  Serial.println("\n=== IR Receiver Siap Kontrol LED ===\n");
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFFFFFFFFFF) {
      lastCode = results.value;
      pressCount++;

      // ===== Tampilan Monitoring =====
      Serial.println(F("\n========================================"));
      Serial.printf("Tombol Ke : %lu\n", pressCount);
      Serial.printf("Waktu     : %.2f s\n", millis() / 1000.0);
      Serial.print(F("Protokol  : "));
      Serial.println(typeToString(results.decode_type).c_str());
      Serial.print(F("HEX       : 0x"));
      Serial.println(uint64ToString(results.value, HEX));
      Serial.print(F("DEC       : "));
      Serial.println(uint64ToString(results.value, DEC));
      Serial.println(F("========================================"));

      // ===== Kontrol LED =====
      if (results.value == CODE_LED_ON) {
        digitalWrite(LED_PIN, LED_ON);
        Serial.println(F("💡 LED ON"));
      }
      else if (results.value == CODE_LED_OFF) {
        digitalWrite(LED_PIN, LED_OFF);
        Serial.println(F("💤 LED OFF"));
      }
    }
    irrecv.resume();
  }
}
