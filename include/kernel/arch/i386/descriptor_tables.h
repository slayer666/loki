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
	
	File: include/kernel/arch/i386/descriptor_tables.h
	Description: descriptor tables
*/ 

#include <stdint.h>

struct  gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__ ((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));
typedef struct gdt_ptr gdt_ptr_t;


struct idt_entry
{
   uint16_t base_lo;             
   uint16_t sel;                 
   uint8_t  always0;
   uint8_t  flags;
   uint16_t base_hi;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;


struct idt_ptr
{
   uint16_t limit;
   uint32_t base;  
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

void init_descriptor_tables();
