// An API call to know the temperature of the particular area.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH_OF_CITY_NAME 20
#define LENGTH_OF_URL 250

void main()
{
	char cityName[LENGTH_OF_CITY_NAME];
	char url[LENGTH_OF_URL];
	printf("Enter the name of the city to know its temperature: ");
	scanf("%s", cityName);
	sprintf(url, "%s%s%s", "curl \"https://api.openweathermap.org/data/2.5/weather?q=" , cityName, "&appid=abe3a0f4d0b6cebfbe7393b4b4e3aa28&units=metric\" > weather.txt" );
	system(url);
	FILE* fpWeatherFile = fopen("weather.txt", "r");
	fseek(fpWeatherFile, 0, SEEK_END);
	int length = (int)ftell(fpWeatherFile);
	char weatherReport[length];
	rewind(fpWeatherFile);
	fread(weatherReport, sizeof(char), length, fpWeatherFile);
	char *temperature = strstr(weatherReport, "temp");
	temperature = strtok(temperature, ":");
	temperature = strtok(NULL, ",");
	if(temperature != NULL)
	{
		printf("\n The temperature at city %s is %s.", cityName, temperature);
	}
	else
	{
		printf("\n City %s is not found.", cityName);
	}
	fclose(fpWeatherFile);
}