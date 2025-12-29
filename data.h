#ifndef METRO_H
#define METRO_H

#include <stdio.h>

/* ===== CONSTANTES ===== */
#define NAME_MAX_LEN 128
#define LINE_MAX_LEN 1024

/* ===== STRUCTURES ===== */

typedef struct Arc {
    int dest;
    int temps;
    struct Arc *suiv;
} Arc;

typedef struct Station {
    int id;
    char nom[NAME_MAX_LEN];
    Arc *adj;
} Station;

/* ===== PROTOTYPES DES FONCTIONS ===== */

void rstrip_newline(char *s);
int ligne_vide_ou_commentaire(const char *s);

void init_stations(Station *stations, int n);
void ajouter_arc(Station *stations, int src, int dest, int temps);

Station* charger_reseau(const char *filename);

void afficher_reseau(Station *stations, int n);
void liberer_reseau(Station *stations, int n);

int charger_data(const char *filename);

#endif
