#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"


/* ===== FONCTIONS UTILITAIRES ===== */

void rstrip_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r'))
        s[n-1] = '\0';
    n = strlen(s);
    if (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r'))
        s[n-1] = '\0';
}

int ligne_vide_ou_commentaire(const char *s) {
    while (*s && isspace((unsigned char)*s)) s++;
    return (*s == '\0' || *s == '#');
}

/* ===== INITIALISATION ===== */

void init_stations(Station *stations, int n) {
    int i = 0;
    while (i < n) {
        stations[i].id = i;
        stations[i].nom[0] = '\0';
        stations[i].adj = NULL;
        i++;
    }
}

/* ===== LISTE D'ADJACENCE ===== */

void ajouter_arc(Station *stations, int src, int dest, int temps) {
    Arc *a = (Arc*)malloc(sizeof(Arc));

    a->dest = dest;
    a->temps = temps;
    a->suiv = stations[src].adj;
    stations[src].adj = a;
}

/* ===== PASS 1 : COMPTER LES STATIONS ===== */

int trouver_max_id_station(FILE *f) {
    char ligne[LINE_MAX_LEN];
    int max_id = -1;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char *tok, *sid;

        rstrip_newline(ligne);
        if (ligne_vide_ou_commentaire(ligne)) continue;

        tok = strtok(ligne, ";");
        if (tok == NULL) continue;

        if (strcmp(tok, "STATION") == 0) {
            sid = strtok(NULL, ";");
            if (sid == NULL || sid[0] == '\0') continue; // STATION fantome 
            int id = atoi(sid);
            if (id > max_id) max_id = id;
        }
    }
    return max_id;
}


/* ===== LECTURE DU FICHIER ===== */

Station* charger_reseau(const char *filename) {
    FILE *f;
    Station *stations;
    char ligne[LINE_MAX_LEN];

    f = fopen(filename, "r");
    if (f == NULL) {
        perror(filename);
        return NULL;
    }

    int nb_stations = trouver_max_id_station(f) + 1;

    if (nb_stations <= 0) {
        fclose(f);
        return NULL;
    }

    stations = malloc(sizeof(Station) * (nb_stations));
    if (stations == NULL) {
        fclose(f);
        return NULL;
    }

    init_stations(stations, nb_stations);
    rewind(f);

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char *tok;

        rstrip_newline(ligne);
        if (ligne_vide_ou_commentaire(ligne)) continue;

        tok = strtok(ligne, ";");
        if (tok == NULL) continue;

        /* ----- STATION ----- */
        if (strcmp(tok, "STATION") == 0) {
            char *sid = strtok(NULL, ";");
            char *nom = strtok(NULL, ";");

            if (sid != NULL && nom != NULL) {
                int id = atoi(sid);
                stations[id].id = id;
                strcpy(stations[id].nom, nom);
            }
        }

        /* ----- EDGE ----- */
        else if (strcmp(tok, "EDGE") == 0) {
            char *src_s = strtok(NULL, ";");
            char *dest_s = strtok(NULL, ";");
            char *temps_s = strtok(NULL, ";");

            if (src_s != NULL && dest_s != NULL && temps_s != NULL) {
                int src = atoi(src_s);
                int dest = atoi(dest_s);
                int temps = atoi(temps_s);

                ajouter_arc(stations, src, dest, temps);
            }
        }
    }

    fclose(f);
    return stations;
}



/* ===== LIBERATION MEMOIRE ===== */

void liberer_reseau(Station *stations, int n) {
    int i;
    for (i = 0; i < n; i++) {
        Arc *a = stations[i].adj;
        while (a != NULL) {
            Arc *tmp = a;
            a = a->suiv;
            free(tmp);
        }
    }
    free(stations);
}


int charger_data(const char *filename) {
    Station *reseau;
    FILE *f = fopen(filename, "r");
    

    int nb_stations = trouver_max_id_station(f) + 1;
    fclose(f);

    reseau = charger_reseau(filename);
    if (reseau == NULL) {
        fprintf(stderr, "Echec du chargement du reseau\n");
        return 1;
    }

    liberer_reseau(reseau, nb_stations);

    return 0;
}

