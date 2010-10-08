#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libQ2.h>
#include "uFb.h"

int main ()
{
    battState state;
    uFbInit(240, 320, fbInit, fbPut, fbDraw);
    fbClear();
    uFbPrint("input %i\n", inputInit());
    uFbPrint("led   %i\n", ledInit());
    ledPower(1);
    ledLevelSet(4);
    /* Bwah, not working -.- fails with errno = 6 */s
    uFbPrint("bread %i errno %i\n", battRead(&state), errno);
    uFbPrint("powah %i errno %i\n", pwSetProfile(PWR_OFF), errno);
    uFbPrint("test  %i errno %i\n", open("/dev/misc/pm", 2), errno);
    while (1) {
        uFbDrawEnd();
    }
}
