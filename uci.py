# uci.py
# The Lemon Man (C) 2010

import os, sys, struct

print 'uciExtract Alpha\n(C) 2010 The Lemon Man'

try:
	uciFile = open(sys.argv[1], 'rb')
except:
	print 'Usage:\n\tpython uci.py uciTheme.uci'
	exit(0)
	
try:
	os.mkdir(sys.argv[1] + '_icons')
except:
	pass

uciHeader = uciFile.read(0x60)

tagsLen = struct.unpack('<I', uciHeader[0x1C:0x20])[0]
fileLen = struct.unpack('<I', uciHeader[0x18:0x1C])[0]
devCode = uciHeader[0x40:0x60]

print 'File len %i' % fileLen
print 'Tags len 0x%x' % tagsLen
print 'Unique device id : %s' % devCode

while uciFile.tell() < tagsLen:
	uciTag = uciFile.read(4)
	uciTagSz = struct.unpack('<I', uciFile.read(4))[0]
	uciTagFlag = uciFile.read(2)
	uciTagPayload = uciFile.read(uciTagSz)

	print 'Tag %s Len 0x%x' % (uciTag, uciTagSz)
	
	if uciTag == 'APIC':
		previewJpg = open(sys.argv[1] + '_icons/' + 'preview.jpg', 'wb')
		previewJpg.write(uciTagPayload)
		previewJpg.close()
	else:
		print '%s' % uciTagPayload

dataHdr = uciFile.read(0x3E)
uciVer = uciFile.read(0x20)
uciDev = uciFile.read(0x20)

print 'Uci version : %s' % uciVer
print 'Uci for %s' % uciDev

shiz = uciFile.read(0x14)
menuHdr = uciFile.read(0x38)

tableStart = struct.unpack('<I', menuHdr[0x2C:0x30])[0]

print 'Table @ 0x%x' % tableStart

tabIndex = 0

# Table len is always 0xBD0 and each record is 0x10 byte wise
# Record format:
# 0x00 Bitmap X
# 0x02 Bitmap Y
# 0x04 Bitmap width
# 0x06 Bitmap height
# 0x08 Unknown (always 5)
# 0x0C Bitmap offset relative to the end of the table

while tabIndex < 0xBD0 / 0x10:
	uciFile.seek(tableStart + (tabIndex * 0x10))

	bitmapX = struct.unpack('<H', uciFile.read(2))[0]
	bitmapY = struct.unpack('<H', uciFile.read(2))[0]
	bitmapW = struct.unpack('<H', uciFile.read(2))[0]
	bitmapH = struct.unpack('<H', uciFile.read(2))[0]
	unknownField = struct.unpack('<I', uciFile.read(4))[0]
	bitmapOffset = struct.unpack('<I', uciFile.read(4))[0]
	
	print 'Bitmap %i' % tabIndex
	print 'Bitmap coord -> %i %i' % (bitmapX, bitmapY)
	print 'Bitmap size  -> %i x %i' % (bitmapW, bitmapH)
	print 'Unknown field-> %x' % (unknownField)
	print 'Bitmap offset-> 0x%x' % bitmapOffset
		
	uciFile.seek(tableStart + 0xbd0 + bitmapOffset)
	
	bmpHdr = uciFile.read(6)
	bmpSz = struct.unpack('i', bmpHdr[2:])[0] - 6
	bmpFile = open(sys.argv[1] + '_icons/' + str(tabIndex) + '.bmp', 'wb')
	bmpFile.write(bmpHdr)
	bmpFile.write(uciFile.read(bmpSz))
	bmpFile.close()

	tabIndex = tabIndex + 1

