#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct Pessoa{
    char data[100];
    char nome[100];
    char telefone[100];
    char email[100];
    float peso;
    float altura;
    float imc;
} Pessoa;

void Create(char CPF[]){
    Pessoa ps;
    FILE *file = fopen (CPF, "a+");

    if(!file){
        printf("Erro ao abrir!\n\n");
    }
    
    else{
        printf("Digite a data atual separados por '/':\n");
        scanf("%s", ps.data);

        printf("Digite o seu nome:\n");
        scanf("%s", ps.nome);

        printf("Digite o seu telefone:\n");
        scanf("%s", ps.telefone);

        printf("Digite seu e-mail:\n");
        scanf("%s", ps.email);

        printf("Digite seu peso:\n");
        scanf("%f", &ps.peso);

        printf("Digite sua altura:\n");
        scanf("%f", &ps.altura);

        ps.imc = ps.peso / (ps.altura * ps.altura);
        fprintf(file, "%s %s %s %s %f %f %f", ps.data, ps.nome, ps.telefone, ps.email, ps.peso, ps.altura, ps.imc);         
    }

    fclose(file);
}

void Read(char CPF[], char filename[]){
    Pessoa ps;
    FILE *file = fopen(CPF, "r");

    strcat(filename, ".txt");

    if(!file){
        printf("Erro ao abrir!\n\n");
    }

    else if(strcmp(CPF, filename) == 0){
        while(fscanf(file, "%s %s %s %s %f %f %f", ps.data, ps.nome, ps.telefone, ps.email, &ps.peso, &ps.altura, &ps.imc) != -1){
            printf("Data: %s\nNome: %s\nTelefone: %s\nE-mail: %s\nPeso: %.2f\nAltura: %.2f\nIMC: %.2f\n\n", ps.data, ps.nome, ps.telefone, ps.email, ps.peso, ps.altura, ps.imc);
        }
    }

    else{
        printf("CPF ainda nao cadastrado.\n\n");
    }

    fclose(file);
}

void Update(char filename[], char data[]){

    Pessoa ps;
    FILE *file = fopen(filename, "a+");
    FILE *file2 = fopen("tmp.txt", "w");

    if(!file){
        printf("Erro ao abrir!\n\n");
    }

    else{
        while(fscanf(file, "%s %s %s %s %f %f %f", ps.data, ps.nome, ps.telefone, ps.email, &ps.peso, &ps.altura, &ps.imc) != -1){
            if(strcmp(ps.data, data) != 0){
                fprintf(file2, "%s %s %s %s %f %f %f", ps.data, ps.nome, ps.telefone, ps.email, &ps.peso, &ps.altura, &ps.imc);
            }
        }
    }

    fclose(file);
    remove(filename);
    fclose(file2);
    rename("tmp.txt", filename);

    FILE *file3 = fopen(filename, "a+");

    if(!file3){
        printf("Erro ao abrir!\n\n");
    }

    else{
        printf("Digite a data atual separados por '/':\n");
        scanf("%s", ps.data);

        printf("Digite o seu nome:\n");
        scanf("%s", ps.nome);

        printf("Digite o seu telefone:\n");
        scanf("%s", ps.telefone);

        printf("Digite seu e-mail:\n");
        scanf("%s", ps.email);

        printf("Digite seu peso:\n");
        scanf("%f", &ps.peso);

        printf("Digite sua altura:\n");
        scanf("%f", &ps.altura);

        ps.imc = ps.peso / (ps.altura * ps.altura);
        fprintf(file3, "%s %s %s %s %f %f %f\n", ps.data, ps.nome, ps.telefone, ps.email, ps.peso, ps.altura, ps.imc);
    }
}

void Delete(char filename[], char data[]){
    Pessoa ps;
    FILE *file = fopen(filename, "a+");
    FILE *file2 = fopen("tmp.txt", "w");

    if(!file){
        printf("Erro ao abrir!\n\n");
    }

    else{
        while(fscanf(file, "%s %s %s %s %f %f %f", ps.data, ps.nome, ps.telefone, ps.email, &ps.peso, &ps.altura, &ps.imc) != -1){
            if(strcmp(ps.data, data) != 0){
                fprintf(file2, "%s %s %s %s %f %f %f", ps.data, ps.nome, ps.telefone, ps.email, &ps.peso, &ps.altura, &ps.imc);
            }
        }
    }

    fclose(file);
    remove(filename);
    fclose(file2);
    rename("tmp.txt", filename);
}

void Menu(){
    printf("OBS: SEMPRE QUE REALIZAR ALGUMA OPERACAO\nFECHE A EXECUCAO E COMECE DO 0 PARA EVITAR ERROS\n\n");
    printf("Digite 1 para cadastrar uma pessoa.\n");
    printf("Digite 2 para ler uma pessoa.\n");
    printf("Digite 3 para atualizar uma pessoa.\n");
    printf("Digite 4 para deletar uma pessoa.\n");
    printf("Digite 5 para sair.\n");
}

int main(void){
    Pessoa ps;
    int escolha;
    char cpf[14], nomeArquivo[20] = "", datadel[100];

    while(escolha != 5){
        Menu();
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                printf("Digite seu CPF:\n");
                scanf(" %s", cpf);

                //STRCAT para concatenar.
                strcat(nomeArquivo, cpf);
                strcat(nomeArquivo, ".txt");
                Create(nomeArquivo);

                break;
            case 2:
                printf("Digite seu CPF:\n");
                scanf(" %s", cpf);

                strcat(nomeArquivo, cpf);
                strcat(nomeArquivo, ".txt");
                Read(nomeArquivo, cpf);

                break;
            case 3:
                printf("Digite o CPF:\n");
                scanf("%s", cpf);

                printf("Digite a data antiga:\n");
                scanf("%s", datadel);

                strcat(nomeArquivo, cpf);
                strcat(nomeArquivo, ".txt");
                Update(nomeArquivo, datadel);

                break;
            case 4:
                printf("Digite o CPF:\n");
                scanf("%s", cpf);

                printf("Digite a data para exclusao:\n");
                scanf("%s", datadel);

                strcat(nomeArquivo, cpf);
                strcat(nomeArquivo, ".txt");
                Delete(nomeArquivo, datadel);

                break;
        }
    }
    
    return 0;
}