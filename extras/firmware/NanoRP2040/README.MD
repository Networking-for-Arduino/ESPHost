
# esp-hosted firmware build for Arduino Nano RP2040 Connect

## The firmware

The firmware in this folder is built from GitHub master tag 0.5.0. Modifications are in build configuration, SPI pins in source, some source fixes and pull-up of TX pin is switched off, to not pull-up the CS pin.

## Upload instructions

before firmware upload, upload SerialNINAPassthrough.ino from WiFiNINA examples into the RP2040

upload command:

> esptool.py -b 460800 --before no_reset  write_flash --flash_mode dio --flash_size 2MB --flash_freq 40m 0x1000 build/bootloader.bin 0x8000 build/partition-table.bin 0xd000 build/ota_data_initial.bin 0x10000 build/network_adapter.bin

Note: the esp-hosted firmware doesn't support access to the RGB LED and pins A4 to A7 as the nina-fw does

## Nano RP2040 Problem with esp32 TX pin

The Nano connects one io of RP2040 to two esp32 pins, SPI and UART. The SPI CS pin is wired to esp32 UART TX pin too. The esp32 with the hosted firmware has a pullup on UART TX even the firmware doesn't use UART (IDF sets the pull-up). The RP2040 was unable to pull down two pulled up io of the esp32.