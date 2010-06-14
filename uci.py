# uci.py
# The Lemon Man (C) 2010

import os, sys, struct

def isInRange(n, range):
	if n >= range[0] and n <= range[1]:
		return 1
	else:
		return 0
		
def hexdump(src, length = 16): # dumps to a "hex editor" style output
	result = []
	for i in xrange(0, len(src), length):
		s = src[i:i + length]
		if(len(s) % 4 == 0):
			mod = 0 
		else: 
			mod = 1 
		hexa = ''
		for j in range((len(s) / 4) + mod):
			hexa += ' '.join(["%02X" % ord(x) for x in s[j * 4:j * 4 + 4]])
			if(j != ((len(s) / 4) + mod) - 1):
				hexa += '  '
		printable = s.translate(''.join([(len(repr(chr(x))) == 3) and chr(x) or '.' for x in range(256)]))
		result.append("0x%04X   %-*s   %s\n" % (i, (length * 3) + 2, hexa, printable))
	return ''.join(result)

	
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
	
xmlDump = open(sys.argv[1] + '_icons/' + 'theme.xml', 'wb')
xmlDump.write('<uciTheme>\n')

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
		xmlDump.write('<preview>' + 'preview.jpg' + '</preview>\n')
	
		previewJpg = open(sys.argv[1] + '_icons/' + 'preview.jpg', 'wb')
		previewJpg.write(uciTagPayload)
		previewJpg.close()
	elif uciTag == 'TCOM':
		print 'Comment %s' % uciTagPayload
	elif uciTag == 'TTAG':
		print 'Tag %s' % uciTagPayload
	else:
		print '%s' % hexdump(uciTagPayload, uciTagSz)

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

animationRanges = [
	['microphoneAnimation'	, [30, 42]], 
	['musicAnimation'		, [43, 55]],
	['textAnimation'		, [56, 68]],
	['musicAnimation'		, [69, 81]],
	['gamesAnimation'		, [85, 97]]
	
]

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

	xmlDump.write('<image index="' + str(tabIndex) + '" Width="' + str(bitmapW) + '" Height="' + str(bitmapH) + '" Xpos="' + str(bitmapX) + '" Ypos="' + str(bitmapY) + '" >' + str(tabIndex) + '.bmp' + '</image>\n')
		
	uciFile.seek(tableStart + 0xbd0 + bitmapOffset)
	
	bmpHdr = uciFile.read(6)
	bmpSz = struct.unpack('i', bmpHdr[2:])[0] - 6
	bmpFile = open(sys.argv[1] + '_icons/' + str(tabIndex) + '.bmp', 'wb')
	bmpFile.write(bmpHdr)
	bmpFile.write(uciFile.read(bmpSz))
	bmpFile.close()

	tabIndex = tabIndex + 1
	
xmlDump.write('</uciTheme>\n')

