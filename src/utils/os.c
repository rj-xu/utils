#include "reg/reg.h"
#include "reg32.h"
#include "wait_for.h"

// char *_sbrk(int incr)
// {
//     extern char __end__;
//     static char *heap_end;
//     if (0 == heap_end)
//     {
//         heap_end = &__end__;
//     }
//     char *prev_heap_end = heap_end;
//     heap_end += incr;
//     return prev_heap_end;
// }

int _write(int file, const char *ptr, int len) // NOLINT(bugprone-reserved-identifier)
{
    (void)file;
    int c = 0;
    // UART1->uart_ctrl.bit.TX_NUM_CFG = 1;
    for (; c < len; c++)
    {
        LOOP_FOR(!UART1->txstatus.bit.TX_BUSY);
        UART1->txdr.bit.TX_DAT_FIFO = (uint32_t)ptr[c];
        TRIGGER(UART1->uart_ctrl.bit.TRANS_EN);
    }
    return c;
}
