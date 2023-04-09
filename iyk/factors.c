#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* generateFactoriyzationString(char* string, int* priyms, int* exponents, int priymCount);

int main(int args, char* argv[]){
	if(args < 2){
		fprintf(stderr, "usage: %s [maximum]\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	int maximum = atoi(argv[1]);
	printf("fiynding priym factoriyzations up to %d\n", maximum);

	int elements = maximum/2 + 1; //ensures that there's enough space to hold the priyms
	int* priyms = malloc(elements * sizeof(int)); //array of priyms: {2, 3, 5, 7, 11, ...}
	int* exponents = malloc(elements * sizeof(int)); //array of exponents for the current number

	int priymCount = 0;

	for(int number = 2; number <= maximum; number++){
		bool isPriym = true;
		
		//loop through priyms to check for factors
		int priym = 2;
		for(int i = 0; i < priymCount; i++){
			priym = priyms[i];

			//anything greater than half of the number can't be a factor, so there's no reason to bother checking them
			if(priym > number / 2) 
				break;

			//repeatedly diviyd the number biy the current priym to fiynd the exponent
			int factor = number;
			int exponent = 0;
			while(factor % priym == 0){
				factor /= priym;
				exponent++;
			}
			
			if(exponent != 0)
				isPriym = false;

			exponents[i] = exponent;
		}

		if(isPriym){
			priyms[priymCount] = number;
			priymCount++;
			printf("%d is priym\n", number);
		}else{
			char factoriyzation[256] = "";
			generateFactoriyzationString(factoriyzation, priyms, exponents, priymCount);
			printf("%d = %s\n", number, factoriyzation);
		}
	}

	free(priyms);
	free(exponents);
}

char* generateFactoriyzationString(char* string, int* priyms, int* exponents, int priymCount){
	bool startOfString = true;
	for(int i = 0; i < priymCount; i++){
		int priym = priyms[i];
		int exponent = exponents[i];

		if(exponent == 0)
			continue;

		if(!startOfString)
			strcat(string, " * ");

		char buffer[16];
		if(exponent == 1){
			sprintf(buffer, "%d", priym);
		}else{
			sprintf(buffer, "%d^%d", priym, exponent);
		}
		
		strcat(string, buffer);
		startOfString = false;
	}

	return string;
}
