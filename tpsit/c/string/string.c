#include <stdio.h>
#include <stdlib.h>
#include "string.h"

void menu()
{
    puts("               MENU");
    puts("");
    puts("[0] Esci");
    puts("[1] Copia stringa.");
    puts("[2] Lunghezza stringa");
    puts("[3] Concatena stringa");
    puts("[4] Compara 2 stringhe");
    puts("[5] Trova occorrenza di un carattere");
    puts("[6] Trova posizioni di un carattere");
    puts("[7] Cerca una sottostringa");
    puts("");
}

int main()
{
    int scelta=1;
    char str1[35];
    char str2[35];
    char c;

    do{
        #ifdef _WIN32
            system("cls");
        #endif
        #ifdef __gnu_linux__
            system("clear");
        #endif
        menu();
        puts("\n\nSeleziona il numero funzione: ");
        scanf("%d%*c", &scelta);


        switch(scelta)
        {
            case 0:
                exit(1);
            case 1:
                puts("Inserire stringa [MAX LENGTH: 35]: ");
                fgets(str1, 35, stdin);
                copia(str1, str2);
                printf("Stringa 2: %s", str2);
                puts("\n\nPREMI UN TASTO PER TORNARE AL MENU");
                getchar();
                break;
            case 2:
                puts("inserire la stringa: ");
                fgets(str1, 35, stdin);
                printf("La stringa lunga %d caratteri", lunghezza(str1));
                puts("\n\nPREMI UN TASTO PER TORNARE AL MENU");
                getchar();
                break;
            case 3:
                puts("\nInserire prima stringa [MAX LENGTH: 35]: ");
                fgets(str1, 35, stdin);
                puts("Inserire seconda stringa [MAX LENGTH: 35]: ");
                fgets(str2, 35, stdin);
                printf("\nStringhe concatenate: %s", concatena(str1, str2));
                puts("\n\nPREMI UN TASTO PER TORNARE AL MENU");
                getchar();
                break;
            case 4:
                puts("\nInserire prima stringa [MAX LENGTH: 35]: ");
                fgets(str1, 35, stdin);
                puts("Inserire seconda stringa [MAX LENGTH: 35]: ");
                fgets(str2, 35, stdin);
                if(compara(str1,str2) == 0)
                    puts("\nLe stringhe sono uguali.");
                else
                    puts("\nLe stringhe sono diverse.");
                puts("\n\nPREMI UN TASTO PER TORNARE AL MENU");
                getchar();
                break;
            case 5:
                puts("Inserire stringa [MAX LENGTH: 35]: ");
                fgets(str1, 35, stdin);
                puts("Inserire carattere da ricercare: ");
                scanf("%c%*c", &c);
                int n = contaChar(str1, c);
                printf("Il carattere %c stato trovato %i volte", 130, n );
                puts("\n\nPREMI UN TASTO PER TORNARE AL MENU");
                getchar();
                break;
              case 6:
                puts("Inserire stringa [MAX LENGTH: 35]: ");
                fgets(str1, 35, stdin);
                puts("Inserire carattere da ricercare: ");
                scanf("%c%*c", &c);
                trovaChar(str1, c);
                puts("\n\nPREMI UN TASTO PER TORNARE AL MENU");
                getchar();
                break;
              case 7:
                puts("\nInserire prima stringa [MAX LENGTH: 35]: ");
                fgets(str1, 35, stdin);
                puts("Inserire seconda stringa [MAX LENGTH: 35]: ");
                fgets(str2, 35, stdin);
                if(strpos(str1, str2) == 0)
                  puts("La sottostringa è presente: ");
                else
                  puts("La sottostringa non è presente");
                puts("\n\nPREMI UN TASTO PER TORNARE AL MENU");
                getchar();
                break;
            default:
                puts("\n\nDIGITA UN NUMERO DA 1 A 7!");
                puts("\nPREMI INVIO PER TORNARE AL MENU");
                getchar();
                scelta=1;
                break;
        }
    }while(scelta != 0);
}
