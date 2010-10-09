#include <stdio.h>
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

int videoInit ()
{
    fbfd = open("/dev/fb", O_RDWR);
    if (fbfd < 0)
        return 0;
    fb = (unsigned short *)mmap(0, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (!fb)
        return 0;
    return 1;
}

int videoBrightnessSet (int level)
{
    char cmd[0x10] = {0, };
    int lcdcr = open("/proc/lfbctrl", O_RDWR);
    if (lcdcr < 0)
        return 0;
    if (level < 0)
        level = 0;
    if (level > 10)
        level = 10;
    sprintf(cmd, "backlight %d", level);
    write(lcdcr, cmd, strlen(cmd));
    close(lcdcr);
    return 1;
}

int videoPowerSet (lcdPwr state)
{
    char cmd[0x10] = {0, };
    int lcdcr = open("/proc/lfbctrl", O_RDWR);
    sprintf(cmd, "lcdif %s", (state) ? "on" : "off");
    write(lcdcr, cmd, strlen(cmd));
    close(lcdcr);
    return 1;
}

void videoDraw ()
{
    const unsigned int screen_region[4] = {0, 0, 320, 240};
    ioctl(fbfd, 0x4010C10A, screen_region);
}

void videoPlot (unsigned int x, unsigned int y, unsigned int pixel)
{
    fb[y*240+x] = (pixel&0xFFFF);
}

void videoClear ()
{
    memset(fb, 0, 320*240*2);
}

unsigned short *videoPtr ()
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
        ioctl(ledfd, 3, &level);

    return level;
}

/* Power management */

int pwSetProfile (pmProfile selected)
{
    int powermanfd;
    int profile = selected;
    if (selected > PWR_MAX_PERF)
        return 0;
    powermanfd = open("/dev/misc/pm", O_RDWR);
    if (powermanfd < 0)
        return 0;
    if (ioctl(powermanfd, 0x40046300, profile))
        return 0;
    close(powermanfd);
    return 1;
}
