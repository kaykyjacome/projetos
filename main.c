#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Para setar o locale e exibir caracteres especiais
#include "includes/menu_bar.h"    // Inclui o novo cabeçalho do menu do bar
#include "includes/item_bar.h" // Inclui o novo cabeçalho dos itens do bar para liberar a lista no final

int main() {
    // Configura o locale para português do Brasil, para exibir caracteres como "ç" e acentos
    setlocale(LC_ALL, "pt_BR.UTF-8");

    printf("=== BEM-VINDO AO SISTEMA DE GERENCIAMENTO DO BAR! ===\n");

    // Chama a função principal do menu do bar
    exibirMenuBar();

    // Libera a memória da lista de itens do bar antes de sair do programa
    liberarListaItensBar();

    return 0;
}