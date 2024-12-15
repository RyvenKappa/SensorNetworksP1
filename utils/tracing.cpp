#include "tracing.h"


void print_memory_info() {
    // allocate enough room for every thread's stack statistics
    int cnt = osThreadGetCount();
    mbed_stats_stack_t *stats = (mbed_stats_stack_t *) malloc(cnt * sizeof(mbed_stats_stack_t));

    if (stats) {
        cnt = mbed_stats_stack_get_each(stats, cnt);
        for (int i = 0; i < cnt; i++) {
            printf("Thread: 0x%lx, Stack size: %u, Max stack: %u\r\n",
                   stats[i].thread_id, stats[i].reserved_size, stats[i].max_size);
        }
        free(stats);
    }
}
