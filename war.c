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


// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// Definição do número máximo de territórios
#define MAX_TERRITORIOS 5

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
// Definição da Estrutura do Território do Jogo

// Definindo o nome do território, a cor predominante e a quantidade de tropas no território
struct Territorio {
    char nome[30]; // Nome do território
    char cor[10]; // Cor dominante do território
    int tropas; // Número de tropas no território
};

// Definição da quantidade máxima de territórios (países)
struct Territorio Pais[MAX_TERRITORIOS];

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
void inicializarTerritorios(); // Função de inicialização (cadastro) dos territórios

// Funções de lógica principal do jogo:
// Função utilitária:
void limparBufferEntrada(); // Função para limpar o buffer de entrada

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial
    printf("========================================\n");
    printf("======       WAR ESTRUTURADO      ======\n");
    printf("========================================\n\n");

    // Cadastro dos territórios
    inicializarTerritorios();

    //(Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(){
    // Definição da função para cadastro dos territórios
    // Entrada dos dados de cada território
    printf("+-------------------------------+\n");
    printf("|   CADASTRO DOS %d TERRITÓRIOS  |\n", MAX_TERRITORIOS);
    printf("+-------------------------------+");

    for(int i=0; i < MAX_TERRITORIOS; i++){
        printf("\n--- Território no. %d ---\n", i + 1);
        printf("Entre com o nome do território            : ");
        scanf("%s", &Pais[i].nome);
        limparBufferEntrada();
        printf("Entre com a cor do território             : ");
        scanf("%s", &Pais[i].cor);
        limparBufferEntrada();
        printf("Entre com o número de tropas do território: ");
        scanf("%d", &Pais[i].tropas);
        limparBufferEntrada();
        // printf("\n\n");
    }

    // Listagem dos territórios criados
    printf("\n\n+-------------------------------+\n");
    printf("|   LISTAGEM DOS %d TERRITÓRIOS  |\n", MAX_TERRITORIOS);
    printf("+-------------------------------+");

    for(int i=0; i < MAX_TERRITORIOS; i++){
        printf("\n--- Território no. %d ---\n", i + 1);
        printf("Nome  : %s\n", Pais[i].nome);
        printf("Cor   : %s\n", Pais[i].cor);
        printf("Tropas: %d\n", Pais[i].tropas);
    }
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
