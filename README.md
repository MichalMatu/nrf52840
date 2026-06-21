# nRF52840 SuperMini PlatformIO Starter

Standalone PlatformIO project for nRF52840 SuperMini / nice!nano boards using
the Arduino nRF52 framework.

The repository contains the board definition and variant files required by
PlatformIO, so a fresh clone does not need the local `vendor/` research
directory to build.

## Quick Start

Build:

```sh
pio run
```

Enter bootloader mode with a quick double reset: short `RST` to `GND`, release,
then short `RST` to `GND` again.

Upload after the board appears as `nice!nano`:

```sh
pio run -t upload
```

If multiple USB devices are attached, pass the detected nice!nano port:

```sh
pio run -t upload --upload-port /dev/cu.usbmodem1101
```

Monitor serial output when the application exposes a CDC port:

```sh
pio device monitor -b 115200
```

## Layout

```text
boards/              Local PlatformIO board definition and Arduino variant
src/                 Application firmware
include/             Project-wide headers and configuration
lib/                 Project-specific reusable libraries
test/                PlatformIO unit tests
examples/            Reference sketches and experiments
scripts/             Developer helper scripts
docs/                Hardware notes, setup, and operating procedures
vendor/              Ignored local research snapshots
```

## Current Firmware

The starter firmware toggles `LED_BUILTIN` once per second and prints a boot
message on USB serial when the CDC interface is available.

## Useful Commands

```sh
pio run
pio run -t upload
pio device list
pio device monitor -b 115200
```

