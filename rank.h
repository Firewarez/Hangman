#include <stdio.h>
#include <locale.h>

void aparecer(const char *arquivo) {
    FILE *abrir = fopen(arquivo, "r"); // Abre o arquivo no modo leitura
    if (abrir == NULL) {
        printf("Erro ao abrir o arquivo ou arquivo não encontrado.\n");
        return;
    }

    printf("\n=== Pontuações Registradas ===\n");
    char nome[50];
    int pontuacao;
    while (fscanf(abrir, "%s %d", nome, &pontuacao) != EOF) {
        printf("Jogador: %s - Pontuação: %d\n", nome, pontuacao);
    }
    printf("================================\n");

    fclose(abrir);
}

void rank() {
    setlocale(LC_ALL, "Portuguese");

    const char *pontuacoes = "pontuacoes.txt";
    aparecer(pontuacoes);

}