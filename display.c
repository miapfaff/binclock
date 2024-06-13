#include "display.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define BLACK 0x0000

pi_framebuffer_t* fb = NULL;
sense_fb_bitmap_t* bm = NULL;

int open_display(void) {
//   sense_fb_bitmap_t *bm = fb->bitmap;
//     clearFrameBuffer(fb, BLACK);
    // Check if the display has already been opened
//    fb = getFrameBuffer();
   if (fb != NULL) {
        fprintf(stderr, "Display has already been opened.\n");
        return 0;
    }
    fb = getFrameBuffer();
    sense_fb_bitmap_t *bm = fb->bitmap;  
  // Get the framebuffer
    if (fb == NULL) {
        fprintf(stderr, "Failed to open display.\n");
        return 0;
    }

    // Successfully open
    return 1;
}

void display_time(int hours, int minutes, int seconds) {
    fb = getFrameBuffer();
    sense_fb_bitmap_t *bm = fb->bitmap;
    clearFrameBuffer(fb, BLACK);
    display_colons();
    display_hours(hours);
    display_minutes(minutes);
    display_seconds(seconds);
}

void display_colons(void) {
     fb = getFrameBuffer();
     sense_fb_bitmap_t *bm = fb->bitmap; 
     bm->pixel[1][4]=WHITE;
     bm->pixel[2][4]=WHITE;
     bm->pixel[1][5]=WHITE;
     bm->pixel[2][5]=WHITE;
     bm->pixel[4][4]=WHITE;
     bm->pixel[4][5]=WHITE;
     bm->pixel[5][4]=WHITE;
     bm->pixel[5][5]=WHITE;

     bm->pixel[5][2]=WHITE;
     bm->pixel[5][1]=WHITE;
     bm->pixel[4][1]=WHITE;
     bm->pixel[4][2]=WHITE;
     bm->pixel[2][1]=WHITE;
     bm->pixel[2][2]=WHITE;
     bm->pixel[1][1]=WHITE;
     bm->pixel[1][2]=WHITE;
}

void display_hours(int hours) {
    fb = getFrameBuffer();
    sense_fb_bitmap_t *bm = fb->bitmap;
    int numBits = 0; // Number of bits needed to represent the hours
    int tempHours = hours;
    
    // Calculate the number of bits needed
    while (tempHours > 0) {
        tempHours >>= 1;
        numBits++;
    }
    
    // Iterate through each bit position
    for (int i = 0; i < numBits; i++) {
        int bit = (hours >> (numBits - 1 - i)) & 1; // Extract individual bit starting from the most significant bit
        bm->pixel[6][7 - i] = bit ? BLUE : 0; // Set LED to blue if the bit is 1, otherwise, turn off
    }
}

void display_minutes(int minutes) {
    fb = getFrameBuffer();
    sense_fb_bitmap_t *bm = fb->bitmap;
    int numBits = 0; // Number of bits needed to represent the minutes
    int tempMinutes = minutes;
    
    // Calculate the number of bits needed
    while (tempMinutes > 0) {
        tempMinutes >>= 1;
        numBits++;
    }
    
    // Iterate through each bit position
    for (int i = 0; i < numBits; i++) {
        int bit = (minutes >> (numBits - 1 - i)) & 1; // Extract individual bit starting from the most significant bit
        bm->pixel[3][7 - i] = bit ? GREEN : 0; // Set LED to green if the bit is 1, otherwise, turn off
    }
}

void display_seconds(int seconds) {
    fb = getFrameBuffer();
    sense_fb_bitmap_t *bm = fb->bitmap;
    int numBits = 0; // Number of bits needed to represent the minutes
    int tempSeconds = seconds;

    // Calculate the number of bits needed
    while (tempSeconds > 0) {
        tempSeconds >>= 1;
        numBits++;
    }

    // Iterate through each bit position
    for (int i = 0; i < numBits; i++) {
        int bit = (seconds >> (numBits - 1 - i)) & 1; // Extract individual bit starting from the most significant bit
        bm->pixel[0][7 - i] = bit ? RED : 0; // Set LED to green if the bit is 1, otherwise, turn off
    }
}
void close_display(void) {
//    fb = getFrameBuffer();
//    clearFrameBuffer(fb, BLACK);
    if(fb != NULL){
        clearFrameBuffer(fb,BLACK);
        sleep(1);
//        printf("Framebuffer freed.\n");
        freeFrameBuffer(fb);
        fb = NULL;
    }
}
