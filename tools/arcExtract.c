/*
 * arcExtract.c
 * The Lemon Man (C) 2010
 * Thanks to booto for discovering some unknown fields
 *
 * gcc -03 -Wall arcExtract.c -o arcExtract
 *
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

typedef struct {
	u32 magic;
	u32 version;
	u32 nameTableStart;
	u32 nameTableLen;
	u32 fileTableStart;
	u32 fileTableLen;
} arcHeader;

char *getName (u8 *nameTable, int index)
{
	char *fileName = (char*)nameTable;
	int nameIndex = 0;
		
	while (nameIndex++ < index)
		fileName += strlen(fileName) + 1;
	
	return fileName;
}

int main (int argc, char *argv[])
{
	FILE * fp = NULL;
	arcHeader arcHdr;
	int fileCount, fileOffset, fileSize, fileIndex;
	u8 *nameTable = NULL, *copyBuf = NULL;
	char *newDir, *extDot;
	
	printf("** arcExtract for SAMSUNG YP-Q2 **\nThe Lemon Man (C) 2010\nUsage:\n\tarcExtract archivename.arc\n\n");
	
	if (argc < 2)
		return 0;
	
	fp = fopen(argv[1], "rb");
	
	assert(fp != NULL);
	
	newDir = strdup(argv[1]);
	extDot = strrchr(newDir, '.');
	
	if (extDot)
		*extDot = '_';
		
	mkdir(newDir);
	chdir(newDir);
	
	fread(&arcHdr, 1, sizeof(arcHeader), fp);
	
	assert (arcHdr.magic != 0x58505246);
		
	printf("Magic %04X\nVersion %04X\nName Table @ %04X\nName Table Len %04X\nFile Table @ %04X\nFile Table Len %04X\n", 
		arcHdr.magic,
		arcHdr.version,
		arcHdr.nameTableStart,
		arcHdr.nameTableLen,
		arcHdr.fileTableStart,
		arcHdr.fileTableLen
	);
	
	fileCount = arcHdr.fileTableLen / 8;
		
	nameTable = malloc(arcHdr.nameTableLen);
	
	assert (nameTable != NULL);
	
	fseek(fp, arcHdr.nameTableStart, SEEK_SET);
	fread(nameTable, 1, arcHdr.nameTableLen, fp);
	fseek(fp, 0x18, SEEK_SET);
	
	for (fileIndex = 0; fileIndex < fileCount; fileIndex++)
	{
		fread(&fileSize, 1, 4, fp);
		fread(&fileOffset, 1, 4, fp);
		
		printf("File %03i -%s- Start @ %08X Size %08X\n", fileIndex, getName(nameTable, fileIndex), fileOffset, fileSize);
		
		int tblPos = ftell(fp);
		fseek(fp, fileOffset, SEEK_SET);
		
		FILE * xtractFile = fopen(getName(nameTable, fileIndex), "w+b");
		
		copyBuf = malloc(fileSize);
		
		assert(copyBuf != NULL);
		
		fread(copyBuf, 1, fileSize, fp);
		fwrite(copyBuf, 1, fileSize, xtractFile);
		
		fclose(xtractFile);
		
		fseek(fp, tblPos, SEEK_SET);
	}
		
	fclose(fp);
	
	return 1;
}

