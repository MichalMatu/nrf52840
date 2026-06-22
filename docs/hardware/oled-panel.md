# OLED Panel Wiring

This describes the currently working black OLED panel with header labels:

```text
GND VCC SCL SDA K4 K3 K2 K1
```

## Working wiring

| OLED pin | nRF52840 alias | Purpose |
| --- | --- | --- |
| GND | GND | Ground |
| VCC | PIN_017 | Test power output |
| SCL | PIN_020 | I2C clock |
| SDA | PIN_022 | I2C data |
| K4 | PIN_024 | Button input |
| K3 | PIN_100 | Button input |
| K2 | PIN_011 | Button input |
| K1 | PIN_104 | Button input |

The firmware enables `PIN_017` before I2C initialization, configures the
buttons as `INPUT_PULLUP`, scans I2C, and tries SSD1306 addresses `0x3C` and
`0x3D`.

## Stability notes

- Disconnect USB before rewiring the panel.
- Verify `GND`, `VCC`, `SCL`, and `SDA` before powering the board.
- If the OLED flickers, resets the board, or fails after adding more hardware,
  move `VCC` to the board supply rail and use `PIN_017` only as an enable
  signal through external switching hardware.
