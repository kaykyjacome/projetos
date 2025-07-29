#include <stdio.h>
#include <stdlib.h>
#include "../includes/menu_bar.h"
#include "../includes/item_bar.h" // Inclui o cabeçalho dos itens do bar

void exibirMenuBar() {
    int opcao;
    int idBusca;
    ItemBar novoItem;
    ItemBar *itemEncontrado;

    do {
        printf("\n--- MENU DE GERENCIAMENTO DO BAR ---\n");
        printf("1. Adicionar Item ao Cardápio\n");
        printf("2. Listar Itens do Cardápio\n");
        printf("3. Editar Item do Cardápio\n");
        printf("4. Excluir Item do Cardápio\n");
        printf("5. Ordenar Cardápio por Preço (MergeSort)\n");
        printf("6. Buscar Item no Cardápio por ID (Busca Binária)\n");
        printf("0. Sair do Sistema do Bar\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n--- NOVO ITEM NO CARDÁPIO ---\n");
                printf("ID do Item: ");
                scanf("%d", &novoItem.id);
                getchar(); // Limpa o buffer do teclado
                printf("Nome do Item: ");
                fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
                strtok(novoItem.nome, "\n"); // Remove o newline
                printf("Tipo (ex: bebida, comida): ");
                fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
                strtok(novoItem.tipo, "\n"); // Remove o newline
                printf("Preço: R$");
                scanf("%f", &novoItem.preco);
                printf("Estoque: ");
                scanf("%d", &novoItem.estoque);
                adicionarItemBar(novoItem);
                break;
            case 2:
                listarItensBar();
                break;
            case 3:
                printf("\nDigite o ID do item para editar: ");
                scanf("%d", &idBusca);
                editarItemBar(idBusca);
                break;
            case 4:
                printf("\nDigite o ID do item para excluir: ");
                scanf("%d", &idBusca);
                excluirItemBar(idBusca);
                break;
            case 5:
                ordenarItensBarPorPreco();
                break;
            case 6:
                printf("\n--- BUSCAR ITEM NO CARDÁPIO POR ID ---\n");
                printf("Digite o ID do item para buscar: ");
                scanf("%d", &idBusca);
                itemEncontrado = buscarItemBarPorIdComBuscaBinaria(idBusca);
                if (itemEncontrado != NULL) {
                    printf("Item encontrado:\n");
                    printf("ID: %d | Nome: %s | Tipo: %s | Preço: R$%.2f | Estoque: %d\n",
                           itemEncontrado->id, itemEncontrado->nome, itemEncontrado->tipo,
                           itemEncontrado->preco, itemEncontrado->estoque);
                    free(itemEncontrado); // Libera a cópia alocada na função de busca
                } else {
                    printf("Item com ID %d não encontrado no cardápio.\n", idBusca);
                }
                break;
            case 0:
                printf("Encerrando o sistema do Bar. Volte sempre! 🍻\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}