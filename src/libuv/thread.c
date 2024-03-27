#include <pthread.h>
#include <stdio.h>

void* start(void* args)
{

}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, start, NULL);
    pthread_join(thread_id);
}