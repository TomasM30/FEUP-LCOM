#ifndef _LCOM_I8042_H
#define _LCOM_I8042_H

#include <lcom/lcf.h>

#define KBC_ESC 0x81
#define KBC_OUT_BUF 0x60
#define KBC_INP_BUF 0x60
#define KBC_STATUS 0x64

#define KBC_IRQ 1

#define KBC_ST_INB BIT(1)
#define KBC_ST_OBF BIT(0)
#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)

#define SCAN_MK_OR_BR BIT(7)

#endif
