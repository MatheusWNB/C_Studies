#include "libs.h"
#include "string.h"

void clearStdinBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void imprime_array (int **p_p, int linhas, int colunas){
    for (int i = 0; i < linhas; i++){
        printf("Linha atual -> %d\n", i);

        for (int c = 0; c < colunas; c++)
            printf("Conteúdo do array [%d][%d] -> %d\n", i, c, p_p[i][c]);

        putchar('\n');
    }

}

int main(){
    int linhas;
    int colunas;
    int **p_p = NULL;

    printf("Quantas linhas e colunas serão necessárias?\n");

    printf("Linhas: ");
    scanf("%d", &linhas);

    printf("Colunas: ");
    scanf("%d", &colunas);

    p_p = (int **) malloc(linhas * sizeof(int *));
    
    int l, c;

    for (int l = 0; l < linhas ; l++){
        p_p[l] = (int *) malloc(colunas * linhas * sizeof(int));

        for (c = 0; c < colunas; c++)
            p_p[l][c] = 0;

    }

    system("clear");

    imprime_array(p_p, linhas, colunas);

    while (true){
        char resposta[3];
        printf("Deseja alterar algum item? (s/n)");
        printf("Sua resposta: ");
        clearStdinBuffer();
        fgets(resposta, 3, stdin);
        
        if (strlen(resposta) > 1){
            system("clear");
            imprime_array(p_p, linhas, colunas);
            printf("Resposta muito grande. Por favor tente novamente!\n");
            continue;
        }

        if (strncmp("s", resposta, 1) == 0){
            int linha;
            int coluna;

            printf("Digite a linha e a coluna do item a ser alterado: \n");
            printf("Linha: ");
            scanf("%d", &linha);

            printf("Coluna: ");
            scanf("%d", &coluna);

            system("clear");
            printf("Conteúdo de [%d][%d] -> %d\n", linha, coluna, p_p[linha][coluna]);

            int adicionar_item;
            printf("Oque deseja adicionar?: \n");
            printf("Item a ser adicionado: ");
            scanf("%d", &adicionar_item);

            int item_removido = p_p[linha][coluna];
            p_p[linha][coluna] = adicionar_item;

            system("clear");

            printf(
                "Alteração registrada:\n" 
                "item removido: %d\n"
                "Item adicionado: %d\n", item_removido, p_p[linha][coluna]
            );

            printf("---------------------------------------------\n");
            putchar('\n');
            printf("Esta é a sua lista atualizada: \n");

            imprime_array(p_p, linhas, colunas);

        } else if (strncmp("n", resposta, 1)){
            system("clear");
            printf("Finalizando aplicativo...\n");
            break;
        } else {
            system("clear");
            imprime_array(p_p, linhas, colunas);
            printf("Por favor, digite uma opção válida!");
            continue;
        }
    }

    for (l = 0; l < linhas; l++)
        free(p_p[l]);

    free(p_p);
    p_p = NULL;

}