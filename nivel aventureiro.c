#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Funções auxiliares ---
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consome o \n do scanf
    }
}

void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Numero de tropas: %d\n", mapa[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[!] O ataque nao pode ser feito: ambos sao do mesmo exercito!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n[!] O ataque nao pode ser feito: o atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1; // 1 a 6
    int dadoDefensor = (rand() % 6) + 1; // 1 a 6

    printf("\n--- Batalha ---\n");
    printf("Atacante %s (%s) rola: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("Defensor %s (%s) rola: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n>> Vitoria do atacante!\n");
        strcpy(defensor->cor, atacante->cor); // defensor muda de dono
        defensor->tropas = atacante->tropas / 2; // transfere metade das tropas
        atacante->tropas = atacante->tropas / 2; // atacante perde metade também
    } else {
        printf("\n>> Defesa bem-sucedida!\n");
        atacante->tropas--; // atacante perde 1 tropa
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\n[Memoria liberada com sucesso]\n");
}

// --- Programa principal ---
int main() {
    srand(time(NULL)); // garante aleatoriedade

    int qtd;
    printf("Digite o numero de territorios: ");
    scanf("%d", &qtd);
    getchar();

    // Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, qtd);

    int opcao;
    do {
        printf("\n=== Menu ===\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            exibirMapa(mapa, qtd);
        } else if (opcao == 2) {
            int a, d;
            exibirMapa(mapa, qtd);
            printf("\nEscolha o territorio atacante (1-%d): ", qtd);
            scanf("%d", &a);
            printf("Escolha o territorio defensor (1-%d): ", qtd);
            scanf("%d", &d);
            getchar();

            if (a >= 1 && a <= qtd && d >= 1 && d <= qtd) {
                atacar(&mapa[a - 1], &mapa[d - 1]);
            } else {
                printf("\n[!] Escolha invalida!\n");
            }
        }
    } while (opcao != 0);

    // Liberação da memória
    liberarMemoria(mapa);
    return 0;
}