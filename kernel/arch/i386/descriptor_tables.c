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
	
	File: kernel/arch/i386/descriptor_tables.c
	Description: descriptor tables
*/ 

#include <kernel/arch.h>

extern void gdt_flush(uint32_t);

static void init_gdt();
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[5]; //there are 5 segments and 5 entries for each one
gdt_ptr_t gdt_ptr;

void
init_descriptor_tables()
{
	init_gdt();
}

static void
init_gdt()
{
	
	gdt_ptr.limit = (sizeof(gdt_entry_t)*5)-1;
	gdt_ptr.base = (uint32_t)gdt_entries;

	//there are 5 segements: null(must be), and both code and data for user mode and kernel mode
	gdt_set_gate(0, 0, 0, 0, 0); //null segment
	gdt_set_gate(1,0,0xFFFFFFFF, 0x9A, 0xCF); //kernel code segment
	gdt_set_gate(2,0,0xFFFFFFFF, 0x92, 0xCF); //kernel data segment
	gdt_set_gate(3,0,0xFFFFFFFF, 0xFA, 0xCF); //user code segment
	gdt_set_gate(4,0,0xFFFFFFFF, 0xF2, 0xCF); //user data segment

	gdt_flush((uint32_t)&gdt_ptr);


}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
} 

