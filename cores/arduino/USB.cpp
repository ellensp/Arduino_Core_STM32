/*
 * USB.cpp
 *
 * USBDevice: start and stop the USB device, and register Mass Storage handlers
 * when it is a CDC + MSC composite (USBD_USE_CDC_MSC).
 */
#include "USB.h"

#ifdef USBCON

#ifdef USBD_USE_CDC
  #include "usbd_cdc_if.h"
#endif
#ifdef USBD_USE_MSC_CLASS
  #include "usbd_msc_storage_if.h"

  extern USBMscHandler **ppUsbMscHandlers;
  extern uint8_t usbMscMaxLun;
#endif

USBComposite USBDevice;

#ifdef USBD_USE_MSC_CLASS

void USBComposite::registerMscHandler(USBMscHandler &handler)
{
  pSingleMscHandler = &handler;
  registerMscHandlers(1, &pSingleMscHandler, nullptr);
}

void USBComposite::registerMscHandlers(uint8_t count, USBMscHandler **ppHandlers, uint8_t *pInquiryData)
{
  if (count == 0 || ppHandlers == nullptr) {
    return;
  }
  ppUsbMscHandlers = ppHandlers;
  usbMscMaxLun = count - 1;
  if (pInquiryData != nullptr) {
    USBD_MSC_fops.pInquiry = (int8_t *)pInquiryData;
  }
}

#endif /* USBD_USE_MSC_CLASS */

// The device is started and stopped with the CDC serial port
void USBComposite::begin(void)
{
#ifdef USBD_USE_CDC
  CDC_init();
#endif
}

void USBComposite::end(void)
{
#ifdef USBD_USE_CDC
  CDC_deInit();
#endif
}

#endif /* USBCON */
