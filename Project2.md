# Implementing children and parent waits #

  * parent: a list of children threads: exec, cleanup on parent exit. use in wait.
  * parent: a list of threads waited on: wait, cleanup on parent exit. use in wait.
  * a global list of exited threads: populate on thread exit. cleanup children on parent exit. lock access when populating and cleaning up.



# Section 04/23/10 #

**Read through DESIGNDOC before implementing** Can use malloc, if returns NULL, kill the user program, do not panic
**synchronizations in case of thread block/unblock.**

**Project 3 & 4 will build on Project 2.**

**example
  1. shell parses user input
  1. shell calls fork() and execve("cp", argv, env)
  1. cp uses file system interface to copy files
  1. cp may print messages to stdout
  1. cp exits**

  * These interactions require system calls

**Syscall handler
  1. syscalls provide the interface btw a user process and the OS
  1. Popular syscalls: open, read, write, wait, exec, exit...**

**User programs in Pintos
  * threads/init.c
  1. main() => run\_actions(Argv) after booting
  1. run\_actions => run\_task(argv)
    * the task to run is argv[1](1.md)
  1. run\_task => process\_wait(process\_Execute(task))**

  * serprog/process.c
  1. process\_execute creates a thread that runs start\_process(filename...) => load(filename...)
  1. load sets up the stack, data, and code, as well as the start address

**Project 2 requirements
  1. passing command-line arguments to programs
  1. safe memory access (bad pointer derefs)
  1. a set of system calls
    * Long list, in section 3.3.4 of the Pintos docs
  1. process termination messages
  1. denying writes to files in use as executables**

**Argument passing
  1. before a user program starts executing, ther kernel must push the functions arguments onto the stack.
  1. This involves breaking the command-line input into individual words.
  1. Implement the string parsing however you like
    * docs say to extend process\_execute() to do this, but you may place the logic...**

**Safe memory access
  1. The kernel will often access memory through user-provided pointers
  1. These pointers can be problematic:
    * null pointers, pointers to unmapped user virtual memory, or pointers to kernel addresses
    * If a user process passes these to the kernel, you must kill the process ...**

  * Two approaches
    1. verify every user pointer before dereference
      * is it in the user's address space, i.e. below PHYS\_BASE? (look at is\_user\_vaddr)
      * mapped? (look at pagedir\_get\_page())
      * these checks apply to buffers/strings as well

  1. modify fault handler in userprog/exception.c
    * only check that a user pointer is below PHYS\_BASE
    * Invalid pointers will trigger a page fault
    * Better performance, takes advantage of hardware MMU
    * See 3.1.5 [User Memory](Accessing.md) for more details

**USE SYNCHRONIZATION!**

**Suggested initial strategy
  1. make a disk and add a few programs (like args**-)