#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "app_config.h"

namespace {
struct Button {
  const char* name;
  uint8_t pin;
};

constexpr Button buttons[] = {
    {"K4", BUTTON_K4_PIN},
    {"K3", BUTTON_K3_PIN},
    {"K2", BUTTON_K2_PIN},
    {"K1", BUTTON_K1_PIN},
};

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

bool led_state = false;
bool display_ready = false;
uint8_t display_address = 0;
uint32_t last_toggle_ms = 0;
uint32_t last_display_ms = 0;

void set_status_led(bool enabled) {
  led_state = enabled;
  digitalWrite(STATUS_LED_PIN, enabled ? LED_STATE_ON : LED_STATE_OFF);
}

bool button_pressed(const Button& button) {
  return digitalRead(button.pin) == LOW;
}

uint8_t scan_i2c() {
  uint8_t found = 0;

  Serial.println("I2C scan:");
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    const uint8_t error = Wire.endTransmission();
    if (error == 0) {
      found++;
      Serial.print("  0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (found == 0) {
    Serial.println("  no devices found");
  }

  return found;
}

bool begin_display_at(uint8_t address) {
  if (!display.begin(SSD1306_SWITCHCAPVCC, address)) {
    return false;
  }

  display_address = address;
  display_ready = true;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(APP_NAME);
  display.print("OLED 0x");
  display.println(address, HEX);
  display.println("I2C: SDA 022 SCL 020");
  display.println("Power: 017");
  display.display();
  return true;
}

void update_display() {
  if (!display_ready) {
    return;
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("nRF52840 OLED");
  display.print("addr: 0x");
  display.println(display_address, HEX);
  display.print("uptime: ");
  display.print(millis() / 1000);
  display.println("s");
  display.println();

  for (const Button& button : buttons) {
    display.print(button.name);
    display.print(": ");
    display.println(button_pressed(button) ? "DOWN" : "up");
  }

  display.display();
}
}  // namespace

void setup() {
  pinMode(OLED_POWER_PIN, OUTPUT);
  digitalWrite(OLED_POWER_PIN, HIGH);
  delay(250);

  pinMode(STATUS_LED_PIN, OUTPUT);
  set_status_led(false);

  for (const Button& button : buttons) {
    pinMode(button.pin, INPUT_PULLUP);
  }

  Serial.begin(SERIAL_BAUDRATE);
  delay(250);

  Serial.println();
  Serial.println(APP_NAME " " APP_VERSION);
  Serial.println("Board: nRF52840 SuperMini / nice!nano");
  Serial.println("OLED power: PIN_017");
  Serial.println("OLED SCL:   PIN_020");
  Serial.println("OLED SDA:   PIN_022");
  Serial.println("Status: booted");

  Wire.setPins(OLED_SDA_PIN, OLED_SCL_PIN);
  Wire.begin();
  Wire.setClock(400000);

  scan_i2c();

  if (!begin_display_at(0x3C) && !begin_display_at(0x3D)) {
    Serial.println("OLED init failed at 0x3C and 0x3D");
  } else {
    Serial.print("OLED initialized at 0x");
    Serial.println(display_address, HEX);
  }
}

void loop() {
  const uint32_t now = millis();

  if (now - last_toggle_ms >= STATUS_BLINK_INTERVAL_MS) {
    last_toggle_ms = now;
    set_status_led(!led_state);
    Serial.println(led_state ? "led:on" : "led:off");
  }

  if (now - last_display_ms >= 250) {
    last_display_ms = now;
    update_display();
  }
}
