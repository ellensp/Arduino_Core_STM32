/*
 * USB.h
 *
 * USBDevice: start and stop the USB device, and register Mass Storage handlers
 * when it is a CDC + MSC composite (USBD_USE_CDC_MSC).
 */
#ifndef _USB_H_
#define _USB_H_

#include "usbd_conf.h"

#ifdef USBCON

#ifdef USBD_USE_MSC_CLASS
  #include "USBMscHandler.h"
#endif

class USBComposite {
  public:
#ifdef USBD_USE_MSC_CLASS
    // One handler, using the default inquiry data
    void registerMscHandler(USBMscHandler &handler);
    // One handler per LUN, with STANDARD_INQUIRY_DATA_LEN bytes of inquiry data per LUN
    void registerMscHandlers(uint8_t count, USBMscHandler **ppHandlers, uint8_t *pInquiryData);
#endif
    void begin(void);
    void end(void);

  private:
#ifdef USBD_USE_MSC_CLASS
    USBMscHandler *pSingleMscHandler = nullptr;
#endif
};

extern USBComposite USBDevice;

#endif /* USBCON */
#endif /* _USB_H_ */
