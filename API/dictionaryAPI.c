// An API call to know the meaning of the given word.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORD_LENGTH 20
#define LENGTH_OF_URL 250
#define VLC "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\""

char mp3[LENGTH_OF_URL];

void playAudio(char* data)
{
	char *audio = strstr(data, "https");
	audio = strtok(audio, "\"");
	sprintf(mp3," %s %s %s", VLC, "-I null --play-and-exit", audio);
	system(mp3);
	data[strlen(data)] = '\"';
}

void printMeaning(char* data)
{
	char *meaning = strstr(data, "\"definition\":\"");
	meaning = strtok(meaning, ",");
	printf("%s\n", meaning);
}

void main()
{
	char word[WORD_LENGTH];
	char url[LENGTH_OF_URL];
	int choice;
	printf("Enter the word to know its meaning: ");
	scanf("%s", word);
	sprintf(url, "%s%s%s", "curl https://api.dictionaryapi.dev/api/v2/entries/en/", word, " > dictionary.txt " );
	system(url);

	FILE* fpDictionary = fopen("dictionary.txt", "r");
	fseek(fpDictionary, 0, SEEK_END);
	int length = ftell(fpDictionary);
	char data[length];
	rewind(fpDictionary);
	fread(data, sizeof(char), length, fpDictionary);
	fclose(fpDictionary);
	while(1)
	{
		printf("\n1. To print meaning.\n2. To hear its pronounciation.\n3. Exit.");
		printf("\nEnter your choice:");
		scanf("%d", &choice);
		switch(choice)
			{
				case 1: printMeaning(data);
						break;
				case 2: playAudio(data);
						break;
				case 3: printf("\nThank you.");
						exit(0);
				default: printf("\nEntered Invalid Choice.");			
			}
	}

	// char *meaning = strtok(data, definition);
	// meaning = strstr(data, "\"definition\":\"");
	// printf("%s\n", meaning);


	


	

}