#include "jogo.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void CriarJogador() {
    
    printf("Digite o nome do jogador:");
    scanf("%s", nomeTemp);
    IniciarJogo();

}

void AdicionarEspaco(int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("\n");
    }
}


void IniciarJogo() {    
    char naipe;
    char escolha[20];
    int linha, colunaOrigem, colunaDestino;

    srand(time(NULL)); // retira informa��es da hora do sistema para a cria��o de
                       // numeros randomicos

    CriarMonte();
    EmbaralharMonte();
    DistribuirCartas();
    //time(&segundos);
    //horaInicial = localtime(&segundos);

    start = time(NULL);

    while ((strcmp("sair", escolha)) != 0) {
        system("cls");
        diff = time(NULL) - start;
        AdicionarEspaco(10);
        printf("'proxima' para mostrar a pr�xima carta do monte.\n");
        printf("'mover' para trocar uma carta de coluna\n");
        printf("'movermontebaixo' para mover uma carta do monte para a pilha de baixo\n");
        printf("'moverbaixocima' mover uma carta da pilha de baixo para a pilha de cima.\n");
        printf("'movermontecima' mover uma carta do monte para a pilha de cima.\n");
        printf("'salvar' para salvar sua pontuacao e sair do jogo.\n");

        printf("\n \nTempo de Jogo: %d segundos", diff);

        imprimeCartas(); // dentro do while porque sempre que fizer uma a��o,
                         // reimprime o monte, atualizado
        scanf("%s", escolha);

        if ((strcmp("proxima", escolha)) == 0) {
            ProximaCarta();
        }
        else if ((strcmp("mover", escolha)) == 0) {
            printf("Digite a linha e coluna da carta que voc� deseja mover.\n");
            scanf("%d %d", &linha, &colunaOrigem);
            printf("Digite a coluna onde voc� deseja colocar a carta.\n");
            scanf("%d", &colunaDestino);
            MoverPilhaBaixoBaixo(linha, colunaOrigem, colunaDestino);
        }
        else if ((strcmp("movermontebaixo", escolha)) == 0) {
            printf("Digite a coluna onde deseja colocar a carta.\n");
            scanf("%d", &colunaDestino);
            MoverMontePilhaBaixo(colunaDestino);
        }
        else if ((strcmp("moverbaixocima", escolha)) == 0) {
            printf("Digite a coluna da carta que deseja mover.\n");
            scanf("%d", &colunaOrigem);
            MoverPilhaBaixoPilhaCima(colunaOrigem);
        } else if ((strcmp("movermontecima", escolha)) == 0) {
            MoverMontePilhaCima();
        }
        //else if ((strcmp("pontuacao", escolha)) == 0) {
        //    //time(&segundos);
        //    //horaFinal = localtime(&segundos);
        //    diff = time(NULL) - start;            
        //}
        else if ((strcmp("salvar", escolha)) == 0) {
            pontuacaoTemp = time(NULL) - start;
            if (pontuacaoTemp != 0) {
                GravaRanking();
                return 0;
            }

        }
        else if ((strcmp("rak", escolha)) == 0) {
            LeArquivoInicio();
            return 0;
        }
    }
}

void Tutorial() {

    system("clear");

    printf(" \n\n 1 - Entenda o objetivo do jogo. Voc� dever� criar quatro "
        "pilhas de "
        "cartas, uma para cada naipe, em ordem crescente (come�ando com o �s "
        "e terminando com o rei. \n\n\n");

    printf(" 2 - Prepare o jogo. Coloque uma carta virada para cima e mais seis "
        "viradas para baixo ao lado dela. Agora, posicione cartas sobre as "
        "que est�o viradas para baixo de forma que sete pilhas sejam "
        "formadas. A primeira pilha ter� apenas a carta que est� virada para "
        "cima, e as outras ter�o, respectivamente, 2, 3, 4, 5, 6 e 7 cartas. "
        "A carta que estiver no topo de cada pilha deve sempre ficar virada "
        "para cima como mostrado na imagem. \n\n\n");

    printf(
        " 3 - Coloque as cartas restantes em uma pilha separada e posicione-a "
        "acima ou abaixo das outras. Essa pilha dever� ser usada para conseguir "
        "mais cartas caso voc� fique sem op��es de movimenta��o. \n\n\n");

    printf(" 4 - Deixe espa�os no topo para outras quatro pilhas acima das "
        "iniciais. Essas pilhas, que chamaremos de pilhas de montagem, s�o as "
        "que ser�o usadas para guardar as sequ�ncias crescentes de cada "
        "naipe. \n\n\n");

    printf(" 5 - Veja as cartas viradas para cima. Se houver ases, coloque cada "
        "um deles em uma das pilhas de montagem; caso contr�rio, reorganize "
        "as cartas dispon�veis, movendo apenas as que estiverem viradas para "
        "cima. Para movimentar uma carta, voc� dever� retir�-la do topo de "
        "sua pilha atual e posicion�-la sobre a carta superior de uma outra "
        "pilha. Para que isso seja poss�vel, a carta que est� no topo da "
        "pilha de destino dever� ser de cor diferente e ter o valor de uma "
        "unidade a mais. Sobre um seis de copas, por exemplo, � permitido "
        "colocar um cinco de paus ou de espadas. Continue movimentando as "
        "cartas at� que voc� n�o tenha mais op��es de movimenta��o. Cada "
        "pilha (exceto as de montagem) deve estar alternando as cores de suas "
        "cartas, que por sua vez devem estar em ordem decrescente.\n\n\n");

    printf(" 6 - Construa pilhas usando ases como base. Se houver um �s em uma "
        "das quatro pilhas de montagem (no final, todos eles devem estar em "
        "uma delas), voc� dever� colocar mais cartas do mesmo naipe sobre ele "
        "em ordem crescente (A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K). Para "
        "vencer, essa sequ�ncia crescente deve ser feita nas quatro pilhas de "
        "montagem, uma para cada naipe. \n\n\n");

    printf(
        " 7 -Use as cartas reservas se voc� ficar sem op��es de movimenta��o. "
        "Vire as tr�s cartas superiores da pilha reserva e veja se � poss�vel "
        "colocar a primeira delas em algum lugar. Se voc� tiver sorte, haver� um "
        "�s nessa posi��o! Se for poss�vel colocar a primeira em alguma pilha, "
        "fa�a o mesmo com a segunda e por fim tente posicionar a terceira. Ao "
        "conseguir posicionar essas tr�s cartas, puxe outras tr�s da pilha "
        "reserva. Por outro lado, se n�o houver op��es de movimenta��o com "
        "nenhuma das tr�s, coloque-as em uma pilha de descarte separada (sem "
        "mudar a ordem). Repita o processo at� que a pilha reserva acabe. Se a "
        "pilha reserva acabar, use a pilha de descarte. Entretanto, "
        "certifique-se de que voc� n�o a embaralhou! \n\n\n");

    printf(" 8 - Se uma carta estiver embaixo de outra, voc� poder� fazer "
        "movimenta��es at� conseguir alcan�ar essa carta desejada e, "
        "eventualmente, coloc�-la no local que desejar. \n\n\n");

    printf(" 9 - Se voc� utilizar todas as cartas de uma pilha, ser� permitido "
        "colocar um rei no espa�o que agora est� vazio. No entanto, "
        "lembre-se: apenas o rei poder� ser colocado nessa posi��o. \n\n\n");

    printf(" 10 - Paci�ncia dos quarenta ladr�es. Essa vers�o do jogo � mais "
        "f�cil que a tradicional porque voc� pode ver todas as cartas das "
        "pilhas (por elas estarem todas viradas para cima). O objetivo � "
        "ainda � formar uma pilha para cada naipe em ordem crescente. Ao "
        "preparar as cartas, posicione 10 pilhas de quatro cartas, todas "
        "viradas para cima. Voc� pode mover apenas a carta que est� no topo "
        "de cada pilha em uma jogada. Existem quatro espa�os sobre as pilhas "
        "iniciais al�m dos usados pelas pilhas de montagem. Eles ser�o usados "
        "pelas pilhas auxiliares. Elas s�o usadas para segurar uma carta que "
        "est� no topo de uma das pilhas principais, dando acesso � carta de "
        "baixo. Voc� poder� usar as cartas da pilha de reserva, mas s� � "
        "permitido ver uma carta de cada vez, n�o tr�s. \n\n\n");

    printf(
        " 11 - Paci�ncia Freecell. Essa � uma das vers�es mais dif�ceis do jogo. "
        "Ela exige ainda mais racioc�nio do que Paci�ncia normal, pois n�o h� "
        "pilha reserva para ajudar. O objetivo dessa vers�o tamb�m � fazer uma "
        "pilha para cada naipe em ordem crescente. Posicione todas as cartas em "
        "oito pilhas, quatro dessas pilhas devem ter sete cartas e as demais "
        "devem conter seis cartas. Nenhuma pilha reserva poder� ser utilizada. "
        "Todas as cartas devem estar nas pilhas iniciais. Assim como no "
        "paci�ncia dos quarenta ladr�es, existem quatro pilhas auxiliares, ent�o "
        "deixe espa�o para elas. Apenas a carta superior de cada pilha poder� "
        "ser movida, mas � poss�vel mover uma carta para uma dessas pilhas "
        "auxiliares para ter acesso a carta que est� embaixo. \n\n\n");

    printf(" 12 - Paci�ncia Golf. Essa � uma varia��o do jogo onde o objetivo � "
        "mover todas as cartas das sete pilhas em vez de criar quatro pilhas "
        "de cada naipe. Posicione sete pilhas com quatro cartas viradas para "
        "cima em cada uma delas. As outras cartas devem ser colocadas viradas "
        "para baixo na pilha reserva. Vire a carta superior da pilha reserva. "
        "Voc� dever� agora tentar posicionar a carta superior de qualquer uma "
        "das outras sete pilhas sobre esta carta da pilha reserva. Quando n�o "
        "houver nenhuma op��o de movimenta��o, vire a pr�xima carta da pilha "
        "reserva e repita o processo com ela. Continue jogando at� que voc� "
        "tenha movimentado todas as cartas das pilhas iniciais ou at� que n�o "
        "existam mais movimentos poss�veis. \n\n\n");

    printf(
        " 13 - Paci�ncia pir�mide. O objetivo dessa vers�o � remover todas as "
        "cartas da pir�mide e da pilha reserva e coloc�-las na pilha de descarte "
        "ao criar pares que juntos tenham o valor 13. Posicione 28 cartas em "
        "formato de pir�mide, todas viradas para cima. Elas devem ser dispostas "
        "em linhas de forma que a primeira deve ter uma carta, a segunda duas, a "
        "pr�xima tr�s, e assim por diante, at� que todas as 28 cartas tenham "
        "sido posicionadas. Cada linha deve sobrepor � que est� acima. Algumas "
        "pessoas usam apenas 21 cartas para formar a pir�mide. Crie uma pilha "
        "reserva com as cartas restantes. Remova as cartas em pares. Voc� poder� "
        "remover as cartas apenas se o valor combinado delas for 13. Os reis "
        "valem 13 pontos, as rainhas 12, os valetes 11 e as demais cartas t�m o "
        "valor que elas mostram (o �s vale 1). Voc� pode, por exemplo, remover "
        "um rei sozinho. � poss�vel tamb�m remover um 8 junto com um 5, pois a "
        "soma deles � 13. A carta superior da pilha reserva tamb�m poder� ser "
        "usada para gerar a soma 13. Se nenhum par puder se formar, a pr�xima "
        "carta reserva dever� ser virada. Quando todas as cartas reservas "
        "acabarem, voc� poder� usar cartas da pilha de descarte para compor a "
        "pilha reserva e continuar reduzindo a pir�mide. \n\n\n");

    printf(" 14 - Paci�ncia Spider. Para jogar essa vers�o, ser�o necess�rios "
        "dois baralhos. Fa�a 10 pilhas. Quatro delas com seis cartas cada e "
        "as outras seis com cinco cada. Apenas a carta superior dever� ficar "
        "virada para cima. As cartas n�o usadas inicialmente devem ficar na "
        "pilha reserva. O objetivo � criar sequ�ncias decrescentes de mesmo "
        "naipe, desde o rei at� o �s. Ao completar uma sequ�ncia decrescente, "
        "voc� dever� mov�-la para uma das 8 pilhas de montagem. As pilhas de "
        "montagem n�o podem ser usadas como pilhas auxiliares, ou seja, elas "
        "n�o podem segurar cartas. Para vencer, ser� necess�rio criar 8 "
        "sequ�ncias decrescentes, cada uma delas posicionada sobre uma pilha "
        "de montagem. � poss�vel formar pequenas sequ�ncias (como 9, 8 e 7 de "
        "espadas) e coloc�-las, por exemplo, sobre um 10 de copas ou de "
        "qualquer outro naipe para dar espa�o a outras movimenta��es. \n\n\n");
}

void CriarMonte(void) {
    int naipe, carta;
    noCarta* no = NULL;

    no = malloc(sizeof(noCarta));

    monte = no;

    for (naipe = 0; naipe < 4; naipe++) {

        for (carta = 1; carta <= 13; carta++) {

            no->valor = carta;

            if (naipe == 0)
                no->naipe = 'p';
            else if (naipe == 1)
                no->naipe = 'c';
            else if (naipe == 2)
                no->naipe = 'e';
            else if (naipe == 3)
                no->naipe = 'o';

            if (naipe != 3 || carta != 13) {
                no->prox = malloc(sizeof(noCarta));
                no = no->prox;
            }
            else {
                no->prox = NULL;
            }
        }
    }
}

// Remove uma carta do monte para distribuir, sem quebrar a lista
noCarta* RemoveCartaMonte(int posicao) {
    noCarta* atual = monte;
    noCarta* anterior = NULL;

    int cartas;

    // la�o para retirar a cart�o desejada que foi passada aleatoriamente no
    // parametro posi��o
    for (cartas = 0; cartas < posicao;
        cartas++) {    // movimentar na lista de 52 cartas.
        anterior = atual; // para n�o quebrar a lista
        atual = atual->prox;
    }

    // caso remova a carta que incia o monte, passa o inicio do monte para a
    // proxima carta
    if (atual == monte)
        monte = monte->prox;
    else // passa o proximo anterior para o proximo do atual, pois o atual vai
         // deixar de existir
        anterior->prox = atual->prox;

    return (atual); // retorna a carta que vai ser removida
}

void EmbaralharMonte() {
    noCarta* no = NULL, * novoMonte = NULL;
    int carta;

    no = RemoveCartaMonte(rand() % 52);
    novoMonte = no;

    for (carta = 51; carta > 0; carta--) {
        no->prox = RemoveCartaMonte(rand() %
            carta); // carta aleatorio para o proximo do no
        no = no->prox; // atribui ao no esse prox aleat�rio obtido acima
    }

    no->prox = NULL; // finaliza a lista

    monte = novoMonte; // adiciona o monte embaralhado ao monte
}

void DistribuirCartas() {
    noCarta* atual = NULL;
    int c1, c2;

    for (c1 = 0; c1 < 7; c1++) {
        pilhaDeBaixo[c1] = monte; // posicao 0 da fila, recebe monte

        for (c2 = 0; c2 <= c1; c2++)
            monte = monte->prox; // redefine o valor do monte para o proximo de monte

        atual =
            pilhaDeBaixo[c1]; // ponteiro atual recebe valor que era atual do monte

        while (atual->prox != monte)
            atual = atual->prox; // define o proximo do atual como o monte

        atual->prox = NULL;
        linhaEscondida[c1] = c1; // define as linhas que s�o 7
    }
}

void imprimeCartas(void) {
    noCarta* baixo[7], * cima[4];
    int c1, c2;

    printf("\n\n\n");

    for (c1 = 0; c1 < 4; c1++)
        cima[c1] = pilhaDeCima[c1];

    for (c1 = 0; c1 < 7; c1++)
        baixo[c1] = pilhaDeBaixo[c1];

    printf("Monte ->  ");
    if (atual == NULL)
        printf("[   ]");
    else
        printf("[%2d%c]", atual->valor, atual->naipe);

    printf("       ");

    for (c1 = 0; c1 < 4; c1++) {
        if (cima[c1] == NULL)
            printf("[   ] ");
        else {
            while (cima[c1]->prox != NULL)
                cima[c1] = cima[c1]->prox;
            printf("[%2d%c] ", cima[c1]->valor, cima[c1]->naipe);
        }
    }

    printf("\n\n");
    printf("      0     1     2     3     4     5     6\n\n");

    c1 = -1;

    while (baixo[0] != NULL || baixo[1] != NULL || baixo[2] != NULL ||
        baixo[3] != NULL || baixo[4] != NULL || baixo[5] != NULL ||
        baixo[6] != NULL) {
        c1++;
        printf("%2d  ", c1);

        for (c2 = 0; c2 < 7; c2++)
            if (baixo[c2] != NULL) {
                if (linhaEscondida[c2] <= c1)
                    printf("[%2d%c] ", baixo[c2]->valor, baixo[c2]->naipe);
                else
                    printf("[???] ");
                baixo[c2] = baixo[c2]->prox;
            }
            else
                printf("      ");

        printf("\n");
    }
    printf("\n");
}

void ProximaCarta() {
    if (atual == NULL)
        atual = monte;
    else
        atual = atual->prox;
}

int podeMover(noCarta* colunaOrigem, noCarta* colunaDestino) {
    if (colunaOrigem->valor != (colunaDestino->valor - 1) ||
        colunaOrigem->prox != NULL) {
        return 0; // valida se a carta � um n�mero menor que o destino
    }

    while (colunaOrigem->prox != NULL) {
        if (colunaOrigem->valor != (colunaOrigem->prox->valor + 1))
            return 0;
        colunaOrigem = colunaOrigem->prox;
    }

    // verifica as combina��es se pode mover por naipe
    if ((colunaDestino->naipe == 'c' && colunaOrigem->naipe == 'o') ||
        (colunaDestino->naipe == 'o' && colunaOrigem->naipe == 'c') ||
        (colunaDestino->naipe == 'p' && colunaOrigem->naipe == 'e') ||
        (colunaDestino->naipe == 'e' && colunaOrigem->naipe == 'p') ||
        (colunaDestino->naipe == 'c' && colunaOrigem->naipe == 'c') ||
        (colunaDestino->naipe == 'e' && colunaOrigem->naipe == 'e') ||
        (colunaDestino->naipe == 'o' && colunaOrigem->naipe == 'o') ||
        (colunaDestino->naipe == 'p' && colunaOrigem->naipe == 'p'))
        return 0;

    return 1;
}

int MoverPilhaBaixoBaixo(int linha, int colunaOrigem, int colunaDestino) {
    noCarta* posicaoDestino = NULL, * posicaoOrigem = NULL,
        * posicaoOrigemAnterior = NULL;
    int c;

    posicaoDestino = pilhaDeBaixo[colunaDestino];
    posicaoOrigem = pilhaDeBaixo[colunaOrigem];

    //if (posicaoOrigem == NULL)
    //  return 0;

    if (EstaVazia(posicaoOrigem)) {
        return 0;
    }

    for (c = 0; c < linha; c++) { // la�o para movimentar na pilha e pegar a carta na linha desejada
        posicaoOrigemAnterior = posicaoOrigem; // essa movimenta��o para n�o quebrar a lista
        posicaoOrigem = posicaoOrigem->prox;
        if (posicaoOrigem == NULL)
            return 0;
    }

    //  if (posicaoDestino == NULL) {
    //    if (posicaoOrigem->valor != 13)
    //      return 0;

    if (EstaVazia(posicaoDestino)) {
        if (posicaoOrigem->valor != 13)
            return 0;

        pilhaDeBaixo[colunaDestino] = posicaoOrigem;
        if (posicaoOrigemAnterior != NULL)
            posicaoOrigemAnterior->prox = NULL;
        else
            pilhaDeBaixo[colunaOrigem] = NULL;

    }
    else {
        //while (posicaoDestino->prox != NULL) // la�o para chegar no final da lista
        //    posicaoDestino = posicaoDestino->prox;
        posicaoDestino = MoverPilhaFim(posicaoDestino);

        if (podeMover(posicaoOrigem, posicaoDestino) == 0)
            return 0;

        // posicaoDestino ficou no final da lista (null), ent�o coloca o prox (final
        // da lista) o posicaoOrigem (que � o valor que quer adicionar)
        posicaoDestino->prox = posicaoOrigem;

        if (posicaoOrigemAnterior != NULL)
            posicaoOrigemAnterior->prox =
            NULL; // coloca o ponteiro da pilha que foi removido para null,
                  // encerrando a lista
        else
            pilhaDeBaixo[colunaOrigem] = NULL; // coloca o ponteiro da pilha que foi removido para null,
                  // encerrando a lista
    }
    linhaEscondida[colunaOrigem]--; // decrementa da onde foi retirado a carta,
                                    // n�o escondendo mais a carta acima

    return 1;
}

int MoverMontePilhaBaixo(int colunaDestino) {
    //Preciso pegar a carta do monte e ent�o percorrer a lista da colunaDestino para chegar ao final dela e adicionar a carta em quest�o
    noCarta* posicaoDestino = pilhaDeBaixo[colunaDestino], * posicaoAnterior = monte, * auxiliar = NULL;
    int c;

    if(EstaVazia(atual))
        return 0;

    if (!EstaVazia(posicaoDestino)) {

        posicaoDestino = MoverPilhaFim(posicaoDestino);

        if (atual->valor != (posicaoDestino->valor - 1)) {
            return 0;
        }

        if ((posicaoDestino->naipe == 'c' && atual->naipe == 'o') ||
            (posicaoDestino->naipe == 'o' && atual->naipe == 'c') ||
            (posicaoDestino->naipe == 'p' && atual->naipe == 'e') ||
            (posicaoDestino->naipe == 'e' && atual->naipe == 'p') ||
            (posicaoDestino->naipe == 'c' && atual->naipe == 'c') ||
            (posicaoDestino->naipe == 'e' && atual->naipe == 'e') ||
            (posicaoDestino->naipe == 'o' && atual->naipe == 'o') ||
            (posicaoDestino->naipe == 'p' && atual->naipe == 'p'))
            return 0;

        if (atual == posicaoAnterior)
            posicaoAnterior = NULL;
        else {
            posicaoAnterior = MoverPilhaFim(posicaoAnterior);
        }

        if (!EstaVazia(posicaoDestino)) {
            posicaoDestino->prox = atual;
        }
        else {
            if (atual->valor != 13)
                return 0; //pois s� pode valor 13 se for nula a lista
            pilhaDeBaixo[colunaDestino] = atual;
        }

        if (posicaoAnterior != NULL) {
            posicaoAnterior->prox = atual->prox; 
        }
        else {
            monte = atual->prox;
        }
        auxiliar = atual; //coloca a carta desejada na origem
        atual = atual->prox; //movimenta a atual do monte pra prox
        auxiliar->prox = NULL; //finaliza a lista da origem

        return 1;
    }

}

int MoverPilhaBaixoPilhaCima(int colunaOrigem) {
    //Preciso identificar o NIPE e ver onde vai colocar, e percorrer a pilha da coluna desejada e pegar a ultima carta
    noCarta* posicaoOrigem = pilhaDeBaixo[colunaOrigem];
    noCarta* posicaoOrigemAnterior = NULL;
    noCarta* posicaoDestino = NULL;
    int c;

    if (EstaVazia(posicaoOrigem)) {
        return 0;
    }
    while (posicaoOrigem->prox != NULL) //colocar isso em fun��o gen�ria amanh�
    {
        posicaoOrigemAnterior = posicaoOrigem;
        posicaoOrigem = posicaoOrigem->prox;
    }

    c = naipeCima(posicaoOrigem->naipe); // para saber qual pilha por naipe �
    posicaoDestino = pilhaDeCima[c];

    if (EstaVazia(posicaoDestino)) {
        if (posicaoOrigem->valor == 1) {
            pilhaDeCima[c] = posicaoOrigem;

            if (posicaoOrigemAnterior != NULL)
                posicaoOrigemAnterior->prox = NULL;
            else
                pilhaDeBaixo[colunaOrigem] = NULL;

            linhaEscondida[colunaOrigem]--;

            return 1;
        }
        else
            return 0;
    }
    else {
        posicaoDestino = MoverPilhaFim(posicaoDestino); //substitui��o pro loop abaixo
        /*while (posicaoDestino->prox != NULL)
            posicaoDestino = posicaoDestino->prox;*/

        if (posicaoDestino->valor == (posicaoOrigem->valor - 1)) {
            //valida se a carta atinge os requisitos de ser 1 numero maior para ir a pilha
            posicaoDestino->prox = posicaoOrigem;

            if (posicaoOrigemAnterior != NULL)
                posicaoOrigemAnterior->prox = NULL;
            else
                pilhaDeBaixo[colunaOrigem] = NULL;

            linhaEscondida[colunaOrigem]--;

            return 1;
        }
    }
    return 0;
}

int MoverMontePilhaCima(void) {
    noCarta* posicaoOrigem = atual, * posicaoDestino = NULL, * posicaoOrigemAnterior = monte;
    int c;

    if (EstaVazia(posicaoOrigem))
        return 0;

    if (posicaoOrigemAnterior == posicaoOrigem)
        posicaoOrigemAnterior = NULL;
    else
        while (posicaoOrigemAnterior->prox != posicaoOrigem) //pegar o anterior a posicaoOrigem
            posicaoOrigemAnterior = posicaoOrigemAnterior->prox;

    c = naipeCima(posicaoOrigem->naipe);
    posicaoDestino = pilhaDeCima[c];

    if (EstaVazia(posicaoDestino)) {
        if (posicaoOrigem->valor == 1) {
            pilhaDeCima[c] = posicaoOrigem; //coloca valor na pilha
            atual = atual->prox; //passa o monte atual para a proxima carta

            if (!EstaVazia(posicaoOrigemAnterior)) {
                posicaoOrigemAnterior->prox = posicaoOrigem->prox;
                posicaoOrigem->prox = NULL;
            }
            else {
                monte = posicaoOrigem->prox;
                posicaoOrigem->prox = NULL;
            }
            return 1;
        }
        else {
            return 0;
        }
    } else {
            posicaoDestino = MoverPilhaFim(posicaoDestino);

            if (posicaoDestino->valor != (posicaoDestino->valor - 1))
                return 0;

            posicaoDestino->prox = posicaoOrigem;
            atual = atual->prox;

            if (!EstaVazia(posicaoOrigemAnterior)) {
                posicaoOrigemAnterior->prox = posicaoOrigem->prox;
                posicaoOrigem->prox = NULL;
            }
            else {
                monte = posicaoOrigem->prox;
                posicaoOrigem->prox = NULL;
            }

            return 1;
    }
        return 0;
}
   

int naipeCima(char c)
{

    if (c == 'c')
        return 0;
    if (c == 'e')
        return 1;
    if (c == 'o')
        return 2;
    if (c == 'p')
        return 3;
    return -1;

}

int EstaVazia(noCarta* PILHA)
{
    if (PILHA == NULL)
        return 1;
    else
        return 0;
}

void AdicionarElemento(noCarta* PILHA)
{
    noCarta* novo = malloc(sizeof(noCarta));
    novo->prox = NULL;

    if (EstaVazia(PILHA))
        PILHA->prox = novo; //se estiver vazia, s� adiciona
    else {
        noCarta* auxiliar = PILHA->prox; //como n�o est� vazia, por meio do ponteiro auxiliar, vamos encontrar o ultimo elemento

        while (auxiliar->prox != NULL) //la�o para encontrar o �ltimo elemento
            auxiliar = auxiliar->prox;

        //if (podeMover(posicaoOrigem, posicaoDestino) == 0)
          //return 0;

        auxiliar->prox = novo; //adiciona o elemento ao final
    }
}

noCarta* RemoverElemento(noCarta* PILHA)
{
    if (PILHA->prox == NULL) { //checa se a pilha � vazia, pois n�o precisa fazer nada se for
        printf("PILHA ja vazia\n\n");
        return NULL;
    }
    else {
        noCarta* ultimo = PILHA->prox,
            * penultimo = PILHA; //vai se tornar o ultimo elemento

        while (ultimo->prox != NULL) { //la�o para chegar no final da lista
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }

        penultimo->prox = NULL; //aponta o pr�ximo para null para finalizar a lista
        //tam--;
        return ultimo; //retorna o elemento a ser removido
    }
}

noCarta* MoverPilhaFim(noCarta* pilha) {
    while (pilha->prox != NULL) {
        pilha = pilha->prox;
    }
    return pilha;
}

void LeArquivoInicio() {
    FILE* Fluxo;
    int j, i;
    char b[100];

    Fluxo = fopen("ranking.txt", "r");

    for (i = 0; i < 10; i++) {
        fscanf(Fluxo, "%s %i\n", rank[i].nomeJogador, &rank[i].pontuacao);
        if(rank[i].pontuacao != 0)
            printf("%s %i\n", rank[i].nomeJogador, rank[i].pontuacao);
    }
    //Bolha
    for (i = 1; i < 10; i++) {
        for (j = 0; j < i; j++) {
            if (rank[i].pontuacao > rank[j].pontuacao) {
                int temp1 = rank[i].pontuacao;
                char temp2[10];
                strcpy(temp2, rank[i].nomeJogador);

                rank[i].pontuacao = rank[j].pontuacao;
                strcpy(rank[i].nomeJogador, rank[j].nomeJogador);

                rank[j].pontuacao = temp1;
                strcpy(rank[j].nomeJogador, temp2);
            }
        }
    }
    printf("%s %i\n", rank[0].nomeJogador, rank[0].pontuacao);
    printf("%s %i\n", rank[1].nomeJogador, rank[1].pontuacao);
    printf("%s %i\n", rank[2].nomeJogador, rank[2].pontuacao);


}

 void GravaRanking() {
    
    FILE* F;

    F = fopen("ranking.txt", "a");

    if (F == NULL) {
        printf("Erro, Nao Foi Possivel Gravar no Arquivo\n");
    }
    else {
        //fputs(rank->nomeJogador, F);
        fprintf(F, "\n%s %i", nomeTemp, pontuacaoTemp);
        fclose(F);
    }
}

void AbrirRanking() {
    FILE* Fluxo;
    int j, i;
    char b[100];

    Fluxo = fopen("ranking.txt", "r");

    //Preenche o vetor ranking com os dados do txt ranking
    for (i = 0; i < 10; i++) {
        fscanf(Fluxo, "%s %i\n", rank[i].nomeJogador, &rank[i].pontuacao);

    }

    //Bolha
    for (i = 1; i < 10; i++) {
        for (j = 0; j < i; j++) {
            if (rank[i].pontuacao < rank[j].pontuacao) {
                int temp1 = rank[i].pontuacao;
                char temp2[10];
                strcpy(temp2, rank[i].nomeJogador);

                rank[i].pontuacao = rank[j].pontuacao;
                strcpy(rank[i].nomeJogador, rank[j].nomeJogador);

                rank[j].pontuacao = temp1;
                strcpy(rank[j].nomeJogador, temp2);
            }
        }
    }

    printf("Ranking ordenado pelo menor tempo de ojogo!\n \n");

    //imprime na tela os valores ordenados
    for (i = 0; i < 10; i++) {

        if (rank[i].pontuacao != 0) {
            printf("%s Tempo: %i\n", rank[i].nomeJogador, rank[i].pontuacao);
        }

    }
}
