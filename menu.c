#include <stdio.h>
#include "menu.h"
#include "jogo.h"

void CriarMenu() {
    system("cls");
    char entrada[50];
    int OqueFazer = 0;
    printf("#####################################################################"
        "######\n");
    printf("#                                                                    "
        "     #\n");
    printf("#                  +++++++++++++++++++++++++++++++++++++             "
        "     #\n");
    printf("#                  +     J O G O   D E   PACIสNCIA     +             "
        "     #\n");
    printf("#                  +++++++++++++++++++++++++++++++++++++             "
        "     #\n");
    printf("#                                                                    "
        "     #\n");
    printf("#                          >Selecione uma Opcao<                     "
        "     #\n");
    printf("#                  จจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจ             "
        "     #\n");
    printf("#                                                                    "
        "     #\n");
    printf("#                                                                    "
        "     #\n");
    printf("#  [1]  --> INICIAR JOGO                                             "
        "     #\n");
    printf("#                                                                    "
        "     #\n");
    printf("#  [2]  --> Ajuda-Tutorial                                           "
        "     #\n");
    printf("#                                                                    "
        "     #\n");
    printf("#  [3]  --> Ranking                                                  "
        "     #\n");
    printf("#                                                                    "
        "     #\n");
    printf("#  [sair!]  --> Sair do jogo                                         "
        "     #\n");
    printf("#                                                                    "
        "     #\n");
    printf("#####################################################################"
        "######\n");
    printf("Digite: ");
    fflush(stdin);
    scanf("%s", entrada);
    printf("\n");

    if (!strcmp(entrada, "sair!")) {
        return;
    }
    else if (!strcmp(entrada, "1")) {
        OqueFazer = 1;
    }
    else if (!strcmp(entrada, "2")) {
        OqueFazer = 2;
    }
    else if (!strcmp(entrada, "3")) {
        OqueFazer = 3;
    }
    else {
        CriarMenu();
    }

    switch (OqueFazer) {
    case 1: {
        CriarJogador();
        break;
    }
    case 2: {
        Tutorial();
        break;
    }
    case 3: {
        AbrirRanking();
        break;
    }
      Default: {
          printf("\n");
          CriarMenu();
          break;
    }
    }
}
