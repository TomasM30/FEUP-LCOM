#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#define SER_OVERRUN_ERR BIT(1)
#define SER_PARITY_ERR BIT(2)
#define SER_FRAME_ERR BIT(3)

#define RBR 0x00
#define THR 0x00
#define IER 0x01
#define IIR 0x02
#define FCR 0x02
#define LCR 0x03
#define MCR 0x04
#define LSR 0x05
#define MSR 0x06
#define SR 0x07
#define DLL 0x00
#define DLM 0x01

#define COM1_IRQ 4
#define COM2_IRQ 3
#define COM1_BASE_ADDR 0x3F8
#define COM2_BASE_ADDR 0x2F8

#define IER_RDAI BIT(0)
#define IER_THREI BIT(1)
#define IER_RLSI BIT(2)
#define IIR_NO_INT BIT(0)
#define IIR_RDA BIT(2)
#define IIR_THRE BIT(1)
#define IIR_ID BIT(1)|BIT(2)|BIT(3)
#define IIR_TIMEOUT BIT(3)|BIT(2)
#define LSR_THRE BIT(5)
#define LSR_RDA BIT(0)
#define FCR_ENABLE BIT(0)
#define FCR_CLEAR_RCVR BIT(1)
#define FCR_CLEAR_XMIT BIT(2)
#define LCR_CONFIG BIT(0)|BIT(1)|BIT(3)



#endif
