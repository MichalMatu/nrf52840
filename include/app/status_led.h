#pragma once

#include <Arduino.h>

namespace app {

class StatusLed {
 public:
  StatusLed(uint8_t pin, uint8_t on_state, uint32_t interval_ms);

  void begin();
  bool update(uint32_t now_ms);
  bool enabled() const;

 private:
  void set(bool enabled);
  uint8_t off_state() const;

  uint8_t pin_;
  uint8_t on_state_;
  uint32_t interval_ms_;
  uint32_t last_toggle_ms_;
  bool enabled_;
};

}  // namespace app
