#include <Arduino.h>

void dumpPtr(const void *ptr) {
  constexpr uint8_t SIZE = 32;

#ifdef ARDUINO_ARCH_AVR
  char str[5];

  sprintf_P(str, PSTR("%04X"), (uint16_t)ptr);
  Serial.print(str);
#else
  Serial.printf("%08X", (uint32_t)ptr);
#endif
  ptr -= SIZE;
  for (uint8_t i = 0; i < SIZE; ++i) {
#ifdef ARDUINO_ARCH_AVR
    sprintf_P(str, PSTR(" %02X"), *(uint8_t*)ptr);
    Serial.print(str);
#else
    Serial.printf(" %02X", *(uint8_t*)ptr);
#endif
    ptr += 1;
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
#ifdef ARDUINO_USB_CDC_ON_BOOT
  delay(2000);
#endif

  void *ptrs[6];

  for (uint8_t i = 0; i < sizeof(ptrs) / sizeof(ptrs[0]); ++i) {
    ptrs[i] = malloc(1 << i);
    memset(ptrs[i], i + 1, 1 << i);
    dumpPtr(ptrs[i]);
  }
}

void loop() {}
