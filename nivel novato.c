#include <stdio.h>
#include <string.h>


//Definição da strucct Territorio
// Onde  que vai ficar guardada as informações de um território
//Nome do território, cor e quantidade de tropas
typedef struct {
    char nome[20];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[5]; // vetor para armazenar os 5 territórios

    printf("=== Cadastro Inicial dos Territorios ===\n");

    // Cadastro dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);

        // Nome do território (limita 19 caracteres)
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 20, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove \n

        // Cor do exercito (limitaa 9 caracteres)
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; 

        // Quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        getchar(); // consome o \n que ficou no buffer do scanf
    }

    // Exibição dos dados
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Numero de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}