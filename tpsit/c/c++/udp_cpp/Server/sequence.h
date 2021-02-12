#include <stdio.h>

// restituisce il nuovo numero sequenziale,

// il valore 0 in caso di errore

unsigned int sequence(void)
{

    FILE* file;

    unsigned int n;

    // apertura del file

    file = fopen("number.txt", "r+");

    if (file == NULL)
        return 0;

    // lettura da file dell'ultimo valore utilizzato

    if (fscanf(file, "%u", &n) != 1)

    {

        fclose(file);

        return 0;

    }

    // generazione nuovo valore da utilizzare

    n++;

    // salvataggio su file del nuovo valore

    fseek(file, 0, SEEK_SET);

    fprintf(file, "%u", n);

    fclose(file);

    return n;

}
