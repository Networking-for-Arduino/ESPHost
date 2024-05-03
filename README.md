# ESPHost library

Arduino driver for communicating with Espressif's [esp-hosted-fg firmware](https://github.com/espressif/esp-hosted).

The library is meant to serve as low level driver for a LwIP network interface implementation. 

The library was originally made by Arduino for Portenta C33 with Arduino Renesas Core.

## Integration

This standalone ESPHost library is now used by lwIP_ESPHost library in Pico Core for RP2040 and in [ESPHost-EMAC library](https://github.com/JAndrassy/ESPHost-EMAC) for Arduino Mbed Core.

## Hardware

The esp-hosted firmware version 0.5.0 runs on classic ESP32, ESP32-S2/S3, ESP32-C2/C3. The pins for released firmware builds are described in esp-hosted-fg documentation. Firmware builds for some specific boards are in this repository in extras/firmware.

Arduino Nano RP2040 Connect is the ideal board for ESPHost because it has on board ESP32 NINA module and it can be used with the Mbed Core and with the Pico Core.

The Adafruit AirLift shields in combination with Adafruit RP2040 boards offer a simple hardware setup in all sizes (Metro, Feather, ItsyBitsy).

The iLabs Challenger 2040 WiFi/BLE board has ESP32-C3 on board. 


## Configuration

Pins are configured with defines. To add the defines, modify boards.txt or create boards.local.txt next to boards.txt and add `<board>.build.extra_flags`. For boards with defines for the WiFiNINA library it is enough to add `-DESPHOSTSPI`.

Complete settings require to specify pins. Example:

```
rpipico.build.extra_flags=-DESPHOST_RESET=D5 -DESPHOST_HANDSHAKE=D7 -DESPHOST_DATA_READY=D6 -DESPHOST_CS=D10 -DESPHOSTSPI=SPI
```

Default SPI frequency set in the library is 10 MHz. It is the highest SPI speed for classic ESP32. Firmware for C and S series ESP32 are build with higher SPI frequency. To specify the SPI frequency to be used by the ESPHost library, add `-DESPHOSTSPI_MHZ=30` to `<board>.build.extra_flags`.

## Notes

* [the released fg fw](https://github.com/espressif/esp-hosted/releases/tag/release%2Ffg-v0.0.5) for classic ESP32 uses SPI on pins [12, 13, 14, 15] even [the doc says](https://github.com/espressif/esp-hosted/blob/master/esp_hosted_fg/docs/MCU_based_host/SPI_setup.md#hardware-connections-for-esp32) it is [23, 19, 18, 5]
