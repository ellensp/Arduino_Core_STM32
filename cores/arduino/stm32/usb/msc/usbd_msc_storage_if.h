/**
  ******************************************************************************
  * @file    usbd_msc_storage_if.h
  * @brief   MSC storage interface, forwarding to the registered USBMscHandler(s)
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_MSC_STORAGE_IF_H
#define __USBD_MSC_STORAGE_IF_H

#if defined(USBCON) && defined(USBD_USE_MSC_CLASS)

#include "usbd_msc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern USBD_StorageTypeDef USBD_MSC_fops;

#ifdef __cplusplus
}
#endif

#endif /* USBCON && USBD_USE_MSC_CLASS */
#endif /* __USBD_MSC_STORAGE_IF_H */
