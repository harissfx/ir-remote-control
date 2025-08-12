
---

# ESP8266 IR Remote Control

Project sederhana untuk membaca sinyal **remote IR** dan menggunakannya untuk **mengontrol perangkat** seperti LED atau relay menggunakan **ESP8266**.

📌 **Cocok untuk belajar**:

* Membaca protokol dan kode remote IR
* Mengontrol perangkat berdasarkan input remote
* Implementasi sederhana untuk smart home

---

## ✨ Fitur

* Membaca **HEX** dan **DEC** kode dari remote IR.
* Menampilkan **nama protokol** (misalnya NEC, SONY, dll) di Serial Monitor.
* Mengontrol LED bawaan **NodeMCU / ESP8266** menggunakan tombol pada remote.
* Tampilan Serial Monitor yang rapi & mudah dibaca.

---

## 🛠 Peralatan

* **ESP8266** (NodeMCU, Wemos D1 Mini, dll)
* **IR Receiver** (misalnya VS1838B)
* **Remote IR** (TV, AC, atau remote universal)
* Kabel jumper

---

## 📦 Library yang Dibutuhkan

Install library berikut melalui **Arduino IDE**:

* [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266)

---

## 📌 Pinout

| ESP8266 Pin | Fungsi            |
| ----------- | ----------------- |
| **D5**      | Input sinyal IR   |
| **D4**      | Output LED bawaan |

---

## 🚀 Cara Penggunaan

### 1️⃣ Mode Pembacaan Kode Remote

Gunakan kode ini untuk **membaca kode HEX & DEC** dari tombol remote:

```cpp
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t IR_PIN = D5; 
IRrecv irrecv(IR_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  Serial.println("\n=== IR Receiver Siap ===\n");
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFFFFFFFFFF) {
      Serial.println();
      Serial.println(F("========================================"));
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
```

📌 **Gunakan mode ini dulu** untuk mengetahui kode tombol yang akan dipakai.

---

### 2️⃣ Mode Kontrol LED

Setelah mengetahui kode tombol, masukkan ke dalam variabel `CODE_LED_ON` dan `CODE_LED_OFF`:

```cpp
#define CODE_LED_ON  0xF7C03F  // Ganti sesuai hasil pembacaan
#define CODE_LED_OFF 0xF740BF  // Ganti sesuai hasil pembacaan
```

Kemudian upload kode berikut untuk **mengontrol LED bawaan**:

```cpp
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t IR_PIN = D5; 
const uint8_t LED_PIN = D4;

#define LED_ON  LOW
#define LED_OFF HIGH

IRrecv irrecv(IR_PIN);
decode_results results;

#define CODE_LED_ON  0xF7C03F
#define CODE_LED_OFF 0xF740BF

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
      Serial.println(F("\n========================================"));
      Serial.print(F("Protokol  : "));
      Serial.println(typeToString(results.decode_type).c_str());
      Serial.print(F("HEX       : 0x"));
      Serial.println(uint64ToString(results.value, HEX));
      Serial.print(F("DEC       : "));
      Serial.println(uint64ToString(results.value, DEC));
      Serial.println(F("========================================"));

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
```

---


## 💡 Tips

* LED bawaan ESP8266 aktif **LOW** (logika terbalik).
* Kalau mau kontrol relay, sambungkan pin `LED_PIN` ke input relay.
* Bisa diperluas untuk mengontrol **lampu, kipas, atau perangkat lain**.

---

## 📜 Lisensi

Proyek ini dibagikan di bawah lisensi MIT.
Silakan gunakan, modifikasi, dan sebarkan untuk belajar & eksperimen.

---
