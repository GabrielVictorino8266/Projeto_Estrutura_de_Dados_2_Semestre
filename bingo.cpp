#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int TAM_CAR = 5; // Tamanho fixo da cartela (5x5)
const int MAX_NUMEROS_CARTELA = TAM_CAR * TAM_CAR; // Total de números por cartela (5x5 = 25 números)

// struct cartela com array de numeors e array de marcados
struct Cartela {
    int numeros[TAM_CAR][TAM_CAR]; // matriz pros numeros da cartela
    int marcados[MAX_NUMEROS_CARTELA] = {0}; // gera o array com 0 para nao gerar lixo.
};

// void teste(const Cartela& cartela);
// prototipacao das funcoes
void show_menu(); // Exibe o menu principal
int selecionar_opcao_menu(); // le opcao do usuario
void gerar_multiplas_cartelas(Cartela*& cartelas, int& num_cartelas); // Gera múltiplas cartelas, chamando a funcao gerar_cartela
void gerar_cartela(Cartela& cartela); // Gera uma cartela individual
void exibir_cartela(const Cartela& cartela); // Exibe uma cartela
void exibir_todas_cartelas(const Cartela* cartelas, int num_cartelas); // exibe todas as cartelas
void imprimir_cartelas_em_arquivos(const Cartela* cartelas, int num_cartelas); // salva as cartelas exibidas em txt
void marcar_numero(Cartela* cartelas, int num_cartelas, int numero); // marca os numeros
void exibir_numeros_chamados_por_cartela(const Cartela& cartela); // Exibe os números chamados de uma cartela
void verificar_ganhador(const Cartela& cartela); // verifica as linhas colunas ou olha a boa.
void sair(); // saida


int main() {
    int escolha; // usado no menu para guardar a opcao do usuario
    Cartela* cartelas = nullptr; // ponteiro para alocacao dinamica.
    int num_cartelas = 0;        // Contador de cartelas geradas

    // loop para executar no minimo uma vez
    do {
        show_menu(); // mostra menu
        escolha = selecionar_opcao_menu(); // le input usuario
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
                    cout << "Sem cartela cadastrada!\n"; // Mensagem caso não haja cartelas
                break;
            case 3:
                if (num_cartelas > 0)
                    imprimir_cartelas_em_arquivos(cartelas, num_cartelas); // Salva as cartelas em arquivos
                else
                    cout << "Sem cartela para imprimir!\n"; // Mensagem caso não haja cartelas
                break;
            case 4:
                if (num_cartelas > 0) {
                    int numero;
                    cout << "Digite o número sorteado: ";
                    cin >> numero; // Lê o número sorteado
                    marcar_numero(cartelas, num_cartelas, numero); // Marca o número
                } else {
                    cout << "Sem cartela cadastrada!\n"; // Mensagem caso não haja cartelas
                }
                break;
            case 5:
                if (num_cartelas > 0) {
                    int cartela_index;
                    cout << "Escolha a cartela (0 a " << num_cartelas - 1 << "): ";
                    cin >> cartela_index; // escolhe a cartela pelo indice dela

                    if (cartela_index >= 0 && cartela_index < num_cartelas){
                        exibir_numeros_chamados_por_cartela(cartelas[cartela_index]); // Exibe os números chamados na cartela
                        // teste(cartelas[cartela_index]);
                    }
                    else
                        cout << "Nao ha essa cartela.\n"; // Mensagem caso o índice da cartela seja inválido
                } else {
                    cout << "Nenhuma cartela cadastrada!\n"; // Mensagem caso não haja cartelas
                }
                break;
            default:
                cout << "Opcao invalida!\n"; // Mensagem caso a opção digitada seja inválida
                break;
        }
    } while (escolha != 0); // Continua o loop até o usuário escolher sair

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
    bool numeros_sorteados[TAM_CAR][15] = {false}; // verificamos se o numero ja foi sorteado

    // Preenche a cartela com números aleatórios dentro dos intervalos de cada coluna (B, I, N, G, O)
    for (int i = 0; i < TAM_CAR; i++) {
        for (int j = 0; j < TAM_CAR; j++) {
            // Conhecendo o central da cartela, temos o FREE, que e -1
            if (j == 2 && i == 2) {
                cartela.numeros[i][j] = -1; // "FREE"
                cartela.marcados[i * TAM_CAR + j] = 1; // Marca o "FREE" como já chamado
                continue;
            }

            // o intervalo para a chamada, vai variar para a coluna
            /*
            B: 1-15 (até 0 * 15 + 1 = 1)
            I: 16-30 (até 1 * 15 + 1 = 16)
            N: 31-45 (até 2 * 15 + 1 = 31)
            G: 46-60 (até 3 * 15 + 1 = 46)
            O: 61-75 (até 4 * 15 + 1 = 61)
            */
            int min = j * 15 + 1;
            int numero;
            do {
                numero = rand() % 15 + min;
                /*
                O rand() % 15 gera um número aleatório entre 0 e 14,
                mas somando com o valor minimo, ele retorna dentro do intervalo que se deseja
                Ex:
                min = 31
                rand() % 15 + min = 46 (31 + 15 = 46)
                */
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
    cin >> num_cartelas; // le a quantidade de cartelas que se quer gerar

    if (num_cartelas <= 0) {
        cout << "Quantidade invalida de cartelas.\n";
        return;
    }

    // Aloca memoria para cada cartela
    cartelas = new Cartela[num_cartelas];
    for (int i = 0; i < num_cartelas; i++) {
        gerar_cartela(cartelas[i]); // gera cada cartela
    }

    cout << num_cartelas << " cartelas geradas co sucesso!\n";
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
        ofstream arquivo(nome_arquivo); // Abre o arquivo gravando
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo " << nome_arquivo << "!\n";
            continue;
        }

        arquivo << "Cartela " << i + 1 << ":\n"; // soma o indice para cada inddicce de cada cartela
        for (int j = 0; j < TAM_CAR; j++) {
            for (int k = 0; k < TAM_CAR; k++) {
                int valor = cartelas[i].numeros[j][k];
                if (valor == -1)
                    arquivo << "FREE\t"; // tambem verifica o -1 e marca o free no arquivo
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
        cout << "Olha a boa! Falta 1 número para o BINGO!\n";
    }
}

// Função para exibir os números chamados por cartela
void exibir_numeros_chamados_por_cartela(const Cartela& cartela) {
    cout << "numeros chamados nesta cartela: "; 
    // Loop para percorrer todas as linhas da cartela (TAM_CAR é o tamanho da cartela)
    for (int linha = 0; linha < TAM_CAR; linha++) { 
        // Exemplo: Se TAM_CAR = 5, o loop começa com linha = 0 e vai até linha = 4, passando as 5 linhas

        // Percorre todas as colunas da cartela
        for (int coluna = 0; coluna < TAM_CAR; coluna++) { 
            // Mesma coisa da linha, mas agora nas colunas, vai de 0 a 4

            //calcula índice linear no array 'marcados' usando (linha, coluna)
            // Para uma matriz 5x5, a posição (linha=1, coluna=2) terá o índice 7 (1*5 + 2)
            int i = linha * TAM_CAR + coluna;
            // Exemplo: Para linha = 1 e coluna = 2, o cálculo seria 1*5 + 2 = 7. Assim, o índice 'i' será 7.

            // Verifica se o número na posição 'i' foi chamado, ou seja, se 'marcados[i]' é 1
            if (cartela.marcados[i]) { 
                // Exemplo: Se cartela.marcados[7] for 1, significa que o número foi chamado, então entra no if.

                // Se o número foi chamado, imprime o número correspondente na matriz 'numeros'
                cout << cartela.numeros[linha][coluna] << " "; 
                // Exemplo: Se cartela.numeros[1][2] for 23, exibe "23" na tela.
            }
        }
    }

    cout << endl; 
}


// void teste(const Cartela& cartela) {
//     for (int i = 0; i < MAX_NUMEROS_CARTELA; i++) {
//         cout << cartela.marcados[i] << " ";
//     }
//     cout << endl;
// }
