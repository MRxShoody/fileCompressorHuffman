// Ce fichier contient la fonction de decompression
// il prend avantage de l'arbre binaire de huffman
// et des bitshifts decrypter le fichier compressé

void decompress(FILE* read, FILE* write, NODE* top);

void decompress(FILE* read, FILE* write, NODE* top){

    NODE* temp = top;
    int readchar;
    while((readchar = fgetc(read)) != EOF) {

        for (int m = 7; m >= 0; m--) {

            //il lit bit par bit et se déplace dans l'arbre
            //jusqu'à ce qu'il trouve un charactère
            //si le bit est 0, il se déplace à gauche
            //si le bit est 1, il se déplace à droite

            if(((readchar >> m) & 1) == 0){
                top = top->left;
            } else {
                top = top->right;
            }

            if(top->character != '1') {

                fwrite(&top->character, sizeof(char), 1, write);
                top = temp;

            }
        }
    }

    fclose(write);
    fclose(read);
}