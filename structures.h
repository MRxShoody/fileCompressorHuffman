//definitions des structures pour la liste chainée, de l'abre binaire et du dictionnaire de huffman

#include <stdio.h>
#include <stdlib.h>


typedef struct _NODE NODE;
typedef struct _DOUBLYLINKEDLIST LIST;
typedef struct _DICTIONARY DICTIONARY;


//définition de la structure NODE
struct _NODE{
    char character;
    int frequency;
    NODE *next;
    NODE *prev;
    NODE *left;
    NODE *right;

};

//définition de la structure LIST
struct _DOUBLYLINKEDLIST{
    NODE *first;
    NODE *last;
    int size;
};

//définition de la structure DICTIONARY
//chaque code ascii est représenté par un tableau de bits
//on lira ce tableau de bits de gauche à droite pour obtenir l'octet
//à écrire dans le fichier
struct _DICTIONARY{
    int size;
    int *bit;
};


