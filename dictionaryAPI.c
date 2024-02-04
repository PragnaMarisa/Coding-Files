// An API call to know the meaning of the given word.

#include <stdio.h>
#define WORD_LENGTH 20
#define LENGTH_OF_URL 250
#define DATA_LENGTH 500

void main()
{
	char word[WORD_LENGTH];
	char url[LENGTH_OF_URL];
	char mp3[LENGTH_OF_URL];
	char data[DATA_LENGTH];
	printf("Enter the word to know its meaning: ");
	scanf("%s", word);
	sprintf(url, "%s%s%s", "curl https://api.dictionaryapi.dev/api/v2/entries/en/", word, " > dictionary.txt " );
	system(url);
	FILE* fpDictionary = fopen("dictionary.txt", "r");
	fread(data, sizeof(char), DATA_LENGTH, fpDictionary);
	printf("\n %s", data);
	fclose(fpDictionary);
	sprintf(mp3,"%s%s%s", " curl https://api.dictionaryapi.dev/media/pronunciations/en/", word,"-uk.mp3 > dictionary.mp3 ");
	system(mp3);
	system("dictionary.mp3");

}