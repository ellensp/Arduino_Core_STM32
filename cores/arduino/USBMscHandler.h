/*
 * USBMscHandler.h
 *
 * Storage behind the USB Mass Storage (MSC) class. Implement one per LUN and
 * register them with USBDevice.registerMscHandlers().
 */
#ifndef _USB_MSC_HANDLER_H_
#define _USB_MSC_HANDLER_H_

#include "usbd_conf.h"

#if defined(USBCON) && defined(USBD_USE_MSC_CLASS)

#include <stdint.h>

class USBMscHandler {
  public:
    // Number of blocks and block size. Return true if successful.
    virtual bool GetCapacity(uint32_t *pBlockNum, uint16_t *pBlockSize) = 0;

    // Read blkLen blocks from blkAddr into pBuf. Return true if successful.
    virtual bool Read(uint8_t *pBuf, uint32_t blkAddr, uint16_t blkLen) = 0;

    // Write blkLen blocks from pBuf to blkAddr. Return true if successful.
    virtual bool Write(uint8_t *pBuf, uint32_t blkAddr, uint16_t blkLen) = 0;

    // Optional
    virtual bool Init() { return true; }
    virtual bool IsReady() { return true; }             // Medium present and usable
    virtual bool IsWriteProtected() { return false; }

    virtual ~USBMscHandler() {}
};

// Never ready. Used until a handler is registered.
class DummyUSBMscHandler : public USBMscHandler {
  public:
    bool GetCapacity(uint32_t *, uint16_t *) override { return false; }
    bool Read(uint8_t *, uint32_t, uint16_t) override { return false; }
    bool Write(uint8_t *, uint32_t, uint16_t) override { return false; }
    bool IsReady() override { return false; }
};

#endif /* USBCON && USBD_USE_MSC_CLASS */
#endif /* _USB_MSC_HANDLER_H_ */
