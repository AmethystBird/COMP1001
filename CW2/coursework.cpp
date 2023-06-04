#include "coursework.h"

//memory addresses for 3 float arrays
float* V1, * V2, * test;

void initialization() {

	//dynamic memory assignment for all arrays
	V1 = (float*)malloc(M * sizeof(float));
	V2 = (float*)malloc(M * sizeof(float));
	test = (float*)malloc(M * sizeof(float));

	//checks if the memory of all floats was assigned
	if (V1 == NULL || V2 == NULL || test == NULL)
	{
		printf("\nMemory was not allocated.\n");
	}
	//runs if memory was assigned
	else
	{
		printf("\nAll memory was allocated.\n");
		float e = 0.1234f, p = 0.7264f, r = 0.11f;
		int i, j;

		for (j = 0; j != M; j++) {
			V1[j] = (j % 17) + p;
			V2[j] = (j % 13) + e;
			test[j] = V1[j];
		}

		//free(V1), free(V2), free(test); //frees up memory that was being utilised by the float arrays
		printf("\nAll memory was freed.\n");
	}
}


unsigned short int default_routine() {
	int i,j;

	 for (j = 0; j < M; j++) {
		V1[j] = V1[j] + V2[j] + 2.12f;
	}


	return 2;
}

unsigned short int SSE() {

//WRITE YOUR CODE HERE
	__m128 num1, num2, num3, num4; //128bit ints

	num1 = _mm_set_ps(2.12f, 2.12f, 2.12f, 2.12f); //vectorised constant value

	int i;
	for (i = 0; i < (M/4)*4; i+=4)
	{
		/*num2 = _mm_loadu_ps(&V1[i]); //loads first array
		num3 = _mm_loadu_ps(&V2[i]); //loads 2nd array
		num4 = _mm_add_ps(num1, num2, num3); //adds both arrays and the constant value
		_mm_storeu_ps(&V1[i], num4); //puts the sum into the first array*/

		num2 = _mm_loadu_ps(&V1[i]); //loads first array
		num3 = _mm_loadu_ps(&V2[i]); //loads 2nd array
		num4 = _mm_add_ps(num1, num2);
		num4 = _mm_add_ps(num4, num3);
		_mm_storeu_ps(&V1[i], num4);
	}

	//non-divisible remaining elements
	for (i = (M / 4) * 4; i < M; i++)
	{
		V1[i] = V1[i] + V2[i] + 2.12f;
	}

	return 2;
}





unsigned short int Compare() {
	int i, j;

	 for (j = 0; j < M; j++) {
		test[j] = test[j] + V2[j] + 2.12f;
	}


		for (j = 0; j < M; j++)
		 if (equal(V1[j], test[j]) == 1) {
			//printf("\n i,j=%d,%d\n", i,j);
			return 1;
		}
		
	free(V1), free(V2), free(test); //frees up memory that was being utilised by the float arrays
	return 0;
}

unsigned short int equal(float a, float b) {
	float temp = a - b;
	//printf("\n %f  %f", a, b);
	if (fabs(temp) < EPSILON)
		return 0; //success
	else
		return 1; //wrong result
}




