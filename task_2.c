#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void * print(void * arg){
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	int i = 0;
	while (1){
		printf("Child thread. Iteration %d.\n", i);
		sleep(1);
		i++;
	}
}

int main(int argc, char **argv){
	if (argc == 1){
		printf("Попытка запуска программы без аргументов...\n");
		printf("Для корректной работы программы нужно задать единственный целочисленный аргумент.\n");
	}else{
		pthread_t thread;
		if (pthread_create(&thread, NULL, &print, NULL) != 0) {
				fprintf(stderr, "Error (thread1)\n");
				return 1;
		}
		sleep(atoi(argv[1]));
		pthread_cancel(thread);
		void *result;
		if (!pthread_equal(pthread_self(), thread))
				pthread_join(thread, &result) ;
		if (result == PTHREAD_CANCELED)
			fprintf(stderr, "Canceled\n");
		else fprintf(stderr, "Succesful exit\n");
	}
	return 0;
}
