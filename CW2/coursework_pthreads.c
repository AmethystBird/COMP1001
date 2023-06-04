/*
------------------COMP1001 COURSEWORK ------------------------------------------------------------------
------------------COMPUTER SYSTEMS MODULE-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/

//THIS CODE RUNS ON LINUX ONLY

//compile with gcc coursework_pthreads.c -o exec -lpthread
//run with ./exec

#include <stdio.h>      //for printf
#include <stdlib.h>
#include <pthread.h>    //for pthreads
#include <math.h>       //for fabs()
#include <time.h>	/* for clock_gettime */
#include <stdint.h>	/* for uint64 definition */

#define TIMES 1
#define BILLION 1000000000L
#define EPSILON 0.01

#define P 4096 //input size
double A2[P][P], test4[P][P], u1[P], v1[P], u2[P], v2[P] ;

void initialization();
//unsigned short int gemver_default();
void * gemver_default(void* thread_num);
unsigned short int Compare_Gemver();
inline unsigned short int equal(double const a, double const b);

//int currentThread = 0;
//int lastThread = 3;

int main() {

   unsigned short int output;
   int t;
   struct timespec start, end; //timers
   uint64_t diff;


	time_t start1, end1;
	struct timeval start2, end2;

	long int thread_num; //will be used to pass the amount of threads being utilised later, between methods
	pthread_t thread_handles[4]; //an array of 4 threads

	//initialize the arrays
	initialization();


	/* measure monotonic time */
      clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */


	//The following for loop is there to make sure we get a good execution time measurement. We must run this several times because this routine runs very fast 
	//The execution time needs to be at least 10 seconds in order to have a good measurement (why?) 
	for (t = 0; t < TIMES; t++) {
		
           //output=gemver_default(); //REMOVE THIS?
		   for (thread_num = 0; thread_num < 4; thread_num++)
		   {
			   pthread_create(&thread_handles[thread_num], NULL, gemver_default, (void*) thread_num); //creates and runs the thread and sends it as input to gemver_default() [CREATE NEW ROUTINE]
		   }
		   for (thread_num = 0; thread_num < 4; thread_num++)
		   {
			   pthread_join(thread_handles[thread_num], NULL); //waits until the thread has finished executing
		   }


	}


       clock_gettime(CLOCK_MONOTONIC, &end);	/* mark the end time */

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
        printf("elapsed time = %llu mseconds\n", (long long unsigned int) diff/1000000);

	
	//this code is for testing
        if (Compare_Gemver() == 0) //this function checks whether the result is correct or not
		printf("\n\n\r -----  output is correct -----\n\r");
        else
		printf("\n\n\r ----- output is INcorrect -----\n\r");

       
return 0;
}


void initialization() {

	double e = 0.1234, p = 0.7264, r = 0.11;

	//gemver
	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++) {
			A2[i][j] = 0.0;
			test4[i][j] = 0.0;
		}

	for (int j = 0; j < P; j++) {
		u1[j] = e + (j % 9);
		v1[j] = e - (j % 9);
		u2[j] = p + (j % 9);
		v2[j] = p - (j % 9);
	}

	
}


//------------ THIS IS THE ROUTINE THAT YOU WILL PARALLELIZE -------------------
//unsigned short int gemver_default() {
void * gemver_default(void *thread_num) {

    //this is the loop to parallelize
	
	long my_thread_num = (long) thread_num;
   	int i, j;
	
   	int local = P/4; //divides the elements of the array
	
   	int initialElement = my_thread_num * local; //finds the first element to modify in one thread
   	int lastElement = initialElement + local - 1; //finds the last element to modify in one thread

	for (i = initialElement; i <= lastElement; i++)
		for (j = 0; j < P; j++)
			A2[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
}



unsigned short int Compare_Gemver() {

	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++)
			test4[i][j] += u1[i] * v1[j] + u2[i] * v2[j];

	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++)
			if (equal(A2[i][j], test4[i][j]) == 1)
				return -1;

	return 0;
}






unsigned short int equal(double const a, double const b) {
	double temp = a - b;
	//printf("\n %f  %f", a, b);
	if (fabs(temp) < EPSILON)
		return 0; //success
	else
		return 1;
}

