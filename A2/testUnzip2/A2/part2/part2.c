#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/**
 * PART ZWEI
 * In this part, you'll check if an IEEE 754 string
 * is normalized, denormalized, or is a special case. check
 * the writeup and autograder for expected values. 
 */

int validateString(char* bitString){
        char* endingPosition = bitString + strlen(bitString);
	int length = strlen(bitString);

     repeat:
        if(!(*bitString == '0' | *bitString == '1')){
		  return 2; //means that they put in an invalid format
        }
        bitString++;

        if(bitString == endingPosition){
		goto end;
	}

	goto repeat;

     end:
        if(length != 16){
		return 1; //string is not the right length
	}

        return 0; //string is all good
}

int main(int argc, char** argv){
        if(argc != 2){
                fprintf(stderr, "invalid format\n");
                return EXIT_FAILURE;
        }
	if(validateString(argv[1]) > 0){
		if(validateString(argv[1]) == 1){
			fprintf(stderr, "must be 16 bits\n");
			return EXIT_FAILURE;
		}
		fprintf(stderr, "invalid format\n");
		return EXIT_FAILURE;
	}

        char* signBit = argv[1];
	char* exponentStart = signBit + 1;
	char* fractionStart = exponentStart + 5;

     checkDenormalized:
	if(exponentStart == fractionStart){
		printf("This value is denormalized");
		goto end;
	}

	if(*exponentStart != '0'){
		exponentStart = signBit + 1;
		goto checkSpecial;
	}

	exponentStart++;
	goto checkDenormalized;

     checkSpecial:
	if(exponentStart == fractionStart){
		printf("This value is a special case");
		goto end;
	}

	if(*exponentStart != '1'){
		printf("This value is normalized");
		goto end;
	}

	exponentStart++;
	goto checkSpecial;


      end:
	return EXIT_SUCCESS;
}

