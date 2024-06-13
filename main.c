#include "framebuffer.h"
#include "display.h"
#include <stdio.h>
#include <unistd.h>
#define BLACK 0x0000

int main(void) {
    if (!open_display()) {
        fprintf(stderr, "Failed to open display.\n");
        return 1;
    }
    open_display();
    int hours, minutes, seconds;

    while (scanf("%d:%d:%d", &hours, &minutes, &seconds) == 3) {
        display_time(hours, minutes, seconds);
        sleep(1);
    }

    printf("closing display!\n");
    close_display();
    return 0;

 }  
