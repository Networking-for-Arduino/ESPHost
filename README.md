# ESPHost library

Arduino driver for communicating with Espressif's [esp-hosted-fg firmware](https://github.com/espressif/esp-hosted).

The library is meant to serve as low level driver for a LwIP network interface implementation. 

The library was originally written for Arduino Portenta C33 with Arduino Renesas Core.

## Configuration

Pins are configured with defines. To add the defines, modify boards.txt or create boards.local.txt next to boards.txt and add <board>.build.extra_flags=. For boards with defines for the WiFiNINA library it is enough to add `-DESPHOSTSPI`.

Complete settings require to specify pins. Example:

```
rpipico.build.extra_flags=-DESPHOST_RESET=D5 -DESPHOST_HANDSHAKE=D7 -DESPHOST_DATA_READY=D6 -DESPHOST_CS=D10 -DESPHOSTSPI=SPI
```

Default SPI frequency set in the library is 10 MHz. It is the highest SPI speed for classic ESP32. Firmware for C and S series ESP32 are build with higher SPI frequency. To specify the SPI frequency to be used by the ESPHost library, add `-DESPHOSTSPI_MHZ=30` to `<board>.build.extra_flags`.

## Firmware

* [the released fg fw](https://github.com/espressif/esp-hosted/releases/tag/release%2Ffg-v0.0.5) for classic ESP32 uses SPI on pins [12, 13, 14, 15] even [the doc says](https://github.com/espressif/esp-hosted/blob/master/esp_hosted_fg/docs/MCU_based_host/SPI_setup.md#hardware-connections-for-esp32) it is [23, 19, 18, 5]
* firmware builds for specific boards are in extras/firmware
