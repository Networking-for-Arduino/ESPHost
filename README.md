# ESPHost library

Arduino driver for communicating with Espressif's [esp-hosted-fg firmware](https://github.com/espressif/esp-hosted).

The library is meant to serve as low level driver for a LwIP network interface implementation. 

The library was originally written for Arduino Portenta C33 with Arduino Renesas Core.

## Notes:

* configuration is TODO
* pins are hardcoded in EspSpiDriver
* SPI SCK is set to 10 MHz for classic ESP32

## Firmware

* [the released fg fw](https://github.com/espressif/esp-hosted/releases/tag/release%2Ffg-v0.0.5) for classic ESP32 uses SPI on pins [12, 13, 14, 15] even [the doc says](https://github.com/espressif/esp-hosted/blob/master/esp_hosted_fg/docs/MCU_based_host/SPI_setup.md#hardware-connections-for-esp32) it is [23, 19, 18, 5]
* firmware builds for specific boards are in extras/firmware
