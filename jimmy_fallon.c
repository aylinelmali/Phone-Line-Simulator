#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t lock;
sem_t operators;
sem_t connected_lock;
int next_id;

//simulates a phonecall
void* phonecall(void* vargp){
	static int NUM_OPERATORS = 3;
	static int NUM_LINES = 5;
	static int connected = 0;
	sem_wait(&lock);
	next_id++;
	sem_post(&lock);
	int id = next_id;
	int connection = 0;
	printf("Thread %i is calling line\n", id);
	while(connection != 1){
		sem_wait(&connected_lock);
		if(connected != NUM_LINES){
			connected++;
			connection = 1;
			sem_post(&connected_lock);
		}
		else{
			sem_post(&connected_lock);
			printf("Thread %i has busy signal\n", id);
			sleep(1);
		}
	}
	printf("Thread %i has available line\n", id);
	sem_wait(&operators);
	printf("Thread %i is speaking to operator\n", id);
	sleep(1);
	printf("Thread %i has bought a ticket!\n", id);
	sem_post(&operators);
	sem_wait(&connected_lock);
	connected--;
	sem_post(&connected_lock);
	printf("Thread %i has hung up!\n", id);
}

//runs program, creates threads
int main(int argc, char *argv[]){
	next_id = 0;
	if(sem_init(&lock, 0, 1) == -1){
		perror("failed to initialize semaphore");
		exit(1);}
	if(sem_init(&operators, 0, 3) == -1){
		perror("failed to initialize semaphore");
		exit(1);}
	if(sem_init(&connected_lock, 0, 1) == -1){
		perror("failed to initialize semaphore");
		exit(1);}
	int num = atoi(argv[1]);
	pthread_t threads[num];
	for(int i = 0; i < num; i++){
		if(pthread_create(&threads[i], NULL, phonecall, NULL) != 0){
			perror("failed to create thread");
			exit(1);}
	} 
	for(int j = 0; j < num; j++){
		pthread_join(threads[j], NULL);
	}
	sem_destroy(&lock);
	sem_destroy(&operators);
	sem_destroy(&connected_lock);
	return 0;
}


