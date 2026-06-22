#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

#include "app/status_led.h"
#include "app_config.h"
#include "drivers/button_panel.h"
#include "drivers/oled_panel.h"

namespace {
constexpr drivers::ButtonConfig kButtons[] = {
    {"K4", app_config::kButtonK4Pin},
    {"K3", app_config::kButtonK3Pin},
    {"K2", app_config::kButtonK2Pin},
    {"K1", app_config::kButtonK1Pin},
};

drivers::ButtonPanel button_panel(kButtons, sizeof(kButtons) / sizeof(kButtons[0]));
app::StatusLed status_led(app_config::kStatusLedPin, app_config::kStatusLedOnState,
                          app_config::kStatusBlinkIntervalMs);
drivers::OledPanel oled_panel(app_config::kOledPowerPin, app_config::kOledSdaPin,
                              app_config::kOledSclPin, app_config::kOledWidth,
                              app_config::kOledHeight, app_config::kI2cClockHz,
                              app_config::kOledUpdateIntervalMs);
}  // namespace

// cppcheck-suppress unusedFunction
void setup() {
  status_led.begin();
  button_panel.begin();

  Serial.begin(app_config::kSerialBaudrate);
  delay(250);

  Serial.println();
  Serial.println(APP_NAME " " APP_VERSION);
  Serial.println("Board: nRF52840 SuperMini / nice!nano");
  Serial.println("Status: booted");

  oled_panel.begin(button_panel);
}

// cppcheck-suppress unusedFunction
void loop() {
  const uint32_t now = millis();

  if (status_led.update(now)) {
    Serial.println(status_led.enabled() ? "led:on" : "led:off");
  }

  oled_panel.update(now, button_panel);
}
