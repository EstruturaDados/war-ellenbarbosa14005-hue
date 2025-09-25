#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Estrutura do território.
 * nome: nome do território
 * cor: cor do exército que controla o território
 * tropas: número de tropas no território
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Protótipos ---
void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirMapa(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, char* missao);
void atribuirMissao(char** destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(char* missao);

// --- Funções auxiliares ---

// Cadastro de territórios com entrada do usuário
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
        getchar(); // Limpa o buffer do teclado
    }
}

// Exibe o estado atual do mapa, mostrando todos os territórios
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Numero de tropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque entre territórios
// Gera números aleatórios simulando dados (1-6)
void atacar(Territorio* atacante, Territorio* defensor) {
    // Validação: não pode atacar território amigo
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[!] O ataque nao pode ser feito: ambos sao do mesmo exercito!\n");
        return;
    }

    // Validação: atacante precisa ter mais de 1 tropa
    if (atacante->tropas <= 1) {
        printf("\n[!] O ataque nao pode ser feito: o atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    // Rolagem de dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- Batalha ---\n");
    printf("Atacante %s (%s) rola: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("Defensor %s (%s) rola: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    // Determina resultado da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("\n>> Vitoria do atacante!\n");
        strcpy(defensor->cor, atacante->cor); // transfere a cor do exército
        defensor->tropas = atacante->tropas / 2 + (atacante->tropas % 2); // metade das tropas para o defensor
        atacante->tropas = atacante->tropas / 2; // metade das tropas permanece no atacante
    } else {
        printf("\n>> Defesa bem-sucedida!\n");
        atacante->tropas--; // atacante perde uma tropa
    }
}

// Sorteia e atribui uma missão ao jogador usando memória dinâmica
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    *destino = (char*) malloc(strlen(missoes[indice]) + 1);
    strcpy(*destino, missoes[indice]);
}

// Verifica se a missão foi cumprida (lógica inicial simples)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "Elimine todas as tropas da cor vermelha")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
    if (strstr(missao, "Ter mais de 10 tropas em um unico territorio")) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 10)
                return 1;
        }
        return 0;
    }
    if (strstr(missao, "Possuir territorios de 3 cores diferentes")) {
        int coresDiferentes = 0;
        char cores[10][10];
        for (int i = 0; i < tamanho; i++) {
            int jaExiste = 0;
            for (int j = 0; j < coresDiferentes; j++) {
                if (strcmp(cores[j], mapa[i].cor) == 0) {
                    jaExiste = 1;
                    break;
                }
            }
            if (!jaExiste) {
                strcpy(cores[coresDiferentes], mapa[i].cor);
                coresDiferentes++;
            }
        }
        return coresDiferentes >= 3;
    }
    if (strstr(missao, "Ter apenas um territorio restante")) {
        int count = 0;
        for (int i = 0; i < tamanho; i++)
            if (mapa[i].tropas > 0)
                count++;
        return count == 1;
    }
    if (strstr(missao, "Conquistar 3 territorios seguidos")) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0)
                consecutivos++;
            else
                consecutivos = 0;
            if (consecutivos >= 3)
                return 1;
        }
        return 0;
    }
    return 0;
}

// Exibe a missão do jogador
void exibirMissao(char* missao) {
    printf("\n=== Sua Missao ===\n%s\n", missao);
}

// Libera memória alocada dinamicamente
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
    printf("\n[Memoria liberada com sucesso]\n");
}

// --- Função principal ---
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int qtd;
    printf("Digite o numero de territorios: ");
    scanf("%d", &qtd);
    getchar();

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, qtd);

    // Definição das missões
    char* missoesDisponiveis[] = {
        "Conquistar 3 territorios seguidos",
        "Elimine todas as tropas da cor vermelha",
        "Ter mais de 10 tropas em um unico territorio",
        "Possuir territorios de 3 cores diferentes",
        "Ter apenas um territorio restante"
    };

    // Atribuição de missão ao jogador
    char* missaoJogador = NULL;
    atribuirMissao(&missaoJogador, missoesDisponiveis, 5);
    exibirMissao(missaoJogador);

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

        // Verificação automática da missão
        if (verificarMissao(missaoJogador, mapa, qtd)) {
            printf("\n=== Missao cumprida! Voce venceu! ===\n");
            break;
        }

    } while (opcao != 0);

    // Liberação de memória
    liberarMemoria(mapa, missaoJogador);
    return 0;
}