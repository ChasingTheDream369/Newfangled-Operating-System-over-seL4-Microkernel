## Newfangled-Operating-System-over-seL4-Microkernel

<!-- Header Section -->
<p align="center">
  <img src="os_logo.png" alt="Operating System Logo" width="200">
</p>

# Newfangled Operating System over seL4 Microkernel

Welcome to the **Newfangled Operating System (SOS)** – a cutting-edge operating system built on the reliable seL4 Microkernel.

<p align="center">
  <a href="#features">Summary</a> •
  <a href="#features">Features</a> •
  <a href="#system-calls">System Calls</a> •
  <a href="#virtual-memory">Virtual Memory</a> •
  <a href="#process-management">Process Management</a> •
  <a href="#get-started">Get Started</a>
</p>

## Summary

• Created an operating system over the world’s most secure and completely formally verified microkernel seL4 with Formulating
a completely threaded execution model for the Operating system encapsulated in servers. Started the process by creating a
separate File server, Process management server, and one thread completely dedicated to handling interrupts.

• Made sure that each user thread has a private endpoint with which it communicates using its own thread and used two con-
currency handling locks including the locks for Cspace, ut allocator, and frame table while other synchronization requirements
were handled implicitly by the servers.

• All the User threads used endpoints to invoke system calls and had their own endpoint and kernel thread leading to concurrent
system calls and parallely we saved the reply objects in a structure concurrently trying to reply later on for both file and
process management.

• On top of it we created a timer device driver and did the file descriptor allocation using a bitmap. Created a separate Serial
interface and file server. Created a 4-level page table using virtual addresses as indices and enforced read-only permissions.
Further furnished with creating demand paging, VM fault handling, and also data transfer between different address spaces.
For dealing with elf loading we read the elf header and created a procedure to find the vsyscall section and created specific
states, and a formal pid allocator for newly created processes. We tried not to replicate our PIDs but made sure to reuse
thread resources under reply objects and also made sure that all long blocking procedures get blocked inside the process
management loop so that the processes can prematurely come out of blocking and further used an explicitly managed device
queue for the same.

• Overall received a 99% in the bench marking results.

<!-- Features Section -->
## ✨ Features

SOS is designed to provide exceptional performance and advanced capabilities, including:

- 🚀 **Concurrent Syscall Management**: Efficiently handles concurrent system calls, ensuring smooth multitasking.
- 🌐 **Device Drivers**: Includes a Timer Device for precise time tracking and callback scheduling.
- 🧠 **Virtual Memory**: Implements demand paging and robust VM fault handling for optimal memory management.
- 🔄 **Process Management**: Manages processes with ease, offering secure thread creation and termination.
- 📡 **Asynchronous File Systems**: Supports UNIX-style file operations with asynchronous NFS calls for high performance.

<p align="center">
  <img src="feature_icons.png" alt="Feature Icons" width="400">
</p>

<!-- System Calls Section -->
## 📞 System Calls

SOS simplifies interaction with the kernel through well-defined system call numbers:

| **Syscall Number** | **Syscall Name**     |
|--------------------|-----------------------|
| NR openat          | sos_sys_open          |
| NR close           | sos_sys_close         |
| NR read            | sos_sys_read          |
| NR write           | sos_sys_write         |
| ...                | ...                   |

Explore the full list of system calls in our [System Calls Documentation](system_calls.md).

<!-- Virtual Memory Section -->
## 💾 Virtual Memory

### Page Table Structure

Our page table structure closely resembles the hardware page tables on the ARMv8-A architecture. It features 4 levels of tables, each containing 512 entries. Each entry keeps track of memory management structures, ensuring efficient memory access.

<p align="center">
  <img src="page_table.png" alt="Page Table Structure" width="500">
</p>

### Modifications to the Frame Table Structure

We've extended the frame entry table structure to include fields like `no evict`, `used`, `dirty`, and `user page cap`. These additions enhance memory management and demand paging.

### Demand Paging

SOS efficiently manages pagefiles and implements the second-chance clock replacement algorithm. This reduces write operations, enhancing system performance.

### Memory Layout and VM Fault Handling

Our memory layout follows a straightforward pattern with distinct segments. VM fault handling is robust, guaranteeing system reliability.

<!-- Process Management Section -->
## 🔄 Process Management

### Process ID Allocation

Process IDs are simply the index of a given process in the process management static array. This straightforward allocation method ensures efficient and unique process identification.

### Process Creation

The Process Management Server (PM server) oversees process creation, efficiently allocating resources for SOS threads and user threads.

<p align="center">
  <img src="process_creation.png" alt="Process Creation" width="400">
</p>

### Blocking and Waiting for Access to Devices

SOS efficiently handles thread blocking and waiting for device access. Threads requesting access to a device are placed in a queue and suspended, ensuring smooth execution.

### Killing a Process

SOS provides a robust process termination mechanism. When a process is killed, its resources are cleaned up, and the PM server efficiently manages the termination process.

<!-- Get Started Section -->
## 🚀 Get Started

Ready to dive into SOS? Follow these steps to get started:

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/your-username/Newfangled-Operating-System-over-seL4-Microkernel.git
   ```
2. **Build and Install**:

```
cd Newfangled-Operating-System-over-seL4-Microkernel
make build
make install
```

3. **Run SOS**:

    ```
    make run
    ```

Congratulations! You're now running SOS on your system.

For detailed documentation and usage instructions, refer to our Documentation.
<!-- License Section -->
License

This project is licensed under the MIT License - see the LICENSE.md file for details.
<p align="center">
  <img src="sos_logo.png" alt="SOS Logo" width="200">
</p>

Explore the future of operating systems with SOS today!

Your feedback and contributions are always welcome. Feel free to report issues or submit pull requests to enhance SOS further.

For more details regarding the design decisions in the project please access the project Report provided above.
