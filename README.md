# Newfangled-Operating-System-over-seL4-Microkernel

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

For more details regarding the design decisions in the project please access the project Report provided above.
