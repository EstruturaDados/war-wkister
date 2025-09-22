// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIOS 5  // Definição do número máximo de países
#define MAX_MISSOES 5      // Definição do número máximo de missões
#define MAX_JOGADORES 3   // Definição do número máximo de jogadores
#define TAM_STRING 30     // Definição do tamanho máximo das strings

// Define o vetor de cores disponíveis para os jogadores
const char *cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto", "Branco"};

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
// Definição da Estrutura do Território do Jogo

// Definição da estrutura para os territórios/países
// definindo o nome, a cor predominante e a quantidade de tropas do território
struct Territorio {
    char nome[TAM_STRING]; // Nome do território
    char cor[10]; // Cor dominante do território
    int tropas; // Número de tropas no território
};

// Definição do vetor País, para os países, do tipo struct Territorio
struct Territorio *Pais;

// Definição da estrutura para os jogadores
// definindo a cor do exército e a missão secreta do jogador
struct Jogador {
    char cor[10]; // Cor do exército do jogador
    char missao[TAM_STRING]; // Missão secreta do jogador
};

// Definição do vetor Jogaador, paraa os jogadores, do tipo struct Jogador
struct Jogador *Jogadores;

// Definição da estrutura para as missões
// definindo o nome, o cumprimento e a descrição da missão
struct Missao {
    int codigo; // Número da missão
    int cumprida; // 1 - Sim e 0 - Não
    char descricao[TAM_STRING]; // Descrição da missão
};

// Definiçãoa do vetor Missões, para as missões, do tipo struct Missao
// struct Missao *Missoes;

// Definição das missões disponíveis para o jogo
const struct Missao Missoes[] = {
    {1, 0, "Destruir o exército Branco. Caso não exista ou é sua própria cor, conquistar 5 territórios"},
    {2, 0, "Destruir o exército Preto. Caso não exista ou é sua própria cor, conquistar 5 territórios"},
    {3, 0, "Destruir o exército Verde. Caso não exista ou é sua própria cor, conquistar 5 territórios"},
    {4, 0, "Destruir o exército Azul. Caso não exista ou é sua própria cor, conquistar 5 territórios"},
    {5, 0, "Destruir o exército Amarelo. Caso não exista ou é sua própria cor, conquistar 5 territórios"},
    {6, 0, "Destruir o exército Vermelho. Caso não exista ou é sua própria cor, conquistar 5 territórios"},
    {7, 0, "Conquistar 3 territórios"},
    {8, 0, "Conquistar 4 territórios"},
    {9, 0, "Conquistar 5 territórios"}
};

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
struct Territorio *alocarMemoriaMapa(); // Função para alocar dinamicamente o mapa do mundo
void liberarMemoria(); // Função para liberar a memória alocada para o mapa

// Funções de interface com o usuário:
void cadastroTerritorios(); // Função de inicialização (cadastro) dos países
void atacar(struct Territorio* ataque, struct Territorio* defesa); // Função para realizar um ataque entre dois países
void ordenarDados(int* dados, int n); // Função auxiliar para ordenar os dados
void mostrarMapa(const struct Territorio* mapa, int totalTerritorios); // Função para mostrar o mapa atual
void definirAtaqueDefesa(struct Territorio *paisAtaque, struct Territorio *paisDefesa); // Função para definir os países de ataque e defesa
void exibirMenuPrincipal(); // Função para exibir o menu principal

// Funções de lógica principal do jogo:
// Função utilitária:
void limparBufferEntrada(); // Função para limpar o buffer de entrada

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    //(Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.

    //Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    Pais = alocarMemoriaMapa();

    if (Pais == NULL){
        printf("Erro na alocação de memória para o mapa.\n");
        return 1;
    }

    // - Define a cor do jogador e sorteia sua missão secreta.


    // 1. Configuração Inicial
    printf("========================================\n");
    printf("======       WAR ESTRUTURADO      ======\n");
    printf("========================================\n\n");

    // Cadastro dos territórios
    // Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    cadastroTerritorios();

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // Variável de opção do menu
    int opcao;

    do {
        // Exibe o menu principal
        exibirMenuPrincipal();

        // Solicita a escolha do jogador
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                // Inicia a fase de ataque
                // Exibe o mapa atual
                mostrarMapa(Pais, MAX_TERRITORIOS);

                // Define os países envolvidos
                struct Territorio *paisAtaque;
                struct Territorio *paisDefesa;

                definirAtaqueDefesa(paisAtaque, paisDefesa);

                // Chama a função de ataque
                atacar(paisAtaque, paisDefesa);

                // Mostra o mapa após o ataque
                mostrarMapa(Pais, MAX_TERRITORIOS);

                break;

            case 2:
                // Verifica se a missão foi cumprida
                // Informa o jogador sobre o status da missão
                break;

            case 0:
                // Sai do jogo
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        // Pausa para que o jogador possa ler os resultados antes da próxima rodada
        if (opcao != 0) {
            printf("Pressione Enter para continuar...");
            getchar();
        }

    } while (opcao != 0); // Continua até o jogador escolher sair

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    liberarMemoria();

    printf("Programa encerrado.\n");

    return 0;
}

// ---------------------------------
// --- Implementação das Funções ---
// ---------------------------------
/**
 * @brief Função para alocar memória para os jogadores
 * @note Aloca dinamicamente a memória para o vetor de jogadores usando calloc
 * @return Ponteiro para o array de jogadores alocado
 */
struct Jogador *alocarMemoriaJogadores() {
    // Aloca dinamicamente a memória para o vetor de jogadores usando calloc
    struct Jogador *ptr = (struct Jogador *) calloc(2, sizeof(struct Jogador));
    // Retorna o ponteiro para a memória alocada ou NULL em caso de falha
    return ptr;
}

// /**
//  * @brief Função para alocar memória para as missões
//  * @note Aloca dinamicamente a memória para o vetor de missões usando calloc
//  * @return Ponteiro para o array de missões alocado
//  */
// struct Missao *alocarMemoriaMissoes() {
//     // Aloca dinamicamente a memória para o vetor de missões usando calloc
//     struct Missao *ptr = (struct Missao *) calloc(MAX_MISSOES, sizeof(struct Missao));
//     // Retorna o ponteiro para a memória alocada ou NULL em caso de falha
//     return ptr;
// }

/**
 * @brief Função para cadastrar os jogadores
 * @note Preenche os dados iniciais de cada jogador (cor do exército, missão secreta).
 */
void cadastroJogadores(struct Jogador *Jogadores, const struct Missao *Missoes){
    // Definição da função para cadastro dos jogadores

    // Pergunta pelo número de jogadores
    int numJogadores;
    do {
        printf("Digite o número de jogadores (1 a %d): ", MAX_JOGADORES);
        scanf("%d", &numJogadores);
        limparBufferEntrada();
    } while (numJogadores < 1 || numJogadores > MAX_JOGADORES);

    // Entrada dos dados de cada jogador
    printf("+-------------------------------+\n");
    printf("|   CADASTRO DOS %d JOGADORES    |\n", numJogadores);
    printf("+-------------------------------+");

    for(int i=0; i < numJogadores; i++){
        printf("\n--- Jogador no. %d ---\n", i + 1);
        printf("Entre com a cor do exército (Vermelho, Azul, Verde, Amarelo, Preto, Branco): ");
        scanf("%s", Jogadores[i].cor);
        limparBufferEntrada();
        // Sorteia uma missão aleatória para o jogador
        int missaoSorteada = rand() % MAX_MISSOES;
        strcpy(Jogadores[i].missao, Missoes[missaoSorteada].codigo);
        printf("Missão sorteada: %s\n", Jogadores[i].missao);
    }
/**
 * @brief Função para definir o nome dos países ataaque e defesa
 */
void definirAtaqueDefesa(struct Territorio *paisAtaque, struct Territorio *paisDefesa){
    // Definir nomes dos países de atque e defesa
    char nomePaisAtaque[30];
    char nomePaisDefesa[30];

    // Solicita os territórios de origem
    printf("Digite o nome do país atacante: ");
    scanf("%s", nomePaisAtaque);
    limparBufferEntrada();

    // Socilita o território a ser atacado
    printf("Digite o nome do território defensor: ");
    scanf("%s", nomePaisDefesa);
    limparBufferEntrada();

    for(int i=0; i < MAX_TERRITORIOS; i++){
        if (strcmp(Pais[i].nome, nomePaisAtaque) == 0){
            paisAtaque = &Pais[i];
        } else if (strcmp(Pais[i].nome, nomePaisDefesa) == 0){
            paisDefesa = &Pais[i];
        }
    }

    // Verifica se as entradas dos países foram corretas
    if (strcmp(paisAtaque->nome, nomePaisAtaque) != 0 && strcmp(paisDefesa->nome, nomePaisDefesa) != 0){
        printf("Território não encontrado. Tente novamente.\n");
    }
}

/**
 * @brief Função para alocar dinamicamente o mapa do mundo
 * @return Ponteiro para o array de territórios alocado
 */

struct Territorio *alocarMemoriaMapa() {
    // Aloca dinamicamente a memória para o vetor de territórios usando calloc
    struct Territorio *ptr = (struct Territorio *) calloc(MAX_TERRITORIOS, sizeof(struct Territorio));
    // Retorna o ponteiro para a memória alocada ou NULL em caso de falha
    return ptr;
}

/**
 * @brief Função para cadastrar os territórios do jogo
 * @note Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
 * @note Esta função modifica o mapa passado por referência (ponteiro).
 */
void cadastroTerritorios(){
    // Definição da função para cadastro dos territórios
    // Entrada dos dados de cada território
    printf("+-------------------------------+\n");
    printf("|   CADASTRO DOS %d TERRITÓRIOS  |\n", MAX_TERRITORIOS);
    printf("+-------------------------------+");

    // for(int i=0; i < MAX_TERRITORIOS; i++){
    //     printf("\n--- Território no. %d ---\n", i + 1);
    //     printf("Entre com o nome do território            : ");
    //     scanf("%s", Pais[i].nome);
    //     limparBufferEntrada();
    //     printf("Entre com a cor do território             : ");
    //     scanf("%s", Pais[i].cor);
    //     limparBufferEntrada();
    //     printf("Entre com o número de tropas do território: ");
    //     scanf("%d", &Pais[i].tropas);
    //     limparBufferEntrada();
    //     // printf("\n\n");
    // }
    strcpy(Pais[0].nome, "America");
    strcpy(Pais[0].cor, "Branco");
    Pais[0].tropas = 4;
    strcpy(Pais[1].nome, "Brasil");
    strcpy(Pais[1].cor, "Preto");
    Pais[1].tropas = 8;
    strcpy(Pais[2].nome, "Chile");
    strcpy(Pais[2].cor, "Branco");
    Pais[2].tropas = 3;
    strcpy(Pais[3].nome, "Peru");
    strcpy(Pais[3].cor, "Preto");
    Pais[3].tropas = 9;
    strcpy(Pais[4].nome, "Argelia");
    strcpy(Pais[4].cor, "Branco");
    Pais[4].tropas = 15;
    printf("\nCadastro dos territórios concluído!\n");

    mostrarMapa(Pais, MAX_TERRITORIOS);
}

/**
 * @brief Libera a memória previamente alocada para o mapa usando free.
 * @note Evita vazamentos de memória.
 */
void liberarMemoria(){
    free(Pais);
    printf("Memória liberada com sucesso.\n");
}

/**
 * @brief Imprime na tela o menu de ações disponíveis para o jogador.
 * @note Esta função não modifica nenhum dado, apenas exibe informações.
 */
void exibirMenuPrincipal(){
    printf("\n\n--------------------------\n");
    printf("------- MENU AÇÕES -------\n");
    printf("--------------------------\n");
    printf("1 - Atacar\n");
    // printf("2 - Verificar vitória\n");
    printf("0 - Sair\n\n");
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

/**
* @brief Executa a lógica de uma batalha entre dois territórios.
* @note Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
* @note Se um território for conquistado, atualiza seu dono e move uma tropa.
* @note implemente void atacar(Territorio* atacante, Territorio* defensor) que utilize rand() para simular um dado de ataque (1 a 6) para cada lado.
*/
void atacar(struct Territorio* ataque, struct Territorio* defesa){
    // Loop de ataque
    printf("\n--- Início do Ataque ---\n");
    char continuar = 's';
    int* dadosAtaque = NULL;
    int* dadosDefesa = NULL;
    do {
        // Verifica se o território atacante possui tropas suficientes para atacar
        if (ataque->tropas < 2) {
            printf("Ataque não possui tropas suficientes para o ataque.\n");
            return;
        }

        // Verifica se o território de ataque é o mesmo que o de defesa
        if (strcmp(ataque->cor, defesa->cor) == 0) {
            printf("Não é possível atacar países de mesma cor.\n");
            return;
        }

        // Pergunta quantos dados o atacante quer rolar (1 ao máximo de trocas - 1)
        int maxDadosAtaque = (ataque->tropas > 3) ? 3 : ataque->tropas - 1;
        int numDadosAtaque;

        // Entra num loop até o usuário entrar um número válido de dados
        do {
            printf ("\nQuantos dados para o ataque? (1 a %d): ", maxDadosAtaque);
            scanf ("%d", &numDadosAtaque);
            limparBufferEntrada();
        } while (numDadosAtaque < 1 || numDadosAtaque > maxDadosAtaque);

        // Rolagem aleatório dos dados do atacante (1 a 6)
        // if (dadosAtaque) free(dadosAtaque);
        dadosAtaque = (int*) malloc(numDadosAtaque * sizeof(int));
        for (int i = 0; i < numDadosAtaque; i++) {
            dadosAtaque[i] = (rand() % 6) + 1;
            // printf("Dada de ataque %d: %d\n", i + 1, dadosAtaque[i]);
        }

        // Define o número máximo de dados da defesaa (número de tropas a 3)
        int maxDadosDefesa = (defesa->tropas > 3) ? 3 : defesa->tropas;
        int numDadosDefesa;

        // Entra num loop até o usuário entrar um número válido de dados
        do {
            printf ("Quantos dados para a defesa? (1 a %d): ", maxDadosDefesa);
            scanf ("%d", &numDadosDefesa);
            limparBufferEntrada();
        } while (numDadosDefesa < 1 || numDadosDefesa > maxDadosDefesa);

        // Rolagem aleatório dos dados da defesa (1 a 6)
        // if (dadosDefesa) free(dadosDefesa);
        dadosDefesa = (int*) malloc(numDadosDefesa * sizeof(int));
        for (int i = 0; i < numDadosDefesa; i++) {
            // dadosDefesa[i] = srand(time(NULL));
            dadosDefesa[i] = (rand() % 6) + 1;
            // printf("Dada de defesa %d: %d\n", i + 1, dadosDefesa[i]);
        }

        // Ordena os dados em ordem decrescente (bubble sort)
        ordenarDados(dadosAtaque, numDadosAtaque);
        ordenarDados(dadosDefesa, numDadosDefesa);

        printf("\nAtacante: %d tropas, Defesa: %d tropas\n", ataque->tropas, defesa->tropas);
        printf("Atacante dados: ");
        for (int i = 0; i < numDadosAtaque; i++) {
            printf("%d ", dadosAtaque[i]);
        }
        printf("\nDefesa dados  : ");
        for (int i = 0; i < numDadosDefesa; i++) {
            printf("%d ", dadosDefesa[i]);
        }
        printf("\n");

        // Compara os dados do atacante e do defensor
        int comparacoes = (numDadosAtaque < numDadosDefesa) ? numDadosAtaque : numDadosDefesa;
        for (int i = 0; i < comparacoes; i++) {
            if (dadosAtaque[i] > dadosDefesa[i]) {
                defesa->tropas--;
                printf("Defensor perde 1 tropa! Tropas restantes: %d\n", defesa->tropas);
            } else {
                ataque->tropas--;
                printf("Atacante perde 1 tropa! Tropas restantes: %d\n", ataque->tropas);
            }
        }

        if (ataque->tropas > 1 && defesa->tropas > 0){
            // Pergunta se quer continuar o ataque
            printf("\nContinuar o ataque? (s/n): ");
            scanf(" %c", &continuar);
            limparBufferEntrada();
        } else {
            continuar = 'n'; // Força a saída do loop se não houver tropas suficientes
        }
    } while ((continuar == 's' || continuar == 'S'));

    // Verifica o vencedor
    if (defesa->tropas == 0) {
        printf("\nTerritório %s conquistado!\n", defesa->nome);
        // Atualiza o dono do território conquistado
        strcpy(defesa->cor, ataque->cor);
        // Pergunta quantas tropas o ataque quer mover (1 a número de tropas - 1)
        int tropasMover;

        // Cria um loop até o número de troas for correto
        do {
            printf("Quantas tropas mover para o território conquistado? (1 a %d): ", (ataque->tropas - 1 > 3 ? 3 : ataque->tropas - 1));
            scanf("%d", &tropasMover);
            limparBufferEntrada();
        } while (tropasMover < 1 || tropasMover >= ataque->tropas);

        // Move as tropas
        ataque->tropas -= tropasMover;
        defesa->tropas += tropasMover;
        printf("%d tropas movidas para o território %s.\n", tropasMover, defesa->nome);
    } else {
        printf("Ataque falhou! Território %s permanece com %d tropas.\n", defesa->nome, defesa->tropas);
    }

    // Libera a memória alocada para os dados
    if (dadosAtaque) free(dadosAtaque);
    if (dadosDefesa) free(dadosDefesa);
}

/**
 * @brief Função auxiliar para ordenar um array de inteiros em ordem decrescente usando o algoritmo Bubble Sort.
 * @param dados Ponteiro para o array de inteiros a ser ordenado.
 * @param n Número de elementos no array.
 */
void ordenarDados(int* dados, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dados[j] < dados[j + 1]) {
                int temp = dados[j];
                dados[j] = dados[j + 1];
                dados[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief função que sorteia e retorna um ID de missão aleatório para o jogador.
 * @note sorteia uma missão e copia para a variável de missão do jogador usando strcpy.
 */
void sortearMissao(char* destino, char* missoes[], int totalMissoes) {
   int indice = rand() % totalMissoes;
   strcpy(destino, missoes[indice]);
}

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

/**
 * @brief Função para limpar o buffer de entrada
 * @note Evita problemas com entradas de dados
 */
void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Função para listar o mapa atual com os territórios, suas cores e número de tropas.
 * @param mapa Ponteiro para o array de territórios (const para evitar modificação acidental).
 * @param totalTerritorios Número total de territórios no mapa.
 */
void mostrarMapa(const struct Territorio* mapa, int totalTerritorios) {
    printf("\n+-----------------------------------------+\n");
    printf("|               MAPA ATUAL       ;\n");
    printf("+-----------------------------------------+\n");
    printf("| %-15s | %-10s | %-8s |\n", "Território", "Cor", "Tropas");
    printf("+-----------------------------------------+\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("| %-13s | %-10s | %-7d |\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("+-----------------------------------------+\n");
}
