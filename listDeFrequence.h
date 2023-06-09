
//Dans cette étape, je vais utiliser une liste chainée
//ou la tête contient le chactère le plus courant avec sa frequence
//et ou la queue contient le caractère le moins courant avec sa frequence

//Ce code est nécessaire pour la création de l'arbre de huffman

void appendToList(LIST *list, char character, int frequency);
LIST* listInit(int* reportoire);
void sortList(LIST *list);
void removeHead(LIST *list);
void appendNode(LIST *list, NODE *node);

//initialise la liste chainée avec les fréquences de chaque caractère
//à partir du repertoire
LIST* listInit(int* repertoire){
    LIST* list = malloc(sizeof(LIST));
    list->size = 0;

    for (int i = 0; i < 113; i++) {
        appendToList(list, (char)(i + '\n'), repertoire[i]);
    }
    return list;
}

//ajoute un noeud à la liste chainée
void appendToList(LIST *list, char character, int frequency){
    NODE* node = malloc(sizeof(NODE));

    if(character!='1') {
        node->left = NULL;
        node->right = NULL;
    }

    if(frequency == 0){
        return;
    }

    node->character = character;
    node->frequency = frequency;

    //si la liste est vide
    if(list->size == 0){
        //le premier = le dernier
        //et il ne possède pas de noeud précédent ou suivant
        list->first = node;
        list->last = node;
        list->first->prev = NULL;
        list->last->next = NULL;
    }else{
        //sinon on ajoute le noeud à la fin de la liste
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
        list->last->next = NULL;
    }

    list->size++;
}

//trie la liste chainée avec un buble sort
//utilisé pour sa stabilité et simplicité
// complexité n carré mais la liste est courte (256 au max)
void sortList(LIST *list){

    int swapped, i;
    NODE *ptr1;
    NODE *lptr = NULL;

    if (list->first == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = list->first;

        while (ptr1->next != lptr)
        {
            if (ptr1->frequency > ptr1->next->frequency)
            {
                int frequency = ptr1->frequency;
                char character = ptr1->character;
                NODE *left = ptr1->left;
                NODE *right = ptr1->right;

                ptr1->frequency = ptr1->next->frequency;
                ptr1->character = ptr1->next->character;
                ptr1->left = ptr1->next->left;
                ptr1->right = ptr1->next->right;

                ptr1->next->frequency = frequency;
                ptr1->next->character = character;
                ptr1->next->left = left;
                ptr1->next->right = right;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);

}

//supprime le premier noeud de la liste chainée
void removeHead(LIST *list){
    NODE *node = list->first;
    list->first = node->next;
    list->first->prev = NULL;

    node->next=NULL;
    node->prev=NULL;

    list->size--;
}

//ajoute un noeud à la liste chainée à la fin
void appendNode(LIST *list, NODE *node){
    //si la liste est vide
    if(list->size == 0){
        //le premier = le dernier
        //et il ne possède pas de noeud précédent ou suivant
        list->first = node;
        list->last = node;
        list->first->prev = NULL;
        list->last->next = NULL;
    }else{
        //sinon on ajoute le noeud à la fin de la liste
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
        list->last->next = NULL;
    }
    list->size++;
}