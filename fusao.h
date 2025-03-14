#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

// Definição do struct para jogador
typedef struct {
    char nome[50];
    int pontuacaoTotal;
} Jogador;

//jogo solo
void salvarPontuacao(Jogador jogador, int pontos, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "a"); // Abre o arquivo no modo append
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");//arquivo sem existir
        return;
    }

    fprintf(arquivo, "\n%s %d\n", jogador.nome, pontos);// salvar no arquivo o nome e a pontução
    fclose(arquivo);//fechar arquivo
    printf("Pontuação salva com sucesso!\n");//mensagem
}

void mostraPontuacao(Jogador jogador, int erros) {
    const char *nomeArquivo = "pontuacoes.txt";//entrar

    // Calcular a pontuação (quanto menos erros, maior a pontuação)
    int pontos = 100 - (erros * 20);
    if (pontos < 0) pontos = 0;

    // Exibir a pontuação
    printf("Você teve %d pontos.\n", pontos);

    // Salvar a pontuação no arquivo
    salvarPontuacao(jogador, pontos, nomeArquivo);
}

void forca(int estado) {//jogo a forca
    if (estado == 0) {
        printf("\n------------");
        printf("\n|          |");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 1) {
        printf("\n------------");
        printf("\n|          |");
        printf("\n|          O");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 2) {
        printf("\n------------");
        printf("\n|          |");
        printf("\n|          O");
        printf("\n|          |");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 3) {
        printf("\n------------");
        printf("\n|          |");
        printf("\n|          O");
        printf("\n|         -|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 4) {
        printf("\n------------");
        printf("\n|          |");
        printf("\n|          O");
        printf("\n|         -|-");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 5) {
        printf("\n------------");
        printf("\n|          |");
        printf("\n|          O");
        printf("\n|         -|-");
        printf("\n|         /");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 6) {
        printf("\n------------");
        printf("\n|          |");
        printf("\n|          O");
        printf("\n|         -|-");
        printf("\n|         / \\");
        printf("\n|");
        printf("\n|   Perdeu o jogo");
        printf("\n-");
        exit(0);
    }
}

void jogando() {//Executa tudo que pertence ao jogo solo
    setlocale(LC_ALL, "Portuguese");//usano a ilioteca para deixar em portugues

    Jogador jogador;

    // Capturar o nome do jogador
    printf("Digite seu nome: ");
    scanf("%s", jogador.nome);//salvar o nome o jogaor em jogador.nome

    int erros = 0;
    char palavra_secreta[30];
    char *palavras[10] = {"abacaxi", "banana", "cachorro", "dinossauro", "elefante", "foca", "girafa", "hipopotamo", "iguana", "jacare"};

    srand(time(NULL));
    int index = rand() % 10;
    strcpy(palavra_secreta, palavras[index]);

    printf("Jogando \n");
    printf("A palavra tem %lu caracteres\n", strlen(palavra_secreta));

    char palavra_tela[30];
    strcpy(palavra_tela, palavra_secreta);
    palavra_tela[strlen(palavra_tela)] = '\0';

    for (int i = 0; i < strlen(palavra_tela); i++) {
        palavra_tela[i] = '_';
    }

    while (1) {
        forca(erros);
        printf("\nAdivinhe: ");
        for (int i = 0; i < strlen(palavra_tela); i++) {
            printf("%c", palavra_tela[i]);
        }

        printf("\nLetra: ");
        char letra;
        scanf(" %c", &letra);

        int sera_que_errou = 1;
        for (int i = 0; i < strlen(palavra_tela); i++) {
            if (letra == palavra_secreta[i]) {
                palavra_tela[i] = letra;
                sera_que_errou = 0;
            }
        }
        if (sera_que_errou) {
            erros++;//erros o jogaor jogano solo
        }

        if (strcmp(palavra_tela, palavra_secreta) == 0) {
            printf("\nParabéns! Você adivinhou a palavra: %s\n", palavra_secreta);
            mostraPontuacao(jogador, erros);
            break;
        }

        if (erros >= 6) {
            printf("\nVocê perdeu! A palavra era: %s\n", palavra_secreta);
            mostraPontuacao(jogador, erros);
            break;
        }
    }
}
//fim do jogo  solo

//jogo multiplayer
char maquina[] = "maquina";

void salvar(Jogador jogador, int pontos, int pontos_maquina ,const char *pontuacoes) {
    FILE *ponteiro = fopen(pontuacoes, "a");//abrir arquivo
    if (ponteiro == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");//erro arquivo sem nada
        return;
    }
    fprintf(ponteiro, "\n%s %d\n %s %d", jogador.nome, pontos, maquina, pontos_maquina);//salvar no arquivo
    fclose(ponteiro);//fechar
    printf("Pontuação salva com sucesso!\n");
}

void mostra(Jogador jogador, int erros_jogador1, int erros_jogador2) {
    const char *pontuacoes = "pontuacoes.txt";//abrino arquivo

    // Calcular a pontuação quanto menos erros, maior a pontuação
    int pontos = 100 - (erros_jogador1 * 20); //jogador
    if (pontos < 0) pontos = 0;

    int pontos_maquina = 100 - (erros_jogador2 * 20);//maquina
    if (pontos_maquina < 0) pontos_maquina = 0;

    printf("Você teve %d pontos.\n", pontos); //mostrar pontos do jogador
    salvar(jogador, pontos, pontos_maquina ,pontuacoes);//salvando tudo no arquivo
}

char adivinhar(char palavra[], char palavra_tela[]) {
    char letra;
    int i;
    int tentada = 0;

    do {
        letra = 'a' + rand() % 26;
        tentada = 0;
        for (i = 0; i < strlen(palavra_tela); i++) {
            if (palavra_tela[i] == letra) {
                tentada = 1;
                break;
            }
        }
    } while (tentada);

    return letra;
}

void mostrarRanking(Jogador jogador) {
    FILE *ponteiro = fopen("pontuacoes.txt", "r");
    if (ponteiro == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    char nome[50];
    int pontos;
    int rank = 1;
    jogador.pontuacaoTotal = 0;
    while (fscanf(ponteiro, "%s %d", nome, &pontos) != EOF) {
        if (strcmp(nome, jogador.nome) == 0) {
            jogador.pontuacaoTotal += pontos;
        }

    }
    fclose(ponteiro);

    printf("Sua pontuação total é: %d pontos\n", jogador.pontuacaoTotal);
    printf("Você está na posição %d no ranking.\n", rank);
}

void jogando_multiplay(Jogador *jogador) {//jogo multiplay
    setlocale(LC_ALL, "Portuguese");

    int erros_jogador1 = 0;
    int erros_jogador2 = 0;
    char palavra_secreta[30];
    char *palavras[10] = {"abacaxi", "banana", "cachorro", "dinossauro", "elefante", "foca", "girafa", "hipopotamo", "iguana", "jacare"};

    srand(time(NULL));
    int index = rand() % 10;
    strcpy(palavra_secreta, palavras[index]);

    printf("Jogando \n");
    printf("A palavra tem %lu caracteres\n", strlen(palavra_secreta));

    char palavra_tela[30];
    strcpy(palavra_tela, palavra_secreta);
    palavra_tela[strlen(palavra_tela)] = '\0';

    for (int i = 0; i < strlen(palavra_tela); i++) {
        palavra_tela[i] = '_';
    }

    while (1) {
        forca(erros_jogador1);
        forca(erros_jogador2);
        printf("\nAdivinhe: ");
        for (int i = 0; i < strlen(palavra_tela); i++) {
            printf("%c", palavra_tela[i]);
        }

        printf("\nLetra: ");
        char letra;
        scanf(" %c", &letra);

        int sera_que_errou = 1;
        for (int i = 0; i < strlen(palavra_tela); i++) {
            if (letra == palavra_secreta[i]) {
                palavra_tela[i] = letra;
                sera_que_errou = 0;
            }
        }
        if (sera_que_errou) {
            erros_jogador1++;
        }

        if (strcmp(palavra_tela, palavra_secreta) == 0) {
            printf("\nParabéns! Você adivinhou a palavra: %s\n", palavra_secreta);
            mostra(*jogador, erros_jogador1, erros_jogador2);
            mostrarRanking(*jogador);
            return;
        }

        if (erros_jogador1 >= 6) {
            printf("\nVocê perdeu! A palavra era: %s\n", palavra_secreta);
            mostra(*jogador, erros_jogador1, erros_jogador1);
            mostrarRanking(*jogador);
            return;
        }

        if (strcmp(palavra_tela, palavra_secreta) != 0) {
            char letra_computador = adivinhar(palavra_secreta, palavra_tela);
            printf("\n(PC) Alex escolheu a letra: %c\n", letra_computador);

            int computador_errou = 1;
            for (int i = 0; i < strlen(palavra_tela); i++) {
                if (letra_computador == palavra_secreta[i]) {
                    palavra_tela[i] = letra_computador;
                    computador_errou = 0;
                }
            }
            if (computador_errou) {
                erros_jogador2++;
            }

            if (strcmp(palavra_tela, palavra_secreta) == 0) {
                printf("\n Alex venceu! A palavra era: %s\n", palavra_secreta);
                mostra(*jogador, erros_jogador1 ,erros_jogador2);
                mostrarRanking(*jogador);
                return;
            }
        }
    }
}

void multiplay() {//Executa tudo que pertence ao jogo multiplay
    Jogador jogador;
    jogador.pontuacaoTotal = 0;

    printf("Digite seu nome: ");
    scanf("%s", jogador.nome);

    jogando_multiplay(&jogador);

}
//fim do jogo multiplayer

void jogar() {

    while(1){
        int fusao;
        printf("\nMODO:\n[1]solo\n[2]multiplayer\nOPÇÃO: ");//menu de escolha
        while (scanf("%d", &fusao) != 1){//guarda resposta e executa no switch case
            while (getchar() !='\n');
            printf("Opção invalida. Tente novamente.\n"); // Opção invalida
            printf("\nMODO:\n[1]solo\n[2]multiplayer\nOPÇÃO: ");
        }
        switch (fusao) {
            case 1:
                jogando();//chamno o jogo solo
                return 0;
            case 2:
                multiplay();//chamno o jogo multiplay
                return 0;
            default:
                printf("Modo inválido.\n");//usuario digitou opção errada
        }
    }
}
