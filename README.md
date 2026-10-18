# OS for seL4

An experimental operating system built on the seL4 microkernel, focused on concurrent execution, process management, virtual memory, and low-level systems programming.

## Overview

The system uses a threaded execution model with dedicated servers for file and process management, alongside a separate interrupt-handling thread. Its architecture explores how operating-system services can be implemented on top of a capability-based microkernel.

## Key Components

- **Process Management:** Process creation, lifecycle management, resource allocation, and process identifier handling.
- **File Management:** File-system services and file operations exposed through dedicated server components.
- **Concurrent Execution:** Threaded service execution and concurrent system-call handling through seL4 endpoints.
- **Virtual Memory:** Address-space management, page tables, virtual-memory fault handling, and demand paging.
- **Executable Loading:** ELF loading and process initialisation.
- **Interrupt Handling:** Timer-device support and interrupt processing through a dedicated handling thread.

## Technical Focus

The project explores microkernel-based operating-system design, inter-process communication, memory management, concurrency, and the implementation of core system services.

## Technology

- seL4 microkernel
- C
- Low-level memory and process management
- Microkernel inter-process communication and capability-based resource access
