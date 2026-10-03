/**
  ******************************************************************************
  * @file    usbd_cdc_msc.c
  * @brief   CDC + MSC composite device, built with the ST composite builder
  ******************************************************************************
  */
#ifdef USBCON
#ifdef USBD_USE_CDC_MSC

#include "usbd_cdc_msc.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_ep_conf.h"
#include "usbd_msc.h"
#include "usbd_msc_storage_if.h"
#include "usbd_composite_builder.h"

/* Endpoints, in the order the composite builder expects for each class */
static uint8_t CDC_EpAdd[] = {CDC_IN_EP, CDC_OUT_EP, CDC_CMD_EP};
static uint8_t MSC_EpAdd[] = {MSC_EPIN_ADDR, MSC_EPOUT_ADDR};

/**
  * @brief  Initialize the device and start it as CDC + MSC
  * @param  pdev: device handle
  * @param  cdc_fops: CDC interface callbacks
  * @retval USBD_OK if the device was started
  */
USBD_StatusTypeDef USBD_CDC_MSC_Init(USBD_HandleTypeDef *pdev, USBD_CDC_ItfTypeDef *cdc_fops)
{
  if (USBD_Init(pdev, &USBD_Desc, 0) != USBD_OK) {
    return USBD_FAIL;
  }

  /* Add both classes. The builder assigns interfaces and appends their descriptors. */
  if (USBD_RegisterClassComposite(pdev, USBD_CDC_CLASS, CLASS_TYPE_CDC, CDC_EpAdd) != USBD_OK) {
    return USBD_FAIL;
  }
  if (USBD_RegisterClassComposite(pdev, USBD_MSC_CLASS, CLASS_TYPE_MSC, MSC_EpAdd) != USBD_OK) {
    return USBD_FAIL;
  }

  /* Register each class' interface against its own class ID */
  if (USBD_CMPSIT_SetClassID(pdev, CLASS_TYPE_CDC, 0) == 0xFFU) {
    return USBD_FAIL;
  }
  if (USBD_CDC_RegisterInterface(pdev, cdc_fops) != USBD_OK) {
    return USBD_FAIL;
  }
  if (USBD_CMPSIT_SetClassID(pdev, CLASS_TYPE_MSC, 0) == 0xFFU) {
    return USBD_FAIL;
  }
  if (USBD_MSC_RegisterStorage(pdev, &USBD_MSC_fops) != USBD_OK) {
    return USBD_FAIL;
  }

  return USBD_Start(pdev);
}

#endif /* USBD_USE_CDC_MSC */
#endif /* USBCON */
