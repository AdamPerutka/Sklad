#include <math.h>

// MAKRA
#define MAX_NAME 100 // max. dlzka pre nazvy
#define MAX_ITEMS 20 // max. pocet poloziek na sklade
#define DB_NUM 50 // pocet skladov v databaze
#define RADIUS_EARTH_KM 6372 // polomer zeme
#define LAT_MIN (-90)
#define LAT_MAX 90
#define LON_MIN (-180)
#define LON_MAX 180
#define deg2rad(X) ((X)*M_PI/180) // makro na konverziu stupnov na radiany

// DATOVE TYPY

// GPS poloha
typedef struct gps {
    double lat; // latitude
    double lon; // longitude
} GPS;

// polozka na sklade (tovar)
typedef struct item {
    char name[MAX_NAME + 1]; // nazov
    int price; // cena
} ITEM;

// sklad
typedef struct warehouse {
    char name[MAX_NAME + 1]; // nazov
    GPS gps; // poloha
    int n; // aktualny pocet poloziek na sklade
    ITEM items[MAX_ITEMS]; // databaza poloziek na sklade
} WAREHOUSE;

// DEKLARACIE FUNKCII
double distance(GPS gps1, GPS gps2);

// DEKLARACIE PREMENNYCH
extern WAREHOUSE db[DB_NUM]; // databaza skladov