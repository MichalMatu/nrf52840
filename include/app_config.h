#pragma once

#include <Arduino.h>

namespace app_config {

constexpr uint8_t kStatusLedPin = LED_BUILTIN;
constexpr uint8_t kStatusLedOnState = LED_STATE_ON;
constexpr uint32_t kStatusBlinkIntervalMs = 1000UL;
constexpr uint32_t kSerialBaudrate = 115200UL;

constexpr uint8_t kOledPowerPin = PIN_017;
constexpr bool kOledUsesGpioPower = false;
constexpr uint8_t kOledSclPin = PIN_020;
constexpr uint8_t kOledSdaPin = PIN_022;
constexpr uint16_t kOledWidth = 128;
constexpr uint16_t kOledHeight = 64;
constexpr uint32_t kOledUpdateIntervalMs = 250UL;
constexpr uint32_t kOledScanIntervalMs = 3000UL;
constexpr uint32_t kI2cClockHz = 400000UL;
constexpr bool kOledDiagnosticMode = false;

constexpr uint8_t kButtonK4Pin = PIN_024;
constexpr uint8_t kButtonK3Pin = PIN_100;
constexpr uint8_t kButtonK2Pin = PIN_011;
constexpr uint8_t kButtonK1Pin = PIN_104;

}  // namespace app_config
