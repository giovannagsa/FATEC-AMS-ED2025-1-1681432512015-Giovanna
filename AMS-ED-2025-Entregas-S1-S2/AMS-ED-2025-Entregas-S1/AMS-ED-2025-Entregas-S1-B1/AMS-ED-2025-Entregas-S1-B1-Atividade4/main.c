
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define MAX_SIZE 100
 
// Estrutura da Pilha
typedef struct {
    double data[MAX_SIZE];
    char exp[MAX_SIZE][300];  // Armazena as expressões matemáticas
    int top;
} Pilha;
 
// Criar pilha vazia
Pilha* criar_pilha() {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->top = -1;
    return pilha;
}
 
// Verificar se a pilha está vazia
int pilha_vazia(Pilha* pilha) {
    return pilha->top == -1;
}
 
// Verificar se a pilha está cheia
int pilha_cheia(Pilha* pilha) {
    return pilha->top == MAX_SIZE - 1;
}
 
// Empilhar número e expressão correspondente
void push(Pilha* pilha, double valor, const char* exp) {
    if (pilha_cheia(pilha)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    pilha->top++;
    pilha->data[pilha->top] = valor;
    strncpy(pilha->exp[pilha->top], exp, sizeof(pilha->exp[pilha->top]) - 1);
    pilha->exp[pilha->top][sizeof(pilha->exp[pilha->top]) - 1] = '\0';  // Garante terminação
}
 
// Desempilhar número e expressão correspondente
double pop(Pilha* pilha, char* exp) {
    if (pilha_vazia(pilha)) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    strcpy(exp, pilha->exp[pilha->top]);  
    return pilha->data[pilha->top--];
}
 
// Processar expressão RPN
void calcular_rpn(char* expressao) {
    Pilha* pilha = criar_pilha();
    char* token = strtok(expressao, " ");
 
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            // Se for número, converte e empilha
            push(pilha, atof(token), token);
        } else {
            // Se for operador, desempilha dois valores e executa a operação
            if (pilha->top < 1) {
                printf("Erro: Expressão inválida!\n");
                free(pilha);
                return;
            }
 
            char a_exp[300], b_exp[300];
            double b = pop(pilha, b_exp);
            double a = pop(pilha, a_exp);
            double resultado = 0;
            char operador = token[0];
 
            switch (operador) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Erro: Divisão por zero!\n");
                        free(pilha);
                        return;
                    }
                    resultado = a / b;
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    free(pilha);
                    return;
            }
 
            // Criar a expressão infixa correspondente
            int tamanho = snprintf(NULL, 0, "(%s %c %s)", a_exp, operador, b_exp) + 1;
            char* resultado_exp = malloc(tamanho);
            snprintf(resultado_exp, tamanho, "(%s %c %s)", a_exp, operador, b_exp);
 
            // Empilhar o resultado e a nova expressão
            push(pilha, resultado, resultado_exp);
            free(resultado_exp);
        }
        token = strtok(NULL, " ");
    }
 
    if (pilha->top != 0) {
        printf("Erro: Expressão inválida!\n");
    } else {
        char resultado_exp[300];
        double resultado = pop(pilha, resultado_exp);
        printf("Resultado: %.2f\n", resultado);
        printf("Expressão: %s\n", resultado_exp);
    }
 
    free(pilha);
}
 
int main() {
    char expressao[100];
 
    printf("Digite a expressão em RPN: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0;  // Remover nova linha
 
    calcular_rpn(expressao);
 
    return 0;
}
 