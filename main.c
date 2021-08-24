#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct linha{
    int id;
    char data[11];
    char mandante[21];
    char visitante[21];
    struct linha *prox;
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

linha* lista(linha *p, linha l) {
    if (p == NULL) {
        p = (linha *) malloc(sizeof(linha));
        if (!p) {
            printf("Erro ao alocar memoria na lista");
            exit(1);
        }
        p->id = l.id;
        strcpy(p->data, l.data);
        strcpy(p->mandante, l.mandante);
        strcpy(p->visitante, l.visitante);
        p->prox = NULL;
    } else {
        linha *novo = (linha *) malloc(sizeof(linha));
        linha *tmp = p;

        while (tmp->prox != NULL) {
            tmp = tmp->prox;
        }

        tmp->prox = novo;
        tmp->prox->id = l.id;
        strcpy(tmp->prox->data, l.data);
        strcpy(tmp->prox->mandante, l.mandante);
        strcpy(tmp->prox->visitante, l.visitante);
        tmp->prox->prox = NULL;
    }

    return p;
}


linha* buble_sort(linha *lista, int t, int op) {
    linha tmp;
    linha *aux = lista;
    linha *aux2 = aux->prox;

    switch (op) {
        case 0: // Organizando como mandante
            while (aux->prox != NULL) {
                aux2 = aux->prox;
                while (aux2->prox != NULL) {
                    if (strcmp(aux->mandante, aux2->mandante) > 0) {
                        tmp.id = aux->id;
                        strcpy(tmp.data, aux->data);
                        strcpy(tmp.mandante, aux->mandante);
                        strcpy(tmp.visitante, aux->visitante);

                        aux->id = aux2->id;
                        strcpy(aux->data, aux2->data);
                        strcpy(aux->mandante, aux2->mandante);
                        strcpy(aux->visitante, aux2->visitante);

                        aux2->id = tmp.id;
                        strcpy(aux2->data, tmp.data);
                        strcpy(aux2->mandante, tmp.mandante);
                        strcpy(aux2->visitante, tmp.visitante);
                    }
                    aux2 = aux2->prox;
                }
                aux = aux->prox;
            }
            break;
        
        case 1: // Organizando como visitante
            while (aux->prox != NULL) {
                aux2 = aux->prox;
                while (aux2->prox != NULL) {
                    if (strcmp(aux->visitante, aux2->visitante) > 0) {
                        tmp.id = aux->id;
                        strcpy(tmp.data, aux->data);
                        strcpy(tmp.mandante, aux->mandante);
                        strcpy(tmp.visitante, aux->visitante);

                        aux->id = aux2->id;
                        strcpy(aux->data, aux2->data);
                        strcpy(aux->mandante, aux2->mandante);
                        strcpy(aux->visitante, aux2->visitante);

                        aux2->id = tmp.id;
                        strcpy(aux2->data, tmp.data);
                        strcpy(aux2->mandante, tmp.mandante);
                        strcpy(aux2->visitante, tmp.visitante);
                    }
                    aux2 = aux2->prox;
                }
                aux = aux->prox;
            }
            break;
        default:
            printf("Ta doido misera.\n");
    }
    
   

    return lista;
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    FILE *fp;
    char *linhaInteira;
    linha linhaFormatada, *p = NULL;
    int tamanho = 0;

    fp = fopen("campeonato-brasileiro-full.csv", "r");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    lerLinha(fp);
    linhaInteira = lerLinha(fp);
    linhaFormatada = getLinhaFormatada(linhaInteira);
    // range 4140 - 4899
    while (linhaFormatada.id <= 4899) {
        if (linhaFormatada.id >= 4140) {
            p = lista(p, linhaFormatada);
            tamanho++;
        }
        linhaInteira = lerLinha(fp);
        linhaFormatada = getLinhaFormatada(linhaInteira);
    }

    
    p = buble_sort(p, tamanho, 0); // Organizando como mandante.
    linha *aux = p;
    while (aux->prox != NULL) {
        printf("%d\t%s\t%s\t%s\n", aux->id, aux->data, aux->mandante, aux->visitante);
        aux = aux->prox;
    }

    puts("\n");
    p = buble_sort(p, tamanho, 1); // Organizando como visitante.
    aux = p;
    while (aux->prox != NULL) {
        printf("%5d\t%s\t%20s\t%20s\n", aux->id, aux->data, aux->mandante, aux->visitante);
        aux = aux->prox;
    }

    fclose(fp);
    free(linhaInteira);
    free(p);
    free(aux);
    
    return 0;
}