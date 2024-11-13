#ifndef __LOCK_H
#define __LOCK_H

typedef struct spinlock {
  int locked;
} spinlock_t;

void spinlock_acquire(spinlock_t *lock);
void spinlock_release(spinlock_t *lock);

#endif // __LOCK_H