"""
    uci.py - UCI theme parser
    The Lemon Man (C) 2010
"""

import struct

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

# Helper functions

def padBuf (buf, boundary = 0x20):
    return buf+('\x00'*(boundary-len(buf)))

def read16 (file):
    if not file:
        return 0
    return struct.unpack('<H', file.read(2))[0]

def read32 (file):
    if not file:
        return 0
    return struct.unpack('<I', file.read(4))[0]

def write16 (file, n):
    if not file:
        return
    file.write(struct.pack('<H', n))

def write32 (file, n):
    if not file:
        return
    file.write(struct.pack('<I', n))

class uciImage ():
    def __init__ (self, X = 0, Y = 0, W = 0, H = 0, data = []):
        self.X = X
        self.Y = Y
        self.W = W
        self.H = H
        self.data = data
    def getData(self):
        return self.data
    def setData(self, data):
        self.data = data
    def getCoords(self):
        return (self.X, self.Y)
    def setCoords(self, new):
        (self.X, self.Y) = new
    def getSize(self):
        return (self.W, self.H)
    def setSize(self, new):
        (self.W, self.H) = new

class uciTag:
    def __init__(self, name = 'NONE', value = ''):
        self.name = name[0:4]
        self.value = value
    def setValue(self, value):
        self.value = value
    def setName(self, name):
        self.name = name
    def getValue(self):
        return self.value
    def getName(self):
        return self.name

class uciTheme:
    def __init__ (self):
        self.tags = []
        self.images = []
    def __str__ (self):
        buf = '[Tags]\n'
        for tag in self.tags:
            buf += 'Name : %s\n' % tag.getName()
        buf += '[Images]\n'
        for img in self.images:
            buf += 'Coords : (%03i, %03i)\n' % img.getCoords()
            buf += 'Size   : (%03i, %03i)\n' % img.getSize()
        return buf
    def save (self, filename):
        uciFd = open(filename, 'w+b')

        # The magic, the version and some unknown values

        uciFd.write('EUCI')
        write16(uciFd, 0x0001)
        write16(uciFd, 0x0101)
        uciFd.write('\xE7\x1A\xD1\x4A\x00\x00\x00\x00'*2)

        # Placeholders for tags end and file size

        write32(uciFd, 0x00000000)
        write32(uciFd, 0x00000000)

        # Device name and code

        uciFd.write(padBuf('YP-Q2'))
        uciFd.write(padBuf('b996996ac1e647becc347d1663f133e2'))

        # Tags

        for tag in self.tags:
            uciFd.write(tag.getName())      # Name
            write32(uciFd, len(tag.value))  # Size
            write16(uciFd, 0x0000)          # Flag
            uciFd.write(tag.value)

        # Some unknown shit...i guess i should figure out wtf does

        uciFd.write('\x53\x55\x01\x0C\x01\x00\x00\x00\x00\x00\x0B\x3C\x1B\x9F\x00\x00\x00\x00\x98\xE0\x56\x00\x3E\x00\x00\x00\x4E\x93\x56\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00')
        uciFd.write(padBuf('UCI V0.1'))
        uciFd.write(padBuf('YP-Q2'))
        uciFd.write('\x10\x93\x56\x00\x00\x00\x00\x00\x01\x00\x00\x00\x8E\x00\x00\x00\x00\x40\x00\x00')

        # The MENU section

        uciFd.write(padBuf('MENU'))
        uciFd.write(padBuf('V0.1'))

        write32(uciFd, uciFd.tell() + 0xC) # Table start
        write32(uciFd, len(self.tags))      # Table entries
        write32(uciFd, 0x00000000)          # Placeholder for data size

        tablePos = uciFd.tell()
        tableEnd = uciFd.tell() + 0x10 * len(self.tags)

        # Place the first data section just after the table

        nextData = 0

        for img in self.images:
            uciFd.seek(tablePos)

            write16(uciFd, img.X)
            write16(uciFd, img.Y)
            write16(uciFd, img.W)
            write16(uciFd, img.H)
            write32(uciFd, 0x00000005)
            write32(uciFd, nextData)

            uciFd.seek(tableEnd + nextData)

            uciFd.write(img.data)

            tablePos += 0x10
            nextData += len(img.data)

        # EOF mark

        uciFd.write('\x53\x55\x03\x0C\x01\x00\x00\x00')

        uciFd.close()
    def load (self, filename):
        uciFd = open(filename, 'rb')

        if uciFd.read(4) != 'EUCI':
            print 'Wrong magic'
            raise Exception

        uciFd.seek(0x18)

        fileLen = read32(uciFd)
        tagsEnd = read32(uciFd)

        if uciFd.read(0x20)[:5] != 'YP-Q2':
            #~ print 'Wrong Q2 signature'
            raise Exception

        if uciFd.read(0x20) != 'b996996ac1e647becc347d1663f133e2':
            #~ print 'Wrong device code'
            raise Exception

        # Load the tags

        while uciFd.tell() < tagsEnd:
            tagName = uciFd.read(4)
            tagSize = read32(uciFd)
            tagFlag = read16(uciFd)
            tagPayl = uciFd.read(tagSize)

            self.tags.append(uciTag(tagName, tagPayl))

        unkpart = uciFd.read(0x3E)

        uciFd.seek(0x20*2+0x14, 1)

        # MENU section parsing

        if uciFd.read(0x20)[:4] != 'MENU':
            #~ print 'Bad MENU signature'
            raise Exception

        if uciFd.read(0x0C)[:5] != 'V0.01':
            #~ print 'Wrong MENU version'
            raise Exception

        tableStart = read32(uciFd)
        tableCount = read32(uciFd)
        dataSize   = read32(uciFd)

        # Read out the images

        tmp = 0

        while tmp < tableCount:
            uciFd.seek(tableStart + (tmp * 0x10))

            imageX = read16(uciFd)
            imageY = read16(uciFd)
            imageW = read16(uciFd)
            imageH = read16(uciFd)
            imageU = read32(uciFd)
            imageO = read32(uciFd)

            uciFd.seek(tableStart + (tableCount * 0x10) + imageO)

            bmpHead = uciFd.read(6)
            bmpSize  = struct.unpack('i', bmpHead[0x2:])[0] - 6

            self.images.append(uciImage(imageX, imageY, imageW, imageH, bmpHead + uciFd.read(bmpSize)))

            tmp = tmp + 1

        uciFd.close()

