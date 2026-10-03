#ifdef USBCON
#include "usbd_conf.h"
#ifdef USBD_USE_MSC_CLASS
#include "usbd_msc.c"
#include "usbd_msc_bot.c"
#include "usbd_msc_data.c"
#include "usbd_msc_scsi.c"
#endif /* USBD_USE_MSC_CLASS */
#endif /* USBCON */
