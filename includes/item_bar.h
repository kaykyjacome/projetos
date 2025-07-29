#ifndef ITEM_BAR_H
#define ITEM_BAR_H

// Estrutura para representar um Item do Cardápio do Bar
typedef struct {
    int id;
    char nome[60]; // Aumentei um pouco o tamanho do nome
    float preco;
    int estoque; // Estoque em vez de quantidade
    char tipo[30]; // Novo campo: tipo (bebida, comida, etc.)
} ItemBar;

// Nó da lista encadeada para Itens do Bar
typedef struct NoItemBar {
    ItemBar dados;
    struct NoItemBar *proximo;
} NoItemBar;

// Variável global para a cabeça da lista de itens do bar
extern NoItemBar *listaItensBar;

// --- Funções da Lista Encadeada ---
void adicionarItemBar(ItemBar novoItem);
void listarItensBar();
ItemBar* buscarItemBarPorId(int id);
void editarItemBar(int id);
void excluirItemBar(int id);
void liberarListaItensBar();

// --- Funções de Ordenação e Busca ---
void ordenarItensBarPorPreco(); // Usa MergeSort
ItemBar* buscarItemBarPorIdComBuscaBinaria(int id); // Usa Busca Binária

// --- Funções Auxiliares para MergeSort ---
NoItemBar* mergeSortBar(NoItemBar* head);
NoItemBar* dividirListaBar(NoItemBar* head);
NoItemBar* unirListasBar(NoItemBar* a, NoItemBar* b);

// --- Função Auxiliar para Busca Binária (converte lista para array temporariamente) ---
ItemBar* buscaBinariaEmArrayBar(ItemBar arr[], int esq, int dir, int idBusca);

#endif