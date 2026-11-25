/*
    EsphostedBtGlue.cpp - core<->driver glue for ESP-Hosted Bluetooth

    Registers the CEspControl entry points the arduino-pico core needs to
    drive Bluetooth HCI over the ESP-Hosted link (see
    cores/rp2040/esphosted_bt.{h,cpp}).

    This object lives in the ESPHost library on purpose: the core must not
    reference CEspControl directly, because a sketch that uses neither WiFi
    nor BLE never links this library and would fail to link.  The core only
    calls through the ops table below; this file is pulled into the link by
    esphostedBtGlueInstall() calls from BLE.begin()/BluetoothHCI::begin() and
    the WiFi driver's initHW() -- i.e. exactly when the driver is present.

    Copyright (c) 2026 Pontus Oldberg

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifdef ESPHOST_BT

#include <Arduino.h>
#include "CEspControl.h"

// Core hooks (cores/rp2040/esphosted_bt.h; declared here so this library
// does not need the btstack headers that header pulls in).
extern "C" {
typedef struct esphostedHciOps {
    bool (*bringUp)(void);
    void (*pump)(void);
    int (*sendHci)(uint8_t packetType, uint8_t *packet, uint16_t size);
    uint16_t (*getHciRx)(uint8_t *packetType, uint8_t *buf, uint16_t bufsize);
} esphostedHciOps;
void esphostedBtRegisterOps(const esphostedHciOps *ops);
}

// The core's link lock (cores/rp2040/lwip_wrap.h): every pass into the
// driver must hold it so the DATA_READY GPIO IRQ and the lwIP background
// pump never run inside the driver concurrently with BTstack servicing.
#include <lwip_wrap.h>

static volatile bool s_linkUp = false;

static int esphostedInitEventCb(CCtrlMsgWrapper *resp) {
    (void) resp;
    s_linkUp = true;
    return ESP_CONTROL_OK;
}

static bool glueBringUp(void) {
    if (s_linkUp) {
        return true;
    }
    // CEspCbk keeps a single callback per event: the init-event slot belongs
    // to this glue whenever ESPHOST_BT is defined (the WiFi driver delegates
    // link bring-up to the core, which lands here).
    CEspControl::getInstance().listenForInitEvent(esphostedInitEventCb);
    if (CEspControl::getInstance().initSpiDriver() != 0) {
        return false;
    }
    uint32_t start = millis();
    while (!s_linkUp && (millis() - start < 10000)) {
        {
            LWIPMutex m;
            CEspControl::getInstance().communicateWithEsp();
        }
        delay(100);
    }
    return s_linkUp;
}

static void gluePump(void) {
    CEspControl::getInstance().communicateWithEsp();
}

static int glueSendHci(uint8_t packetType, uint8_t *packet, uint16_t size) {
    int rv = CEspControl::getInstance().sendHciPacket(packetType, packet, size);
    return rv == ESP_CONTROL_OK ? 0 : -1;
}

static uint16_t glueGetHciRx(uint8_t *packetType, uint8_t *buf, uint16_t bufsize) {
    return CEspControl::getInstance().getHciRx(*packetType, buf, bufsize);
}

static const esphostedHciOps s_ops = {
    &glueBringUp,
    &gluePump,
    &glueSendHci,
    &glueGetHciRx,
};

extern "C" void esphostedBtGlueInstall(void) {
    esphostedBtRegisterOps(&s_ops);
}

#endif // ESPHOST_BT
