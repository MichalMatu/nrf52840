#pragma once

#include <Arduino.h>
#include <stddef.h>

namespace drivers {

struct ButtonConfig {
  const char* name;
  uint8_t pin;
};

class ButtonPanel {
 public:
  ButtonPanel(const ButtonConfig* buttons, size_t count);

  void begin() const;
  size_t count() const;
  const ButtonConfig& at(size_t index) const;
  bool pressed(size_t index) const;

 private:
  const ButtonConfig* buttons_;
  size_t count_;
};

}  // namespace drivers
