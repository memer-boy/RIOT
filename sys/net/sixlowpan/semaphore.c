#include <semaphore.h>
#include <mutex.h>

sem_t sem_init(int8_t value) {
    sem_t sem;
    sem.value = value;
    mutex_init(&sem.mutex);
    sem.locked = 0;
    return sem;
}

int sem_wait(sem_t *sem) {
    int res;
    if(--(sem->value) <= 0 && !sem->locked) {
        sem->locked = !(sem->locked);
        res = mutex_lock(&(sem->mutex));
        if (res < 0) {
            return res;
        }
    }
    
    return 0;
}

int sem_signal(sem_t *sem) {
    if (++(sem->value) > 0 && sem->locked) {
        sem->locked = !(sem->locked);
        mutex_unlock(&(sem->mutex),0);
    }
    
    return 0;
}
