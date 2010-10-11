#include <stdio.h>
#include <string.h>
#include "libQ2.h"
#include "uFb.h"
#include "core/neopop.h"

// ---

unsigned char system_frameskip_key = 3;
unsigned char frameskip_count = 0;

void drawScreen (unsigned short *dst, unsigned short *src); /* asm.S */

// ---
void system_VBL(void)
{
    unsigned char keys;

    drawScreen(videoPtr(), cfb);

    keys = inputRead();

    unsigned char up = KEY_PRESSED(keys, KEY_UP) ? 1 : 0;
    unsigned char down = KEY_PRESSED(keys, KEY_DOWN) ? 1 : 0;
    unsigned char left = KEY_PRESSED(keys, KEY_LEFT) ? 1 : 0;
    unsigned char right = KEY_PRESSED(keys, KEY_RIGHT) ? 1 : 0;
    unsigned char button_a = KEY_PRESSED(keys, KEY_POWER) ? 1 : 0;
    unsigned char button_b = KEY_PRESSED(keys, KEY_USER) ? 1 : 0;
    unsigned char option = KEY_PRESSED(keys, KEY_MENU) ? 1 : 0;

    ram[0x6F82] = up | (down << 1) | (left << 2) | (right << 3) |
        (button_a << 4) | (button_b << 5) | (option << 6);

    videoDraw();
}

void
system_message(char *vaMessage, ...)
{
}

BOOL system_comms_read(_u8* buffer)
{
    return 0;
}

BOOL system_comms_poll(_u8* buffer)
{
    return 0;
}

void system_comms_write(_u8 data)
{
}

BOOL system_io_flash_read(_u8* buffer, _u32 bufferLength)
{
    return FALSE;
}

BOOL system_io_flash_write(_u8* buffer, _u32 bufferLength)
{
    return FALSE;
}

BOOL system_io_state_read(char* filename, _u8* buffer, _u32 bufferLength)
{
    return FALSE;

}

BOOL system_io_state_write(char* filename, _u8* buffer, _u32 bufferLength)
{
    return FALSE;
}


char* system_get_string(STRINGS string_id)
{
    return "";
}

void
system_sound_chipreset(void)
{
    return;
}


BOOL
system_sound_init(void)
{
    return FALSE;
}

void
system_sound_shutdown(void)
{
}

void
system_sound_update(int nframes)
{
}

void
system_sound_silence(void)
{
}
void system_message(char *vaMessage, ...);
// ---

void loadRom (char *path)
{
    FILE * fp;
    int size;

    fp = fopen(path, "rb");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    rom.length = size;
    rom.data = malloc(size);
    fread(rom.data, 1, size, fp);
    fclose(fp);
    rom_loaded();
}

int main ()
{
    uFbInit(240, 320, videoInit, videoPlot, videoDraw);
    videoClear();
    inputInit();
    ledInit();
    videoBrightnessSet(LCD_BRIGHTNESS_MAX);
    pwSetProfile(PWR_MAX_CPU);

    bios_install();
    reset();
    mute = TRUE;
    language_english = TRUE;
    system_colour = COLOURMODE_AUTO;

    loadRom("/mnt/usb/test.ngp");
    reset();

    while (1) {
        emulate();
    }
    return 1;
}
