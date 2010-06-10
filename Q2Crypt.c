/*
 * Q2Crypt.c
 * The Lemon Man (C) 2010
 *
 * gcc -03 -Wall Q2Crypt.c md5.c -o Q2Crypt
 *
 */
 
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "md5.h"

#define HEADER_LEN        0x34
#define MD5_DIGEST_LEN    0x10
#define DATA_BLOCK_LEN    128

static unsigned char xorTable[DATA_BLOCK_LEN] = {
	0xA3,0x04,0xB9,0xCD,0x34,0x13,0x4A,0x19,0x19,0x35,0xDF,0xBB,0x8F,0x3D,0x7F,0x09,
	0x42,0x3C,0x96,0xC6,0x41,0xA9,0x95,0xF1,0xD0,0xAC,0x16,0x37,0x57,0x1F,0x28,0xE7,
	0x0B,0xC2,0x12,0x09,0x39,0x42,0xD2,0x96,0xF5,0x00,0xD2,0x23,0xA4,0x24,0xE2,0x8E,
	0x50,0x3C,0x6E,0x23,0xEB,0x68,0xED,0x31,0xB7,0xEE,0xC0,0xC7,0x09,0xF8,0x0E,0x9D,
	0x51,0xED,0x17,0x95,0x64,0x09,0xE0,0xF9,0xF0,0xEF,0x86,0xC0,0x04,0x46,0x89,0x8A,
	0x6E,0x27,0x69,0xDE,0xC7,0x9D,0x1E,0xEE,0x3C,0x3F,0x17,0x05,0x44,0xBB,0xBB,0x1D,
	0x3D,0x5D,0x6E,0xF2,0xCF,0x15,0xD6,0x3C,0xCC,0x7D,0x67,0x1A,0xB8,0xD2,0x1B,0x54,
	0x97,0xA2,0x58,0x58,0xF7,0x4E,0x5E,0x50,0x42,0x69,0xDC,0xE7,0x3A,0x87,0x2E,0x22
};

void xorBlock (unsigned char *block)
{
	int bPos = 0;
		
	for (bPos = 0; bPos < DATA_BLOCK_LEN; bPos++)
	{
		block[bPos] ^= xorTable[bPos];
	}
}

int createUpdate (char *dest, char *updateArchivePath)
{
	FILE * updateDat = NULL;
	FILE * updateArk = NULL;
	
	unsigned char 	updateHeader	[HEADER_LEN + 4];
	unsigned char 	updateBlock		[DATA_BLOCK_LEN];
	md5_byte_t 		digest			[MD5_DIGEST_LEN];
	
	int updateSz;
	
	md5_state_t hashState;
	
	md5_init(&hashState);
	
	updateDat = fopen(dest, "w+b");
	updateArk = fopen(updateArchivePath, "rb");
	
	assert(updateDat);
	assert(updateArk);
	
	memset(updateHeader, 0, sizeof(updateHeader));
	
	fwrite(updateHeader, 1, 0x38, updateDat);
	
	while (fread(updateBlock, 1, DATA_BLOCK_LEN, updateArk) == DATA_BLOCK_LEN)
	{
		xorBlock(updateBlock);
		md5_append(&hashState, (const md5_byte_t *)updateBlock, DATA_BLOCK_LEN);
		fwrite(updateBlock, 1, DATA_BLOCK_LEN, updateDat);
	}
	
	md5_finish(&hashState, digest);
	
	fwrite(digest, 1, MD5_DIGEST_LEN, updateDat);
	
	updateSz = ftell(updateDat);
	
	fseek(updateDat, 0x34, SEEK_SET);
	
	fwrite(&updateSz, 1, 4, updateDat);
	
	fclose(updateDat);
	fclose(updateArk);
	
	return updateSz;
}

int decryptUpdate (char *dest, char *updateDat)
{
	FILE * encFile = NULL;
	FILE * decFile = NULL;
	
	int 			updateSz;
	int				totalRead;
	unsigned char 	updateBlock		[DATA_BLOCK_LEN];
	md5_byte_t 		md5Digest		[MD5_DIGEST_LEN];
	md5_byte_t 		myDigest		[MD5_DIGEST_LEN];
	md5_state_t 	hashState;
	
	encFile = fopen(updateDat, "rb");
	decFile = fopen(dest, "w+b");
	
	assert(encFile);
	assert(decFile);
	
	md5_init(&hashState);	
	
	fseek(encFile, HEADER_LEN, SEEK_SET);
	
	fread(&updateSz, 1, 4, encFile);
	
	totalRead = 0;
		
	while (totalRead < updateSz)
	{
		totalRead += fread(updateBlock, 1, DATA_BLOCK_LEN, encFile);
		md5_append(&hashState, (const md5_byte_t *)updateBlock, DATA_BLOCK_LEN);
		xorBlock(updateBlock);
		fwrite(updateBlock, 1, DATA_BLOCK_LEN, decFile);
	}
	
	md5_finish(&hashState, myDigest);
	
	fread(&md5Digest, 1, MD5_DIGEST_LEN, encFile);
	
	if (!memcmp(md5Digest, myDigest, MD5_DIGEST_LEN))
	{
		printf("MD5 Hashes are matching!\n");
	} else	
	{
		printf("MD5 Hash mismatch, the update may be corrupt!\n");
	}
	
	fclose(encFile);
	fclose(decFile);
	
	return (HEADER_LEN + updateSz + MD5_DIGEST_LEN);
}
	
int main (int argc, char *argv[])
{
	int retSz;
	
	printf("** Q2Crypt for SAMSUNG YP-Q2 **\nThe Lemon Man (C) 2010\nUsage:\n\tQ2Crypt -enc/-dec infile outfile\n\n");
	
	if (argc < 3)
		return 0;
		
	if (!strcmp(argv[1], "-enc"))
	{
		retSz = decryptUpdate(argv[3], argv[2]);
		if (retSz < 1)
			printf("Hash mismatch while unpacking, update may be corrupt\n");
		printf("Update encrypted to %s (%ib)\n", argv[3], retSz);
	} else if (!strcmp(argv[1], "-dec"))
	{
		retSz = createUpdate(argv[3], argv[2]);
		printf("Update decrypted to %s (%ib)\n", argv[3], retSz);
	} else
	{
		return 0;
	}
	
	return 1;
}
