/*
 * Q2BootImgExtract.c
 * The Lemon Man (C) 2010
 * Parts based off booto's work
 *
 * gcc -03 -Wall Q2BootImgExtract.c -o Q2BootImgExtract
 *
 */

#include <stdio.h>
#include <assert.h>

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

int saveImg (char *outImage, FILE * bootImg, u32 offset)
{
	FILE * ppmImg = fopen(outImage, "w+b");
	
	u8 ppmPix[3];
			
	u16 imgW, imgH, imgData, dataLen;
	u32 pixWritten = 0;
	
	fseek(bootImg, offset, SEEK_SET);
	
	fread(&imgW, 1, 2, bootImg);
	fread(&imgH, 1, 2, bootImg);
	
	fprintf(ppmImg, "P6 %d %d 255\n", imgW, imgH);
		
	printf("Image size %i x %i\n", imgW, imgH);
	
	while (1)
	{
		fread(&imgData, 1, 2, bootImg);
		fread(&dataLen, 1, 2, bootImg);
	
		ppmPix[0] = (0xff * ((imgData >>11) & 0x1f))  / 0x1f;
		ppmPix[1] = (0xff * ((imgData >> 5) & 0x3f))  / 0x3f;
		ppmPix[2] = (0xff * ((imgData >> 0) & 0x1f))  / 0x1f;
		
		while (dataLen--)
		{
			fwrite(ppmPix, 1, 3, ppmImg);
			pixWritten++;
		}
		
		if (pixWritten / imgW == imgH)
			break;
	}

	fclose(ppmImg);
	
	return ftell(bootImg);
}

int main (int argc, char *argv[])
{
	FILE * bootImg = NULL;
	
	u32 iEnd = 0, fSize;
	char imgName[20];
	
	printf("** Q2BootImgExtract for SAMSUNG YP-Q2 **\nThe Lemon Man (C) 2010\nUsage:\n\nQ2BootImgExtract Q2BootBMP.img\n\n");
	
	if (argc < 2)
		return 0;
		
	bootImg = fopen(argv[1], "rb");
	
	assert (bootImg != NULL);
	
	fseek(bootImg, 0, SEEK_END);
	fSize = ftell(bootImg);
	fseek(bootImg, 0, SEEK_SET);
	
	printf("File size : %ib\n", fSize);
	
	while (iEnd < fSize)
	{
		sprintf(imgName, "boot_%08i.ppm", iEnd);
		printf("%s @ %#x\n", imgName ,iEnd);
		iEnd = saveImg(imgName, bootImg, iEnd);
	}
	
	fclose(bootImg);
	
	return 1;
}
