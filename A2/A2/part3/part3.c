#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/**
 * in this part of the assignment, you will be converting
 * a half-precision floating using an IEEE754 representation
 * to its decimal equivalent. You will have to account for
 * normalized, denormalized, and special cases.
 * +-+-----+----------+
 * |S|EEEEE|FFFFFFFFFF| <- representation of a half precision float 
 * +-+-----+----------+
 * 
 * example input:
 * ./floattoIEEE754 001110000000000000
 * output:
 * 0.50000000
 *
 * you'll only have to print out eight decimal places.
 * printf("%.xxLf", myLongdouble) will let you print myLongdouble to 
 * xx decimal places. 
 *
 * USE GOTO statements.
 *
 * I highly recommend splitting your code into different functions for
 * cleanliness, and to make troubleshooting easier. Don't use recursion.
 *
 * you may use strtol() ```man 3 strtol```
 *
 */



//Don't change these macros for this assignment.
//If you want to experiment with different EXP and
//FRAC for practice, you can, when compiling, use:
//-DEXP=XX, defines EXP as XX, and -DFRAC=XX, defining
//FRAC as XX
#ifndef EXP
    #define EXP 5
#endif

#ifndef FRAC
    #define FRAC 10
#endif

int validate (char* bitString){
	int size = strlen(bitString);
	int count = 0;

      repeat:
	if(!(*bitString == '0' || *bitString == '1')){
		return 2; //invald IEEE754 string
	}

	count++;
	bitString++;

	if(count < size){
		goto repeat;
	}

	if(size < 16){
		return 1; //wrong size
	}

	return 0;
}

int checkNormalization(char* bitString){
	char* exponentStart = bitString + 1;
	char* fractionStart = exponentStart + 5;

      checkDenormalized:
	if(exponentStart == fractionStart){
		return 2; //say that it is a denormalized guy
	}

	if(*exponentStart != '0'){
		exponentStart = bitString + 1;
		goto checkSpecial;
	}

	exponentStart++;
	goto checkDenormalized;

      checkSpecial:
	if(exponentStart == fractionStart){
		return 1; //say that this is a special guy
	}

	if(*exponentStart != '1'){
		return 0; //say this is a normal guy
	}

	exponentStart++;
	goto checkSpecial;

}

int normalizedExponent(char* bitString){
	char* front = bitString;
	bitString += 5;
	int bitLocation = 0;
	int exp = 0;

      repeat:
	if(bitString == front){
		return exp;
	}

	if(*bitString == '1'){
		exp += pow(2, bitLocation);
	}
	bitLocation++;
	bitString--;
	goto repeat;

}

int special(char* bitString){
	int count = 0;
      repeat:
	if(*bitString == '1'){
		return 1; //NaN
	}

	count++;
	bitString++;

	if(count < FRAC) {
		goto repeat;
	}

	return 0; //Infinite

}


int main(int argc, char** argv){
   // printf("%d\n",EXP); //example of how to use a macro.
    //EXP = 5, Macros are not variables; you cannot do this. 
	if(argc != 2){
		fprintf(stderr, "insert IEEE754 string with length >= 16\n");
		return EXIT_FAILURE;
	}

	if(validate(argv[1]) == 1){
		fprintf(stderr, "insert IEEE754 string with length >= 16\n");
		return EXIT_FAILURE;
	}

	if(validate(argv[1]) == 2){
		fprintf(stderr, "invalid binary format\n");
		return EXIT_FAILURE;
	}

	int kindOfValue = checkNormalization(argv[1]);
//	printf("%d", kindOfValue);

	int bias = (int)pow(2.0, (EXP-1)) - 1;
//	printf("%d", bias);
	int exp;
	int e;
	int power = argv[1][0] - 48;
	if(kindOfValue == 0){
		exp = normalizedExponent(argv[1]);
	}

	if(kindOfValue == 1){
		//special plans
		char* frac = argv[1] + EXP + 1;
		int kindOfSpecial = special(frac);
		if(kindOfSpecial == 1){
			printf("NaN\n");
			return EXIT_SUCCESS;
		}

		if(power == 0){
			printf("+infinity\n");
			return EXIT_SUCCESS;
		}

		printf("-infinity\n");
		return EXIT_SUCCESS;
	}

	if(kindOfValue == 2){
		exp = 1;
	}
	e = exp - bias;

	int currentLocation = 0;
	double m;

	if(kindOfValue == 0){
		m = pow(2.0, currentLocation);
	}

	if(kindOfValue == 2){
		m = 0;
	}

	currentLocation--;
	char* fractionString = argv[1] + 1 + EXP;
	int stoppingPoint = (FRAC+1) * -1;

      getM:
	if(currentLocation == stoppingPoint){
		goto nextStep; //temp name
	}

	if(*fractionString == '1'){
		m += pow(2.0, currentLocation);
	}
	currentLocation--;
	fractionString++;
	goto getM;
//	printf("%lf", m);


      nextStep:
	float finalValue = pow(-1.0, power) * m * pow(2,e);
	printf("%.8lf\n", finalValue);
	return EXIT_SUCCESS;

}
