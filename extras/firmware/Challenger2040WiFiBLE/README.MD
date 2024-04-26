
# esp-hosted firmware build for iLabs Challenger 2040 WiFi/BLE (ESP32C3) board

## The firmware

The firmware in this folder is built from GitHub master tag 0.5.0. Modifications are in build configuration and some source fixes.

## Upload instructions

// TODO

upload command:

> esptool.py -b 460800 write_flash --flash_mode dio --flash_size 2MB --flash_freq 80m 0x0 build/bootloader.bin 0x8000 build/partition-table.bin 0x10000 build/network_adapter.bin
