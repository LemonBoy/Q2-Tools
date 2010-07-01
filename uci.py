# uci.py
# The Lemon Man (C) 2010

import os, sys, struct

""" 
MENU section format:
	0x00 MENU magic tag
	0x20 version
	0x2C image table start offset
	0x30 image table entries (0x10 for each entry)
	0x34 data size (from the position till the end - 8)

Table len is calculated by multiplying the table entries for the record size.

Table record format:
	0x00 Bitmap X
	0x02 Bitmap Y
	0x04 Bitmap width
	0x06 Bitmap height
	0x08 Unknown (always 5)
	0x0C Bitmap offset relative to the end of the table
"""

class uciImage ():
	def __init__ (self, index):
		self.index = index
		self.bitmapX = self.bitmapY = 0
		self.bitmapW = self.bitmapH = 0
		self.unknownField = 5
		self.bitmapOffset = 0
		self.data = []
	def fromTable(self, tableRecord):
		self.bitmapX = struct.unpack('<H', tableRecord[0:2])[0]
		self.bitmapY = struct.unpack('<H', tableRecord[2:4])[0]
		self.bitmapW = struct.unpack('<H', tableRecord[4:6])[0]
		self.bitmapH = struct.unpack('<H', tableRecord[6:8])[0]
		self.unknownField = struct.unpack('<I', tableRecord[8:12])[0]
		self.bitmapOffset = struct.unpack('<I', tableRecord[12:16])[0]
	def setCoords (self, newCoords):
		self.bitmapX = newCoords[0]
		self.bitmapY = newCoords[1]
		return 1
	def setData(self, bmpData):
		if len(self.data) != 0 and len(bmpData) > len(self.data):
			print '%i > %i' % (len(bmpData), len(self.data))
			return 0
		if bmpData[:2] != 'BM':
			return 0
			
		self.data = bmpData

		return 1

class uciTheme:
	def __init__ (self, uciFile = None):
		self.tags  = []
		self.images = []
		
		self.uciHeader = self.dataHdr = self.shiz = self.menuHdr = []
		self.tagsLen = self.fileLen = self.tableStart = 0
		
		self.devCode = 'b996996ac1e647becc347d1663f133e2'
		self.uciVer  = 'UCI V0.1                        '
		self.uciDev  = 'YP-Q2                           '
		
		self.uciFile = uciFile
		
		if self.uciFile != None:
			self.uciHeader = self.uciFile.read(0x60)

			self.tagsLen = struct.unpack('<I', self.uciHeader[0x1C:0x20])[0]
			self.fileLen = struct.unpack('<I', self.uciHeader[0x18:0x1C])[0]
			self.devCode = self.uciHeader[0x40:0x60]

			print 'File len %i' % self.fileLen
			print 'Tags len 0x%x' % self.tagsLen
			print 'Unique device id : %s' % self.devCode

			while self.uciFile.tell() < self.tagsLen:
				uciTag = self.uciFile.read(4)
				uciTagSz = struct.unpack('<I', self.uciFile.read(4))[0]
				uciTagFlag = struct.unpack('<H', self.uciFile.read(2))[0]
				uciTagPayload = self.uciFile.read(uciTagSz)
				
				self.tags.append({'Name' : uciTag, 'Size' : uciTagSz, 'Flags' : uciTagFlag, 'Payload' : uciTagPayload})

			self.dataHdr = self.uciFile.read(0x3E)
			
			#open('datahdr.bin', 'wb').write(self.dataHdr)
			
			self.uciVer = self.uciFile.read(0x20)
			self.uciDev = self.uciFile.read(0x20)

			print 'Uci version : %s' % self.uciVer
			print 'Uci for %s' % self.uciDev

			self.shiz = self.uciFile.read(0x14)
			
			#open('themeshiz.bin', 'wb').write(self.shiz)
			
			self.menuHdr = self.uciFile.read(0x38)

			self.menuMagic = self.menuHdr[:0x20]
			if self.menuMagic[:4] != 'MENU':
				print 'MENU tag not found'
				raise valueError
			else:
				print 'MENU tag found'
			self.menuVersion = self.menuHdr[0x20:0x2C]
			self.tableStart = struct.unpack('<I', self.menuHdr[0x2C:0x30])[0]
			self.tableEntries = struct.unpack('<I', self.menuHdr[0x30:0x34])[0]
			self.dataSize = struct.unpack('<I', self.menuHdr[0x34:0x38])[0]

			print 'Menu version : %s' % self.menuVersion
			print 'Table @ 0x%x (%i entries)' % (self.tableStart, self.tableEntries)
			print 'Menu data len %i' % self.dataSize
			
			tabIndex = 0
			
			while tabIndex < self.tableEntries:
				self.uciFile.seek(self.tableStart + (tabIndex * 0x10))

				image = uciImage(tabIndex)
				image.fromTable(self.uciFile.read(0x10))
				
				print 'Bitmap %i' % tabIndex
				print 'Bitmap coord -> %i %i' % (image.bitmapX, image.bitmapY)
				print 'Bitmap size  -> %i x %i' % (image.bitmapW, image.bitmapH)
				print 'Unknown field-> %x' % (image.unknownField)
				print 'Bitmap offset-> 0x%x' % image.bitmapOffset

				self.uciFile.seek(self.tableStart + (self.tableEntries * 0x10) + image.bitmapOffset)
				
				bmpHdr = self.uciFile.read(6)
				bmpSz = struct.unpack('i', bmpHdr[2:])[0] - 6
				image.setData(bmpHdr + self.uciFile.read(bmpSz))
				
				self.images.append(image)

				tabIndex = tabIndex + 1
				
	def dumpImages (self, outputPath):
		for image in self.images:
			bmpFile = open(outputPath + '/' + str(image.index) + '.bmp', 'wb')
			bmpFile.write(image.data)
			bmpFile.close()
	def dumpTags (self):
		for tag in self.tags:
			print 'Tag %s Len 0x%x Flags %02x' % (tag['Name'], tag['Size'], tag['Flags'])
		
			if tag['Name'] == 'APIC':
				print 'Preview JPEG'
			elif tag['Name'] == 'TAUT':
				print 'Author %s' % tag['Payload']
			elif tag['Name'] == 'TTAG':
				print 'Tag %s' % tag['Payload']				
			else:
				print '%s' % hexdump(tag['Payload'], tag['Size'])
	def updateIconCoord (self, index, coord):
		if index > self.tableEntries:
			print 'Index out of range %i' % index
			return 0
		return self.images[index].setCoords(coord)		
	def updateIconData (self, index, data):
		if index > self.tableEntries:
			print 'Index out of range %i' % index
			return 0
		self.images[index].data = data
		return 1
	def updateIconTableEntry (self,index):
		if index > self.tableEntries:
			print 'Index out of range %i' % index
			return 0
		self.uciFile.seek(self.tableStart + (index * 0x10))
		
		print 'Updating table entry @ %x' % self.uciFile.tell()
		
		self.uciFile.write(struct.pack('<H', self.images[index].bitmapX))
		self.uciFile.write(struct.pack('<H', self.images[index].bitmapY))
		self.uciFile.write(struct.pack('<H', self.images[index].bitmapW))
		self.uciFile.write(struct.pack('<H', self.images[index].bitmapH))
		self.uciFile.write(struct.pack('<I', self.images[index].unknownField))
		self.uciFile.write(struct.pack('<I', self.images[index].bitmapOffset))	
		
		self.uciFile.seek(self.tableStart + (self.tableEntries * 0x10))
		self.uciFile.seek(self.images[index].bitmapOffset, 1)
		self.uciFile.write(self.images[index].data)
		
		# u.u why i have to do this ?
		
		self.uciFile.seek(-2, 1)
		self.uciFile.write('BM')
			
		return 1
		
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
		result.append("0x%04X   %-*s   %s" % (i, (length * 3) + 2, hexa, printable))
	return ''.join(result)



