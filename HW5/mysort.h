#include <stdbool.h>
#include <pthread.h>

#define MAX_MEMMORY 4000000000
#define BUFFER_SIZE 100 // one line
#define ERROR -1

typedef struct ttask {
    void *(*thread_task)(void *);
    void *args;
    struct ttask* next;
} ttasks_t;

typedef struct {
    bool is_close; 
    int num_threads;
    int num_busy; // busy thread
    pthread_t check_t;
    pthread_mutex_t busy_lock;  
    pthread_t* ids_t;
    pthread_cond_t ready; // condition variable
    pthread_mutex_t lock;  // lock

    ttasks_t* head;
    ttasks_t* tail;

} tpools_t;