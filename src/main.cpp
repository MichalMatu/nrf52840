#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

#include "app_config.h"

namespace {
bool led_state = false;
uint32_t last_toggle_ms = 0;

void set_status_led(bool enabled) {
  led_state = enabled;
  digitalWrite(STATUS_LED_PIN, enabled ? LED_STATE_ON : LED_STATE_OFF);
}
}  // namespace

void setup() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  set_status_led(false);

  Serial.begin(SERIAL_BAUDRATE);
  delay(250);

  Serial.println();
  Serial.println(APP_NAME " " APP_VERSION);
  Serial.println("Board: nRF52840 SuperMini / nice!nano");
  Serial.println("Status: booted");
}

void loop() {
  const uint32_t now = millis();

  if (now - last_toggle_ms >= STATUS_BLINK_INTERVAL_MS) {
    last_toggle_ms = now;
    set_status_led(!led_state);
    Serial.println(led_state ? "led:on" : "led:off");
  }
}

