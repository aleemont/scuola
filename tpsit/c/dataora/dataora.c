#include "dataora.h"
#include <stdlib.h>
#include <stdio.h>

void menu(){
    puts("");
    puts("                MENU");
    puts("");
    puts(" [0] Esci                                  ");
    puts(" [1] Ora Locale.                           ");
    puts(" [2] Giorni tra due date                   ");
    puts(" [3] Giorni dall'1/1/1970                  ");
    puts(" [4] Calcolo Pasqua                        ");
    puts(" [5] Cronometro                            ");
    puts(" [6] Somma giorni                          ");
    puts(" [7] Convalida data                        ");
    puts("");
    puts("                MENU");
}

int main(void){
   int scelta = 0;
   do{
        menu();
        puts("Scelta: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 0:
                exit(1);
            case 1:
                oraLocale();
                break;
            case 2:
                puts("Inserire data di inizio e di fine: (GG/MM/AAAA)");
                unsigned int gg, mm, aa, gg1, mm1, aa1;
                scanf("%u/%u/%u %u/%u/%u", &gg, &mm, &aa, &gg1, &mm1, &aa1);
                if(dataValida(gg, mm, aa) && dataValida(gg1, mm1, aa1))
                    differenzaGiorni(gg,mm,aa,gg1,mm1,aa1);
                else
                    puts("Hai inserito una data non valida!");
                break;
            case 3:
                giorniPassati();
                break;
            case 4:
                puts("Inserire anno: ");
                int anno;
                scanf("%u", &anno);
                if(anno < 1583 || anno > 2499){
                    puts("Errore, scegliere un anno tra il 1583 e il 2500.");
                    break;
                }
                pasqua(anno);
                break;
            case 5:
                cronometro();
                break;
            case 6:
                puts("Inserire data di inizio e i giorni da aggiungere: (GG/MM/AAAA gg)");
                unsigned int giorno, mese, ann;
                int gio;
                scanf("%u/%u/%u %i", &giorno, &mese, &ann, &gio);
                if(dataValida(giorno, mese, ann)==true){
                    sommaGiorni(giorno, mese, ann, gio);
                }
                else{
                    puts("Hai inserito una data non valida!");
                }
                break;
            case 7:
                puts("Inserire una data da convalidare: (GG/MM/AAAA)");
                unsigned int g, m, a;
                scanf("%u/%u/%u", &g, &m, &a);
                if(dataValida(g, m, a))
                    printf("La data inserita %c valida", 130);
                else
                    puts("Hai inserito una data non valida!");
                break;     
            default:
                puts("Errore, selezionare un numero tra 1 e 7");
                break;
        }
    }while(scelta!=0);
    return 0;
}
