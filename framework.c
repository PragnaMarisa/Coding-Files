// To create  a framework.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATAFILE "framework.dat"
#define FIELDSFILE "fields.cfg"
#define MENUFILE "menu.cfg"
#define MESSAGES_FILE "customizedMessages.cfg"
#define LENGTH 60


FILE* fpMenu;
FILE* fpFields;
FILE* fpDatafile;
FILE* fpMessages;


char fieldName[LENGTH];
char fieldValue[LENGTH];
char searchId[LENGTH];
char message[LENGTH];
char id[LENGTH];
char status;
char** fieldsNames;
char** customisedMessagesArray;


int countOfCustomisedMessages;
int sizeOfDatafile;
int fieldsCount;
int counter;
int recordPosition;


void showMenu();
void showAll();
void create();
int getFieldsCount(FILE* fp);
char* removeNewLine(char* dataline);
int getSizeOfDataFile(FILE* fpDatafile);
char** getDataArray(int count, FILE* fp);
int getRecordPosition(char* searchId);
char* getRecordId();
void delete(char* searchId);
void update(char* searchId);
void search(char* searchId);
void printNoRecordFound(char* searchId);

void printNoRecordFound(char* searchId)
{
	printf("\n Record with Id %s is  not found.", searchId);
}

void create()
{
	int counter = 0;
	rewind(fpFields);
	
	while(counter < fieldsCount)
	{
		printf("Enter %s: ", fieldsNames[counter]);
		scanf(" %[^\n]s", fieldValue);
		if(counter == 0)
		{
			strcpy(id, fieldValue);
			recordPosition = getRecordPosition(id);
			if(recordPosition > -1)
			{
				printf("\n ID:%s already exists!!!", id);
				showMenu();
				break;
			}
			else
			{
				fpDatafile = fopen(DATAFILE, "a");
				putc('A',fpDatafile);
				// fclose(fpDatafile);
				// fpDatafile = fopen(DATAFILE, "a");
				fwrite(id, sizeof(char), LENGTH, fpDatafile);
				fclose(fpDatafile);

			}
		}
		if(counter > 0)
		{
		fpDatafile = fopen(DATAFILE, "a");
		fwrite(fieldValue, sizeof(char), LENGTH, fpDatafile);
		fclose(fpDatafile);
		}
		counter++;
		if(counter == fieldsCount)
		{
		printf("\n %s %s.", customisedMessagesArray[0] , id);
		}
	}
}
void showAll()
{
	rewind(fpFields);
	fpDatafile = fopen(DATAFILE, "r");
	sizeOfDatafile = getSizeOfDataFile(fpDatafile);
	rewind(fpDatafile);
	while(ftell(fpDatafile) < sizeOfDatafile)
	{
		int counter = 0;
		status = getc(fpDatafile);
		if(status == 'A')
		{
			printf("\n------------------------------------------------------------------\n");
			while(counter < fieldsCount)
			{
				if(fread(fieldValue, sizeof(char), LENGTH, fpDatafile))
				{
					printf("\n%s: %s", fieldsNames[counter], fieldValue);
				}
				counter++;
			}
		}
		else
		{
			fseek(fpDatafile, LENGTH * fieldsCount, SEEK_CUR);
		}
	}
	printf("\n------------------------------------------------------------------\n");
	fclose(fpDatafile);

}

int getRecordPosition(char* searchId)
{
	fpDatafile = fopen(DATAFILE, "r");
	sizeOfDatafile = getSizeOfDataFile(fpDatafile);
	rewind(fpDatafile);
	while(ftell(fpDatafile) < sizeOfDatafile)
	{
		status = getc(fpDatafile);
		if(status == 'A')
		{
			fread(fieldValue, sizeof(char), LENGTH, fpDatafile);
			if(!strcmp(fieldValue, searchId))
			{
				fseek(fpDatafile, -LENGTH, SEEK_CUR);
				return ftell(fpDatafile);
			}
			else
			{
				fseek(fpDatafile, LENGTH * (fieldsCount - 1), SEEK_CUR);			
			}
		}
		else
		{
			fseek(fpDatafile, LENGTH * fieldsCount , SEEK_CUR);
		}

	}
	return -1;

}

void search(char* searchId)
{
	int counter = 0;
	int recordPosition = getRecordPosition(searchId);
	if(recordPosition > -1)
	{
		printf("\n------------------------------------------------------------------\n");
		fseek(fpDatafile, recordPosition, SEEK_SET);
		for(counter = 0; counter < fieldsCount; counter++)
			{
				fread(fieldValue, sizeof(char), LENGTH, fpDatafile);
				printf("\n%s: %s", fieldsNames[counter], fieldValue);
			}
	printf("\n%s %s.", customisedMessagesArray[1], searchId);
	}
	else
	{
		printNoRecordFound(searchId);
	}
	printf("\n------------------------------------------------------------------\n");
    fclose(fpDatafile);
}

void update(char* searchId)
{
	int counter = 1, updateChoice;
	int recordPosition = getRecordPosition(searchId);
	if(recordPosition > -1)
	{
		while(counter < fieldsCount)
		{
			printf("%d.  %s\n", counter, fieldsNames[counter]);
			counter++;
		}
		printf("\n Enter what to update: ");
		scanf("%d", &updateChoice);
		if(updateChoice > 0 && updateChoice < fieldsCount)
		{
			printf(" Enter new %s: ", fieldsNames[updateChoice]);
			scanf(" %[^\n]s", fieldValue);
			printf("%s", fieldValue);
			fpDatafile = fopen(DATAFILE, "r+");
			fseek(fpDatafile, recordPosition + (LENGTH * updateChoice), SEEK_SET);
			fwrite(fieldValue, sizeof(char), LENGTH, fpDatafile);
			fclose(fpDatafile);
			printf("\nNew %s of bus registration number %s %s", fieldsNames[updateChoice], searchId, customisedMessagesArray[2]);

		}
	}
	else
	{
		printNoRecordFound(searchId);
	}

}

void delete(char* searchId)
{
	int recordPosition = getRecordPosition(searchId);
	if(recordPosition > -1)
	{
		fpDatafile = fopen(DATAFILE, "r+");
		fseek(fpDatafile, recordPosition - 1, SEEK_SET);
		fputc('D',fpDatafile);
		fclose(fpDatafile);
		printf("\n%s %s.", customisedMessagesArray[3], searchId);
	}
	else
	{
		printNoRecordFound(searchId);
	}

}


void showMenu()
{
	int choice;
	char menu[LENGTH];
	fpMenu = fopen(MENUFILE, "r");
	while(fgets(menu, LENGTH, fpMenu))
	{
		printf("%s", menu);
	}
	printf("Enter you choice: ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1: create();
				break;
		case 2: showAll();
				break;
		case 3: printf("\nEnter an record id to be searched: ");
				search(getRecordId());
				break;
		case 4: printf("\nEnter an record id to be updated: ");
				update(getRecordId());
				break;
		case 5: printf("\nEnter an record id to be deleted: ");
				delete(getRecordId());
				break;
		case 6: printf("Thank you!!!");
				exit(1);
		default: printf("\nEnter a valid choice.");	
				 break;		
	}

}

int getSizeOfDataFile(FILE* fpDatafile)
{
	fseek(fpDatafile, 0 ,SEEK_END);
	return ftell(fpDatafile);
}

char* removeNewLine(char* dataline)
{
	dataline[strlen(dataline) - 1] = '\0';
	return dataline;
}

int getFieldsCount(FILE* fp)
{
	counter = 0;
	rewind(fp);
	while(fgets(fieldName, LENGTH, fp))
	{
		counter++;
	}
	return counter;
}

char* getRecordId()
{
	scanf(" %[^\n]s", searchId);
	return searchId;
}

char** getDataArray(int count, FILE* fp)
{
	int counter;
	char** ptr;
	ptr = (char**)malloc(sizeof(char*) * fieldsCount);
	for(counter = 0; counter < count; counter++)
	{
		ptr[counter] = (char*)malloc(sizeof(char) * LENGTH);
		fgets(fieldName, LENGTH, fp);
		removeNewLine(fieldName);
		strcpy(ptr[counter], fieldName);
	}
	return ptr;
}

void main()
{
	int counter;
	fpFields = fopen(FIELDSFILE, "r");
	fieldsCount = getFieldsCount(fpFields);
	rewind(fpFields);
	fieldsNames = getDataArray(fieldsCount, fpFields);
	fpMessages = fopen(MESSAGES_FILE, "r");
	countOfCustomisedMessages = getFieldsCount(fpMessages);
	rewind(fpMessages);
	customisedMessagesArray = getDataArray(countOfCustomisedMessages, fpMessages);
	printf("%d", fieldsCount);
	printf("%d", countOfCustomisedMessages);
	while(1)
	{
		showMenu();
	}
	fclose(fpFields);
	fclose(fpMessages);
}