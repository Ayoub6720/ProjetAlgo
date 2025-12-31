#include <stdio.h>   
#include <stdlib.h>  

// Fonction qui lit un entier depuis l'entrée utilisateur avec gestion d'erreur
int lire_entier(char* message) {
    int nombre;
    printf("%s", message);
    
    // Vérifie que l'entrée est bien un entier
    if (scanf("%d", &nombre) != 1) {
        while (getchar() != '\n'); // Vide le buffer
        return -1;                 // Erreur de lecture
    }
    return nombre;
}

// Affiche le menu et retourne le choix de l'utilisateur
int afficher_menu() {
    int choix;
    
    printf("\n===== MENU RESEAU DE TRANSPORT =====\n");
    printf("1 - Afficher les informations d'une station\n");
    printf("2 - Lister les voisins d'une station\n");
    printf("3 - Calculer un chemin minimal\n");
    printf("4 - Afficher les stations triées par degré\n");
    printf("0 - Quitter\n");
    
    choix = lire_entier("Votre choix : ");
    return choix;
}

// Fonction principale
int main(int argc, char *argv[]) {
    int choix;
    
    // Vérifie la présence du fichier en argument
    if (argc != 2) {
        printf("Erreur : vous devez fournir un fichier en argument.\n");
        printf("Exemple : ./metro metro.txt\n");
        return 1;
    }
    
    printf("Chargement du réseau depuis %s...\n", argv[1]);
    
    // Boucle principale du menu
    while (1) {
        choix = afficher_menu();
        
        // Vérification du choix
        if (choix < 0 || choix > 4) {
            printf("Erreur : veuillez entrer un nombre entre 0 et 4.\n");
            continue;
        }
        
        // Quitter le programme
        if (choix == 0) {
            printf("Fin.\n");
            break;
        }
        
        // Option 1 : informations d'une station
        if (choix == 1) {
            int id = lire_entier("\nEntrez l'ID de la station : ");
            if (id < 0) {
                printf("Erreur : ID invalide.\n");
            } else {
                printf("Affichage de la station %d\n", id);
            }
        }
        // Option 2 : voisins d'une station
        else if (choix == 2) {
            int id = lire_entier("\nEntrez l'ID de la station : ");
            if (id < 0) {
                printf("Erreur : ID invalide.\n");
            } else {
                printf("Voisins de la station %d\n", id);
            }
        }
        // Option 3 : chemin minimal
        else if (choix == 3) {
            int depart = lire_entier("\nID station de départ : ");
            int arrivee = lire_entier("ID station d'arrivée : ");
            
            if (depart < 0 || arrivee < 0) {
                printf("Erreur : ID invalide.\n");
            } else {
                printf("Chemin de %d vers %d\n", depart, arrivee);
            }
        }
        // Option 4 : stations triées par degré
        else if (choix == 4) {
            printf("\nStations triées par degré\n");
        }
    }
    
    return 0;
}
