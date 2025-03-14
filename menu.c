    //Bibliotecas
    #include <stdio.h>
    #include <locale.h>

    //Chamar arquivos
    #include "fusao.h"
    #include "rank.h"

    int main() {
        // Configurar idioma
        setlocale(0, "portuguese");

        // Variaveis
        int escolha;

        // Logica do menu
        while (1) {  // Loop infinito até o usuario escolher ate ele "sair"
            printf("\nMenu: \n [1] Jogar\n [2] Rank\n [3] Sair\nEscolha a opção: ");
            while (scanf("%d", &escolha) != 1){
                while (getchar() !='\n');
                printf("Opção invalida. Tente novamente.\n"); // Opção invalida
                printf("\nMenu: \n [1] Jogar\n [2] Rank\n [3] Sair\nEscolha a opção: ");
            }

            // Logica das opções

            switch (escolha) {
                case 1:
                    jogar(); // Chamar a função jogar
                    break;
                case 2:
                    rank(); // Chamar a função rank
                    break;
                case 3:
                    printf("Saindo...\n"); // Sair do loop
                    return 0;
                default:
                    printf("Opção invalida. Tente novamente.\n"); // Opção invalida
                    break;
            }
        }
    }
