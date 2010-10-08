#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "libQ2.h"

/* Input support */

static int ttyfd = 0;
static unsigned char oldKeys = 0;

#define LINUX_KDGKBMODE     0x4B44
#define LINUX_KDSKBMODE     0x4B45
#define K_MEDIUMRAW         2

int inputInit ()
{
    struct termios newTerm;
    int termMode = 0;
    ttyfd = open("/dev/tty0", O_RDONLY);
    if (ttyfd < 0)
        return 0;
    if (ioctl(ttyfd, LINUX_KDGKBMODE, &termMode))
        return 0;
    tcgetattr(ttyfd, &newTerm);
    newTerm.c_lflag &= ~0xB;
    newTerm.c_iflag &= ~0x15C0;
    newTerm.c_iflag &= ~0x22;
    newTerm.c_cc[VSTOP] = 0;
    newTerm.c_cc[VSUSP] = 0;
    newTerm.c_cc[VMIN] = 0;
    newTerm.c_cc[VTIME] = 0;
    tcsetattr(ttyfd, TCSAFLUSH, &newTerm);
    if (ioctl(ttyfd, LINUX_KDSKBMODE, K_MEDIUMRAW))
        return 0;
    return 1;
}

unsigned char inputRead ()
{
    unsigned char keys;

    if (ttyfd < 0)
        return 0;

    if (read(ttyfd, &keys, 1) != 1)
    {
        keys = oldKeys;
    } else {
        oldKeys = keys;
    }

    return keys;
}

/* Framebuffer support */

static int fbfd = 0;
static unsigned short *fb = NULL;

int fbInit ()
{
    fbfd = open("/dev/fb", O_RDWR);
    if (fbfd < 0)
        return 0;
    fb = (unsigned short *)mmap(0, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (!fb)
        return 0;
    return 1;
}

void fbDraw ()
{
    const unsigned int screen_region[4] = {0, 0, 320, 240};
    if (ioctl(fbfd, 0x4010C10A, screen_region))
        return;
}

void fbPut (unsigned int x, unsigned int y, unsigned int pixel)
{
    fb[y*240+x] = (pixel&0xFFFF);
}

void fbClear ()
{
    memset(fb, 0, 320*240*2);
}

unsigned short *fbPtr ()
{
    if (ttyfd < 0)
        return NULL;
    return fb;
}

/* Touchpad led support */

static int ledfd = 0;

int ledInit ()
{
    ledfd = open("/dev/led", O_RDWR);
    if (ledfd < 0)
        return 0;
    return 1;
}

void ledPower (int state)
{
    unsigned int level;

    level = 0;

    if (ledfd < 0)
        return;

    if (state)
    {
        ioctl(ledfd, 0, level);
    } else {
        ioctl(ledfd, 1, level);
    }
}

void ledLevelSet (unsigned int level)
{
    if (ledfd)
        ioctl(ledfd, 2, level);
}

unsigned int ledLevelGet ()
{
    unsigned int level = 0;

    if (ledfd)
        ioctl(ledfd, 3, level);

    return level;
}
