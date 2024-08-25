#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * C does include a pow function, but it returns
 * a float value. Unfortunately, converting from
 * a float too long/int can lead to precision
 * issues. For this reason, you'll be asked to 
 * implement a custom pow function. make sure to
 * handle 2^0 :-)
 *
 * example input:
 *  mathpow(3,2)
 *  return value:
 *  9
 *
 *  Use goto statements
 */
long mathpow(int base, int exp){
	long risen = 1;

	if(exp == 0){
		return risen;
	}

	multiply:
		risen *= base;
		exp--;


	if(exp > 0){
		goto multiply;
	}

	return risen;

}

int validate(char* binaryNum, int length){
	char* current = binaryNum;

	increment:
	//	printf("%c\n", *current);
		if(*current < 48 | *current > 49){
			return 1; //invalid
		}
		current++;
		length--;

	if(length > 0){
		goto increment;
	}
	return 0; //valid
}


/**
 * Part one - Binary to Decimal conversion:
 * In this part of the assignment, you will
 * convert a binary string to it's signed
 * or unsigned decimal representation. assume twos
 * complement for this representation
 * 
 * example input:
 * ./part1 11111111 1
 * output:
 * -1
 *
 * YOU MAY NOT USE STRTOL FOR THIS!
 *
 * one more thing:
 *
 * YOU MUST USE GOTO statements, no loops, else if, else.
 */
int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "./binarytodec {binary string} {1 for signed, 0 for unsigned}\n");
		return EXIT_FAILURE;
	}


	char* binaryString = argv[1];
	char sign = *argv[2];
	char* ptr = binaryString + strlen(binaryString) - 1;
	char location = 0;
	int finalNumber = 0;


	if(!(sign == '1' | sign == '0')){
		fprintf(stderr, "./binarytodec {binary string} {1 for signed, 0 for unsigned}\n");
		return EXIT_FAILURE;
	}

	if(validate(binaryString, strlen(binaryString))){
		fprintf(stderr, "invalid binary string\n");
		return EXIT_FAILURE;
	}

//	printf("%c", sign);

	repeat:

		if(ptr == binaryString){
			goto end;
		}
		if(*ptr == '1'){
			finalNumber += mathpow(2,location);
		}
	location++;
	ptr--;
	goto repeat;


//poo poo code
/**	if(sign == '0'){
		goto notsigned;

	}

	singed:
		if(*ptr == '1'){
	//		printf("%d", location);
			finalNumber += mathpow(2, location);
		}

	if(sign == '1'){
//		printf("%d\n", location);
		ptr--;
		location++;

		if(location < strlen(binaryString)){
			finalNumber -= mathpow(2, location);
//			printf("%d", location);
			goto end;
		}
		goto singed;
	}


	notsigned:
//		printf("%d", location);
		if(*ptr == '1'){
//			printf("%d", location);
			finalNumber += mathpow(2, location);
		}

	if(sign == '0'){
//		printf("%d\n", location);
		ptr--;
		location++;

		if(location <= strlen(binaryString)){
			goto end;
		}

		goto notsigned;
	}

*/

	end:
		if(*ptr == '1' && sign == '0'){
			finalNumber += mathpow(2, location);
		}
		if(*ptr == '1' && sign == '1'){
			finalNumber -= mathpow(2, location);
		}
		if(sign == '0'){
			printf("%lu\n", finalNumber);
		}
		if(sign == '1'){
			printf("%d\n", finalNumber);
		}
		return EXIT_SUCCESS;
}
