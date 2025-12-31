#ifndef TRI_H
#define TRI_H

#include "data.h"

typedef struct {
    int id_station;
    int degre;
} InfoStation;

/* Calcul du degré */
int calculer_degre(Station *s);
InfoStation *calculer_degres(Station *stations, int n);

/* Tris avec comptage */
void tri_selection(InfoStation *tab, int n, int *comp, int *perm);
void tri_insertion(InfoStation *tab, int n, int *comp, int *perm);
void quick_sort(InfoStation *tab, int debut, int fin, int *comp, int *perm);

/* Affichage */
void afficher_stations_triees(InfoStation *infos, Station *stations, int n);

#endif
