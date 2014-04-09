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
	
	File: include/kernel/arch/i386/screen.h
	Description: header for simple vga text-mode driver
*/ 
#ifndef _KERNEL_SCREEN_H
#define _KERNEL_SCREEN_H
#include <kernel/arch.h>
int xpos;
int ypos;
volatile unsigned char *video;
void cls (void);
void putchar (int c);
#endif