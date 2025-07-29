#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/item_bar.h" // Inclui o novo cabeçalho

// Inicializa a lista de itens do bar como vazia
NoItemBar *listaItensBar = NULL;

// Adiciona um novo item ao final da lista
void adicionarItemBar(ItemBar novoItem) {
    NoItemBar *novoNo = (NoItemBar *)malloc(sizeof(NoItemBar));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória ao adicionar item.\n");
        return;
    }
    novoNo->dados = novoItem;
    novoNo->proximo = NULL;

    if (listaItensBar == NULL) {
        listaItensBar = novoNo;
    } else {
        NoItemBar *temp = listaItensBar;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
    }
    printf("Item '%s' adicionado ao cardápio com sucesso!\n", novoItem.nome);
}

// Lista todos os itens no cardápio
void listarItensBar() {
    if (listaItensBar == NULL) {
        printf("Nenhum item cadastrado no cardápio do bar.\n");
        return;
    }

    printf("\n--- CARDÁPIO DO BAR ---\n");
    NoItemBar *temp = listaItensBar;
    while (temp != NULL) {
        printf("ID: %d | Nome: %s | Tipo: %s | Preço: R$%.2f | Estoque: %d\n",
               temp->dados.id, temp->dados.nome, temp->dados.tipo, temp->dados.preco, temp->dados.estoque);
        temp = temp->proximo;
    }
    printf("-------------------------\n");
}

// Busca um item no cardápio por ID e retorna um ponteiro para ele
ItemBar* buscarItemBarPorId(int id) {
    NoItemBar *temp = listaItensBar;
    while (temp != NULL) {
        if (temp->dados.id == id) {
            return &(temp->dados);
        }
        temp = temp->proximo;
    }
    return NULL; // Não encontrou
}

// Edita os dados de um item existente
void editarItemBar(int id) {
    ItemBar *itemAEditar = buscarItemBarPorId(id);
    if (itemAEditar == NULL) {
        printf("Item com ID %d não encontrado no cardápio.\n", id);
        return;
    }

    printf("\n--- EDITAR ITEM (ID: %d - %s) ---\n", id, itemAEditar->nome);
    printf("Novo nome (%s): ", itemAEditar->nome);
    getchar(); // Limpa o buffer
    fgets(itemAEditar->nome, sizeof(itemAEditar->nome), stdin);
    strtok(itemAEditar->nome, "\n"); // Remove o newline

    printf("Novo tipo (%s): ", itemAEditar->tipo);
    fgets(itemAEditar->tipo, sizeof(itemAEditar->tipo), stdin);
    strtok(itemAEditar->tipo, "\n"); // Remove o newline

    printf("Novo preço (%.2f): R$", itemAEditar->preco);
    scanf("%f", &itemAEditar->preco);

    printf("Novo estoque (%d): ", itemAEditar->estoque);
    scanf("%d", &itemAEditar->estoque);

    printf("Item atualizado no cardápio com sucesso!\n");
}

// Exclui um item do cardápio por ID
void excluirItemBar(int id) {
    NoItemBar *temp = listaItensBar;
    NoItemBar *anterior = NULL;

    // Se o item a ser excluído é o primeiro da lista
    if (temp != NULL && temp->dados.id == id) {
        listaItensBar = temp->proximo;
        printf("Item '%s' excluído do cardápio com sucesso!\n", temp->dados.nome);
        free(temp);
        return;
    }

    // Procura o item na lista, mantendo o anterior
    while (temp != NULL && temp->dados.id != id) {
        anterior = temp;
        temp = temp->proximo;
    }

    // Se o item não foi encontrado
    if (temp == NULL) {
        printf("Item com ID %d não encontrado para exclusão.\n", id);
        return;
    }

    // Remove o nó da lista
    anterior->proximo = temp->proximo;
    printf("Item '%s' excluído do cardápio com sucesso!\n", temp->dados.nome);
    free(temp);
}

// Libera toda a memória alocada para a lista encadeada de itens
void liberarListaItensBar() {
    NoItemBar *atual = listaItensBar;
    NoItemBar *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    listaItensBar = NULL; // Garante que a lista esteja vazia após a liberação
    printf("\nMemória da lista de itens do bar liberada.\n");
}

// --- Implementação do MergeSort ---

// Divide a lista em duas metades
NoItemBar* dividirListaBar(NoItemBar* head) {
    if (head == NULL || head->proximo == NULL) {
        return head;
    }
    NoItemBar* lento = head;
    NoItemBar* rapido = head->proximo;

    while (rapido != NULL && rapido->proximo != NULL) {
        lento = lento->proximo;
        rapido = rapido->proximo->proximo;
    }

    NoItemBar* segundaMetade = lento->proximo;
    lento->proximo = NULL; // Quebra a lista em duas
    return segundaMetade;
}

// Une duas listas ordenadas
NoItemBar* unirListasBar(NoItemBar* a, NoItemBar* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    NoItemBar* resultado = NULL;

    // Compara os preços para ordenar
    if (a->dados.preco <= b->dados.preco) {
        resultado = a;
        resultado->proximo = unirListasBar(a->proximo, b);
    } else {
        resultado = b;
        resultado->proximo = unirListasBar(a, b->proximo);
    }
    return resultado;
}

// Função principal do MergeSort para lista encadeada
NoItemBar* mergeSortBar(NoItemBar* head) {
    if (head == NULL || head->proximo == NULL) {
        return head;
    }

    NoItemBar* a = head;
    NoItemBar* b = dividirListaBar(head);

    a = mergeSortBar(a); // Ordena a primeira metade recursivamente
    b = mergeSortBar(b); // Ordena a segunda metade recursivamente

    return unirListasBar(a, b); // Une as duas metades ordenadas
}

// Chama o MergeSort para ordenar a lista global de itens por preço
void ordenarItensBarPorPreco() {
    if (listaItensBar == NULL) {
        printf("Nenhum item no cardápio para ordenar.\n");
        return;
    }
    listaItensBar = mergeSortBar(listaItensBar);
    printf("Cardápio ordenado por preço (usando MergeSort)!\n");
    listarItensBar(); // Mostra o cardápio ordenado
}

// --- Implementação da Busca Binária ---

// Função auxiliar de busca binária em um array (necessário para a busca binária)
ItemBar* buscaBinariaEmArrayBar(ItemBar arr[], int esq, int dir, int idBusca) {
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;

        if (arr[meio].id == idBusca) {
            return &arr[meio]; // Encontrou!
        }

        if (arr[meio].id < idBusca) {
            esq = meio + 1; // Busca na metade direita
        } else {
            dir = meio - 1; // Busca na metade esquerda
        }
    }
    return NULL; // Não encontrou
}

// Prepara a lista para a busca binária (converte para array e ordena por ID)
ItemBar* buscarItemBarPorIdComBuscaBinaria(int id) {
    if (listaItensBar == NULL) {
        printf("Nenhum item para buscar no cardápio.\n");
        return NULL;
    }

    // 1. Contar o número de elementos na lista
    int count = 0;
    NoItemBar *temp = listaItensBar;
    while (temp != NULL) {
        count++;
        temp = temp->proximo;
    }

    if (count == 0) {
        printf("Nenhum item cadastrado para busca binária.\n");
        return NULL;
    }

    // 2. Copiar os elementos da lista para um array
    ItemBar *itensArray = (ItemBar *)malloc(count * sizeof(ItemBar));
    if (itensArray == NULL) {
        printf("Erro de alocação de memória para busca binária.\n");
        return NULL;
    }

    temp = listaItensBar;
    for (int i = 0; i < count; i++) {
        itensArray[i] = temp->dados;
        temp = temp->proximo;
    }

    // 3. Ordenar o array por ID (necessário para a busca binária)
    // Usando Bubble Sort simples para ordenar por ID no array temporário
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (itensArray[j].id > itensArray[j+1].id) {
                ItemBar temp_item = itensArray[j];
                itensArray[j] = itensArray[j+1];
                itensArray[j+1] = temp_item;
            }
        }
    }

    // 4. Realizar a busca binária no array ordenado
    ItemBar *encontrado = buscaBinariaEmArrayBar(itensArray, 0, count - 1, id);

    // Se encontrado, faz uma cópia para retornar, pois o array será liberado
    if (encontrado != NULL) {
        ItemBar *copiaEncontrado = (ItemBar *)malloc(sizeof(ItemBar));
        if (copiaEncontrado == NULL) {
            printf("Erro de alocação de memória para cópia do item.\n");
            free(itensArray);
            return NULL;
        }
        *copiaEncontrado = *encontrado;
        free(itensArray); // Libera a memória do array temporário
        return copiaEncontrado;
    }

    free(itensArray); // Libera a memória do array temporário
    return NULL;
}