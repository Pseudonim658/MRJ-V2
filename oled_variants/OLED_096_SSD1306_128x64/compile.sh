#!/bin/bash
FQBN="esp32:esp32:esp32"
DIR="$(cd "$(dirname "$0")" && pwd)"
FLAGS="-DMRJ_DISPLAY_SSD1306_096 -DMRJ_DISPLAY_WIDTH=128 -DMRJ_DISPLAY_HEIGHT=64"
arduino-cli compile --fqbn "$FQBN" --build-property "compiler.cpp.extra_flags=$FLAGS" --build-property "compiler.c.extra_flags=$FLAGS" "$DIR"
