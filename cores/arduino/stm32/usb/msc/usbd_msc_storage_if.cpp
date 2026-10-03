/**
  ******************************************************************************
  * @file    usbd_msc_storage_if.cpp
  * @brief   MSC storage interface, forwarding to the registered USBMscHandler(s)
  ******************************************************************************
  */
#include "usbd_conf.h"

#if defined(USBCON) && defined(USBD_USE_MSC_CLASS)

#include "usbd_msc_storage_if.h"
#include "USBMscHandler.h"

/* Until a handler is registered every LUN reports "not ready" */
static DummyUSBMscHandler dummyHandler;
static USBMscHandler *pDummyHandler = &dummyHandler;

USBMscHandler **ppUsbMscHandlers = &pDummyHandler;
uint8_t usbMscMaxLun = 0;

/* Default SCSI inquiry data, one entry of STANDARD_INQUIRY_DATA_LEN bytes per LUN */
static uint8_t STORAGE_Inquirydata[STANDARD_INQUIRY_DATA_LEN] = {
  0x00,                                      /* Direct access device */
  0x80,                                      /* Removable media */
  0x02,                                      /* SPC-2 */
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5U),
  0x00, 0x00, 0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ',    /* Vendor (8 bytes) */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ',    /* Product (16 bytes) */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0', '1'                         /* Version (4 bytes) */
};

static USBMscHandler *handler(uint8_t lun)
{
  return ppUsbMscHandlers[lun <= usbMscMaxLun ? lun : 0];
}

static int8_t STORAGE_Init(uint8_t lun)
{
  return handler(lun)->Init() ? USBD_OK : -1;
}

static int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  return handler(lun)->GetCapacity(block_num, block_size) ? USBD_OK : -1;
}

static int8_t STORAGE_IsReady(uint8_t lun)
{
  return handler(lun)->IsReady() ? USBD_OK : -1;
}

static int8_t STORAGE_IsWriteProtected(uint8_t lun)
{
  return handler(lun)->IsWriteProtected() ? 1 : USBD_OK;
}

static int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  return handler(lun)->Read(buf, blk_addr, blk_len) ? USBD_OK : -1;
}

static int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  return handler(lun)->Write(buf, blk_addr, blk_len) ? USBD_OK : -1;
}

static int8_t STORAGE_GetMaxLun(void)
{
  return (int8_t)usbMscMaxLun;
}

extern "C" {

USBD_StorageTypeDef USBD_MSC_fops = {
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  (int8_t *)STORAGE_Inquirydata
};

}

#endif /* USBCON && USBD_USE_MSC_CLASS */
