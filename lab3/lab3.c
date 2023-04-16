#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "kbc.h"

extern uint32_t cnt;
extern uint8_t scancode;
extern int counter;

int main(int argc, char *argv[]) {
	// sets the language of LCF messages (can be either EN-US or PT-PT)
	lcf_set_language("EN-US");

	// enables to log function invocations that are being "wrapped" by LCF
	// [comment this out if you don't want/need it]
	// lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

	// enables to save the output of printf function calls on a file
	// [comment this out if you don't want/need it]
	// lcf_log_output("/home/lcom/labs/lab3/output.txt");

	// handles control over to LCF
	// [LCF handles command line arguments and invokes the right function]
	if (lcf_start(argc, argv))
		return 1;

	// LCF clean up tasks
	// [must be the last statement before return]
	lcf_cleanup();

	return 0;
}

int (kbd_test_scan)() {
	int ipc_status;
	uint8_t irq_set;
	message msg;
	uint8_t r;

	uint8_t bytes[2];

	if (kbc_subscribe_int(&irq_set) != 0) return 1;

	int i = 0;

	while (scancode != KBC_BRK_ESC_KEY) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver receiver failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
					if (msg.m_notify.interrupts & irq_set) {
						kbc_ih();
						if (scancode == KBC_2BYTE_CODE) {
							bytes[i] = scancode;
							i++; 
							continue;
						}
						
						bytes[i] = scancode;
						kbd_print_scancode(!(scancode & KBC_MSB_SCNCD), i + 1, bytes);
						i = 0;
					}
					break;

				default: break;
			}
		}
	}

	if (kbc_unsubscribe_int() != 0) return 1;
	
	if (kbd_print_no_sysinb(cnt) != 0) return 1;

	return 0;
}

int (kbd_test_poll)() {
	/* To be completed by the students */
	printf("%s is not yet implemented!\n", __func__);

	return 1;
}

int (kbd_test_timed_scan)(uint8_t n) {
	int ipc_status;
	uint8_t irq_set_timer, irq_set_kbc;
	message msg;
	uint8_t r;

	uint8_t bytes[2];

	if (timer_set_frequency(0, 60) != 0) return 1;

	if (timer_subscribe_int(&irq_set_timer) != 0) return 1;

	if (kbc_subscribe_int(&irq_set_kbc) != 0) return 1;

	int i = 0;
	while ((scancode != KBC_BRK_ESC_KEY) && (counter < 60 * n)) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver receiver failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
					if (msg.m_notify.interrupts & BIT(irq_set_timer)) {
						timer_int_handler();
					}

					if (msg.m_notify.interrupts & BIT(irq_set_kbc)) {
						kbc_ih();
						if (scancode == KBC_2BYTE_CODE) {
							bytes[i] = scancode;
							i++;
							continue;
						}

						bytes[i] = scancode;
						if (kbd_print_scancode(!(scancode & KBC_MSB_SCNCD), i + 1, bytes));
						i = 0; counter = 0;
					}
					break;

				default: break;
			}
		}
	}

	if (timer_unsubscribe_int() != 0) return 1;

	if (kbc_unsubscribe_int() != 0) return 1;

	if (kbd_print_no_sysinb(cnt) != 0) return 1;

	return 0;
}
