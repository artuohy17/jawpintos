# Questions #
  * should we be implementing heaps (malloc) for user processes?
  * should we implement stack allocation during page\_fault handling?
  * one hash for each thread? can our suppl table and frame table be kernel memory (without being swapped at all).
  * can all page tables/frame tables be in kernel memory.
  * is kernel memory swappable? (is it pageable? seems like it is)
  * is 'frame table' a mapping of kpage to upage?
  * what are pde and pte? do we need to use/change 'pool' directly?
