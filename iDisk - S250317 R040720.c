;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.0 #9253 (Apr  3 2018) (Linux)
; This file was generated Fri Jul  3 07:45:35 2020
;--------------------------------------------------------
	.module idisk4
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _writeDiskSect
	.globl _verifyDiskSect
	.globl _readOneLine
	.globl _readHexByte
	.globl _getOneChar
	.globl _printErr
	.globl _upperCase
	.globl _putchar
	.globl _getchar
	.globl _printf
	.globl _c
	.globl _lastSector
	.globl _sector
	.globl _track
	.globl _lastTrack
	.globl _firstTrack
	.globl _SegDone
	.globl _segment
	.globl _sectors
	.globl _targetDisk
	.globl _i
	.globl _boundFillFlag
	.globl _writeErrorCode
	.globl _writeDoneFlag
	.globl _writeFlag
	.globl _errFlag
	.globl _magic
	.globl _startAddr
	.globl _addr
	.globl _ii
	.globl _hiAddr
	.globl _lowAddr
	.globl _dataBuffIdx
	.globl _byteCount
	.globl _dataBuff
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
_SELDISK	=	0x0009
_SELTRACK	=	0x000a
_SELSECT	=	0x000b
_WRITESECT	=	0x000c
_ERRDISK	=	0x0005
_READSECT	=	0x0006
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_dataBuff::
	.ds 32768
_byteCount::
	.ds 2
_dataBuffIdx::
	.ds 2
_lowAddr::
	.ds 2
_hiAddr::
	.ds 2
_ii::
	.ds 2
_addr::
	.ds 4
_startAddr::
	.ds 4
_magic::
	.ds 1
_errFlag::
	.ds 1
_writeFlag::
	.ds 1
_writeDoneFlag::
	.ds 1
_writeErrorCode::
	.ds 1
_boundFillFlag::
	.ds 1
_i::
	.ds 1
_targetDisk::
	.ds 1
_sectors::
	.ds 2
_segment::
	.ds 1
_SegDone::
	.ds 16
_firstTrack::
	.ds 1
_lastTrack::
	.ds 1
_track::
	.ds 1
_sector::
	.ds 1
_lastSector::
	.ds 1
_c::
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;idisk4.c:65: char upperCase(unsigned char c)
;	---------------------------------
; Function upperCase
; ---------------------------------
_upperCase::
;idisk4.c:68: if ((c > 96) && (c < 123)) c = c - 32;
	ld	a,#0x60
	ld	iy,#2
	add	iy,sp
	sub	a, 0 (iy)
	jr	NC,00102$
	ld	a,0 (iy)
	sub	a, #0x7B
	jr	NC,00102$
	ld	hl,#2
	add	hl,sp
	ld	a,(hl)
	add	a,#0xE0
	ld	(hl),a
00102$:
;idisk4.c:69: return c;
	ld	iy,#2
	add	iy,sp
	ld	l,0 (iy)
	ret
;idisk4.c:72: void printErr(unsigned char errCode)
;	---------------------------------
; Function printErr
; ---------------------------------
_printErr::
	push	ix
	ld	ix,#0
	add	ix,sp
;idisk4.c:88: if (errCode != 0) {
	ld	a,4 (ix)
	or	a, a
	jp	Z,00116$
;idisk4.c:89: printf("\n\nDisk error %03u: ", errCode);
	ld	l,4 (ix)
	ld	h,#0x00
	ld	de,#___str_0+0
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:90: switch (errCode) {
	ld	a,4 (ix)
	dec	a
	jr	Z,00101$
	ld	a,4 (ix)
	sub	a, #0x02
	jr	Z,00102$
	ld	a,4 (ix)
	sub	a, #0x03
	jr	Z,00103$
	ld	a,4 (ix)
	sub	a, #0x04
	jr	Z,00104$
	ld	a,4 (ix)
	sub	a, #0x08
	jr	Z,00105$
	ld	a,4 (ix)
	sub	a, #0x09
	jr	Z,00106$
	ld	a,4 (ix)
	sub	a, #0x0A
	jr	Z,00107$
	ld	a,4 (ix)
	sub	a, #0x0B
	jr	Z,00108$
	ld	a,4 (ix)
	sub	a, #0x0C
	jr	Z,00109$
	ld	a,4 (ix)
	sub	a, #0x0D
	jr	Z,00110$
	ld	a,4 (ix)
	sub	a, #0x0E
	jr	Z,00111$
	jr	00112$
;idisk4.c:91: case 1:	printf("data too long to fit in transmit buffer (I2C)");break;
00101$:
	ld	hl,#___str_1
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:92: case 2:	printf("received NACK on transmit of address (I2C)");break;
00102$:
	ld	hl,#___str_2
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:93: case 3:	printf("received NACK on transmit of data (I2C)");break;
00103$:
	ld	hl,#___str_3
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:94: case 4:	printf("other error (I2C)");break;
00104$:
	ld	hl,#___str_4
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:95: case 8:	printf("write error (I/O byte counter overrun)");break;
00105$:
	ld	hl,#___str_5
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:96: case 9:	printf("read error (I/O byte counter overrun)");break;
00106$:
	ld	hl,#___str_6
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:97: case 10:    printf("data read error (I2C)");break;
00107$:
	ld	hl,#___str_7
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:98: case 11:    printf("invalid disk number");break;
00108$:
	ld	hl,#___str_8
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:99: case 12:    printf("invalid track number");break;
00109$:
	ld	hl,#___str_9
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:100: case 13:    printf("invalid sector number");break;
00110$:
	ld	hl,#___str_10
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:101: case 14:    printf("virtual disk module not found");break;
00111$:
	ld	hl,#___str_11
	push	hl
	call	_printf
	pop	af
	jr	00113$
;idisk4.c:102: default:    printf("unknown error");break;
00112$:
	ld	hl,#___str_12
	push	hl
	call	_printf
	pop	af
;idisk4.c:103: }
00113$:
;idisk4.c:104: printf("\n");
	ld	hl,#___str_13+0
	push	hl
	call	_printf
	pop	af
00116$:
	pop	ix
	ret
___str_0:
	.db 0x0A
	.db 0x0A
	.ascii "Disk error %03u: "
	.db 0x00
___str_1:
	.ascii "data too long to fit in transmit buffer (I2C)"
	.db 0x00
___str_2:
	.ascii "received NACK on transmit of address (I2C)"
	.db 0x00
___str_3:
	.ascii "received NACK on transmit of data (I2C)"
	.db 0x00
___str_4:
	.ascii "other error (I2C)"
	.db 0x00
___str_5:
	.ascii "write error (I/O byte counter overrun)"
	.db 0x00
___str_6:
	.ascii "read error (I/O byte counter overrun)"
	.db 0x00
___str_7:
	.ascii "data read error (I2C)"
	.db 0x00
___str_8:
	.ascii "invalid disk number"
	.db 0x00
___str_9:
	.ascii "invalid track number"
	.db 0x00
___str_10:
	.ascii "invalid sector number"
	.db 0x00
___str_11:
	.ascii "virtual disk module not found"
	.db 0x00
___str_12:
	.ascii "unknown error"
	.db 0x00
___str_13:
	.db 0x0A
	.db 0x00
;idisk4.c:108: char getOneChar()
;	---------------------------------
; Function getOneChar
; ---------------------------------
_getOneChar::
;idisk4.c:113: do {
00108$:
;idisk4.c:114: inChar = getchar();
	call	_getchar
	ld	h,l
;idisk4.c:115: if ((inChar != CR) || (inChar != LF)) putchar(inChar);
	ld	a,h
	sub	a, #0x0D
	jr	NZ,00133$
	ld	a,#0x01
	jr	00134$
00133$:
	xor	a,a
00134$:
	ld	l,a
	ld	a,h
	sub	a, #0x0A
	jr	NZ,00135$
	ld	a,#0x01
	jr	00136$
00135$:
	xor	a,a
00136$:
	ld	d,a
	ld	a,l
	or	a, a
	jr	Z,00103$
	ld	a,d
	or	a, a
	jr	NZ,00104$
00103$:
	push	hl
	push	de
	push	hl
	inc	sp
	call	_putchar
	inc	sp
	pop	de
	pop	hl
	jr	00109$
00104$:
;idisk4.c:116: else if (inChar == CR) {
	ld	a,l
	or	a, a
	jr	Z,00109$
;idisk4.c:117: putchar(CR);					// CR + LF
	push	hl
	push	de
	ld	a,#0x0D
	push	af
	inc	sp
	call	_putchar
	inc	sp
	ld	a,#0x0A
	push	af
	inc	sp
	call	_putchar
	inc	sp
	pop	de
	pop	hl
00109$:
;idisk4.c:120: } while ((inChar == CR) || (inChar == LF));		// Loop until a valid char is read
	ld	a,l
	or	a,a
	jr	NZ,00108$
	or	a,d
	jr	NZ,00108$
;idisk4.c:121: return inChar;
	ld	l,h
	ret
;idisk4.c:124: unsigned char readHexByte(unsigned char *byte)
;	---------------------------------
; Function readHexByte
; ---------------------------------
_readHexByte::
	push	ix
	ld	ix,#0
	add	ix,sp
;idisk4.c:131: *byte = 0;
	ld	l,4 (ix)
	ld	h,5 (ix)
	ld	(hl),#0x00
;idisk4.c:132: for (i = 1;	i >= 0;	i--) {
	ld	e,#0x01
00113$:
;idisk4.c:133: inChar = getOneChar();				 // Get a char
	push	hl
	push	de
	call	_getOneChar
	ld	c,l
	pop	de
	pop	hl
;idisk4.c:137: if ((inChar >= 'a') && (inChar <= 'f')) inChar = inChar - 32;	 // a - f to upper case
	ld	a,c
	xor	a, #0x80
	sub	a, #0xE1
	jr	C,00102$
	ld	a,#0x66
	sub	a, c
	jp	PO, 00149$
	xor	a, #0x80
00149$:
	jp	M,00102$
	ld	a,c
	add	a,#0xE0
	ld	c,a
00102$:
;idisk4.c:138: if ((inChar >= '0') && (inChar <= '9')) inChar = inChar - 48;	 // 0 - 9
	ld	a,c
	xor	a, #0x80
	sub	a, #0xB0
	jr	C,00109$
	ld	a,#0x39
	sub	a, c
	jp	PO, 00150$
	xor	a, #0x80
00150$:
	jp	M,00109$
	ld	a,c
	add	a,#0xD0
	ld	c,a
	jr	00110$
00109$:
;idisk4.c:139: else if ((inChar >= 'A') && (inChar <= 'F')) inChar = inChar - 55;	 // A - F
	ld	a,c
	xor	a, #0x80
	sub	a, #0xC1
	jr	C,00105$
	ld	a,#0x46
	sub	a, c
	jp	PO, 00151$
	xor	a, #0x80
00151$:
	jp	M,00105$
	ld	a,c
	add	a,#0xC9
	ld	c,a
	jr	00110$
00105$:
;idisk4.c:142: return 1;					// Illegal char: syntax error
	ld	l,#0x01
	jr	00115$
00110$:
;idisk4.c:145: *byte = *byte | (inChar << (i * 4));		 // Byte in binary
	ld	d,(hl)
	ld	a,e
	add	a, a
	add	a, a
	ld	b,a
	inc	b
	jr	00153$
00152$:
	sla	c
00153$:
	djnz	00152$
	ld	a,d
	or	a, c
	ld	(hl),a
;idisk4.c:132: for (i = 1;	i >= 0;	i--) {
	dec	e
	bit	7, e
	jr	Z,00113$
;idisk4.c:147: return 0;						// No errors
	ld	l,#0x00
00115$:
	pop	ix
	ret
;idisk4.c:150: unsigned char readOneLine()
;	---------------------------------
; Function readOneLine
; ---------------------------------
_readOneLine::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-14
	add	hl,sp
	ld	sp,hl
;idisk4.c:160: inChar = getOneChar();
	call	_getOneChar
	ld	a,l
;idisk4.c:161: if (inChar != ':') return 10;				// Read first char = ':'
	sub	a, #0x3A
	jr	Z,00102$
	ld	l,#0x0A
	jp	00145$
00102$:
;idisk4.c:162: if (readHexByte(&recLength) > 0) return 10;		// Read record length
	ld	hl,#0x0002
	add	hl,sp
	push	hl
	call	_readHexByte
	pop	af
	ld	a,l
	or	a, a
	jr	Z,00104$
	ld	l,#0x0A
	jp	00145$
00104$:
;idisk4.c:163: sum = recLength;
	ld	d,-12 (ix)
;idisk4.c:164: if (readHexByte(&byte) > 0) return 10;			// Read 16 bit address MSB
	ld	hl,#0x0003
	add	hl,sp
	push	hl
	push	de
	push	hl
	call	_readHexByte
	pop	af
	ld	a,l
	pop	de
	pop	bc
	or	a, a
	jr	Z,00106$
	ld	l,#0x0A
	jp	00145$
00106$:
;idisk4.c:165: sum = sum + byte;
	ld	a,d
	add	a, -11 (ix)
	ld	h,a
;idisk4.c:166: lowAddr = ((unsigned int)byte) << 8;
	ld	l,-11 (ix)
	ld	iy,#_lowAddr
	ld	1 (iy),l
	ld	iy,#_lowAddr
	ld	0 (iy),#0x00
;idisk4.c:167: if (readHexByte(&byte) > 0) return 10;			// Read 16 bit address LSB
	ld	e, c
	ld	d, b
	push	hl
	push	bc
	push	de
	call	_readHexByte
	pop	af
	ld	a,l
	pop	bc
	pop	hl
	or	a, a
	jr	Z,00108$
	ld	l,#0x0A
	jp	00145$
00108$:
;idisk4.c:168: sum = sum + byte;
	ld	a,h
	add	a, -11 (ix)
	ld	-1 (ix),a
;idisk4.c:169: lowAddr = lowAddr | byte;
	ld	d,-11 (ix)
	ld	e,#0x00
	ld	a,(#_lowAddr + 0)
	or	a, d
	ld	(#_lowAddr + 0),a
	ld	a,(#_lowAddr + 1)
	or	a, e
	ld	(#_lowAddr + 1),a
;idisk4.c:170: if (readHexByte(&recType) > 0) return 10;		// Read record type
	ld	hl,#0x0000
	add	hl,sp
	push	bc
	push	hl
	call	_readHexByte
	pop	af
	ld	a,l
	pop	bc
	or	a, a
	jr	Z,00110$
	ld	l,#0x0A
	jp	00145$
00110$:
;idisk4.c:171: sum = sum + recType;
	ld	a,-1 (ix)
	add	a, -14 (ix)
	ld	-1 (ix),a
;idisk4.c:172: switch (recType) {
	ld	a,-14 (ix)
	or	a, a
	jr	Z,00111$
	ld	a,-14 (ix)
	dec	a
	jp	Z,00127$
	ld	a,-14 (ix)
	sub	a, #0x04
	jp	Z,00128$
	ld	a,-14 (ix)
	sub	a, #0x09
	jp	Z,00135$
	jp	00136$
;idisk4.c:173: case 0:							// Data record
00111$:
;idisk4.c:174: addr = (((unsigned long)hiAddr) << 16 ) | lowAddr;
	ld	hl,#_hiAddr + 0
	ld	h, (hl)
	ld	iy,#_hiAddr
	ld	l,1 (iy)
	ld	de,#0x0000
	push	af
	ld	-9 (ix),h
	ld	-8 (ix),l
	ld	-7 (ix),d
	ld	-6 (ix),e
	pop	af
	ld	a,#0x10
00248$:
	sla	-9 (ix)
	rl	-8 (ix)
	rl	-7 (ix)
	rl	-6 (ix)
	dec	a
	jr	NZ,00248$
	ld	a,(#_lowAddr + 0)
	ld	-5 (ix),a
	ld	a,(#_lowAddr + 1)
	ld	-4 (ix),a
	ld	-3 (ix),#0x00
	ld	-2 (ix),#0x00
	ld	a,-9 (ix)
	or	a, -5 (ix)
	ld	(#_addr + 0),a
	ld	a,-8 (ix)
	or	a, -4 (ix)
	ld	(#_addr + 1),a
	ld	a,-7 (ix)
	or	a, -3 (ix)
	ld	(#_addr + 2),a
	ld	a,-6 (ix)
	or	a, -2 (ix)
	ld	(#_addr + 3),a
;idisk4.c:175: if (byteCount == 0) {
	ld	a,(#_byteCount + 1)
	ld	hl,#_byteCount + 0
	or	a,(hl)
	jp	NZ,00165$
;idisk4.c:177: if ((addr != 0) && (addr != 0x8000) && (addr != 0x10000) && (addr != 0x18000)) return 14;	  // Verify starting address
	ld	a,(#_addr + 3)
	ld	hl,#_addr + 2
	or	a,(hl)
	ld	hl,#_addr + 1
	or	a,(hl)
	ld	hl,#_addr + 0
	or	a,(hl)
	jr	Z,00113$
	ld	a,(#_addr + 0)
	or	a, a
	jr	NZ,00250$
	ld	a,(#_addr + 1)
	sub	a, #0x80
	jr	NZ,00250$
	ld	a,(#_addr + 2)
	or	a, a
	jr	NZ,00250$
	ld	a,(#_addr + 3)
	or	a, a
	jr	Z,00113$
00250$:
	ld	a,(#_addr + 0)
	or	a, a
	jr	NZ,00251$
	ld	a,(#_addr + 1)
	or	a, a
	jr	NZ,00251$
	ld	a,(#_addr + 2)
	dec	a
	jr	NZ,00251$
	ld	a,(#_addr + 3)
	or	a, a
	jr	Z,00113$
00251$:
	ld	a,(#_addr + 0)
	or	a, a
	jr	NZ,00252$
	ld	a,(#_addr + 1)
	sub	a, #0x80
	jr	NZ,00252$
	ld	a,(#_addr + 2)
	dec	a
	jr	NZ,00252$
	ld	a,(#_addr + 3)
	or	a, a
	jr	Z,00113$
00252$:
	ld	l,#0x0E
	jp	00145$
00113$:
;idisk4.c:178: startAddr = addr;									 // Save starting address
	push	bc
	ld	de, #_startAddr
	ld	hl, #_addr
	ld	bc, #4
	ldir
	pop	bc
;idisk4.c:179: segment = (unsigned char)(addr / 0x8000);						 // Calculate the EEPROM segment to write
	push	af
	ld	hl,#_addr + 0
	ld	h, (hl)
	ld	iy,#_addr
	ld	l,1 (iy)
	ld	iy,#_addr
	ld	d,2 (iy)
	ld	iy,#_addr
	ld	e,3 (iy)
	pop	af
	ld	a,#0x0F
00253$:
	srl	e
	rr	d
	rr	l
	rr	h
	dec	a
	jr	NZ,00253$
	ld	iy,#_segment
	ld	0 (iy),h
;idisk4.c:181: for (i = 0;	i < recLength;	i++) {
00165$:
	ld	-5 (ix),c
	ld	-4 (ix),b
	ld	-13 (ix),#0x00
00143$:
	ld	a,-13 (ix)
	sub	a, -12 (ix)
	jp	NC,00126$
;idisk4.c:183: if (readHexByte(&byte) > 0) return 10;		// Read a data byte
	ld	l,-5 (ix)
	ld	h,-4 (ix)
	push	hl
	call	_readHexByte
	pop	af
	ld	a,l
	or	a, a
	jr	Z,00120$
	ld	l,#0x0A
	jp	00145$
00120$:
;idisk4.c:184: sum = sum + byte;
	ld	a,-1 (ix)
	add	a, -11 (ix)
	ld	-1 (ix),a
;idisk4.c:185: if ((addr + i) == (startAddr + byteCount)) {
	ld	e,-13 (ix)
	ld	d,#0x00
	ld	bc,#0x0000
	ld	a,(#_addr + 0)
	add	a, e
	ld	-9 (ix),a
	ld	a,(#_addr + 1)
	adc	a, d
	ld	-8 (ix),a
	ld	a,(#_addr + 2)
	adc	a, b
	ld	-7 (ix),a
	ld	a,(#_addr + 3)
	adc	a, c
	ld	-6 (ix),a
	ld	hl,#_byteCount + 0
	ld	e, (hl)
	ld	hl,#_byteCount + 1
	ld	d, (hl)
	ld	bc,#0x0000
	ld	a,(#_startAddr + 0)
	add	a, e
	ld	e,a
	ld	a,(#_startAddr + 1)
	adc	a, d
	ld	d,a
	ld	a,(#_startAddr + 2)
	adc	a, c
	ld	c,a
	ld	a,(#_startAddr + 3)
	adc	a, b
	ld	b,a
	ld	a,-9 (ix)
	sub	a, e
	jr	NZ,00124$
	ld	a,-8 (ix)
	sub	a, d
	jr	NZ,00124$
	ld	a,-7 (ix)
	sub	a, c
	jr	NZ,00124$
	ld	a,-6 (ix)
	sub	a, b
	jr	NZ,00124$
;idisk4.c:186: if (byteCount >= dataBuffSize) return 16;	  // Data buffer full
	ld	a,(#_byteCount + 1)
	sub	a, #0x80
	jr	C,00122$
	ld	l,#0x10
	jp	00145$
00122$:
;idisk4.c:187: dataBuff[byteCount] = byte;
	ld	a,#<(_dataBuff)
	ld	hl,#_byteCount
	add	a, (hl)
	ld	e,a
	ld	a,#>(_dataBuff)
	inc	hl
	adc	a, (hl)
	ld	d,a
	ld	a,-11 (ix)
	ld	(de),a
;idisk4.c:188: byteCount++;
	ld	hl, #_byteCount+0
	inc	(hl)
	jr	NZ,00144$
	ld	hl, #_byteCount+1
	inc	(hl)
	jr	00144$
00124$:
;idisk4.c:190: else return 15;					// Data address not in sequence
	ld	l,#0x0F
	jp	00145$
00144$:
;idisk4.c:181: for (i = 0;	i < recLength;	i++) {
	inc	-13 (ix)
	jp	00143$
00126$:
;idisk4.c:195: retValue = 0;
	ld	e,#0x00
;idisk4.c:196: break;
	jp	00137$
;idisk4.c:198: case 1:							// EOF record
00127$:
;idisk4.c:199: retValue = 1;
	ld	e,#0x01
;idisk4.c:200: break;
	jp	00137$
;idisk4.c:202: case 4:							// Extended linear address record
00128$:
;idisk4.c:203: if (lowAddr != 0) return 12;			 // Expected "0000" address in type 04 record
	ld	a,(#_lowAddr + 1)
	ld	hl,#_lowAddr + 0
	or	a,(hl)
	jr	Z,00130$
	ld	l,#0x0C
	jp	00145$
00130$:
;idisk4.c:204: if (readHexByte(&byte) > 0) return 10;		 // Read 16 bit extended address MSB
	ld	l, c
	ld	h, b
	push	bc
	push	hl
	call	_readHexByte
	pop	af
	ld	a,l
	pop	bc
	or	a, a
	jr	Z,00132$
	ld	l,#0x0A
	jp	00145$
00132$:
;idisk4.c:205: sum = sum + byte;
	ld	a,-1 (ix)
	add	a, -11 (ix)
	ld	l,a
;idisk4.c:206: hiAddr = ((unsigned int)byte) << 8;
	ld	e,-11 (ix)
	ld	h,#0x00
	ld	iy,#_hiAddr
	ld	1 (iy),e
	ld	iy,#_hiAddr
	ld	0 (iy),#0x00
;idisk4.c:207: if (readHexByte(&byte) > 0) return 10;		 // Read 16 bit extended address LSB
	push	hl
	push	bc
	call	_readHexByte
	pop	af
	ld	a,l
	pop	hl
	or	a, a
	jr	Z,00134$
	ld	l,#0x0A
	jr	00145$
00134$:
;idisk4.c:208: i = sum + byte;					 // Splitted to avoid a strange SDDC "liverange" warning
	ld	a,l
	add	a, -11 (ix)
	ld	-1 (ix),a
;idisk4.c:210: hiAddr = hiAddr | byte;
	ld	d,-11 (ix)
	ld	e,#0x00
	ld	a,(#_hiAddr + 0)
	or	a, d
	ld	(#_hiAddr + 0),a
	ld	a,(#_hiAddr + 1)
	or	a, e
	ld	(#_hiAddr + 1),a
;idisk4.c:211: retValue = 4;
	ld	e,#0x04
;idisk4.c:212: break;
	jr	00137$
;idisk4.c:214: case 9:							// Just4Fun "magic" record :-)
00135$:
;idisk4.c:215: magic = (unsigned char)lowAddr;
	ld	a,(#_lowAddr + 0)
	ld	(#_magic + 0),a
;idisk4.c:216: retValue = 9;
	ld	e,#0x09
;idisk4.c:217: break;
	jr	00137$
;idisk4.c:219: default:						// Illegal record type
00136$:
;idisk4.c:220: return 11;
	ld	l,#0x0B
	jr	00145$
;idisk4.c:221: }
00137$:
;idisk4.c:222: if (readHexByte(&checksum) > 0) return 10;		// Read checksum byte
	ld	hl,#0x0004
	add	hl,sp
	push	de
	push	hl
	call	_readHexByte
	pop	af
	ld	a,l
	pop	de
	or	a, a
	jr	Z,00139$
	ld	l,#0x0A
	jr	00145$
00139$:
;idisk4.c:223: sum = 1 + ~sum;						// Calculate checksum
	ld	a,-1 (ix)
	cpl
	ld	d,a
	inc	d
;idisk4.c:224: if (sum != checksum) return 13;				// Validate checksum
	ld	a,-10 (ix)
	sub	a, d
	jr	Z,00141$
	ld	l,#0x0D
	jr	00145$
00141$:
;idisk4.c:225: return retValue;
	ld	l,e
00145$:
	ld	sp, ix
	pop	ix
	ret
;idisk4.c:228: unsigned char verifyDiskSect(unsigned char disk, unsigned char track, unsigned char sector, unsigned int *buffIndex )
;	---------------------------------
; Function verifyDiskSect
; ---------------------------------
_verifyDiskSect::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
;idisk4.c:235: unsigned char notEqual = 0;
	ld	-2 (ix),#0x00
;idisk4.c:237: SELDISK = disk;						// Disk number
	ld	a,4 (ix)
	out	(_SELDISK),a
;idisk4.c:238: SELTRACK = track;					// Track LSB
	ld	a,5 (ix)
	out	(_SELTRACK),a
;idisk4.c:239: SELTRACK = 0;						// Track MSB
	ld	a,#0x00
	out	(_SELTRACK),a
;idisk4.c:240: SELSECT = sector;					// Sector LSB
	ld	a,6 (ix)
	out	(_SELSECT),a
;idisk4.c:241: SELSECT = 0;						// Sector MSB
	ld	a,#0x00
	out	(_SELSECT),a
;idisk4.c:242: for (ii = 0;	ii < 128;	ii++) {
	ld	hl,#0x0080
	ex	(sp), hl
00106$:
;idisk4.c:244: if (READSECT != dataBuff[*buffIndex]) notEqual = 1;
	ld	c,7 (ix)
	ld	b,8 (ix)
	ld	l, c
	ld	h, b
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	hl,#_dataBuff
	add	hl,de
	ld	a,(hl)
	ld	-1 (ix),a
	in	a,(_READSECT)
	sub	a, -1 (ix)
	jr	Z,00102$
	ld	-2 (ix),#0x01
00102$:
;idisk4.c:245: (*buffIndex)++;
	inc	de
	ld	a,e
	ld	(bc),a
	inc	bc
	ld	a,d
	ld	(bc),a
	ld	l,-4 (ix)
	ld	h,-3 (ix)
	dec	hl
	inc	sp
	inc	sp
	push	hl
;idisk4.c:242: for (ii = 0;	ii < 128;	ii++) {
	ld	a,h
	or	a,l
	jr	NZ,00106$
;idisk4.c:247: return notEqual;
	ld	l,-2 (ix)
	ld	sp, ix
	pop	ix
	ret
;idisk4.c:250: unsigned char writeDiskSect(unsigned char disk, unsigned char track, unsigned char sector, unsigned int *buffIndex )
;	---------------------------------
; Function writeDiskSect
; ---------------------------------
_writeDiskSect::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;idisk4.c:258: SELDISK = disk;						// Disk number
	ld	a,4 (ix)
	out	(_SELDISK),a
;idisk4.c:259: SELTRACK = track;					// Track LSB
	ld	a,5 (ix)
	out	(_SELTRACK),a
;idisk4.c:260: SELTRACK = 0;						// Track MSB
	ld	a,#0x00
	out	(_SELTRACK),a
;idisk4.c:261: SELSECT = sector;					// Sector LSB
	ld	a,6 (ix)
	out	(_SELSECT),a
;idisk4.c:262: SELSECT = 0;						// Sector MSB
	ld	a,#0x00
	out	(_SELSECT),a
;idisk4.c:263: for (ii = 0;	ii < 128;	ii++) {
	ld	de,#0x0000
00102$:
;idisk4.c:265: WRITESECT = dataBuff[*buffIndex];
	ld	a,7 (ix)
	ld	-2 (ix),a
	ld	a,8 (ix)
	ld	-1 (ix),a
	pop	hl
	push	hl
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	hl,#_dataBuff
	add	hl,bc
	ld	a,(hl)
	out	(_WRITESECT),a
;idisk4.c:266: (*buffIndex)++;
	inc	bc
	pop	hl
	push	hl
	ld	(hl),c
	inc	hl
	ld	(hl),b
;idisk4.c:263: for (ii = 0;	ii < 128;	ii++) {
	inc	de
	ld	a,e
	sub	a, #0x80
	ld	a,d
	sbc	a, #0x00
	jr	C,00102$
;idisk4.c:268: return ERRDISK;
	in	a,(_ERRDISK)
	ld	l,a
	ld	sp, ix
	pop	ix
	ret
;idisk4.c:271: void main()
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;idisk4.c:273: printf("\n\niDisk - Intel-Hex Disk image Loader - S250317");
	ld	hl,#___str_14
	push	hl
	call	_printf
	pop	af
;idisk4.c:274: for (i = 0;	i < NDISKS;	i++)
	ld	hl,#_i + 0
	ld	(hl), #0x00
00193$:
;idisk4.c:275: for (ii=0;ii<4;ii++)
	ld	hl,#0x0000
	ld	(_ii),hl
00191$:
;idisk4.c:276: SegDone[i][ii]=0;
	ld	iy,#_i
	ld	l,0 (iy)
	ld	h,#0x00
	add	hl, hl
	add	hl, hl
	ld	a,#<(_SegDone)
	add	a, l
	ld	e,a
	ld	a,#>(_SegDone)
	adc	a, h
	ld	d,a
	ld	hl,(_ii)
	add	hl,de
	ld	(hl),#0x00
;idisk4.c:275: for (ii=0;ii<4;ii++)
	ld	hl, #_ii+0
	inc	(hl)
	jr	NZ,00421$
	ld	hl, #_ii+1
	inc	(hl)
00421$:
	ld	a,(#_ii + 0)
	sub	a, #0x04
	ld	a,(#_ii + 1)
	sbc	a, #0x00
	jr	C,00191$
;idisk4.c:274: for (i = 0;	i < NDISKS;	i++)
	ld	hl, #_i+0
	inc	(hl)
	ld	a,(#_i + 0)
	sub	a, #0x04
	jr	C,00193$
;idisk4.c:278: if (ERRDISK == 14) {
	in	a,(_ERRDISK)
	sub	a, #0x0E
	jr	NZ,00188$
;idisk4.c:279: printf("\n");
	ld	hl,#___str_15
	push	hl
	call	_printf
;idisk4.c:280: printErr(14);
	ld	h,#0x0E
	ex	(sp),hl
	inc	sp
	call	_printErr
	inc	sp
;idisk4.c:281: printf("\n* Program aborted *\n");
	ld	hl,#___str_16
	push	hl
	call	_printf
	pop	af
;idisk4.c:282: return;
	jp	00207$
;idisk4.c:284: do {
00188$:
;idisk4.c:285: for (ii = 0;	ii < dataBuffSize;	ii++) dataBuff[ii] = 0xe5;	 // Initialize data buffer
	ld	hl,#0x0000
	ld	(_ii),hl
	ld	de,#_dataBuff+0
00195$:
	ld	hl,(_ii)
	add	hl,de
	ld	(hl),#0xE5
	ld	hl, #_ii+0
	inc	(hl)
	jr	NZ,00424$
	ld	hl, #_ii+1
	inc	(hl)
00424$:
	ld	a,(#_ii + 1)
	sub	a, #0x80
	jr	C,00195$
;idisk4.c:286: byteCount = 0;						 // Initialize read bytes counter
	ld	hl,#0x0000
	ld	(_byteCount),hl
;idisk4.c:287: hiAddr = 0;
	ld	l, #0x00
	ld	(_hiAddr),hl
;idisk4.c:288: startAddr = 0;
	xor	a, a
	ld	iy,#_startAddr
	ld	0 (iy),a
	ld	iy,#_startAddr
	ld	1 (iy),a
	ld	iy,#_startAddr
	ld	2 (iy),a
	ld	iy,#_startAddr
	ld	3 (iy),a
;idisk4.c:289: magic = 0xff;
	ld	iy,#_magic
	ld	0 (iy),#0xFF
;idisk4.c:290: dataBuffIdx = 0;
	ld	l, #0x00
	ld	(_dataBuffIdx),hl
;idisk4.c:291: errFlag = 0;
	ld	hl,#_errFlag + 0
	ld	(hl), #0x00
;idisk4.c:292: writeFlag = 0;
	ld	hl,#_writeFlag + 0
	ld	(hl), #0x00
;idisk4.c:293: boundFillFlag = 0;
	ld	hl,#_boundFillFlag + 0
	ld	(hl), #0x00
;idisk4.c:294: writeErrorCode = 0;
	ld	hl,#_writeErrorCode + 0
	ld	(hl), #0x00
;idisk4.c:295: writeDoneFlag = 0;
	ld	hl,#_writeDoneFlag + 0
	ld	(hl), #0x00
;idisk4.c:296: printf("\n\nDisk segments write status: ");
	ld	hl,#___str_17
	push	hl
	call	_printf
	pop	af
;idisk4.c:297: for (ii=0;ii<NDISKS;ii++)
	ld	hl,#0x0000
	ld	(_ii),hl
00199$:
;idisk4.c:299: printf(" D%d[",ii);
	ld	de,#___str_18
	ld	hl,(_ii)
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:300: for (i=0;i<4;i++)
	ld	hl,#_i + 0
	ld	(hl), #0x00
00197$:
;idisk4.c:302: putchar(SegDone[ii][i]?'0'+i:'.');
	ld	a,(#_ii + 0)
	ld	-2 (ix),a
	ld	a,(#_ii + 1)
	ld	-1 (ix),a
	ld	a,#0x02+1
	jr	00426$
00425$:
	sla	-2 (ix)
	rl	-1 (ix)
00426$:
	dec	a
	jr	NZ,00425$
	ld	a,#<(_SegDone)
	add	a, -2 (ix)
	ld	-2 (ix),a
	ld	a,#>(_SegDone)
	adc	a, -1 (ix)
	ld	-1 (ix),a
	ld	hl,#_i + 0
	ld	e, (hl)
	pop	hl
	push	hl
	ld	d,#0x00
	add	hl, de
	ld	a,(hl)
	or	a, a
	jr	Z,00209$
	ld	a,(#_i + 0)
	ld	-2 (ix), a
	add	a, #0x30
	ld	e,a
	jr	00210$
00209$:
	ld	e,#0x2E
00210$:
	ld	a,e
	push	af
	inc	sp
	call	_putchar
	inc	sp
;idisk4.c:300: for (i=0;i<4;i++)
	ld	hl, #_i+0
	inc	(hl)
	ld	a,(#_i + 0)
	sub	a, #0x04
	jr	C,00197$
;idisk4.c:304: printf("] %c",ii!=3?'-':' ');
	ld	a,(#_ii + 0)
	sub	a, #0x03
	jr	NZ,00427$
	ld	a,(#_ii + 1)
	or	a, a
	jr	Z,00211$
00427$:
	ld	a,#0x2D
	jr	00212$
00211$:
	ld	a,#0x20
00212$:
	ld	e,a
	rla
	sbc	a, a
	ld	d,a
	ld	hl,#___str_19
	push	de
	push	hl
	call	_printf
	pop	af
	pop	af
;idisk4.c:297: for (ii=0;ii<NDISKS;ii++)
	ld	hl, #_ii+0
	inc	(hl)
	jr	NZ,00428$
	ld	hl, #_ii+1
	inc	(hl)
00428$:
	ld	a,(#_ii + 0)
	sub	a, #0x04
	ld	a,(#_ii + 1)
	sbc	a, #0x00
	jp	C,00199$
;idisk4.c:306: printf("\n\nWaiting input stream...\n");
	ld	hl,#___str_20
	push	hl
	call	_printf
	pop	af
;idisk4.c:307: do {
00109$:
;idisk4.c:309: i =  readOneLine();
	call	_readOneLine
	ld	iy,#_i
	ld	0 (iy),l
;idisk4.c:310: printf("\n");
	ld	hl,#___str_15
	push	hl
	call	_printf
	pop	af
;idisk4.c:311: } while ((i != 1) && (i < 10));
	ld	a,(#_i + 0)
	dec	a
	jr	Z,00111$
	ld	a,(#_i + 0)
	sub	a, #0x0A
	jr	C,00109$
00111$:
;idisk4.c:312: if (i > 9) {
	ld	a,#0x09
	ld	iy,#_i
	sub	a, 0 (iy)
	jp	NC,00148$
;idisk4.c:314: errFlag = 1;
	ld	hl,#_errFlag + 0
	ld	(hl), #0x01
;idisk4.c:315: printf("\nERROR: ");
	ld	hl,#___str_21
	push	hl
	call	_printf
	pop	af
;idisk4.c:316: switch (i) {
	ld	a,(#_i + 0)
	sub	a, #0x0A
	jr	C,00119$
	ld	a,#0x10
	ld	iy,#_i
	sub	a, 0 (iy)
	jr	C,00119$
	ld	iy,#_i
	ld	a,0 (iy)
	add	a,#0xF6
	ld	e,a
	ld	d,#0x00
	ld	hl,#00430$
	add	hl,de
	add	hl,de
;idisk4.c:317: case 10:
	jp	(hl)
00430$:
	jr	00112$
	jr	00113$
	jr	00114$
	jr	00115$
	jr	00116$
	jr	00117$
	jr	00118$
00112$:
;idisk4.c:318: printf("syntax error");
	ld	hl,#___str_22
	push	hl
	call	_printf
	pop	af
;idisk4.c:319: break;
	jr	00119$
;idisk4.c:320: case 11:
00113$:
;idisk4.c:321: printf("illegal record type");
	ld	hl,#___str_23
	push	hl
	call	_printf
	pop	af
;idisk4.c:322: break;
	jr	00119$
;idisk4.c:323: case 12:
00114$:
;idisk4.c:324: printf("expected address 0000 in type 04 record");
	ld	hl,#___str_24
	push	hl
	call	_printf
	pop	af
;idisk4.c:325: break;
	jr	00119$
;idisk4.c:326: case 13:
00115$:
;idisk4.c:327: printf("checksum error");
	ld	hl,#___str_25
	push	hl
	call	_printf
	pop	af
;idisk4.c:328: break;
	jr	00119$
;idisk4.c:329: case 14:
00116$:
;idisk4.c:330: printf("illegal starting address");
	ld	hl,#___str_26
	push	hl
	call	_printf
	pop	af
;idisk4.c:331: break;
	jr	00119$
;idisk4.c:332: case 15:
00117$:
;idisk4.c:333: printf("data address not in sequence");
	ld	hl,#___str_27
	push	hl
	call	_printf
	pop	af
;idisk4.c:334: break;
	jr	00119$
;idisk4.c:335: case 16:
00118$:
;idisk4.c:336: printf("data buffer full");
	ld	hl,#___str_28
	push	hl
	call	_printf
	pop	af
;idisk4.c:338: }
00119$:
;idisk4.c:339: printf("\nPress ESC to continue...");
	ld	hl,#___str_29
	push	hl
	call	_printf
	pop	af
;idisk4.c:340: do c = getchar();
00120$:
	call	_getchar
	ld	iy,#_c
	ld	0 (iy),l
;idisk4.c:341: while (c != 27);
	ld	a,(#_c + 0)
	sub	a, #0x1B
	jp	Z,00149$
	jr	00120$
	jp	00149$
00148$:
;idisk4.c:346: printf("\nRead bytes count: %u", byteCount);
	ld	de,#___str_30
	ld	hl,(_byteCount)
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:347: printf("\nEEPROM first addr to write: 0x%05lX", startAddr);
	ld	de,#___str_31
	ld	hl,(_startAddr + 2)
	push	hl
	ld	hl,(_startAddr)
	push	hl
	push	de
	call	_printf
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;idisk4.c:348: printf("\nEEPROM current 32kB segment: %01u", segment);
	ld	hl,#_segment + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_32
	push	de
	push	hl
	call	_printf
	pop	af
	pop	af
;idisk4.c:349: firstTrack = (diskSectors / 128) * segment;	// Calculate first track to write
	ld	a,(#_segment + 0)
	rlca
	rlca
	rlca
	and	a,#0xF8
	ld	(#_firstTrack + 0),a
;idisk4.c:350: printf("\nFirst Track/Sector to write: %02u/01", firstTrack);
	ld	hl,#_firstTrack + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_33
	push	de
	push	hl
	call	_printf
	pop	af
	pop	af
;idisk4.c:351: sectors = byteCount / 128;			// Calculate how many contiguous sectors to write
	ld	a,(#_byteCount + 0)
	ld	(#_sectors + 0),a
	ld	a,(#_byteCount + 1)
	ld	(#_sectors + 1),a
	ld	iy,#_sectors
	srl	1 (iy)
	ld	iy,#_sectors
	rr	0 (iy)
	ld	iy,#_sectors
	srl	1 (iy)
	ld	iy,#_sectors
	rr	0 (iy)
	ld	iy,#_sectors
	srl	1 (iy)
	ld	iy,#_sectors
	rr	0 (iy)
	ld	iy,#_sectors
	srl	1 (iy)
	ld	iy,#_sectors
	rr	0 (iy)
	ld	iy,#_sectors
	srl	1 (iy)
	ld	iy,#_sectors
	rr	0 (iy)
	ld	iy,#_sectors
	srl	1 (iy)
	ld	iy,#_sectors
	rr	0 (iy)
	ld	iy,#_sectors
	srl	1 (iy)
	ld	iy,#_sectors
	rr	0 (iy)
;idisk4.c:352: if ((byteCount % 128) != 0) {			// Check if sector filling is needed
	ld	a,(#_byteCount + 0)
	and	a, #0x7F
	jr	Z,00124$
;idisk4.c:353: sectors++;
	ld	hl, #_sectors+0
	inc	(hl)
	jr	NZ,00434$
	ld	hl, #_sectors+1
	inc	(hl)
00434$:
;idisk4.c:354: boundFillFlag = 1;
	ld	hl,#_boundFillFlag + 0
	ld	(hl), #0x01
00124$:
;idisk4.c:356: printf("\nContiguous sectors to write: %03u", sectors);
	ld	de,#___str_34
	ld	hl,(_sectors)
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:357: if (sectors > 0) lastTrack = firstTrack + ((sectors - 1) / 32);
	ld	a,(#_sectors + 1)
	ld	hl,#_sectors + 0
	or	a,(hl)
	jr	Z,00126$
	ld	hl,#_sectors + 0
	ld	e, (hl)
	ld	hl,#_sectors + 1
	ld	d, (hl)
	dec	de
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	ld	hl,#_lastTrack
	ld	a,(#_firstTrack + 0)
	add	a, e
	ld	(hl),a
	jr	00127$
00126$:
;idisk4.c:358: else lastTrack = firstTrack;
	ld	a,(#_firstTrack + 0)
	ld	(#_lastTrack + 0),a
00127$:
;idisk4.c:359: printf("\nLast Track/Sector to write: %02u", lastTrack);
	ld	hl,#_lastTrack + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_35
	push	de
	push	hl
	call	_printf
	pop	af
	pop	af
;idisk4.c:360: if (sectors < 2) lastSector = 1;
	ld	a,(#_sectors + 0)
	sub	a, #0x02
	ld	a,(#_sectors + 1)
	sbc	a, #0x00
	jr	NC,00129$
	ld	hl,#_lastSector + 0
	ld	(hl), #0x01
	jr	00130$
00129$:
;idisk4.c:361: else lastSector = ((sectors - 1) % 32) + 1;
	ld	hl,#_sectors + 0
	ld	e, (hl)
	ld	hl,#_sectors + 1
	ld	d, (hl)
	dec	de
	ld	a,e
	and	a, #0x1F
	ld	hl,#_lastSector
	inc	a
	ld	(hl),a
00130$:
;idisk4.c:362: printf("/%02u", lastSector);
	ld	hl,#_lastSector + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_36
	push	de
	push	hl
	call	_printf
	pop	af
;idisk4.c:363: printf("\nLast sector boundary fill: ");	// Sector boudary fill
	ld	hl, #___str_37
	ex	(sp),hl
	call	_printf
	pop	af
;idisk4.c:364: if (!boundFillFlag) printf("not needed");
	ld	a,(#_boundFillFlag + 0)
	or	a, a
	jr	NZ,00132$
	ld	hl,#___str_38
	push	hl
	call	_printf
	pop	af
	jr	00133$
00132$:
;idisk4.c:365: else printf("yes");
	ld	hl,#___str_39
	push	hl
	call	_printf
	pop	af
00133$:
;idisk4.c:366: if (byteCount > 0) {
	ld	a,(#_byteCount + 1)
	ld	hl,#_byteCount + 0
	or	a,(hl)
	jr	Z,00145$
;idisk4.c:367: if (magic < NDISKS) targetDisk = magic;
	ld	a,(#_magic + 0)
	cp	a,#0x04
	jr	NC,00142$
	ld	(#_targetDisk + 0),a
	jr	00143$
00142$:
;idisk4.c:370: printf("\n\nEnter the target virtual disk [0-%d] >",NDISKS-1);
	ld	hl,#___str_40
	ld	bc,#0x0003
	push	bc
	push	hl
	call	_printf
	pop	af
	pop	af
;idisk4.c:371: do {
00138$:
;idisk4.c:372: c = getchar();
	call	_getchar
	ld	iy,#_c
	ld	0 (iy),l
;idisk4.c:374: if (c>='0' && c<'0'+NDISKS) putchar(c);
	ld	a,(#_c + 0)
	xor	a, #0x80
	sub	a, #0xB0
	jr	C,00135$
	ld	a,(#_c + 0)
	xor	a, #0x80
	sub	a, #0xB4
	jr	NC,00135$
	ld	a,(_c)
	push	af
	inc	sp
	call	_putchar
	inc	sp
00135$:
;idisk4.c:375: targetDisk = c - '0';
	ld	hl,#_targetDisk
	ld	a,(#_c + 0)
	add	a,#0xD0
	ld	(hl),a
;idisk4.c:376: } while ((c < '0') || (c >='0'+NDISKS ));
	ld	a,(#_c + 0)
	xor	a, #0x80
	sub	a, #0xB0
	jr	C,00138$
	ld	a,(#_c + 0)
	xor	a, #0x80
	sub	a, #0xB4
	jr	NC,00138$
00143$:
;idisk4.c:378: printf("\nTarget virtual disk: %u", targetDisk);
	ld	hl,#_targetDisk + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_41
	push	de
	push	hl
	call	_printf
	pop	af
	pop	af
	jr	00149$
00145$:
;idisk4.c:380: else printf("\nNothing to do...");
	ld	hl,#___str_42
	push	hl
	call	_printf
	pop	af
00149$:
;idisk4.c:382: if ((byteCount > 0) && !errFlag) {
	ld	a,(#_byteCount + 1)
	ld	hl,#_byteCount + 0
	or	a,(hl)
	jp	Z,00174$
	ld	a,(#_errFlag + 0)
	or	a, a
	jp	NZ,00174$
;idisk4.c:384: printf("\n\nPress W to write or A to abort [W/A] >");
	ld	hl,#___str_43
	push	hl
	call	_printf
	pop	af
;idisk4.c:385: do c = upperCase(getchar());
00151$:
	call	_getchar
	ld	h,l
	push	hl
	inc	sp
	call	_upperCase
	inc	sp
	ld	iy,#_c
	ld	0 (iy),l
;idisk4.c:386: while ((c != 'W') && (c != 'A'));
	ld	a,(#_c + 0)
	cp	a,#0x57
	jr	Z,00153$
	sub	a, #0x41
	jr	NZ,00151$
00153$:
;idisk4.c:387: putchar(c);
	ld	a,(_c)
	push	af
	inc	sp
	call	_putchar
	inc	sp
;idisk4.c:388: if (c == 'W') {
	ld	a,(#_c + 0)
	sub	a, #0x57
	jr	NZ,00161$
;idisk4.c:389: printf("\n\n* WARNING * ALL PREVIOUS DATA IN THE TARGET SECTORS WILL BE OVERWRITTEN!");
	ld	hl,#___str_44
	push	hl
	call	_printf
;idisk4.c:390: printf("\n\nAre you sure [Y/N]? >");
	ld	hl, #___str_45
	ex	(sp),hl
	call	_printf
	pop	af
;idisk4.c:391: do c = upperCase(getchar());
00155$:
	call	_getchar
	ld	h,l
	push	hl
	inc	sp
	call	_upperCase
	inc	sp
	ld	iy,#_c
	ld	0 (iy),l
;idisk4.c:392: while ((c != 'Y') && (c != 'N'));
	ld	a,(#_c + 0)
	cp	a,#0x59
	jr	Z,00157$
	sub	a, #0x4E
	jr	NZ,00155$
00157$:
;idisk4.c:393: putchar(c);
	ld	a,(_c)
	push	af
	inc	sp
	call	_putchar
	inc	sp
;idisk4.c:394: if (c == 'Y') writeFlag = 1;
	ld	a,(#_c + 0)
	sub	a, #0x59
	jr	NZ,00161$
	ld	hl,#_writeFlag + 0
	ld	(hl), #0x01
00161$:
;idisk4.c:396: if (!writeFlag) printf("\nWrite operation cancelled!");
	ld	a,(#_writeFlag + 0)
	or	a, a
	jr	NZ,00171$
	ld	hl,#___str_46
	push	hl
	call	_printf
	pop	af
	jp	00174$
00171$:
;idisk4.c:398: track = firstTrack;
	ld	a,(#_firstTrack + 0)
	ld	(#_track + 0),a
;idisk4.c:399: sector = 1;
	ld	hl,#_sector + 0
	ld	(hl), #0x01
;idisk4.c:400: for (ii = 0;	ii < sectors;	ii++) {
	ld	hl,#0x0000
	ld	(_ii),hl
00202$:
	ld	hl,#_sectors
	ld	a,(#_ii + 0)
	sub	a, (hl)
	ld	a,(#_ii + 1)
	inc	hl
	sbc	a, (hl)
	jp	NC,00167$
;idisk4.c:402: printf("\n#%03u: writing... ", ii + 1);
	ld	hl,(_ii)
	inc	hl
	ld	de,#___str_47
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:403: printf(" Disk: %01u", targetDisk);
	ld	hl,#_targetDisk + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_48
	push	de
	push	hl
	call	_printf
	pop	af
	pop	af
;idisk4.c:404: printf(" - Track: %02u", track);
	ld	hl,#_track + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_49
	push	de
	push	hl
	call	_printf
	pop	af
	pop	af
;idisk4.c:405: printf(" - Sector: %02u", sector);
	ld	hl,#_sector + 0
	ld	e, (hl)
	ld	d,#0x00
	ld	hl,#___str_50
	push	de
	push	hl
	call	_printf
	pop	af
;idisk4.c:406: writeErrorCode = writeDiskSect(targetDisk, track, sector, &dataBuffIdx);
	ld	hl, #_dataBuffIdx
	ex	(sp),hl
	ld	a,(_sector)
	push	af
	inc	sp
	ld	a,(_track)
	push	af
	inc	sp
	ld	a,(_targetDisk)
	push	af
	inc	sp
	call	_writeDiskSect
	pop	af
	pop	af
	inc	sp
	ld	iy,#_writeErrorCode
	ld	0 (iy),l
;idisk4.c:407: if (writeErrorCode > 0) break;		// Abort write operation if an error occurred
	ld	a,(#_writeErrorCode + 0)
	or	a, a
	jr	NZ,00167$
;idisk4.c:408: if (sector < 32) sector++;
	ld	a,(#_sector + 0)
	sub	a, #0x20
	jr	NC,00165$
	ld	hl, #_sector+0
	inc	(hl)
	jr	00203$
00165$:
;idisk4.c:410: sector = 1;
	ld	hl,#_sector + 0
	ld	(hl), #0x01
;idisk4.c:411: track++;
	ld	hl, #_track+0
	inc	(hl)
00203$:
;idisk4.c:400: for (ii = 0;	ii < sectors;	ii++) {
	ld	hl, #_ii+0
	inc	(hl)
	jp	NZ,00202$
	ld	hl, #_ii+1
	inc	(hl)
	jp	00202$
00167$:
;idisk4.c:414: printErr(writeErrorCode);		 // Print write error (if any)
	ld	a,(_writeErrorCode)
	push	af
	inc	sp
	call	_printErr
	inc	sp
;idisk4.c:415: if (writeErrorCode > 0) printf("\n* WRITE ABORTED! *");
	ld	a,(#_writeErrorCode + 0)
	or	a, a
	jr	Z,00174$
	ld	hl,#___str_51
	push	hl
	call	_printf
	pop	af
00174$:
;idisk4.c:419: if ((writeErrorCode == 0) && writeFlag) {
	ld	a,(#_writeErrorCode + 0)
	or	a, a
	jp	NZ,00188$
	ld	a,(#_writeFlag + 0)
	or	a, a
	jp	Z,00188$
;idisk4.c:420: dataBuffIdx = 0;
	ld	hl,#0x0000
	ld	(_dataBuffIdx),hl
;idisk4.c:421: track = firstTrack;
	ld	a,(#_firstTrack + 0)
	ld	(#_track + 0),a
;idisk4.c:422: sector = 1;
	ld	hl,#_sector + 0
	ld	(hl), #0x01
;idisk4.c:423: writeDoneFlag = 1;
	ld	hl,#_writeDoneFlag + 0
	ld	(hl), #0x01
;idisk4.c:424: printf("\n");
	ld	hl,#___str_15
	push	hl
	call	_printf
	pop	af
;idisk4.c:425: for (ii = 0;	ii < sectors;	ii++) {
	ld	hl,#0x0000
	ld	(_ii),hl
00205$:
	ld	hl,#_sectors
	ld	a,(#_ii + 0)
	sub	a, (hl)
	ld	a,(#_ii + 1)
	inc	hl
	sbc	a, (hl)
	jp	NC,00182$
;idisk4.c:427: printf("\n#%03u: verifying...", ii + 1);
	ld	hl,(_ii)
	inc	hl
	ld	de,#___str_52
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:428: printf(" Disk: %01u", targetDisk);
	ld	iy,#_targetDisk
	ld	l,0 (iy)
	ld	h,#0x00
	ld	de,#___str_48
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:429: printf(" - Track: %02u", track);
	ld	iy,#_track
	ld	l,0 (iy)
	ld	h,#0x00
	ld	de,#___str_49
	push	hl
	push	de
	call	_printf
	pop	af
	pop	af
;idisk4.c:430: printf(" - Sector: %02u", sector);
	ld	iy,#_sector
	ld	l,0 (iy)
	ld	h,#0x00
	ld	de,#___str_50
	push	hl
	push	de
	call	_printf
	pop	af
;idisk4.c:431: if (verifyDiskSect(targetDisk, track, sector, &dataBuffIdx)) {
	ld	hl, #_dataBuffIdx+0
	ex	(sp),hl
	ld	a,(_sector)
	push	af
	inc	sp
	ld	a,(_track)
	push	af
	inc	sp
	ld	a,(_targetDisk)
	push	af
	inc	sp
	call	_verifyDiskSect
	pop	af
	pop	af
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00177$
;idisk4.c:433: printf("\n\n* FOUND MISMATCH - VERIFY FAILED! *\n");
	ld	hl,#___str_53+0
	push	hl
	call	_printf
	pop	af
;idisk4.c:434: writeDoneFlag = 0;
	ld	hl,#_writeDoneFlag + 0
	ld	(hl), #0x00
;idisk4.c:435: break;
	jr	00182$
00177$:
;idisk4.c:437: else printf(" -> OK");
	ld	hl,#___str_54
	push	hl
	call	_printf
	pop	af
;idisk4.c:438: if (sector < 32) sector++;
	ld	a,(#_sector + 0)
	sub	a, #0x20
	jr	NC,00180$
	ld	hl, #_sector+0
	inc	(hl)
	jr	00206$
00180$:
;idisk4.c:440: sector = 1;
	ld	hl,#_sector + 0
	ld	(hl), #0x01
;idisk4.c:441: track++;
	ld	hl, #_track+0
	inc	(hl)
00206$:
;idisk4.c:425: for (ii = 0;	ii < sectors;	ii++) {
	ld	hl, #_ii+0
	inc	(hl)
	jp	NZ,00205$
	ld	hl, #_ii+1
	inc	(hl)
	jp	00205$
00182$:
;idisk4.c:444: if (writeDoneFlag) {
	ld	a,(#_writeDoneFlag + 0)
	or	a, a
	jp	Z,00188$
;idisk4.c:445: SegDone[targetDisk][segment]=1;
	ld	iy,#_targetDisk
	ld	l,0 (iy)
	ld	h,#0x00
	add	hl, hl
	add	hl, hl
	ld	a,#<(_SegDone)
	add	a, l
	ld	e,a
	ld	a,#>(_SegDone)
	adc	a, h
	ld	d,a
	ld	iy,#_segment
	ld	l, 0 (iy)
	ld	h,#0x00
	add	hl,de
	ld	(hl),#0x01
;idisk4.c:448: } while (1);
	jp	00188$
00207$:
	ld	sp, ix
	pop	ix
	ret
___str_14:
	.db 0x0A
	.db 0x0A
	.ascii "iDisk - Intel-Hex Disk image Loader - S250317"
	.db 0x00
___str_15:
	.db 0x0A
	.db 0x00
___str_16:
	.db 0x0A
	.ascii "* Program aborted *"
	.db 0x0A
	.db 0x00
___str_17:
	.db 0x0A
	.db 0x0A
	.ascii "Disk segments write status: "
	.db 0x00
___str_18:
	.ascii " D%d["
	.db 0x00
___str_19:
	.ascii "] %c"
	.db 0x00
___str_20:
	.db 0x0A
	.db 0x0A
	.ascii "Waiting input stream..."
	.db 0x0A
	.db 0x00
___str_21:
	.db 0x0A
	.ascii "ERROR: "
	.db 0x00
___str_22:
	.ascii "syntax error"
	.db 0x00
___str_23:
	.ascii "illegal record type"
	.db 0x00
___str_24:
	.ascii "expected address 0000 in type 04 record"
	.db 0x00
___str_25:
	.ascii "checksum error"
	.db 0x00
___str_26:
	.ascii "illegal starting address"
	.db 0x00
___str_27:
	.ascii "data address not in sequence"
	.db 0x00
___str_28:
	.ascii "data buffer full"
	.db 0x00
___str_29:
	.db 0x0A
	.ascii "Press ESC to continue..."
	.db 0x00
___str_30:
	.db 0x0A
	.ascii "Read bytes count: %u"
	.db 0x00
___str_31:
	.db 0x0A
	.ascii "EEPROM first addr to write: 0x%05lX"
	.db 0x00
___str_32:
	.db 0x0A
	.ascii "EEPROM current 32kB segment: %01u"
	.db 0x00
___str_33:
	.db 0x0A
	.ascii "First Track/Sector to write: %02u/01"
	.db 0x00
___str_34:
	.db 0x0A
	.ascii "Contiguous sectors to write: %03u"
	.db 0x00
___str_35:
	.db 0x0A
	.ascii "Last Track/Sector to write: %02u"
	.db 0x00
___str_36:
	.ascii "/%02u"
	.db 0x00
___str_37:
	.db 0x0A
	.ascii "Last sector boundary fill: "
	.db 0x00
___str_38:
	.ascii "not needed"
	.db 0x00
___str_39:
	.ascii "yes"
	.db 0x00
___str_40:
	.db 0x0A
	.db 0x0A
	.ascii "Enter the target virtual disk [0-%d] >"
	.db 0x00
___str_41:
	.db 0x0A
	.ascii "Target virtual disk: %u"
	.db 0x00
___str_42:
	.db 0x0A
	.ascii "Nothing to do..."
	.db 0x00
___str_43:
	.db 0x0A
	.db 0x0A
	.ascii "Press W to write or A to abort [W/A] >"
	.db 0x00
___str_44:
	.db 0x0A
	.db 0x0A
	.ascii "* WARNING * ALL PREVIOUS DATA IN THE TARGET SECTORS WILL B"
	.ascii "E OVERWRITTEN!"
	.db 0x00
___str_45:
	.db 0x0A
	.db 0x0A
	.ascii "Are you sure [Y/N]? >"
	.db 0x00
___str_46:
	.db 0x0A
	.ascii "Write operation cancelled!"
	.db 0x00
___str_47:
	.db 0x0A
	.ascii "#%03u: writing... "
	.db 0x00
___str_48:
	.ascii " Disk: %01u"
	.db 0x00
___str_49:
	.ascii " - Track: %02u"
	.db 0x00
___str_50:
	.ascii " - Sector: %02u"
	.db 0x00
___str_51:
	.db 0x0A
	.ascii "* WRITE ABORTED! *"
	.db 0x00
___str_52:
	.db 0x0A
	.ascii "#%03u: verifying..."
	.db 0x00
___str_53:
	.db 0x0A
	.db 0x0A
	.ascii "* FOUND MISMATCH - VERIFY FAILED! *"
	.db 0x0A
	.db 0x00
___str_54:
	.ascii " -> OK"
	.db 0x00
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
