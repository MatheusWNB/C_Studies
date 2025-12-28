#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/dir.h>

//Variaveis globais uteis
int validacao_listas; //Valida a ação dentro da função
int arquivo_materias_aberto_fechado = 1;//Arquivo aberto (0) e arquivo fechado (1)
int arquivo_alunos_aberto_fechado = 1;

//Struct Para registro dos alunos
struct registro {
    char alunos[20];
    char materias[20];
    float notas[5];
};

//Função para limpar o buffer da entrada padrão
void clearStdinBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

//Limpa a quebra de linha do fgets
void limpar_quebra_linha(char nome[20]){
    nome[strcspn(nome, "\n")] = '\0';
}

//Função pra fechar o arquivo
void fechar_arquivo(FILE *arquivo1, FILE *arquivo2){
    if (arquivo_materias_aberto_fechado == 0)
        fclose(arquivo1);

    if (arquivo_alunos_aberto_fechado == 0)
        fclose(arquivo2);
}

//Função para listar os itens de uma struct
void abrir_arquivo(FILE *arquivo){
    if (validacao_listas == 0)
        system("open /home/matheuswnb/pasta/materias.txt");

    else if (validacao_listas == 1)
        system("open /home/matheuswnb/pasta/alunos.txt");
    
}
void mostrar_listas(int opcao_do_menu, struct registro cadastro[5], FILE *arquivo){ 
        
        if (opcao_do_menu == 1 || opcao_do_menu == 3)
            abrir_arquivo(arquivo);
    
        for(int i = 0; i < 5; i++){

            if (validacao_listas == 0)
                printf("%d -> %s\n", i, cadastro[i].materias);

            else if (validacao_listas == 1)
                printf("%d -> %s\n", i, cadastro[i].alunos);
        }
}

void cadastrar_na_struct(int opcao_do_menu, struct registro cadastro[5], FILE *arquivo){
    int indice;
    system("clear");

    if (opcao_do_menu == 0){
        arquivo = fopen("/home/matheuswnb/pasta/materias.txt", "w");
        arquivo_alunos_aberto_fechado = 0;
        fprintf(arquivo, "Essas são as suas matérias cadastradas:\n");

        for (indice = 0; indice < 5; indice++){
            printf("Digite aqui o item a cadastrar: ");
            fgets(cadastro[indice].materias, sizeof(cadastro[indice].materias), stdin);
            limpar_quebra_linha(cadastro[indice].materias);

            printf("Matéria '%d: %s' cadastrada com sucesso!\n", indice, cadastro[indice].materias);

            fprintf(arquivo, "%d -> %s\n", indice, cadastro[indice].materias);
            fprintf(arquivo, "---------\n");

            system("clear");

        }

        arquivo_materias_aberto_fechado = 1;

    } else if (opcao_do_menu == 2){
        arquivo = fopen("/home/matheuswnb/pasta/alunos.txt", "w");
        arquivo_alunos_aberto_fechado = 0;
        fprintf(arquivo, "Esses são os seus alunos cadastrados:\n");

        for (indice = 0; indice < 5; indice++){
            printf("Digite aqui o item a cadastrar: ");
            fgets(cadastro[indice].alunos, sizeof(cadastro[indice].alunos), stdin);
            limpar_quebra_linha(cadastro[indice].alunos);

            printf("Matéria '%d: %s' cadastrada com sucesso!\n", indice, cadastro[indice].alunos);

            fprintf(arquivo, "%d -> %s\n", indice, cadastro[indice].alunos);
            fprintf(arquivo, "---------\n");

            system("clear");
        }

        arquivo_alunos_aberto_fechado = 1;

    }

    fclose(arquivo);

}

int main(){
    struct registro cadastro[5];

    //Criação do arquivo para salvar o registro dos alunos
    if (opendir("/home/matheuswnb/pasta")){
        DIR *pasta_ponteiro = opendir("/home/matheuswnb/pasta");
        printf("Arquivo existe.\n");
        closedir(pasta_ponteiro);

    } else {
        printf("Criando diretório...\n");
        system("mkdir /home/matheuswnb/pasta");
    }

    FILE *alunos;
    FILE *materias;
    FILE *notas;

    printf("Seja bem-vindo, escolha uma opção abaixo: \n");
    
    int validacao_while_principal = 0;//Valida a ação do while principal
    while(validacao_while_principal == 0){
        printf(
            "0-> Cadastro de matérias\n"
            "1-> Visualizar matérias cadastradas\n"
            "2-> Cadastrar alunos\n"
            "3-> Visualizar alunos cadastrados\n"
        );
        int escolha_de_opcao_menu;
        printf("Escolha sua opção: ");
        scanf("%d", &escolha_de_opcao_menu);
        clearStdinBuffer();
        
        switch(escolha_de_opcao_menu){
            case 0:
                cadastrar_na_struct(escolha_de_opcao_menu, cadastro, materias);
                break;
            
            case 1:
                printf("Essas são suas matérias cadastradas:\n");

                validacao_listas = 0;
                mostrar_listas(escolha_de_opcao_menu, cadastro, materias);
                arquivo_materias_aberto_fechado = 1;

                break;

            case 2:
                cadastrar_na_struct(escolha_de_opcao_menu, cadastro, alunos);
                break;

            case 3:
                printf("Esses são os alunos cadastrados: \n");
                validacao_listas = 1;
                mostrar_listas(escolha_de_opcao_menu, cadastro, alunos);
                arquivo_alunos_aberto_fechado = 1;

                break;

            case 4:

            case 5:
                validacao_while_principal = 1;
                fechar_arquivo(materias, alunos);
                printf("Saindo do aplicativo...");
        };
    }

    return 0;
}   