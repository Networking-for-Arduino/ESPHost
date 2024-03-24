
# esp-hosted firmware build for Adaruit AirLift (all form factors)

## The firmware

The firmware in this folder is built from GitHub master tag 0.5.0. Modifications are in build configuration, SPI pins in source and some source fixes.

## Upload instructions

Apply [the instructions for updating the firmware on AirLift shields](https://learn.adafruit.com/upgrading-esp32-firmware/upgrade-external-esp32-airlift-firmware-2).

upload command:

> esptool.py -b 460800 --before no_reset  write_flash --flash_mode dio --flash_freq 40m 0x1000 bootloader.bin 0x10000 network_adapter.bin 0x8000 partition-table.bin

Note: the esp-hosted firmware doesn't support access to the RGB LED on AirLift shields
