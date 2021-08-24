#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

typedef struct linha{
    int id;
    char data[11];
    char mandante[21];
    char visitante[21];
    struct linha *prox;
} linha;


// Ler uma linha de um arquivo e retorna essa mesma linha.
// Tem um buffer que adptar o tamanho para caber apenas a linha em questão.
char* lerLinha(FILE *p) {
    char c;
    int count = 1;

    char *s = (char *) malloc(sizeof(char)*count); // aloca um espaço na memória de tamamho char

    while ((c = fgetc(p)) != EOF && c != '\n') { // Verifica se chegou ao final do arquivo ou se chegou o final da linha
        *(s+(count-1)) = c; // coloca no espaço alocado anteriormente o caracter retirado do arquivo.
        count++;
        s = realloc(s, count*sizeof(char)); // Remaneja o espaço alocada anteriormente para caber mais um espaço na memória
    }
    *(s+(count-1)) = '\0'; // com todos os caracteres da linha já retirada. Coloca-se um '\0' para indicar um fim de String

    return s; // retorna a string com a linha retirada do arquivo.
}


// Formata a linha pra obter os valores necessários para a struct linha
linha getLinhaFormatada(char *l) {
    linha temp; // varável temporária para formatar a String com a linha do arquivo.

    char *aux = strtok(l, ";"); // Quebra a string cada vez que encontrar um ';'
    for(int i = 0; i < 7; i++) {
        if(i == 0) {
            temp.id = atoi(aux);
        } else if(i == 2) {
            strcpy(temp.data, aux);
        } else if(i == 5) {
            strcpy(temp.mandante, aux);
        } else if(i == 6) {
            strcpy(temp.visitante, aux);
        }
        aux = strtok(NULL, ";");
    }
    return temp;
}


// Produz uma lista encadeade.
linha* lista(linha *p, linha l) {
    if (p == NULL) { // Verifica se p está fazio
        p = (linha *) malloc(sizeof(linha)); // caso esteja vazio, aloca a primeira variável
        if (!p) {
            printf("Erro ao alocar memoria na lista");
            exit(1);
        }

        // Atribui os valores da variável l para o novo no da lista.
        p->id = l.id;
        strcpy(p->data, l.data);
        strcpy(p->mandante, l.mandante);
        strcpy(p->visitante, l.visitante);
        p->prox = NULL;

    } else { // Coso p não esteja vazio, deve-se procurar a última no da lista
        linha *novo = (linha *) malloc(sizeof(linha)); // aloca um novo no para por na lista
        linha *tmp = p;

        while (tmp->prox != NULL) { // Aqui a variável tmp vai à caça do último no da lista
            tmp = tmp->prox;
        }

        tmp->prox = novo; // coloca o novo no na lista.
        tmp->prox->id = l.id;
        strcpy(tmp->prox->data, l.data);
        strcpy(tmp->prox->mandante, l.mandante);
        strcpy(tmp->prox->visitante, l.visitante);
        tmp->prox->prox = NULL; // atribui NULL para explicitar que este é agora o último no da lista
    }

    return p; // Retorna a lista devidamente melhorada
}


// Organiza a lista. 0 para organizar pelos times mandantes. 1 para organizar pelos times visitantes.
// A lista é reorganizada seguindo o alfabeto.
linha* buble_sort(linha *lista, int op) {
    linha tmp;
    linha *aux = lista;
    linha *aux2 = aux->prox;

    switch (op) {
        case 0: // Organizando como mandante
            while (aux->prox != NULL) { // Primeiro loop para controlar os nos da lista que devem ser alterados
            
                aux2 = aux->prox; // variável para comparar qual no deve ser alterado.

                while (aux2->prox != NULL) {
                    if (strcmp(aux->mandante, aux2->mandante) > 0) { // caso o valor de aux->mandante seja mais alto que aux2->mandante, é feita a troca.
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
            while (aux->prox != NULL) { // Primeiro loop para controlar os nos da lista que devem ser alterados

                aux2 = aux->prox; // variável para comparar qual no deve ser alterado.

                while (aux2->prox != NULL) {
                    if (strcmp(aux->visitante, aux2->visitante) > 0) { // caso o valor de aux->visitante seja mais alto que aux2->visitante, é feita a troca.
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
        default: // Caso aplica algum valor errado é devolvido a mensagem de alerta.
            printf("Ta doido misera.\n");
    }
    
   

    return lista; // Retorna a lista reorganizada
}


// Faz uma busca sequencial de uma palavra chave na lista.
void buscaSeq(linha *lista, char *chave) {
    linha *aux = lista;
    bool found = false;

    while (aux->prox != NULL) {
        if (strcmp(aux->mandante, chave) == 0) { // Se o valor de aux->mandante corresponde a chave, printa o resultado na tela
            printf("%5d\t%s\t%20s\t%20s\n", aux->id, aux->data, aux->mandante, aux->visitante);
            found = true;
        }

        if (strcmp(aux->visitante, chave) == 0) { // Se o valor de aux->visitante corresponde a chave, printa o resultado na tela
            printf("%5d\t%s\t%20s\t%20s\n", aux->id, aux->data, aux->mandante, aux->visitante);
            found = true;
        }
        
        aux = aux->prox;
    }

    if (!found) { // Verifica se foi encontrado algum valor correspontente a chave.
        printf("Não foi possível encontrar nenhum time com essa nome.\n");
    }
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Portuguese"); // Tenta fazer o programa aceitar a lingua portuguesa.
    FILE *fp;
    char *linhaInteira;
    linha linhaFormatada, *p = NULL;
    int tamanho = 0;

    if (argc != 2) {
        printf("Precisa do nome do time, camarada.\n");
        return 1;
    }

    argv[1][0] = toupper(argv[1][0]); // transforma a primeira letra de da chave em maiuscula.

    fp = fopen("campeonato-brasileiro-full.csv", "r");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    lerLinha(fp);
    linhaInteira = lerLinha(fp);
    linhaFormatada = getLinhaFormatada(linhaInteira);
    
    // range 4140 - 4899
    while (linhaFormatada.id <= 4899) { // Faz um busca pelo range necessário.
        if (linhaFormatada.id >= 4140) {
            p = lista(p, linhaFormatada);
            tamanho++;
        }
        linhaInteira = lerLinha(fp); // pega mais uma linha do arquivo
        linhaFormatada = getLinhaFormatada(linhaInteira); // formata a linha para comparar os valores.
    }

    
    p = buble_sort(p, 0); // Organizando como mandante.
    buscaSeq(p, argv[1]);


    fclose(fp);
    free(linhaInteira);
    free(p);
    
    return 0;
}