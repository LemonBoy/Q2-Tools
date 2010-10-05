#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "uFb.h"

static int fbfd = 0;
static unsigned short *fb = NULL;

int fbInit ()
{
    fbfd = open("/dev/fb", O_RDWR);
    if (!fbfd)
        return 0;
    fb = (unsigned short *)mmap(0, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (!fb)
        return 0;
    return 1;
}

void fbFlip ()
{
    unsigned int screen_region[4] = {
        0, // X
        0, // Y
        320, // Width
        240, // Height
    };
    if (ioctl(fbfd, 0x4010C10A, screen_region))
        printf("Cannot update screen!\n");
}

void fbPut (unsigned int x, unsigned int y, unsigned int pixel)
{
    fb[y*240+x] = (pixel&0xFFFF);
}

int main ()
{
    uFbInit(240, 320, fbInit, fbPut, fbFlip);
    memset(fb, 0, 320*240*2);
    uFbPrint("Hello World YP-Q2!\nHack&code : The Lemon Man!\nLess drama and moar haxx!\n\nGreetz to #HACKERCHANNEL crew\nReset the player to quit :)");
    while (1)
        uFbDrawEnd();
}
