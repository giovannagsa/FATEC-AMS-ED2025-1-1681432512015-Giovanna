#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50
#define MAX_NOME 100

typedef struct {
    char nome[MAX_NOME];
    float notasPE[4];
    float notasAC[5];
    float notasPP[10];
    float notasEB[3];
    float notaFinal;
} Candidato;

void inserirNotas(float *notas, int tamanho, char *tipo) {
    printf("\nDigite as notas para %s:\n", tipo);
    for (int i = 0; i < tamanho; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

float calcularNotaFinal(float *notas, int tamanho) {
    float soma = 0.0, maior = notas[0], menor = notas[0];
    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }
    return (soma - maior - menor) / (tamanho - 2);
}

void ordenarCandidatos(Candidato *candidatos, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (candidatos[j].notaFinal < candidatos[j + 1].notaFinal) {
                Candidato temp = candidatos[j];
                candidatos[j] = candidatos[j + 1];
                candidatos[j + 1] = temp;
            }
        }
    }
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int numCandidatos = 0;
    
    printf("Quantos candidatos deseja cadastrar? (Máximo %d): ", MAX_CANDIDATOS);
    scanf("%d", &numCandidatos);
    if (numCandidatos > MAX_CANDIDATOS) numCandidatos = MAX_CANDIDATOS;
    getchar(); // Consumir a quebra de linha pendente
    
    for (int i = 0; i < numCandidatos; i++) {
        printf("\nNome do candidato %d: ", i + 1);
        fgets(candidatos[i].nome, MAX_NOME, stdin);
        candidatos[i].nome[strcspn(candidatos[i].nome, "\n")] = 0; // Remover a quebra de linha
        
        inserirNotas(candidatos[i].notasPE, 4, "Prova Escrita");
        inserirNotas(candidatos[i].notasAC, 5, "Análise Curricular");
        inserirNotas(candidatos[i].notasPP, 10, "Prova Prática");
        inserirNotas(candidatos[i].notasEB, 3, "Entrevista Banca");
        
        float pe = calcularNotaFinal(candidatos[i].notasPE, 4);
        float ac = calcularNotaFinal(candidatos[i].notasAC, 5);
        float pp = calcularNotaFinal(candidatos[i].notasPP, 10);
        float eb = calcularNotaFinal(candidatos[i].notasEB, 3);
        
        candidatos[i].notaFinal = (pe * 0.3) + (ac * 0.1) + (pp * 0.4) + (eb * 0.2);
    }
    
    ordenarCandidatos(candidatos, numCandidatos);
    
    printf("\nTop 5 Candidatos:\n");
    for (int i = 0; i < (numCandidatos < 5 ? numCandidatos : 5); i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].notaFinal);
    }
    
    return 0;
}
