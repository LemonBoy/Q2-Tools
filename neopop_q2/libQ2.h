#ifndef LIBQ2
#define LIBQ2

#define LIBQ2_VERSION "0.01"

/* -- Framebuffer */

int fbInit ();
void fbPut (unsigned int x, unsigned int y, unsigned int pixel);
void fbDraw ();
void fbClear ();
unsigned short *fbPtr ();

/* -- Input */

int inputInit ();
unsigned char inputRead ();

/* Key values */
#define KEY_RETURN 0x0E
#define KEY_MENU   0x01
#define KEY_OK     0x1C
#define KEY_UP     0x67
#define KEY_DOWN   0x6C
#define KEY_LEFT   0x69
#define KEY_RIGHT  0x6A
#define KEY_POWER  0x57
#define KEY_USER   0x58

#define HELD_BIT  0x80

/* Check if key is pressed */
#define KEY_PRESSED(kMap, key) ((kMap!=0) && ((kMap&~HELD_BIT) == key) && !(kMap&HELD_BIT))

/* -- Led */

int ledInit ();
void ledPower (int state);
unsigned int ledLevelGet ();
void ledLevelSet (unsigned int level);


#endif
