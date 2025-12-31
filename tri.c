#include <stdio.h>
#include <stdlib.h>
#include "tri.h"

/* Fonction d’échange pour InfoStation */
void swap_info(InfoStation *a, InfoStation *b) {
    InfoStation tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Calcul du degré d’une station */
int calculer_degre(Station *s) {
    int degre = 0;
    Arc *a = s->adj;

    while (a != NULL) {
        degre++;
        a = a->suiv;
    }

    return degre;
}

/* Tableau des degrés */
InfoStation *calculer_degres(Station *stations, int n) {
    InfoStation *infos = malloc(n * sizeof(InfoStation));
    if (!infos)
        return NULL;

    for (int i = 0; i < n; i++) {
        infos[i].id_station = stations[i].id;
        infos[i].degre = calculer_degre(&stations[i]);
    }

    return infos;
}

/* Tri par sélection */
void tri_selection(InfoStation *tab, int n, int *comp, int *perm) {
    *comp = 0;
    *perm = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comp)++;
            if (tab[j].degre < tab[min].degre) {
                min = j;
            }
        }
        if (min != i) {
            swap_info(&tab[i], &tab[min]);
            (*perm)++;
        }
    }
}

/* Tri par insertion */
void tri_insertion(InfoStation *tab, int n, int *comp, int *perm) {
    *comp = 0;
    *perm = 0;

    for (int i = 1; i < n; i++) {
        InfoStation key = tab[i];
        int j = i - 1;
        int local_perm = 0;

        while (j >= 0) {
            (*comp)++;
            if (tab[j].degre > key.degre) {
                tab[j + 1] = tab[j];
                j--;
                local_perm++;
            } else {
                break;
            }
        }
        tab[j + 1] = key;
        if (local_perm > 0) {
            (*perm)++;
        }
    }
}

/* Partition pour quicksort */
int partition(InfoStation *tab, int debut, int fin, int *comp, int *perm) {
    InfoStation pivot = tab[fin];
    int i = debut - 1;

    for (int j = debut; j < fin; j++) {
        (*comp)++;
        if (tab[j].degre <= pivot.degre) {
            i++;
            swap_info(&tab[i], &tab[j]);
            (*perm)++;
        }
    }

    swap_info(&tab[i + 1], &tab[fin]);
    (*perm)++;
    return i + 1;
}

/* Quicksort */
void quick_sort(InfoStation *tab, int debut, int fin, int *comp, int *perm) {
    if (debut < fin) {
        int p = partition(tab, debut, fin, comp, perm);
        quick_sort(tab, debut, p - 1, comp, perm);
        quick_sort(tab, p + 1, fin, comp, perm);
    }
}

/* Affichage */
void afficher_stations_triees(InfoStation *infos, Station *stations, int n) {
    printf("Stations triées par degré :\n");
    for (int i = 0; i < n; i++) {
        int id = infos[i].id_station;
        printf("Station %d (%s) - Degré : %d\n", id, stations[id].nom, infos[i].degre);
    }
}
