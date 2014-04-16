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
	
	File: kernel/kprintf.c
	Description: freestanding printf function
*/ 
#include <kernel/arch.h>
#include <kernel/string.h>  
void
kprintf (const char *format, ...)
{
	char **arg = (char **) &format;
	int c;
	char buf[20];
  
	arg++;
  
	while ((c = *format++) != 0)
	{
		if (c != '%')
		{
			putchar (c);
		}
		else
		{
			char *p;
  
			c = *format++;
			switch (c)
			{
				case 'd':
				case 'u':
				case 'x':
					itoa (buf, c, *((int *) arg++));
					p = buf;
					goto string;
				break;
				case 's':
					p = *arg++;
					if (! p)
					{
						p = "(null)";
					}
				string:
					while (*p)
					{
						putchar (*p++);
					}
				break;
  
				default:
					putchar (*((int *) arg++));
					break;
			}
		}
	}
}