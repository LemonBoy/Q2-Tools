#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/dir.h>
#include <unistd.h>
#include <libQ2.h>
#include "uFb.h"

int main ()
{
    uFbInit(240, 320, videoInit, videoPlot, videoDraw);
    videoClear();
    inputInit();
    ledInit();
    ledPower(1);
    ledLevelSet(1);
    pwSetProfile(PWR_MAX_CPU);
    videoBrightnessSet(10);

    while (1) {
        if (KEY_PRESSED(inputRead(), KEY_UP))
            videoPowerSet(0);
        if (KEY_PRESSED(inputRead(), KEY_DOWN))
            videoPowerSet(1);
        if (KEY_PRESSED(inputRead(), KEY_POWER))
            pwSetProfile(PWR_OFF);
        uFbDrawEnd();
    }

    return 1;
}
