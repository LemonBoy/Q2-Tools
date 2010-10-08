//---------------------------------------------------------------------------
// NEOPOP : Emulator as in Dreamland
//
// Copyright (c) 2001-2002 by neopop_uk
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version. See also the license.txt file for
//	additional informations.
//---------------------------------------------------------------------------

/*
//---------------------------------------------------------------------------
//=========================================================================

	TLCS900h_registers_mapCodeB3.h

//=========================================================================
//---------------------------------------------------------------------------

  History of changes:
  ===================

20 JUL 2002 - neopop_uk
=======================================
- Cleaned and tidied up for the source release

//---------------------------------------------------------------------------
*/

	((_u8*)&gprBank[0][0]) + 0,((_u8*)&gprBank[0][0]) + 1,			//BANK 0
		((_u8*)&gprBank[0][0]) + 2, ((_u8*)&gprBank[0][0]) + 3,
	((_u8*)&gprBank[0][1]) + 0,((_u8*)&gprBank[0][1]) + 1,
		((_u8*)&gprBank[0][1]) + 2, ((_u8*)&gprBank[0][1]) + 3,
	((_u8*)&gprBank[0][2]) + 0,((_u8*)&gprBank[0][2]) + 1,
		((_u8*)&gprBank[0][2]) + 2, ((_u8*)&gprBank[0][2]) + 3,
	((_u8*)&gprBank[0][3]) + 0,((_u8*)&gprBank[0][3]) + 1,
		((_u8*)&gprBank[0][3]) + 2, ((_u8*)&gprBank[0][3]) + 3,

	((_u8*)&gprBank[1][0]) + 0,((_u8*)&gprBank[1][0]) + 1,			//BANK 1
		((_u8*)&gprBank[1][0]) + 2, ((_u8*)&gprBank[1][0]) + 3,
	((_u8*)&gprBank[1][1]) + 0,((_u8*)&gprBank[1][1]) + 1,
		((_u8*)&gprBank[1][1]) + 2, ((_u8*)&gprBank[1][1]) + 3,
	((_u8*)&gprBank[1][2]) + 0,((_u8*)&gprBank[1][2]) + 1,
		((_u8*)&gprBank[1][2]) + 2, ((_u8*)&gprBank[1][2]) + 3,
	((_u8*)&gprBank[1][3]) + 0,((_u8*)&gprBank[1][3]) + 1,
		((_u8*)&gprBank[1][3]) + 2, ((_u8*)&gprBank[1][3]) + 3,

	((_u8*)&gprBank[2][0]) + 0,((_u8*)&gprBank[2][0]) + 1,			//BANK 2
		((_u8*)&gprBank[2][0]) + 2, ((_u8*)&gprBank[2][0]) + 3,
	((_u8*)&gprBank[2][1]) + 0,((_u8*)&gprBank[2][1]) + 1,
		((_u8*)&gprBank[2][1]) + 2, ((_u8*)&gprBank[2][1]) + 3,
	((_u8*)&gprBank[2][2]) + 0,((_u8*)&gprBank[2][2]) + 1,
		((_u8*)&gprBank[2][2]) + 2, ((_u8*)&gprBank[2][2]) + 3,
	((_u8*)&gprBank[2][3]) + 0,((_u8*)&gprBank[2][3]) + 1,
		((_u8*)&gprBank[2][3]) + 2, ((_u8*)&gprBank[2][3]) + 3,

	((_u8*)&gprBank[3][0]) + 0,((_u8*)&gprBank[3][0]) + 1,			//BANK 3
		((_u8*)&gprBank[3][0]) + 2, ((_u8*)&gprBank[3][0]) + 3,
	((_u8*)&gprBank[3][1]) + 0,((_u8*)&gprBank[3][1]) + 1,
		((_u8*)&gprBank[3][1]) + 2, ((_u8*)&gprBank[3][1]) + 3,
	((_u8*)&gprBank[3][2]) + 0,((_u8*)&gprBank[3][2]) + 1,
		((_u8*)&gprBank[3][2]) + 2, ((_u8*)&gprBank[3][2]) + 3,
	((_u8*)&gprBank[3][3]) + 0,((_u8*)&gprBank[3][3]) + 1,
		((_u8*)&gprBank[3][3]) + 2, ((_u8*)&gprBank[3][3]) + 3,

	(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,
	(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,
	(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,
	(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,
	(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,(_u8*)&rErr,

	//Previous Bank
	((_u8*)&gprBank[2][0]) + 0,((_u8*)&gprBank[2][0]) + 1,
		((_u8*)&gprBank[2][0]) + 2, ((_u8*)&gprBank[2][0]) + 3,
	((_u8*)&gprBank[2][1]) + 0,((_u8*)&gprBank[2][1]) + 1,
		((_u8*)&gprBank[2][1]) + 2, ((_u8*)&gprBank[2][1]) + 3,
	((_u8*)&gprBank[2][2]) + 0,((_u8*)&gprBank[2][2]) + 1,
		((_u8*)&gprBank[2][2]) + 2, ((_u8*)&gprBank[2][2]) + 3,
	((_u8*)&gprBank[2][3]) + 0,((_u8*)&gprBank[2][3]) + 1,
		((_u8*)&gprBank[2][3]) + 2, ((_u8*)&gprBank[2][3]) + 3,

	//Current Bank
	((_u8*)&gprBank[3][0]) + 0,((_u8*)&gprBank[3][0]) + 1,
		((_u8*)&gprBank[3][0]) + 2, ((_u8*)&gprBank[3][0]) + 3,
	((_u8*)&gprBank[3][1]) + 0,((_u8*)&gprBank[3][1]) + 1,
		((_u8*)&gprBank[3][1]) + 2, ((_u8*)&gprBank[3][1]) + 3,
	((_u8*)&gprBank[3][2]) + 0,((_u8*)&gprBank[3][2]) + 1,
		((_u8*)&gprBank[3][2]) + 2, ((_u8*)&gprBank[3][2]) + 3,
	((_u8*)&gprBank[3][3]) + 0,((_u8*)&gprBank[3][3]) + 1,
		((_u8*)&gprBank[3][3]) + 2, ((_u8*)&gprBank[3][3]) + 3,
	
	((_u8*)&gpr[0]) + 0, ((_u8*)&gpr[0]) + 1, 
		((_u8*)&gpr[0]) + 2, ((_u8*)&gpr[0]) + 3,
	((_u8*)&gpr[1]) + 0, ((_u8*)&gpr[1]) + 1, 
		((_u8*)&gpr[1]) + 2, ((_u8*)&gpr[1]) + 3,
	((_u8*)&gpr[2]) + 0, ((_u8*)&gpr[2]) + 1, 
		((_u8*)&gpr[2]) + 2, ((_u8*)&gpr[2]) + 3,
	((_u8*)&gpr[3]) + 0, ((_u8*)&gpr[3]) + 1,
		((_u8*)&gpr[3]) + 2, ((_u8*)&gpr[3]) + 3

//=============================================================================
