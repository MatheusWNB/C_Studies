#include "libs.h"

#define CAPACIDADE_MAX_ESTOQUE 50

int main(){
    int itens_estoque;

    printf("Quantos itens terão no estoque?: ");
    scanf("%d", &itens_estoque);
    
    int *p;
    p = (int *) malloc(itens_estoque * sizeof(int));

    if (p == NULL){
        printf("malloc falhou\n");
        return 1;
    }

    int espacos_usados = 0;
    
    for (int i = 0; i < CAPACIDADE_MAX_ESTOQUE; i++){
        printf("Digite um valor: ");
        scanf("%d", &p[i]);
        espacos_usados++;
        putchar('\n');

        if (espacos_usados == CAPACIDADE_MAX_ESTOQUE){
            printf("Limite de itens no estoque foi atingido!\n");
            printf("Aperte 'ENTER' para continuar!\n");
            getchar();
            getchar();
            break;
        }

        if (i == itens_estoque - 1){
            int adicionar;
            int resposta;
            printf("Limite de itens alcançado, deseja colocar mais?: ");
            scanf("%d", &resposta);   
            
            if (resposta == 0){
                printf("Quantos itens deseja adicionar?: ");
                scanf("%d", &adicionar);

                itens_estoque += adicionar;
                int *try_realloc = realloc(p, itens_estoque * sizeof(int));

                if(try_realloc == NULL){
                    printf("Realloc falhou\n");
                    free(p);
                    return 1;
                }

                p = try_realloc;

                printf("Quantidade de itens aumentada!\n\n");

            } else if (resposta == 1) {
                break;
            }

            
        }

        
    }
    
    system("clear");

    for (int i = 0; i < itens_estoque; i++){
        printf("Item %d -> %d\n", i, p[i]);
    }
    
    free(p);
    return 0;

}
