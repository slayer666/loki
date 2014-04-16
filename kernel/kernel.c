/*
    loki 0.01
    Copyright (C) 2014 Wojciech R�owski

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
	
	File: kernel/kernel.c
	Description: main kernel file
*/ 

#include <multiboot.h>
#include <kernel/arch.h>
#include <kernel/kprintf.h>
 
void
kernel_main (unsigned long magic, unsigned long addr)
{	
	multiboot_info_t *mbi;
	init_descriptor_tables();
    cls ();

    /* Am I booted by a Multiboot-compliant boot loader? */
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		kprintf ("Invalid magic number: 0x%x\n", (unsigned) magic);
		return;
	}
 
    /* Set MBI to the address of the Multiboot information structure. */
    mbi = (multiboot_info_t *) addr;
 
    /* Print out the flags. */
    kprintf ("flags = 0x%x\n", (unsigned) mbi->flags);
 
    /* Are mem_* valid? */
    if (CHECK_FLAG (mbi->flags, 0))
    {
		kprintf ("mem_lower = %uKB, mem_upper = %uKB\n",(unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);
    }
 
    /* Is boot_device valid? */
    if (CHECK_FLAG (mbi->flags, 1))
	{
		kprintf ("boot_device = 0x%x\n", (unsigned) mbi->boot_device);
	}
 
    /* Is the command line passed? */
    if (CHECK_FLAG (mbi->flags, 2))
    {
		kprintf ("cmdline = %s\n", (char *) mbi->cmdline);
	}
 
    /* Are mods_* valid? */
    if (CHECK_FLAG (mbi->flags, 3))
	{
		multiboot_module_t *mod;
		int i;
 
		kprintf ("mods_count = %d, mods_addr = 0x%x\n",
		(int) mbi->mods_count, (int) mbi->mods_addr);
		for (i = 0, mod = (multiboot_module_t *) mbi->mods_addr; i < mbi->mods_count; i++, mod++)
		kprintf (" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
			(unsigned) mod->mod_start,
			(unsigned) mod->mod_end,
			(char *) mod->cmdline);
	}
 
	/* Bits 4 and 5 are mutually exclusive! */
	if (CHECK_FLAG (mbi->flags, 4) && CHECK_FLAG (mbi->flags, 5))
	{
		kprintf ("Both bits 4 and 5 are set.\n");
		return;
	}
 
	/* Is the symbol table of a.out valid? */
	if (CHECK_FLAG (mbi->flags, 4))
	{
		multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);
		kprintf ("multiboot_aout_symbol_table: tabsize = 0x%0x, "
			"strsize = 0x%x, addr = 0x%x\n",
			(unsigned) multiboot_aout_sym->tabsize,
			(unsigned) multiboot_aout_sym->strsize,
			(unsigned) multiboot_aout_sym->addr);
	}
 
	/* Is the section header table of ELF valid? */
	if (CHECK_FLAG (mbi->flags, 5))
	{
		multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);
 
		kprintf ("multiboot_elf_sec: num = %u, size = 0x%x,"
			" addr = 0x%x, shndx = 0x%x\n",
			(unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size,
			(unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
 }
 
	/* Are mmap_* valid? */
	if (CHECK_FLAG (mbi->flags, 6))
	{
		multiboot_memory_map_t *mmap;
 
		kprintf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
			(unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
		for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
			(unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
			mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
			+ mmap->size + sizeof (mmap->size)))
			{
				kprintf (" size = 0x%x, base_addr = 0x%x%x,"
					" length = 0x%x%x, type = 0x%x\n",
					(unsigned) mmap->size,
					mmap->addr >> 32,
					mmap->addr & 0xffffffff,
					mmap->len >> 32,
					mmap->len & 0xffffffff,
					(unsigned) mmap->type);
			}
	}
 }