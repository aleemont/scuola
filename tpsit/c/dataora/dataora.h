#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
/*
            ####################################
            ##            dataora.h           ##
            ##    Alessandro Monticelli VCI   ##
            ####################################
*/
#ifdef _WIN32           //se il sistema operativo è windows
    #include <windows.h> //includo windows.h
#endif

#ifdef linux       //se il sistema operativo è linux-based
    #include <unistd.h>     //includo unistd.h
#endif

void oraLocale(){
    #ifdef _WIN32           //se il sistema operativo è windows
        system("cls");
    #endif
    #ifdef linux    //se il sistema operativo è linux-based
        system("clear");
    #endif
    time_t start;
    unsigned int ore = 0, min = 0, sec = 0;

    while(1){
        ore--;              //evito che le ore vengano incrementate ad ogni ciclo
        start = time(0);    //secondi a partire dall'1/1/1970
        sec = start % 86400;    //calcolo i secondi rimanenti dalla mezzanotte del giorno corrente
        ore = sec/3600;     //calcolo le ore a partire dalla mezzanotte del giorno corrente
        sec %= 3600;    //calcolo i secondi rimanenti dall'ora corrente
        ore++;         //sistemo il fuso orario su GMT +1.00
        if(ore == 24)
            ore = 0;    //mezzanotte
        min = sec/60;   //calcolo i minuti
        sec %= 60;  //calcolo i secondi
        puts("Sono le: ");
        printf("%u:%u:%u",ore, min, sec);
        #ifdef _WIN32           //se il sistema operativo è windows
            Sleep(1000);    //delay di 1 secondo per visualizzare lo scorrimento dei secondi
            system("cls");  //svuoto la console per una corretta visualizzazione
        #endif
        #ifdef linux       //se il sistema operativo è linux-based
            usleep(1000000);    //delay di 1 secondo per visualizzare lo scorrimento dei secondi
            system("clear");    //svuoto la console per una corretta visualizzazione
        #endif
    }
}
void giorniPassati(){
    #ifdef _WIN32           //se il sistema operativo è windows
        system("cls");
    #endif
    #ifdef linux        //se il sistema operativo è linux-based
        system("clear");
    #endif
    time_t start;
    unsigned int ore, giorni;
    start = time(0);            //Numero di secondi dall'1/1/1970
    ore = start/3600;           //Ore dall'1/1/1970
    ++ore;                      //Aggiusto il fuso orario
    giorni = ore/24;            //Giorni dall'1/1/1970
    puts("Ci sono: ");
    printf("%u giorni dall'1/1/1970.", giorni);
}
void differenzaGiorni(unsigned int gio,unsigned int mese,unsigned int anno,
        unsigned int gio1, unsigned int mese1, unsigned int anno1){
    #ifdef _WIN32           //se il sistema operativo è windows
        system("cls");
    #endif
    #ifdef linux    //se il sistema operativo è linux-based
        system("clear");
    #endif
    int mesi[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};    //numero di giorni per ogni mese
    int an = anno1 - anno;     //differenza di anni
    int n_bis = (an)/4;     //calcolo del numero di anni bisestili tra i due anni scelti
    int gg = gio1-gio;  //differenza tra i giorni delle due date
    gg += n_bis;    //aggiungo 1 per ogni anno bisestile tra le due date

    if(anno1 % 4 == 0)
        gg += 1;            //se l'anno di fine è bisestile aggiungi un giorno
    if(anno % 4 == 0)
        gg += 1;        //se l'anno di inizio è bisestile aggiungi un giorno
    if(anno == anno1 && anno%4==0){
        gg -= 2;        //se l'anno di inizio e quello di fine corrispondono e sono bisestili non aggiungere niente
        if(mese <= 2 && mese1 > 2)
            gg += 1;    //se gli anni corrispondono e sono bisestili e se il mese di inizio è < 2 e quello di fine > 2 aggiungi   
    }
    gg += an*365;       //aggiungo il numero di giorni passato tra un anno e l'altro
    puts("Sono passati: ");
    printf("%i giorni tra il %u/%u/%u e il %u/%u/%u",
            gg, gio, mese, anno, gio1, mese1, anno1);
}

bool dataValida(unsigned int giorno,unsigned int mese,unsigned int anno){
    int mesi[] = {0,31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(mese > 12 || mese < 1){
        return false;
    }
    if(giorno > mesi[mese] || giorno < 1){
        return false;
    }
    if(mese == 2 && anno%4 != 0 && giorno > 28){
        return false;
    }
    return true;
}

void pasqua(int anno){
    int a, b, c, d, e, M, N, pas;
    #ifdef _WIN32           //se il sistema operativo è windows
        system("cls");
    #endif
    #ifdef linux    //se il sistema operativo è linux-based
        system("clear");
    #endif
    if(anno > 1582 && anno < 1700){M=22; N=2;}
    if(anno > 1699 && anno < 1800){M=23; N=3;}
    if(anno > 1799 && anno < 1900){M=23; N=4;}
    if(anno > 1899 && anno < 2100){M=24; N=5;}
    if(anno > 2099 && anno < 2200){M=24; N=6;}
    if(anno > 2199 && anno < 2300){M=25; N=0;}
    if(anno > 2299 && anno < 2400){M=26; N=1;}
    if(anno > 2399 && anno < 2500){M=26; N=1;}

    a = anno%19;
    b = anno%4;
    c = anno%7;
    d = (19*a + M)%30;
    e = (2*b + 4*c + 6*d + N)%7;
    pas = d+e;
    if(pas < 10){
        pas = d+e+22;
        printf("Pasqua %i cade il: %i marzo", anno, pas);
    }
    else{
        pas = d+e-9;
        if(pas == 25)
            printf("Pasqua %i cade il 18 aprile", anno);
        else if(pas == 26)
            printf("Pasqua %i cade il 19 aprile", anno);
        else
            printf("Pasqua %i cade il: %i aprile", anno, pas);
    }
}

void cronometro(){
    unsigned short int sec = 0, min = 0, ore = 0;
    #ifdef _WIN32           //se il sistema operativo è windows
        system("cls");
    #endif
    #ifdef linux    //se il sistema operativo è linux-based
        system("clear");
    #endif
    puts("Premere un tasto per avviare...");
    getchar();
    while(1){
    #ifdef _WIN32           //se il sistema operativo è windows
        Sleep(1000);
        system("cls");
    #endif
    #ifdef linux    //se il sistema operativo è linux-based
        usleep(1000000);
        system("clear");
    #endif
        sec++;
        if(sec == 60){
            sec = 0;
            min++;
            if(min == 60){
                min = 0;
                ore++;
            }
        }
	puts("");
        printf("%u:%u:%u", ore, min, sec);
    }
}

void sommaGiorni(unsigned short int gg, unsigned short int mm, unsigned short aa, int gio){
    printf("la data %i giorni dopo il %u/%u/%u ", gio, gg, mm, aa);
    int mesi[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for(int i = 0; i < gio; ++i){
        if(gg >= mesi[mm-1]){
            gg = 0;
            ++mm;
            if(mm > 12){
                mm = 1;
                ++aa;
            }
        }
        ++gg;
    }
    if(mm>=2 && aa%4 == 0)
        ++gg;
    printf("%c il: %u/%u/%u",130, gg, mm, aa);
}
