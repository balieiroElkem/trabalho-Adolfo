#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>

typedef struct linha{
    int id;
    char rodada[21]; //Novo
    char data[11];
    char horario[6]; //Novo
    char dia[14]; //Novo
    char mandante[21];
    char visitante[21];
    char vencedor[21]; //Novo
    char arena[31]; //Novo
    int mandante_placar; //Novo
    int visitante_placar; //Novo
    char estado_mandante[3]; //Novo
    char estado_visitante[3]; //Novo
    char estado_vencedor[3]; //Novo
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
    linha temp; // variável temporária para formatar a String com a linha do arquivo.

    char *aux = strtok(l, ";"); // Quebra a string cada vez que encontrar um ';'
    for(int i = 0; i < 14; i++) {
        if(i == 0) {
            temp.id = atoi(aux);
        } else if(i == 1) {
				strcpy(temp.rodada, aux);
        } else if(i == 2) {
            strcpy(temp.data, aux);
        } else if(i == 3) {
			strcpy(temp.horario, aux);
		} else if(i == 4){
			strcpy(temp.dia, aux);
        } else if(i == 5) {
            strcpy(temp.mandante, aux);
        } else if(i == 6) {
            strcpy(temp.visitante, aux);
        } else if(i == 7) {
			strcpy(temp.vencedor, aux);
		} else if(i == 8) {
			strcpy(temp.arena, aux);
		} else if(i == 9) {
			temp.mandante_placar = atoi(aux);
		} else if(i == 10) {
			temp.visitante_placar = atoi(aux);
		} else if(i == 11) {
			strcpy(temp.estado_mandante, aux);
		} else if(i == 12) {
		    strcpy(temp.estado_visitante, aux);
		} /*else if(i == 13) {
			strcpy(temp.estado_vencedor, aux);
		}*/
        aux = strtok(NULL, ";");
    }
    
    return temp;
}


// Produz uma lista encadeade.
linha* lista(linha *p, linha l) {
    if (p == NULL) { // Verifica se p está vazio
        p = (linha *) malloc(sizeof(linha)); // caso esteja vazio, aloca a primeira variável
        if (!p) {
            printf("Erro ao alocar memoria na lista");
            exit(1);
        }

        // Atribui os valores da variável l para o novo no da lista.
        p->id = l.id;
        strcpy(p->rodada, l.rodada);
        strcpy(p->data, l.data);
        strcpy(p->horario, l.horario);
        strcpy(p->dia, l.dia);
        strcpy(p->mandante, l.mandante);
        strcpy(p->visitante, l.visitante);
        strcpy(p->vencedor, l.vencedor);
        strcpy(p->arena, l.arena);
        p->mandante_placar = l.mandante_placar;
        p->visitante_placar = l.visitante_placar;
        strcpy(p->estado_mandante, l.estado_mandante);
        strcpy(p->estado_visitante, l.estado_visitante);
        strcpy(p->estado_vencedor, l.estado_vencedor);
        p->prox = NULL;

    } else { // Caso p não esteja vazio, deve-se procurar o último no da lista
        linha *novo = (linha *) malloc(sizeof(linha)); // aloca um novo no para por na lista
        linha *tmp = p;

        while (tmp->prox != NULL) { // Aqui a variável tmp vai à caça do último no da lista
            tmp = tmp->prox;
        }

        tmp->prox = novo; // coloca o novo no na lista.
        tmp->prox->id = l.id;
        strcpy(tmp->prox->rodada, l.rodada);
        strcpy(tmp->prox->data, l.data);
        strcpy(tmp->prox->horario, l.horario);
        strcpy(tmp->prox->dia, l.dia);
        strcpy(tmp->prox->mandante, l.mandante);
        strcpy(tmp->prox->visitante, l.visitante);
        strcpy(tmp->prox->vencedor, l.vencedor);
        strcpy(tmp->prox->arena, l.arena);
        tmp->prox->mandante_placar = l.mandante_placar;
        tmp->prox->visitante_placar = l.visitante_placar;
        strcpy(tmp->prox->estado_mandante, l.estado_mandante);
        strcpy(tmp->prox->estado_visitante, l.estado_visitante);
        strcpy(tmp->prox->estado_vencedor, l.estado_vencedor);
        tmp->prox->prox = NULL; // atribui NULL para explicitar que este é agora o último no da lista
    }

    return p; // Retorna a lista devidamente melhorada
}


// Faz uma busca sequencial de uma palavra chave na lista.
int buscaSeq(linha *lista, char *chave) {
    linha *aux = lista;
    bool found = false;
    int quantJogos = 0;

    while (aux->prox != NULL) {
        if (strcmp(aux->mandante, chave) == 0) { // Se o valor de aux->mandante corresponde a chave, printa o resultado na tela
            printf("%4d %4s %6s %13s\t%s %20s\t%20s\t%20s\t%25s\t%2d %2d %2s %2s\n", aux->id, aux->rodada, aux->horario, aux->dia, aux->data, aux->mandante, aux->visitante, aux->vencedor, aux->arena, aux->mandante_placar, aux->visitante_placar, aux->estado_mandante, aux->estado_visitante);
            found = true;
            quantJogos++;
        }

        if (strcmp(aux->visitante, chave) == 0) { // Se o valor de aux->visitante corresponde a chave, printa o resultado na tela
            printf("%4d %4s %6s %13s\t%s %20s\t%20s\t%20s\t%25s\t%2d %2d %2s %2s\n", aux->id, aux->rodada, aux->horario, aux->dia, aux->data, aux->mandante, aux->visitante, aux->vencedor, aux->arena, aux->mandante_placar, aux->visitante_placar, aux->estado_mandante, aux->estado_visitante);
            found = true;
            quantJogos++;
        }
        
        aux = aux->prox;
    }

    if (!found) { // Verifica se foi encontrado algum valor correspontente a chave.
        printf("Não foi possível encontrar nenhum time com essa nome.\n");
    }

    return quantJogos;
}


int main(int argc, char **argv) {
    setlocale(LC_ALL, ""); // Tenta fazer o programa aceitar a lingua portuguesa.
    FILE *fp;
    char *linhaInteira;
    linha linhaFormatada, *p = NULL;
    int quantJogos = 0;

    if (argc != 2) {
        printf("Precisa do nome do time, camarada.\nNão pode executar assim.\n");
        return 1;
    }

    argv[1][0] = toupper(argv[1][0]); // transforma a primeira letra de da chave em maiuscula.

    fp = fopen("campeonato-brasileiro-full.csv", "r");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    lerLinha(fp); // Ler o cabeçalho
    linhaInteira = lerLinha(fp);
    linhaFormatada = getLinhaFormatada(linhaInteira);
    
    // range 4140 - 4899
    while (linhaFormatada.id <= 4899) { // Faz um busca pelo range necessário.
        if (linhaFormatada.id >= 4140) {
            p = lista(p, linhaFormatada);
        }
        linhaInteira = lerLinha(fp); // pega mais uma linha do arquivo
        linhaFormatada = getLinhaFormatada(linhaInteira); // formata a linha para comparar os valores.
    }

    // p = buble_sort(p, 0); // Organizando como mandante.
    printf("ID:  Rod:  Hora:\t  Dia:\t     Data:\t     Mandante:\t\t  Visitante:\t\t   Vencedor:\t\t\t   Arena:       PM PV EM EV\n");
    quantJogos = buscaSeq(p, argv[1]);
    printf("\nQuantidade de jogos = %d\n", quantJogos);


    fclose(fp);
    free(linhaInteira);
    free(p);
    
    return 0;
}