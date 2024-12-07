#include <iostream>
#include <cassert>
#include "bingo.cpp" // Incluindo a implementação

void test_gerar_cartela() {
    Cartela cartela;
    gerar_cartela(cartela);

    // Verifica se a cartela tem o tamanho correto
    assert(sizeof(cartela.numeros) / sizeof(cartela.numeros[0]) == TAM_CAR);

    // Verifica se o "FREE" está marcado corretamente
    assert(cartela.numeros[2][2] == -1);
    assert(cartela.marcados[2 * TAM_CAR + 2] == 1); // Marcado no "FREE"
}

void test_marcar_numero() {
    Cartela cartela;
    gerar_cartela(cartela);

    int numero = cartela.numeros[0][0]; // Pega o primeiro número da cartela
    marcar_numero(&cartela, 1, numero); // Marca esse número

    // Verifica se o número foi marcado corretamente
    assert(cartela.numeros[0][0] == -1); // Número marcado
    assert(cartela.marcados[0 * TAM_CAR + 0] == 1); // Marcado no array de marcados
}

void test_verificar_ganhador() {
    Cartela cartela;
    gerar_cartela(cartela);

    // Marca todos os números da cartela
    for (int i = 0; i < TAM_CAR; i++) {
        for (int j = 0; j < TAM_CAR; j++) {
            cartela.marcados[i * TAM_CAR + j] = 1;
        }
    }

    // Verifica se a cartela é ganhadora (Bingo)
    verificar_ganhador(cartela);
}

int main() {
    test_gerar_cartela();
    test_marcar_numero();
    test_verificar_ganhador();

    std::cout << "Todos os testes passaram!" << std::endl;
    return 0;
}
