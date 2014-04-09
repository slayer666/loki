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
	
	File: 
	Description:
*/
					
#define ASM_FILE 1
#include <multiboot.h>

.set MBOOT_ALIGN, 1<<0
.set MBOOT_MEMINFO, 1<<1
.set MBOOT_FLAGS, MBOOT_ALIGN | MBOOT_MEMINFO
.set MBOOT_MAGIC, 0x1BADB002
.set MBOOT_CHECKSUM, -(MBOOT_MAGIC + MBOOT_FLAGS)

.section .multiboot
.align 4
.long MBOOT_MAGIC
.long MBOOT_FLAGS
.long MBOOT_CHECKSUM

.section .bootstrap_stack, "aw", @nobits

stack_bottom:
.skip 16384 # 16 KiB

stack_top:

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
	pushl $0
	popf
	pushl %ebx
	pushl %eax
	
	call kernel_main
	cli
	hlt
	
.Lhang:
	jmp .Lhang
	
.size _start, . - _start
