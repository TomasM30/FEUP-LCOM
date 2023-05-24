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

#define THR_EMPTY BIT(5)
#define RR_READY BIT(0)
#define IER_RDAI BIT(0)
#define INT_PEND BIT(0)
#define INT_ID BIT(1)
#define RX_INT BIT(2)

#endif
