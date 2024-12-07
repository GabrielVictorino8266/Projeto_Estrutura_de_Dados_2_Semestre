#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int TAM_CAR = 5; // Tamanho fixo da cartela (5x5)
const int MAX_NUMEROS_CARTELA = TAM_CAR * TAM_CAR; // Total de números por cartela (5x5 = 25 números)

// Estrutura para representar uma cartela
struct Cartela {
    int numeros[TAM_CAR][TAM_CAR]; // Matriz que armazena os números da cartela
    int marcados[MAX_NUMEROS_CARTELA] = {0}; // Array para rastrear quais números foram chamados (0 = não chamado, 1 = chamado)
};

// Prototypes das funções
void show_menu(); // Exibe o menu principal
int selecionar_opcao_menu(); // Lê a opção do menu selecionada pelo usuário
void gerar_multiplas_cartelas(Cartela*& cartelas, int& num_cartelas); // Gera múltiplas cartelas
void gerar_cartela(Cartela& cartela); // Gera uma cartela individual
void exibir_cartela(const Cartela& cartela); // Exibe uma cartela
void exibir_todas_cartelas(const Cartela* cartelas, int num_cartelas); // Exibe todas as cartelas
void imprimir_cartelas_em_arquivos(const Cartela* cartelas, int num_cartelas); // Salva as cartelas em arquivos separados
void marcar_numero(Cartela* cartelas, int num_cartelas, int numero); // Marca um número nas cartelas
void exibir_numeros_chamados_por_cartela(const Cartela& cartela); // Exibe os números chamados de uma cartela
void verificar_ganhador(const Cartela& cartela); // Verifica se há um ganhador (linha, coluna ou bingo completo)
void sair(); // Encerra o programa

int main() {
    int escolha; // Variável para armazenar a escolha do usuário no menu
    Cartela* cartelas = nullptr; // Ponteiro para armazenar múltiplas cartelas (alocação dinâmica)
    int num_cartelas = 0;        // Contador de cartelas geradas

    // Loop principal que mantém o menu ativo até que o usuário escolha sair
    do {
        show_menu(); // Exibe o menu
        escolha = selecionar_opcao_menu(); // Lê a opção do menu
        switch (escolha) {
            case 0:
                sair(); // Encerra o programa
                break;
            case 1:
                gerar_multiplas_cartelas(cartelas, num_cartelas); // Gera múltiplas cartelas
                break;
            case 2:
                if (num_cartelas > 0)
                    exibir_todas_cartelas(cartelas, num_cartelas); // Exibe todas as cartelas
                else
                    cout << "Nenhuma cartela cadastrada!\n"; // Mensagem caso não haja cartelas
                break;
            case 3:
                if (num_cartelas > 0)
                    imprimir_cartelas_em_arquivos(cartelas, num_cartelas); // Salva as cartelas em arquivos
                else
                    cout << "Nenhuma cartela para imprimir!\n"; // Mensagem caso não haja cartelas
                break;
            case 4:
                if (num_cartelas > 0) {
                    int numero;
                    cout << "Digite o número sorteado: ";
                    cin >> numero; // Lê o número sorteado
                    marcar_numero(cartelas, num_cartelas, numero); // Marca o número nas cartelas
                } else {
                    cout << "Nenhuma cartela cadastrada!\n"; // Mensagem caso não haja cartelas
                }
                break;
            case 5:
                if (num_cartelas > 0) {
                    int cartela_index;
                    cout << "Selecione a cartela (0 a " << num_cartelas - 1 << "): ";
                    cin >> cartela_index; // Lê o índice da cartela a ser exibida

                    if (cartela_index >= 0 && cartela_index < num_cartelas)
                        exibir_numeros_chamados_por_cartela(cartelas[cartela_index]); // Exibe os números chamados na cartela selecionada
                    else
                        cout << "Cartela inválida.\n"; // Mensagem caso o índice da cartela seja inválido
                } else {
                    cout << "Nenhuma cartela cadastrada!\n"; // Mensagem caso não haja cartelas
                }
                break;
            default:
                cout << "Opção inválida!\n"; // Mensagem caso a opção digitada seja inválida
                break;
        }
    } while (escolha != 0); // Continua o loop até o usuário escolher sair

    // Libera memória alocada para as cartelas
    delete[] cartelas;

    return 0;
}

// Função para exibir o menu de opções
void show_menu() {
    cout << "======BINGO======\n";
    cout << "0 - Sair\n";
    cout << "1 - Cadastrar Cartelas\n";
    cout << "2 - Exibir Cartelas\n";
    cout << "3 - Salvar Cartelas em Arquivos Separados\n";
    cout << "4 - Marcar Número\n";
    cout << "5 - Exibir Números Chamados por Cartela\n";
    cout << "=================\n";
}

// Função para ler a opção escolhida pelo usuário
int selecionar_opcao_menu() {
    int opcao_menu;
    cout << ">> ";
    cin >> opcao_menu; // Lê a entrada do usuário
    return opcao_menu;
}

// Função para sair do programa
void sair() {
    cout << "Saindo do programa...\n";
    exit(0); // Encerra o programa
}

// Função para gerar uma cartela de bingo
void gerar_cartela(Cartela& cartela) {
    bool numeros_sorteados[TAM_CAR][15] = {false}; // Array para verificar se um número já foi sorteado por coluna

    // Preenche a cartela com números aleatórios dentro dos intervalos de cada coluna (B, I, N, G, O)
    for (int i = 0; i < TAM_CAR; i++) {
        for (int j = 0; j < TAM_CAR; j++) {
            // Se for o centro da cartela, já marca como "FREE"
            if (j == 2 && i == 2) {
                cartela.numeros[i][j] = -1; // "FREE"
                cartela.marcados[i * TAM_CAR + j] = 1; // Marca o "FREE" como já chamado
                continue;
            }

            // Determina o intervalo para o sorteio de números com base na coluna
            int min = j * 15 + 1;
            int numero;
            do {
                numero = rand() % 15 + min; // Sorteia um número dentro do intervalo
            } while (numeros_sorteados[j][numero - min]); // Verifica se o número já foi sorteado na coluna

            cartela.numeros[i][j] = numero; // Atribui o número à cartela
            cartela.marcados[i * TAM_CAR + j] = 0; // Marca como não chamado
            numeros_sorteados[j][numero - min] = true; // Marca o número como sorteado para a coluna
        }
    }
}

// Função para gerar múltiplas cartelas
void gerar_multiplas_cartelas(Cartela*& cartelas, int& num_cartelas) {
    cout << "Quantas cartelas deseja gerar? ";
    cin >> num_cartelas; // Lê o número de cartelas que o usuário deseja gerar

    if (num_cartelas <= 0) {
        cout << "Número inválido de cartelas.\n";
        return;
    }

    // Aloca memória para o número de cartelas especificado
    cartelas = new Cartela[num_cartelas];
    for (int i = 0; i < num_cartelas; i++) {
        gerar_cartela(cartelas[i]); // Gera cada cartela individualmente
    }

    cout << num_cartelas << " cartelas geradas com sucesso!\n";
}

// Função para exibir uma cartela
void exibir_cartela(const Cartela& cartela) {
    for (int i = 0; i < TAM_CAR; i++) {
        for (int j = 0; j < TAM_CAR; j++) {
            // Se o número for marcado como "FREE", exibimos a palavra "FREE"
            if (cartela.numeros[i][j] == -1)
                cout << "FREE\t"; // Exibe "FREE" no centro da cartela
            else if (cartela.marcados[i * TAM_CAR + j] == 1)
                cout << "[X]\t"; // Marca o número como chamado
            else
                cout << cartela.numeros[i][j] << "\t"; // Exibe o número original
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
}

// Função para exibir todas as cartelas
void exibir_todas_cartelas(const Cartela* cartelas, int num_cartelas) {
    for (int i = 0; i < num_cartelas; i++) {
        cout << "Cartela " << i + 1 << ":\n";
        exibir_cartela(cartelas[i]); // Exibe cada cartela
    }
}

// Função para salvar todas as cartelas em arquivos separados
void imprimir_cartelas_em_arquivos(const Cartela* cartelas, int num_cartelas) {
    for (int i = 0; i < num_cartelas; i++) {
        string nome_arquivo = "cartela_" + to_string(i + 1) + ".txt";
        ofstream arquivo(nome_arquivo); // Abre o arquivo para escrita
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo " << nome_arquivo << "!\n";
            continue;
        }

        arquivo << "Cartela " << i + 1 << ":\n";
        for (int j = 0; j < TAM_CAR; j++) {
            for (int k = 0; k < TAM_CAR; k++) {
                int valor = cartelas[i].numeros[j][k];
                if (valor == -1)
                    arquivo << "FREE\t"; // Se for "FREE", coloca no arquivo
                else if (cartelas[i].marcados[j * TAM_CAR + k] == 1)
                    arquivo << "[X]\t"; // Marca o número como chamado
                else
                    arquivo << valor << "\t"; // Caso contrário, coloca o número
            }
            arquivo << endl;
        }

        arquivo.close();
        cout << "Cartela " << i + 1 << " salva em " << nome_arquivo << "!\n";
    }
}


// Função para marcar um número nas cartelas
void marcar_numero(Cartela* cartelas, int num_cartelas, int numero) {
    bool encontrado = false;

    for (int i = 0; i < num_cartelas; i++) {
        for (int j = 0; j < TAM_CAR; j++) {
            for (int k = 0; k < TAM_CAR; k++) {
                // Verifica se o número encontrado corresponde ao sorteado
                if (cartelas[i].numeros[j][k] == numero || (numero == -1 && j == 2 && k == 2)) {
                    cartelas[i].marcados[j * TAM_CAR + k] = 1; // Marca o número como chamado
                    encontrado = true;
                    cout << "Número " << numero << " marcado na cartela " << i + 1 << "!\n";
                    verificar_ganhador(cartelas[i]); // Verifica se a cartela é ganhadora
                }
            }
        }
    }

    if (!encontrado) {
        cout << "Número " << numero << " não encontrado em nenhuma cartela.\n"; // Caso o número não seja encontrado
    }
}


// Função para verificar se uma cartela ganhou (linha, coluna ou bingo completo)
void verificar_ganhador(const Cartela& cartela) {
    bool linha_completa, coluna_completa, bingo_completo = true;
    int num_faltando = 0;

    // Verifica se todas as 5 posições de uma linha estão marcadas
    for (int i = 0; i < TAM_CAR; i++) {
        linha_completa = true;
        for (int j = 0; j < TAM_CAR; j++) {
            if (cartela.marcados[i * TAM_CAR + j] == 0) {
                linha_completa = false;
                break;
            }
        }
        if (linha_completa) {
            cout << "LINHA! - Linha " << i + 1 << " completa!\n";
        }
    }

    // Verifica se todas as 5 posições de uma coluna estão marcadas
    for (int j = 0; j < TAM_CAR; j++) {
        coluna_completa = true;
        for (int i = 0; i < TAM_CAR; i++) {
            if (cartela.marcados[i * TAM_CAR + j] == 0) {
                coluna_completa = false;
                break;
            }
        }
        if (coluna_completa) {
            cout << "COLUNA! - Coluna " << j + 1 << " completa!\n";
        }
    }

    // Verifica se todos os 25 números da cartela estão marcados (BINGO)
    for (int i = 0; i < MAX_NUMEROS_CARTELA; i++) {
        if (cartela.marcados[i] == 0) {
            num_faltando++;
            bingo_completo = false;
        }
    }

    if (bingo_completo) {
        cout << "BINGO! - Cartela completa!\n";
    }

    // Verifica se faltou apenas 1 número
    if (num_faltando == 1 && !bingo_completo) {
        cout << "Olha a boa! Só falta 1 número para o BINGO!\n";
    }
}

// Função para exibir os números chamados por cartela
void exibir_numeros_chamados_por_cartela(const Cartela& cartela) {
    cout << "Números chamados nesta cartela: ";
    for (int i = 0; i < MAX_NUMEROS_CARTELA; i++) {
        if (cartela.marcados[i] == 1) {
            int linha = i / TAM_CAR;
            int coluna = i % TAM_CAR;
            cout << cartela.numeros[linha][coluna] << " "; // Exibe os números chamados
        }
    }
    cout << endl;
}
