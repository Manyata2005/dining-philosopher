#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readers = 0;
sem_t mutex, rw;

void* reader(void* arg) {
    int id = *(int*)arg;
    sem_wait(&mutex);
    readers++;
    if (readers == 1) sem_wait(&rw);  
    sem_post(&mutex);
    
    printf("Reader %d reading...\n", id);
    sleep(1);
    
    sem_wait(&mutex);
    readers--;
    if (readers == 0) sem_post(&rw);  
    sem_post(&mutex);
    printf("Reader %d done\n", id);
}

void* writer(void* arg) {
    int id = *(int*)arg;
    sem_wait(&rw);
    printf("Writer %d writing...\n", id);
    sleep(2);
    sem_post(&rw);
    printf("Writer %d done\n", id);
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&rw, 0, 1);
    
    pthread_t r1, r2, r3, w1, w2;
    int ids[] = {1,2,3,1,2};
    
    pthread_create(&r1, NULL, reader, &ids[0]);
    pthread_create(&r2, NULL, reader, &ids[1]);
    pthread_create(&w1, NULL, writer, &ids[3]);
    pthread_create(&r3, NULL, reader, &ids[2]);
    pthread_create(&w2, NULL, writer, &ids[4]);
    
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&rw);
    return 0;
}