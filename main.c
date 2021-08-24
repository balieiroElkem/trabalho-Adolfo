#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct linha{
    int id;
    char data[11];
    char mandante[21];
    char visitante[21];
} linha;


char* lerLinha(FILE *p) {
    char c;
    int count = 1;

    char *s = (char *) malloc(sizeof(char)*count);

    while ((c = fgetc(p)) != EOF && c != '\n') {
        *(s+(count-1)) = c;
        count++;
        s = realloc(s, count*sizeof(char));
    }
    *(s+(count-1)) = '\0';

    return s;
}

linha getLinhaFormatada(char *l){
    linha temp;

    char *aux = strtok(l, ";");
    for(int i = 0; i < 7; i++){
        if(i == 0){
            temp.id = atoi(aux);
        } else if(i == 2){
            strcpy(temp.data, aux);
        } else if(i == 5){
            strcpy(temp.mandante, aux);
        } else if(i == 6){
            strcpy(temp.visitante, aux);
        }
        aux = strtok(NULL, ";");
    }
    return temp;
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    FILE *fp;
    char *linhaInteira;
    linha linhaFormatada;

    fp = fopen("campeonato-brasileiro-full.csv", "r");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    lerLinha(fp);
    linhaInteira = lerLinha(fp);
    linhaFormatada = getLinhaFormatada(linhaInteira);
    while (linhaFormatada.id != 4140) {
        linhaInteira = lerLinha(fp);
        linhaFormatada = getLinhaFormatada(linhaInteira);
    }

    printf("%d\t%s\t%s\t%s\n", linhaFormatada.id, linhaFormatada.data, linhaFormatada.mandante, linhaFormatada.visitante);

    fclose(fp);
    free(linhaInteira);
    
    return 0;
}