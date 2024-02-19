#include <stdio.h>
#include "isPrime.c"
#define COUNT 10

void main()
{
	char number[COUNT][10] = {"q1", "45", "37", "!@", "pp", "0", "&5", "7", "d}", "."};
	bool results[COUNT][10] = {false, false, true, false, false, false, false, true, false, false};
	bool isSuccessful = true;
	int counter;
	for(counter = 0; counter < COUNT; counter++)
	{
		 bool status = isPrime(number[counter]);
		 if(status == results[counter])
		 {
		 	printf("\ncode failed at %s.", number[counter]);
		 	isSuccessful = false;
		 }
	}
	if(isSuccessful)
	{
		printf("All are successfull");
	}
	
}