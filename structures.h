//definitions des structures pour la liste chainée
#include <stdio.h>
#include <stdlib.h>


typedef struct _NODE NODE;              //définition du type NODE
typedef struct _DOUBLYLINKEDLIST LIST;  //définition du type LIST
typedef struct _DICTIONARY DICTIONARY;


struct _NODE{                  //définition de la structure NODE
    char character;
    int frequency;
    NODE *next;
    NODE *prev;
    NODE *left;
    NODE *right;

};

struct _DOUBLYLINKEDLIST{     //définition de la structure LIST
    NODE *first;
    NODE *last;
    int size;
};

struct _DICTIONARY{
    int size;
    int *bit;
};


