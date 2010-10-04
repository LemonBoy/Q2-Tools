#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>

int main ()
{
    int fbfd = open("/dev/fb", O_RDWR);
    struct fb_var_screeninfo screeninfo;
    if (!fbfd) {
        printf("Cannot open /dev/fb\n");
        return 0;
    }
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &screeninfo)) {
        printf("Cannot get screen info\n");
        return 0;
    }
    int fbsize = screeninfo.xres*screeninfo.yres*screeninfo.bits_per_pixel/8;
    char *fb = mmap(0, fbsize, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (!fb) {
        printf("Cannot mmap the vram\n");
        return 0;
    }
    memset(fb, 0, fbsize/2);
    memset(fb+(fbsize/2), 0xff, fbsize/2);
    while (1);
}
