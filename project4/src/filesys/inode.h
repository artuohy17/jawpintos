#ifndef FILESYS_INODE_H
#define FILESYS_INODE_H

#include <stdbool.h>
#include "filesys/off_t.h"
#include "devices/block.h"
#include <list.h>
#include <inttypes.h>
#include "devices/block.h"
#include <debug.h>
#include "threads/synch.h"

struct bitmap;

#define MI_SIZE 124

struct inode_disk
{
  off_t length;                       /* File size in bytes. */
  unsigned magic;                     /* Magic number. */
  block_sector_t multi_index[MI_SIZE];    /* Multi-level block index */
  bool is_dir;                        /* Directory or file */
  block_sector_t parent_dir_sector;   /* Parent directory */
};

/* In-memory inode. */
struct inode
{
  struct list_elem elem;              /* Element in inode list. */
  block_sector_t sector;              /* Sector number of disk
					 location. */
  int open_cnt;                       /* Number of openers. */
  bool removed;                       /* True if deleted, false
					 otherwise. */
  int deny_write_cnt;                 /* 0: writes ok, >0: deny writes. */
  struct inode_disk data;             /* Inode content. */
  struct lock extension_lock;         /* lock for extension of file */
};


void inode_init (void);
bool inode_create (block_sector_t, off_t);
struct inode *inode_open (block_sector_t);
struct inode *inode_reopen (struct inode *);
block_sector_t inode_get_inumber (const struct inode *);
void inode_close (struct inode *);
void inode_remove (struct inode *);
off_t inode_read_at (struct inode *, void *, off_t size, off_t offset);
off_t inode_write_at (struct inode *, const void *, off_t size, off_t offset);
void inode_deny_write (struct inode *);
void inode_allow_write (struct inode *);
off_t inode_length (const struct inode *);
block_sector_t get_sector (struct inode_disk *disk_inode, 
			   block_sector_t block_index);
void put_sector (struct inode_disk *disk_inode,
		 block_sector_t block_index, 
		 block_sector_t sector);

bool inode_is_dir (const struct inode *);
void inode_set_is_dir (struct inode *);
block_sector_t inode_get_parent_dir_sector (struct inode *inode);
void inode_set_parent_dir_sector (struct inode *inode, block_sector_t parent_dir_sector);

#endif /* filesys/inode.h */
