/*
 loki 0.01
 Copyright (C) 2014 Wojciech Ró¿owski

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
	
	File: kernel/arch/i386/string.c
	Description: string functtions like itoa, memset, memcpy
*/ 

#include <kernel/arch.h>

void
itoa (char *buf, int base, int d)
{
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

 
	if (base == 'd' && d < 0)
    {
		*p++ = '-';
		buf++;
		ud = -d;
    }
	else if (base == 'x')
	{
		divisor = 16;
	}

	do
    {
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
	while (ud /= divisor);

	*p = 0;
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2)
    {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
    }
}