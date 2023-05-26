// Ce code traite tout ce qui concerne la conversion entre fichier / fréquence

int charactersFrequency (int* repertoire, FILE* file);
int* repertoireInit (void);
void printRepertoire (int* repertoire);
void repertoireToFile (const int* repertoire, FILE* read, float cr);
float fileToRepertoire (int* repertoire, FILE* read);

//Ce code initialise le tableau de fréquence appellé repertoire et
// initialise les valeurs à 0
int* repertoireInit (void ) {
    int* dictonary = malloc(sizeof(int)*113);
    for (int i = 0; i < 113; i++) {
        dictonary[i]= 0;
    }
    return dictonary;
}

//Ce code compte le nombre d'occurence de chaque caractère
//et le stock dans repertoire grâce à leur code ascii
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

//afficher les fréquences de chaque caractère contenu dans repertoire
//pour débugger
void printRepertoire (int* repertoire) {

    for (int i = 0; i < 113; i++) {
        printf("%c : %d\n", i + '\n', repertoire[i]);
    }

}


//Ce code écrit dans un fichier les fréquences des caractères
void repertoireToFile (const int* repertoire, FILE* write, float cr) {

    fprintf(write, "%f\n", cr);
    for (int i = 0; i < 113; i++) {
        int temp = repertoire[i];
        fprintf(write, "%d\n", temp);
    }
    fclose(write);

}

//Ce code lit dans un fichier les fréquences des caractères
//afin de reconstituer les codes de huffman
float fileToRepertoire (int* repertoire, FILE* read) {

    char line[100];
    int num;
    float cr;
    int index = 0;
    while (fgets(line, sizeof(line), read)) {
        if (index == 0) {
            sscanf(line, "%f", &cr);
            index++;
            continue;
        }
        sscanf(line, "%d", &num);
        repertoire[index-1] = num;
        index++;
    }
    fclose(read);
    return cr;
}
