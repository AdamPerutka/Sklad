#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define MAX 30




void vypisovanie_tovaro_centricke(int pozicia) {
    for (int k = 0; k < db[pozicia].n; k++) {
        printf("%d. %s %d : %s %.3f %.3f %d\n", k + 1, db[pozicia].items[k].name,
               db[pozicia].items[k].price, db[pozicia].name,
               db[pozicia].gps.lat, db[pozicia].gps.lon, db[pozicia].n);
    }
}
void vypisovanie_tovaro_centricke_tovar(int databaza, int itemy, int i) {

    printf("%d. %s %d : %s %.3f %.3f %d\n", i, db[databaza].items[itemy].name,
           db[databaza].items[itemy].price, db[databaza].name,
           db[databaza].gps.lat, db[databaza].gps.lon, db[databaza].n);

}
void sklado_centricke_SKLAD(int pozicia){
    printf("%s %.3f %.3f %d :\n", db[pozicia].name,
           db[pozicia].gps.lat, db[pozicia].gps.lon, db[pozicia].n);
}
void sklado_centricke_TOVAR(int pozicia,int itemy,int k) {


        printf("%d. %s %d\n", k + 1, db[pozicia].items[itemy].name,
               db[pozicia].items[itemy].price);

}
int main(int argc, char *argv[]) {


    int sklado_centricke = 0;
    char prepinace[MAX];
    for(int i = 0; i<MAX;i++){
        prepinace[i] = 0;
    }





    int opt;
    char *optstring = ":w:i:n:e:t:p:W";
//TODO  w p-W t-W
//      i p-W t-W
//      ne p-W t-W
//      p-W t-W
    double d; GPS gps1,gps2;
    struct WAREHOUSE;
//    distance(db[1].gps.lat,db[1].gps.lon);

   // printf("%f",db[2].gps.lon);




  //  printf("%.3lf", distance(gps,gps4));


    while ((opt = getopt(argc, argv, optstring)) != -1) {


        switch (opt) {
            case 'w': {
                prepinace[1] = 'w';
                break;
            }
            case 'i': {
                prepinace[2] = 'i';
                break;
            }
            case 'n': {
                prepinace[3] = 'n';
                break;
            }
            case 'e': {
                prepinace[4] = 'e';
                break;
            }
            case 't': {
                prepinace[5] = 't';
                break;
            }
            case 'p': {
                prepinace[6] = 'p';
                break;
            }
            case 'W': {
                prepinace[7] = 'W';
                break;
            }
            default: {
                if (opt == '?') {
                    return 1;
                }
                if (opt == ':') {
                    return 2;
                }
                return 1;
            }

        }
    }
if(prepinace[7] == 'W'){
    sklado_centricke = 1;
}
    if(prepinace[3] == 'n' && prepinace[4] =='e') {
    float n_number;
    float e_number;
    e_number = atof(argv[4]);
    n_number = atof(argv[2]);

    gps1.lon = e_number;
    gps1.lat = n_number;

    if (strtol(argv[2], NULL, 10) == 0 || strtol(argv[4], NULL, 10) == 0 ){
        return 4;
    }


    //POKIAL N ALEBO E NIE JE V ROZSAHU
    if (n_number > LAT_MAX || n_number < LAT_MIN ||
        e_number > LON_MAX || e_number < LON_MIN) {
        return 4;
    }
}
    // pokial -n -e prepinace niesu zapnute naraz
    if(prepinace[3] == 'n' && prepinace[4] !='e' || prepinace[3] != 'n' && prepinace[4] == 'e'){
        return 3;
    }

int jeden_argument = 3;



    // AK SA ZADA IBA CESTA
    // -W
    if(argc <= 2){
        int pocet = 1;
        int i;

        for(int l = 0; l<DB_NUM;l++) {
            if(sklado_centricke == 0) {
                for (i = 0; i < db[l].n; i++) {
                    printf("%d %s %d : %s %.3f %.3f %d\n", pocet, db[l].items[i].name, db[l].items[i].price, db[l].name,
                           db[l].gps.lat, db[l].gps.lon, db[l].n);
                    pocet++;
                }
            }
            if(sklado_centricke == 1){
                sklado_centricke_SKLAD(l);
                for(i = 0; i<db[l].n;i++){
                    sklado_centricke_TOVAR(l,i,i);
                }
            }
        }
    }


    //samotne -w
    //kombinacia -w -W
    //kombinacia -w -t +W
    //kombinacia -w -p +W
    if(prepinace[1] =='w' && argc < 7){
        int databaza,w,pozicia = -1; int itemy = 0;
        int i = 0;
        int pocitanie = 1;
        int cislo_po_p = 0;
        int cislo_pre_p = 0;
        char tovar_pre_t;

        if(prepinace[6] == 'p'){

            for(int najdenie_p = 1; najdenie_p<argc;najdenie_p++){
                if(argv[najdenie_p][1]=='p'&&argv[najdenie_p][0] == '-'){
                    cislo_po_p = najdenie_p +1;
                }

            }
            cislo_pre_p = strtol(argv[cislo_po_p],NULL,10);

        }
        if(prepinace[5] == 't'){
            for(int najdenie_p = 1; najdenie_p<argc;najdenie_p++){
                if(argv[najdenie_p][1]=='t'&& argv[najdenie_p][0] == '-'){
                    cislo_pre_p = najdenie_p +1;
                }

            }

        }





        for(w = 1; w<argc;w++)
        {
            if (argv[w][1] == 'w' && argv[w][0] == '-')
            {

                w++;

                for (databaza = 0; databaza < DB_NUM; databaza++)
                {
                    if ((strcmp(db[databaza].name, argv[w]) )== 0)
                    {
//                        TODO zistit ako vypisat cely sklad a ABY TO NADVAZOVALO
                        pozicia = databaza;
                    }

                }
            }
        }
        if (pozicia != -1)
        {

            if(prepinace[5]!= 't'&&prepinace[6]!= 'p')
            {
                if(sklado_centricke == 1)
                {

                    sklado_centricke_SKLAD(pozicia);
                    i = 0;
                    for(itemy = 0; itemy<db[pozicia].n;itemy++)
                    {
                        sklado_centricke_TOVAR(pozicia,itemy,i);
                        i++;
                    }
                }
                if(sklado_centricke == 0)
                {
                    vypisovanie_tovaro_centricke(pozicia);
                }
            }
            if(prepinace[5] == 't')
            {//TODO prepinac t a p
                if(sklado_centricke==1)
                {
                    sklado_centricke_SKLAD(pozicia);
                    pocitanie = 0;

                    for (itemy = 0; itemy < db[pozicia].n; itemy++) {
                        if(strcmp(db[pozicia].items[itemy].name,argv[cislo_pre_p]) == 0){
                        sklado_centricke_TOVAR(pozicia, itemy, pocitanie);
                        pocitanie++;}
                    }
                }
                if(sklado_centricke == 0){
                    pocitanie = 1;

                    for (itemy = 0; itemy < db[pozicia].n; itemy++) {
                        if(strcmp(db[pozicia].items[itemy].name,argv[cislo_pre_p]) == 0){
                            vypisovanie_tovaro_centricke_tovar(pozicia, itemy, pocitanie);
                            pocitanie++;}
                    }
                }


            }
            if(prepinace[6] == 'p' &&prepinace[5] != 't'){
                if(sklado_centricke == 0)
                {

                    pocitanie = 1;
                    for (itemy = 0; itemy < db[pozicia].n; itemy++)
                    {
                        if (db[pozicia].items[itemy].price <= cislo_pre_p) {
                            vypisovanie_tovaro_centricke_tovar(pozicia, itemy, pocitanie);
                            pocitanie++;
                        }

                    }
                }

                if(sklado_centricke == 1){
                    pocitanie = 1;
                    sklado_centricke_SKLAD(pozicia);
                    for (itemy = 0; itemy < db[pozicia].n; itemy++) {

                        if (db[pozicia].items[itemy].price <= cislo_pre_p) {
                            printf("%d. %s %d\n", pocitanie, db[pozicia].items[itemy].name,
                                   db[pozicia].items[itemy].price);
                            pocitanie++;
                        }
                    }

                }

            }



        }
    }

    //samotne -i
    //kombinacia -i -W
    //kombinacia -i -t +W
    //kombinacia -i -p +W
    if(prepinace[2] == 'i' && argc <9)
    {
        int databaza, w, itemy = 0;
        int pozicia = -1;
        int pocitanie = 1;
        int pocitanie2 = 1;
        int P = 1;
        int cislo_po_p = 0;
        int cislo_pre_p = 0;
        char tovar_pre_t;

        if(prepinace[5] == 't'){
            for(int najdenie_p = 1; najdenie_p<argc;najdenie_p++)
            {
                if(argv[najdenie_p][1]=='t'&&argv[najdenie_p][0] == '-')
                {
                    cislo_po_p = najdenie_p +1;
                }
            }
        }
        if(prepinace[6] == 'p'){

            for(int najdenie_p = 1; najdenie_p<argc;najdenie_p++){
                if(argv[najdenie_p][1]=='p'&&argv[najdenie_p][0] == '-'){
                    cislo_po_p = najdenie_p +1;
                }

            }
            cislo_pre_p = strtol(argv[cislo_po_p],NULL,10);

        }
        for (w = 1; w < argc; w++)
        {
            if (argv[w][1] == 'i'&& argv[w][0] == '-')
            {
                w++;
                for (databaza = 0; databaza < DB_NUM; databaza++)
                {

                        for (itemy = 0; itemy < db[databaza].n; itemy++)
                        {
                            if (strcmp(db[databaza].items[itemy].name, argv[w]) == 0)
                            {
                                if(prepinace[2]== 'i' && prepinace[5] != 't' && prepinace[6] != 'p'){
                                    if(sklado_centricke==1)
                                    {
                                        sklado_centricke_SKLAD(databaza);

                                         for(int i = 0; i<db[databaza].n;i++){
                                             sklado_centricke_TOVAR(databaza,i,i);
                                         }
                                    }
                                    if(sklado_centricke==0)
                                    {

                                        pozicia = databaza;
                                        for(int i = 0; i<db[databaza].n;i++)
                                        {
                                            vypisovanie_tovaro_centricke_tovar(pozicia,i,pocitanie);
                                            pocitanie++;
                                        }
//                                        vypisovanie_tovaro_centricke(pozicia);
                                    }
                                }
                                if(prepinace[5] == 't' && prepinace[6] != 'p'){


                                    if(sklado_centricke ==1){

                                        sklado_centricke_SKLAD(databaza);
                                        for (int k = 0; k < db[databaza].n; k++) {
                                            pocitanie2= 1;
                                            if (
                                                    strcmp(db[databaza].items[k].name, argv[cislo_po_p]) == 0)
                                            {
                                                printf("%d. %s %d\n",pocitanie2,db[databaza].items[k].name, db[databaza].items[k].price);

                                                pocitanie2++;
                                            }
                                        }


                                    }
                                    if(sklado_centricke==0){

                                        for (itemy = 0; itemy < db[databaza].n; itemy++) {

                                            if (strcmp(db[databaza].items[itemy].name, argv[cislo_po_p]) == 0)
                                            {
                                                vypisovanie_tovaro_centricke_tovar(databaza,itemy,pocitanie2);
                                                pocitanie2+=1;
                                            }
                                        }

                                    }
                                }
                                if(prepinace[6] == 'p' && prepinace[5] != 't'){

                                    if(sklado_centricke == 0)
                                    {

                                    pocitanie = 0;
                                    for (itemy = 0; itemy < db[databaza].n; itemy++)
                                    {
                                            if (db[databaza].items[itemy].price <= cislo_pre_p) {
                                                vypisovanie_tovaro_centricke_tovar(databaza, itemy, P);
                                                P++;
                                            }

                                    }
                                }

                                    if(sklado_centricke == 1){
                                        P = 1;
                                        sklado_centricke_SKLAD(databaza);
                                        pocitanie = 0;
                                        for (itemy = 0; itemy < db[databaza].n; itemy++) {

                                            if (db[databaza].items[itemy].price <= cislo_pre_p) {
                                                printf("%d. %s %d\n", P, db[databaza].items[itemy].name,
                                                       db[databaza].items[itemy].price);
                                                P++;
                                            }
                                        }

                                    }



                                }
                            }
                        }

                }
            }
        }

    }

    //samotne -n -e
    //kombinacia -n -e a -W
    //kombinacia -n -e -t + W
    //kombinacia -n -e -p + W
    if(prepinace[3] =='n'&& prepinace[4] == 'e' && argc <9){
        double hodnoty_vzdialenost[DB_NUM];
        int najmensia_vzdialenost = 0;
        int pocitanie = 0;
        int i;
        int itemy = 0;

        int cislo_po_p = 0;
        int cislo_pre_p = 0;
        char tovar_pre_t;

        if(prepinace[6] == 'p'){

            for(int najdenie_p = 1; najdenie_p<argc;najdenie_p++){
                if(argv[najdenie_p][1]=='p'&&argv[najdenie_p][0] == '-'){
                    cislo_po_p = najdenie_p +1;
                }

            }
            cislo_pre_p = strtol(argv[cislo_po_p],NULL,10);

        }
        if(prepinace[5] == 't'){
            for(int najdenie_p = 1; najdenie_p<argc;najdenie_p++){
                if(argv[najdenie_p][1]=='t'&& argv[najdenie_p][0] == '-'){
                    cislo_pre_p = najdenie_p +1;
                }

            }

        }

        for(i = 0; i < DB_NUM;i++){


            gps2.lon = db[i].gps.lon;
            gps2.lat = db[i].gps.lat;
            hodnoty_vzdialenost[i] = distance(gps1,gps2);
            if(i > 0)
            {
                if(hodnoty_vzdialenost[najmensia_vzdialenost] > hodnoty_vzdialenost[i])
                {
                    najmensia_vzdialenost = i;
                }
            }
        }
        if(prepinace[5]!= 't' && prepinace[6] != 'p') {
            if (sklado_centricke == 1 ) {


                sklado_centricke_SKLAD(najmensia_vzdialenost);
                pocitanie = 0;

                for (itemy = 0; itemy < db[najmensia_vzdialenost].n; itemy++) {
                    sklado_centricke_TOVAR(najmensia_vzdialenost, itemy, pocitanie);
                    pocitanie++;
                }
            }


            if (sklado_centricke == 0 ) {
                vypisovanie_tovaro_centricke(najmensia_vzdialenost);
            }
        }
        if(prepinace[6] == 'p') {
            if (sklado_centricke == 1 && prepinace[6] == 'p') {
                int P = 1;
                sklado_centricke_SKLAD(najmensia_vzdialenost);
                pocitanie = 0;
                for (itemy = 0; itemy < db[najmensia_vzdialenost].n; itemy++) {

                    if (db[najmensia_vzdialenost].items[itemy].price <= cislo_pre_p) {
                      printf("%d. %s %d\n", P, db[najmensia_vzdialenost].items[itemy].name,
                             db[najmensia_vzdialenost].items[itemy].price);
                      P++;
                  }
              }
    }
              if (sklado_centricke == 0 && prepinace[6] == 'p') {
                  int P = 1;
                  pocitanie = 0;
                  for (itemy = 0; itemy < db[najmensia_vzdialenost].n; itemy++) {

                      if (db[najmensia_vzdialenost].items[itemy].price <= cislo_pre_p) {
                          vypisovanie_tovaro_centricke_tovar(najmensia_vzdialenost, itemy, P);
                          P++;
                      }
                  }

              }
}
        if(prepinace[5] == 't') {
          if (sklado_centricke == 0) {
              int ko = 1;

              for (int k = 0; k < db[najmensia_vzdialenost].n; k++) {
                  if (strcmp(db[najmensia_vzdialenost].items[k].name, argv[cislo_pre_p]) == 0)
                  {

                      vypisovanie_tovaro_centricke_tovar(najmensia_vzdialenost, k, ko);
                      ko++;
                  }
              }
          }
        if(sklado_centricke == 1){
          int ko = 1;
          sklado_centricke_SKLAD(najmensia_vzdialenost);
          for (int k = 0; k < db[najmensia_vzdialenost].n; k++) {
              if (
                      strcmp(db[najmensia_vzdialenost].items[k].name, argv[cislo_pre_p]) == 0)
              {
                  printf("%d. %s %d",ko,db[najmensia_vzdialenost].items[k].name, db[najmensia_vzdialenost].items[k].price);

                  ko++;
              }
          }
}


}






    }

    //samotne -t
    //kombinacia -p a -W
    if(prepinace[5] == 't' && argc < 5){
        int databaza, w, itemy = 0;
        int pozicia = -1;
        int i = 1;

        for (w = 1; w < argc; w++)
        {
            if (argv[w][1] == 't' && argv[w][0] == '-')
            {
                w++;
                for (databaza = 0; databaza < DB_NUM; databaza++)
                {
                    if(sklado_centricke == 1){
                        sklado_centricke_SKLAD(databaza);
                        i = 0;}

                    for (itemy = 0; itemy < db[databaza].n; itemy++)
                    {
                        if (strcmp(db[databaza].items[itemy].name, argv[w]) == 0)
                        {
                            if(sklado_centricke ==1) {
                                sklado_centricke_TOVAR(databaza, itemy, i);
                            }
                            if(sklado_centricke == 0){
                                vypisovanie_tovaro_centricke_tovar(databaza, itemy, i);
                            }
                            i++;
//
                        }
                    }
                }
            }
        }

    }


    //samotne -p
    //kombinacia -p a -W
    if(prepinace[6] == 'p'&& argc < 5){
        int databaza, w, itemy = 0;
        int pozicia = -1;
        int max_price = 0;
        for (w = 1; w < argc; w++)
        {
            if (argv[w][1] == 'p' && argv[w][0] == '-')
            {
                int i = 1;
                w++;
                max_price = strtol(argv[w],NULL,10);

                for (databaza = 0; databaza < DB_NUM; databaza++)
                {
                if(sklado_centricke == 1){
                    sklado_centricke_SKLAD(databaza);
                    i = 0;}

                    for (itemy = 0; itemy < db[databaza].n; itemy++)
                    {
                        if(db[databaza].items[itemy].price<=max_price){
                            if(sklado_centricke ==1) {
                                sklado_centricke_TOVAR(databaza, itemy, i);
                            }
                            if(sklado_centricke == 0){
                                vypisovanie_tovaro_centricke_tovar(databaza, itemy, i);
                            }
                            i++;
                        }
                    }
//                    printf("%d",max_price);
                }
            }
        }
    }







    return 0;
}
