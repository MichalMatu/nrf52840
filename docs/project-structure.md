# Project Structure

This repository is intended to be a standalone firmware workspace.

## Source of Truth

- `platformio.ini` defines the build environments.
- `boards/nicenano.json` defines the local PlatformIO board.
- `boards/nicenano/variant.h` and `boards/nicenano/variant.cpp` define the
  Arduino pin map.
- `src/main.cpp` is the default firmware entry point.
- `include/app_config.h` holds project-wide constants.

## Local-Only Research

The `vendor/` directory is ignored by git. It can contain large cloned
reference projects, but the firmware must not depend on files under `vendor/`.

When a useful example is promoted from `vendor/`, copy the relevant source into
`src/`, `lib/`, or `examples/` and update `platformio.ini` if needed.

