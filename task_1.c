#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int *mas;

void * findNumber(void * arg) { 
	 int value = *(int*) arg;
     sleep(value);
     srand(time(NULL));
     int r = rand() % 10 + 1;
     mas[value] = r;
     sleep(r);
}

void* print(void* arg) {
	int value = *(int*) arg;
	int i;
	while (mas[value - 1] == 0){
		for(i = 0; i < value; i++){
			printf("%d ", mas[i]);
		}
		printf("\n");
		sleep(1);
	}
	for(i = 0; i < value; i++){
			printf("%d ", mas[i]);
		}
		printf("\n");
		pthread_exit(NULL);
}


int main(int argc, char **argv){
	pthread_t *pt;
	if (argc == 1){
		printf("Попытка запуска программы без аргументов...\n");
		printf("Для корректной работы программы нужно задать единственный целочисленный аргумент.\n");
	}else{
		int number = atoi(argv[1]);
		mas = malloc (sizeof(int) * number);
		pt = malloc (sizeof(pthread_t) * number);


		pthread_attr_t attr;
		pthread_t thr;
		pthread_attr_init (&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_create(&thr, &attr, &print, &number);
		pthread_attr_destroy (&attr);

		int i;
		for (i = 0; i < number; ++i){
			if (pthread_create(&pt[i], NULL, &findNumber, &i) != 0) {
				fprintf(stderr, "Error (thread)\n");
				return 1;
			}	
		}
		for(i = 0; i < number; ++i){
			if (pthread_join(pt[i], NULL) == 0) {
				printf("Thread %d finished sucessfully.\n", i);		
			}
		}

	}
	free(mas);
	free(pt);
	return 0;
}
