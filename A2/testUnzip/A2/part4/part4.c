#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

int first_set_bit(int i) {
	// YOUR CODE HERE
	int count = 0;

      repeat:

	int iCopy = i >> count;
	iCopy = iCopy & 1;

	if(iCopy == 1){
		return count;
	}

	count++;
	if(count < 32)
		goto repeat;

	return -1;
}

int main(int argc, char** argv) {
	if (argc != 2) { 
		fprintf(stderr, "Usage: ./firstsetbit INTEGER");
		return 1;
	}
	printf("%d\n", first_set_bit(atoi(argv[1])));
}
