// To test whether a number is prime or not

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

bool testPrime(int number);
bool isPrime(char* number);
bool isprime;

bool isPrime(char* number)
{
	int allNum = 1, counter, Number;
	for(counter = 0; counter < strlen(number); counter++)
	{
		if(!(isdigit(number[counter])))
		{
			allNum = 0;
			break;
		}
	}
	if(allNum == 1)
	{
		Number = atoi(number);
		isprime = testPrime(Number); // storing status of input in global variable. 
		return isprime;// will return true or false according to the input.
	}
	return false; // returns false when entered a invalid input.
}


bool testPrime(int number)
{
	int counter;
	int sqrtValue = sqrt(number);
	if(number % 2 != 0 && number > 2 )
	{
		for(counter = 3; counter < sqrtValue; counter += 2)
		{
			if(number % counter == 0)
			{
				return false;
			}
		}
	}
	else
	{
		if(number != 2)
		{
			return false;
		}
	}
	return true;
}


