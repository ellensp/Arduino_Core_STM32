/**
  ******************************************************************************
  * @file    usbd_cdc_msc.h
  * @brief   CDC + MSC composite device, built with the ST composite builder
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_MSC_H
#define __USBD_CDC_MSC_H

#if defined(USBCON) && defined(USBD_USE_CDC_MSC)

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"
#include "usbd_cdc.h"

/* Exported functions ------------------------------------------------------- */
USBD_StatusTypeDef USBD_CDC_MSC_Init(USBD_HandleTypeDef *pdev, USBD_CDC_ItfTypeDef *cdc_fops);

#ifdef __cplusplus
}
#endif

#endif /* USBCON && USBD_USE_CDC_MSC */
#endif /* __USBD_CDC_MSC_H */
