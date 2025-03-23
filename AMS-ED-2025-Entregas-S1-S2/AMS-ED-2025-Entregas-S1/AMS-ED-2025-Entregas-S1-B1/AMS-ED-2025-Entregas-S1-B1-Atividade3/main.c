#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Pedido
typedef struct Pedido {
    int numero;
    char nome_cliente[50];
    char descricao_prato[100];
    int quantidade;
    char status[20];
    struct Pedido* proximo;
} Pedido;

// Estrutura da Lista de Pedidos
typedef struct {
    Pedido* head;
} ListaPedidos;

// Criar lista de pedidos
ListaPedidos* criar_lista() {
    ListaPedidos* lista = (ListaPedidos*)malloc(sizeof(ListaPedidos));
    if (!lista) {
        printf("Erro ao criar lista!\n");
        exit(1);
    }
    lista->head = NULL;
    printf("Lista de pedidos criada com sucesso!\n");
    return lista;
}

// Inserir novo pedido
void inserir_pedido(ListaPedidos* lista) {
    Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    printf("Digite o número do pedido: ");
    scanf("%d", &novo->numero);
    getchar();
    printf("Digite o nome do cliente: ");
    fgets(novo->nome_cliente, sizeof(novo->nome_cliente), stdin);
    strtok(novo->nome_cliente, "\n");
    printf("Digite a descrição do prato: ");
    fgets(novo->descricao_prato, sizeof(novo->descricao_prato), stdin);
    strtok(novo->descricao_prato, "\n");
    printf("Digite a quantidade: ");
    scanf("%d", &novo->quantidade);
    getchar();
    strcpy(novo->status, "Pendente");
    novo->proximo = lista->head;
    lista->head = novo;
    printf("Pedido adicionado com sucesso!\n");
}

// Obter um pedido específico
void obter_pedido(ListaPedidos* lista) {
    int numero;
    printf("Digite o número do pedido: ");
    scanf("%d", &numero);
    Pedido* atual = lista->head;
    while (atual) {
        if (atual->numero == numero) {
            printf("Pedido #%d | Cliente: %s | Prato: %s | Quantidade: %d | Status: %s\n",
                   atual->numero, atual->nome_cliente, atual->descricao_prato, atual->quantidade, atual->status);
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido não encontrado!\n");
}

// Atualizar status de um pedido
void atualizar_status(ListaPedidos* lista) {
    int numero;
    char novo_status[20];
    printf("Digite o número do pedido: ");
    scanf("%d", &numero);
    getchar();
    Pedido* atual = lista->head;
    while (atual) {
        if (atual->numero == numero) {
            printf("Digite o novo status: ");
            fgets(novo_status, sizeof(novo_status), stdin);
            strtok(novo_status, "\n");
            strcpy(atual->status, novo_status);
            printf("Status atualizado!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido não encontrado!\n");
}

// Deletar um pedido
void deletar_pedido(ListaPedidos* lista) {
    int numero;
    printf("Digite o número do pedido a deletar: ");
    scanf("%d", &numero);
    Pedido *atual = lista->head, *anterior = NULL;
    while (atual) {
        if (atual->numero == numero) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                lista->head = atual->proximo;
            free(atual);
            printf("Pedido deletado com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Pedido não encontrado!\n");
}

// Liberar toda a memória da lista
void liberar_lista(ListaPedidos* lista) {
    Pedido* atual = lista->head;
    while (atual) {
        Pedido* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista);
    printf("Lista liberada com sucesso!\n");
}

// Menu
int main() {
    ListaPedidos* lista = NULL;
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Criar Lista de Pedidos\n");
        printf("2. Inserir Pedido\n");
        printf("3. Obter Pedido\n");
        printf("4. Atualizar Status do Pedido\n");
        printf("5. Deletar Pedido\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1:
                if (!lista)
                    lista = criar_lista();
                else
                    printf("A lista já foi criada!\n");
                break;
            case 2:
                if (lista)
                    inserir_pedido(lista);
                else
                    printf("Crie a lista primeiro!\n");
                break;
            case 3:
                if (lista)
                    obter_pedido(lista);
                else
                    printf("Crie a lista primeiro!\n");
                break;
            case 4:
                if (lista)
                    atualizar_status(lista);
                else
                    printf("Crie a lista primeiro!\n");
                break;
            case 5:
                if (lista)
                    deletar_pedido(lista);
                else
                    printf("Crie a lista primeiro!\n");
                break;
            case 6:
                if (lista)
                    liberar_lista(lista);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);
    return 0;
}