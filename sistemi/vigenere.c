#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void removeSpaces(char* input);

int main(void)
{
	char message[100];
	char worm[100];
	char ciphred[100];
	char deciphred[100];
	puts("\t\t\tCIFRARIO DI VIGENERE\r\t");
	puts("Inserire frase da codificare:");
	scanf("%[^\n]%*c", &message);
	puts("Inserire verme:");
	scanf("%[^\n]%*c", &worm);
	puts("Cifro il messaggio...\n");
	size_t i = 0;
	size_t j = 0;
	removeSpaces(message);
	removeSpaces(worm);
	while(message[i])
	{
		message[i] = (char)tolower(message[i]);
		++i;
	}
	while(worm[j])
	{
		worm[j] = (char)tolower(worm[j]);
		++j;
	}
	size_t k = 0;
	while(j < strlen(message))
	{	
		worm[j] = worm[k];
		++k;
		++j;
		if(k == strlen(worm)-1)
			k = 0;
	}
	i = 0;
	while(i < strlen(message))
	{
		ciphred[i] = ((message[i] + (worm[i]-12)) % 26) + 97;
		++i;
	}

	printf("Codifica: \n\t%s\n\t", message);
	printf("%s\n\t", worm);
	printf("%s\n", ciphred);

	i = 0;
	while(i < strlen(message))
	{
		deciphred[i] = (((message[i] - worm[i]) + 26) % 26) + 'a';
		++i;
	}
	printf("\n\nMessaggio ridecifrato: %s\n", deciphred);
}

void removeSpaces(char *str) 
{ 
    int count = 0; 
  
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i];
    str[count] = '\0'; 
} 

