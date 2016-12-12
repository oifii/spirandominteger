/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// spirandominteger.cpp : Defines the entry point for the console application.
//
//ref.:
//http://en.wikipedia.org/wiki/Multiply-with-carry
//
#include "stdafx.h"

#include <ctime> //for random number initialization seed

#include <stdint.h>
 
#define cmwc_PHI 0x9e3779b9
 
static uint32_t cmwc_Q[4096], cmwc_c = 362436;
 
void init_rand_cmwc(uint32_t x)
{
	int i;
 
	cmwc_Q[0] = x;
	cmwc_Q[1] = x + cmwc_PHI;
	cmwc_Q[2] = x + cmwc_PHI + cmwc_PHI;
 
	for (i = 3; i < 4096; i++)
		cmwc_Q[i] = cmwc_Q[i - 3] ^ cmwc_Q[i - 2] ^ cmwc_PHI ^ i;
}
 
uint32_t rand_cmwc(void)
{
	static uint32_t cmwc_i = 4095;
	uint64_t t;
 
	cmwc_i = (cmwc_i + 1) & 4095;
	t = (18705ULL * cmwc_Q[cmwc_i]) + cmwc_c;
	cmwc_c = t >> 32;
	cmwc_Q[cmwc_i] = 0xfffffffe - t;
 
	return cmwc_Q[cmwc_i];
}



int _tmain(int argc, _TCHAR* argv[])
{
	init_rand_cmwc((unsigned)time(0));
	for(int ii=0; ii<100; ii++)
	{
		printf("%d\n",rand_cmwc()%11);
	}
	return 0;
}

