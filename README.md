Welcome!

Recently Loki is a stub for an operating system based on microkernel,intended to use on many platforms and compatible with UNiX.
It's my second operating system project. My first big os project was called CoryOS. It was commited to Google Science Fair,
and it is avalible on Google Code platform. Loki is a remake of CoryOS using gas instead of nasm, and also it has got isolated
arch dependent parts from the arch independent parts.

Why it's called LOKI?
cause it's       Little, Open, microKernel based, and Inter-platform

To do list:
-improve tty driver

-add more string functions

-try to improve head.s using the multiboot.h

-add GDT and IDT (port it from CoryOS)

-add IRQ (port it from CoryOS)

-add ISR and clock interface (port it from CoryOS)

-add memory paging (port it from CoryOS)

-write memory manager (port it from CoryOS)

-improve Makefile

-add TSS and multitasking (port it from CoryOS)

-write syscall interface

-write sys_* syscalls and do_sys_* functions

-add library for developing servers and drivers using the sys_* syscalls

-write multiboot modules loader

-make kernel execve for running servers and drivers

-create fs server

-create other servers and drivers ;-)

-port newlib

-and more...


If you are interested in joining to Loki project, email me: wojciech.rozowski@gmail.com ;-)


Greetings
Wojciech R�owski