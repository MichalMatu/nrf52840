#pragma once

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

#include "drivers/button_panel.h"

namespace drivers {

class OledPanel {
 public:
  OledPanel(uint8_t power_pin, bool uses_gpio_power, uint8_t sda_pin, uint8_t scl_pin,
            uint16_t width, uint16_t height, uint32_t i2c_clock_hz, uint32_t update_interval_ms);

  void begin(const ButtonPanel& buttons);
  void update(uint32_t now_ms, const ButtonPanel& buttons);
  bool ready() const;
  uint8_t address() const;

 private:
  void begin_power();
  void ensure_wire();
  bool begin_display_at(uint8_t address);
  void draw_boot_screen();
  void draw_status_screen(const ButtonPanel& buttons);

  uint8_t power_pin_;
  bool uses_gpio_power_;
  uint8_t sda_pin_;
  uint8_t scl_pin_;
  uint32_t i2c_clock_hz_;
  uint32_t update_interval_ms_;
  uint32_t last_update_ms_;
  Adafruit_SSD1306 display_;
  bool ready_;
  bool wire_ready_;
  uint8_t address_;
};

}  // namespace drivers
