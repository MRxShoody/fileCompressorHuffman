#include <stdio.h>
#include <stdlib.h>

//Dans cette étape je vais comptabiliser le nombre d'occurence de chaque caractère
//en utilisant les codes ascii des caractères pour les diriger à un endroit précis du dictionnaire
//qui est un tableau de 26 cases

//ouvre le fichier texte1.txt et compte le nombre d'occurence de chaque lettre
int charactersFrequency (int* repertoire, FILE* file);

//créer un dictionnaire de 26 grâce aux codes ascii des caractères
//on se limite à des lettres minuscules pour simplifier
int* repertoireInit (void);

//affiche le dictionnaire
void printRepertoire (int* repertoire);


int* repertoireInit (void ) {
    int* dictonary = malloc(sizeof(int)*163);
    for (int i = 0; i < 113; i++) {
        dictonary[i]= 0;
    }
    return dictonary;
}


int charactersFrequency (int* repertoire, FILE* file) {

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        repertoire[c-'\n'] = repertoire[c-'\n'] + 1;
        i++;

    }
    return i;
}

void printRepertoire (int* repertoire) {
    for (int i = 0; i < 113; i++) {
        printf("%c : %d\n", i + '\n', repertoire[i]);
    }
}