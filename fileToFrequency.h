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

void repertoireToFile (const int* repertoire, FILE* read);
void fileToRepertoire (int* repertoire, FILE* read);

int* repertoireInit (void ) {
    int* dictonary = malloc(sizeof(int)*113);
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
    fclose(file);
    return i;
}

void printRepertoire (int* repertoire) {

    for (int i = 0; i < 113; i++) {
        printf("%c : %d\n", i + '\n', repertoire[i]);
    }
}

void repertoireToFile (const int* repertoire, FILE* write) {

    for (int i = 0; i < 113; i++) {
        int temp = repertoire[i];
        char str[10];
        sprintf(str, "%d\n", temp);
        fputs(str, write);
    }
    fclose(write);
}

void fileToRepertoire (int* repertoire, FILE* read) {

    char line[100];
    int num;
    int index = 0;
    while (fgets(line, sizeof(line), read)) {
        sscanf(line, "%d", &num);
        repertoire[index] = num;
        index++;
    }
    fclose(read);
}
