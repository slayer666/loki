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
	
	File: include/kernel/arch/i386/vga.h
	Description: header containing some useful defines for i386 vga text-mode driver
*/ 

#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H
 
#include <stdint.h>
 
#define COLUMNS                 80
#define LINES                   24
#define ATTRIBUTE               7
#define VIDEO                   0xB8000
 
#endif