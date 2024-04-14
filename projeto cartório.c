// bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

// variáveis gerais do sistema
char registered_id[15] = "";
bool onreg = false;

int registro() // função de registro de usuário
{   
    setlocale(LC_ALL, "Portuguese"); // aplicando português como linguagem, para o uso de acentuação correta.
    
    // variáveis do sistema
    char arquivo[15];
    char cpf[15];
    char nome[40];
    char sobrenome[40];
    char cargo[40];
    int ifcon = 0;
    // fim das variáveis do sistema
    
    // inicio da lógica de registro
    printf("\t##### Registro de usuário #####\n\n");
    printf("\tDigite o CPF para continuar, 'N' para Sair.\n\n");
    
    if (onreg!=true){
        printf("CPF: ");
        scanf("%s", &cpf);
        strcpy(arquivo, cpf);
    }else{
        strcpy(arquivo, registered_id);
        strcpy(arquivo, "");
        onreg=false;
    }
    if (strcmp(arquivo, "N")==0 || strcmp(arquivo, "n")==0){
       printf("Voltando ao menu principal...\n");
       system("pause");
    }else{
        FILE *file;
        FILE *iop = fopen(arquivo, "r");
        if (iop!=NULL){
           fclose(iop);
           printf("Esse registro já existe, Deseja Consultar o CPF?\n");
           printf("\t1 - Sim.\n"); printf("\t2 - Não.\n\nOpção:");
           scanf("%d", &ifcon);
           
           if (ifcon==1){
               strcpy(registered_id, cpf);
               onreg = true;
               system("cls");
               consulta();
           }else{
               strcpy(registered_id, "");
               system("cls");
               printf("Voltando ao menu principal...\n");
               system("pause");
           }
    
        } else {
            file = fopen(arquivo, "w");
            fprintf(file, "CPF: ");
            fprintf(file, cpf);
            fclose(file);
            
            file = fopen(arquivo, "a");
            fprintf(file, "\nNome: ");
            fclose(file);
            
            printf("Digite o Nome: ");
            scanf("%s", &nome);
            file = fopen(arquivo, "a");
            fprintf(file, nome);
            fclose(file);
            
            file = fopen(arquivo, "a");
            fprintf(file, "\nSobrenome: ");
            fclose(file);
            
            printf("Digite o Sobrenome: ");
            scanf("%s", &sobrenome);
            file = fopen(arquivo, "a");
            fprintf(file, sobrenome);
            fclose(file);
            
            file = fopen(arquivo, "a");
            fprintf(file, "\nCargo: ");
            fclose(file);
            
            printf("Digite o Cargo: ");
            scanf("%s", &cargo);
            file = fopen(arquivo, "a");
            fprintf(file, cargo);
            fclose(file);
            system("pause");
        }
    }
    // fim da lógica de registro
}

int consulta() // função de consulta de usuário
{
    setlocale(LC_ALL, "Portuguese");
    int retr = 0;
    char conteudo[200];
    char cpf[15];
    
    // inicio da lógica de consulta
    printf("\t##### Consulta de usuário #####\n");
    
    
    if(onreg!=true){
        printf("\tDigite o CPF para continuar, 'N' para Sair.\n\n");
        printf("CPF: ");
        onreg = false;
        scanf("%s", &cpf);
        if (strcmp(cpf, "N")==0 || strcmp(cpf, "n")==0){
           printf("Voltando ao menu principal...\n");
           strcpy(cpf, "");
           system("pause");
        }else{
            FILE *file = fopen(cpf, "r");
            if (file==NULL){
               printf("Não foi prossível encontrar o usuário. Deseja Registrar?\n");
               printf("\t1 - Sim.\n"); printf("\t2 - Não.\n\nOpção:");
               scanf("%d", &retr);
               if(retr==1){
                   strcpy(registered_id, cpf);
                   onreg=true;
                   system("cls");
                   registro();
               }else{
                   system("cls");
                   printf("Voltando ao menu principal...\n");
                   fclose(file);
                   system("pause");
               }
               
            }else{
                printf("Informações do Usuário:\n\n");
                while(fgets(conteudo, 200, file) != NULL){
                    printf("%s", &conteudo);  
                }
                fclose(file);
                printf("\n\n");  
                system("pause");
            }
        }
    }else{
        printf("Consultando o CPF: %s\n\n", registered_id);
        strcpy(cpf, registered_id);
        printf("Informações do Usuário:\n\n");
        FILE *file = fopen(cpf, "r");
        while(fgets(cpf, 200, file) != NULL){
            printf("%s", &cpf);  
        }
        printf("\n\n");  
        system("pause");
        strcpy(registered_id, "");
        onreg = false;
    }
    // fim da lógica de consulta
}

int deletar()// função de deletar usuário
{
    setlocale(LC_ALL, "Portuguese");
    char nome[200];
    char conteudo[200];
    char cpf[15];
    int ifdel = 0;
    
    // inicio da lógica de deletar
    printf("\t##### Exclusão de usuário #####\n");
    printf("\tDigite o CPF para continuar, 'N' para Sair.\n\n");
    
    printf("Digite o CPF: ");
    scanf("%s", &cpf);
    if (strcmp(cpf, "N")==0 || strcmp(cpf, "n")==0){
        printf("Voltando ao menu principal...\n");
        strcpy(cpf, "");
        system("pause");
    }else{
        FILE *todel = fopen(cpf, "r");
        
        if (todel != NULL){
            system("cls");
            printf("Deseja deletar o registro %s?\n\n", cpf);
            printf("\t1 - Sim.\n"); printf("\t2 - Não.\n\nOpção:");
            
            printf("Informações do Usuário:\n");
            while(fgets(conteudo, 200, todel) != NULL){
                printf("%s", &conteudo);  
            }
            printf("\n\n:");  
            fclose(todel);
            
            scanf("%d", &ifdel);
            if(ifdel==1){
                system("cls");
                remove(cpf);
                printf("Registro %s deletado.\n", cpf);
                system("pause");
            }else{
                system("cls");
                printf("Voltando ao menu principal...\n");
                system("pause");
            }
        }else{
            printf("O registro %s não foi encontrado, deseja tentar novamente?\n", cpf);
            printf("\t1 - Sim.\n"); printf("\t2 - Não.\n\nOpção:");
            scanf("%d", &ifdel);
            if(ifdel==1){
                system("cls");
                deletar();
            }else{
                system("cls");
                printf("Voltando ao menu principal...\n");
                system("pause");
            }
        }
    }
    // fim da lógica de deletar
}

int main() // função principal do sistema
{
    int opcao = 0;
    int laco = 1;

    for(laco=1; laco=1;){ // laço que permite a constancia na repetecição, até ser quebrado.
        system("cls");
        
        // apresentação do sistema e opções
        setlocale(LC_ALL, "Portuguese");
        printf("\t###### Cartório do Markus ######\n\n");
        printf("Por favor, selecione abaixo a opção desejada:\n\n");
        printf("\t1 - Adicionar Nome\n");
        printf("\t2 - Consultar Nome\n");
        printf("\t3 - Deletar Nome\n");
        printf("\nOpção:");
        
        scanf("%d", &opcao);
        
        system("cls");
        
        if (opcao==4){
           break;
        }
        
        // sistema de escolha das opções do sistema
        
        switch (opcao) { // função de condição otimizada
            case 1:
                registro();
                break;
            case 2:
                consulta();
                break;
            case 3:
                deletar();
                break;
            default:
                printf("Opção selecionada nao disponível!\n");
                system("pause");
                break;
        }
    }
}
