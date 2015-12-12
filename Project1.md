# Priority Scheduling #
  1. When a thread is added to the ready list that has a higher priority than the currently running thread, the current thread should immediately yield the processor to the new thread. DONE
  1. When threads are waiting for a lock, semaphore, or condition variable, the highest priority waiting thread should be awakened first. DONE, THOUGH no test captures.
  1. A thread may raise or lower its own priority at any time, but lowering its priority such that it no longer has the highest priority must cause it to immediately yield the CPU.
  1. Implement priority donation: H to "donate" its priority to L while L is holding the lock, then recall the donation once L releases (and thus H acquires) the lock.
  1. Be sure to handle multiple donations, in which multiple priorities are donated to a single thread. You must also handle nested donation: if H is waiting on a lock that M holds and M is waiting on a lock that L holds, then both M and L should be boosted to H's priority. If necessary, you may impose a reasonable limit on depth of nested priority donation, such as 8 levels.
  1. You must implement priority donation for locks. You need not implement priority donation for the other Pintos synchronization constructs. You do need to implement priority scheduling in all cases.
  1. Implement thread\_set\_priority: Sets the current thread's priority to new\_priority. If the current thread no longer has the highest priority, yields.
  1. Implement thread\_get\_priority: Returns the current thread's priority. In the presence of priority donation, returns the higher (donated) priority.
  * You need not provide any interface to allow a thread to directly modify other threads' priorities.

  * **priority queue**: list.c/h has sorting and insert-in-order functions, so it can be used as a priority queue, but it is not as efficient as a heap.

# QUESTIONS #
  1. timer\_interrupt correct place to handle waiting thread while loop?
> > - What's too big?
  1. does interrupt handler run to completion?
  1. priority queue implementation available?
  1. thread\_block/unblock() vs semaphore
> > - why are synchronization primitives preferred?

# ABOUT SEMAPHORES #
  * sema\_down pushes the calling thread to the waiting threads list and thread\_blocks it.
  * sema\_up pops the calling thread from the waiting threads list and thread\_unblocks it.
  * thread\_unblock, instead of resuming right to the unblocked process, pushes it into the ready queue, just like thread\_yield is doing.
    * I called thread\_yield after sema\_up to push the thread into the ready queue; I'm guessing this was redundant.
    * This may mean that using thread\_block/unblock() is the same as using semaphores, it's just implemented at a higher level.
    * sema\_up()ing doesn't resume right into the corresponding thread. I guess the scheduler just picks it up after it's been pushed into the ready list.

# PROJECT BUGS #
  1. priority scheduling: is the problem because we are using the same _elem_ element for both semaphore waiter list and ready list?
  1. For Nested Donation, we might want to add a list of locks that a thread is waiting on to the thread struct.
  1. Changes made at 7:50pm 04/12/10: priority calculation at thread initialization, priority recalculation every 4 clock ticks.

# DESIGNDOC #
  1. Alarm Clock
    * We are locking(synchronizing) insertion into wait\_semas list. Should we be locking pop from wait\_semas as well? But pop is called within the timer interrupt.