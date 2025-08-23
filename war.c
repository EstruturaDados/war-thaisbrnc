#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Desafio War

// declaraçao da struct com as propriedades e próximo elemento
typedef struct territorio
{
    char nome[30];
    char cor[10];
    int tropas;
    struct Territorio *prox;
} Territorio;

Territorio cadastrarTerritorio(Territorio territorio);
void exibirTerritorio(Territorio *territorio);
Territorio *buscarTerritorio(Territorio *no_cabeca, char nome[]);
Territorio *inserirNaLista(Territorio territorio, Territorio *noCabeca);
void imprimirLista(Territorio *noCabeca);
int realizarAtaque(Territorio *atacante, Territorio *defensor);
int *validarCoresExercitos(Territorio *noCabeca);
void liberarMemoria(Territorio *noCabeca);

// solicita e armazena os dados do territorio
Territorio cadastrarTerritorio(Territorio territorio)
{
    printf("\nInforme o nome do território: ");
    scanf(" %[^\n]", territorio.nome);
    printf("Informe a cor do exército: ");
    scanf(" %[^\n]", territorio.cor);
    printf("Informe a quantidade de tropas: ");
    scanf(" %d", &territorio.tropas);

    return territorio;
}

// exibe os dados do territorio
void exibirTerritorio(Territorio *territorio)
{
    // valida se territorio é vazio
    if (territorio == NULL)
    {
        printf("\nTerritório não cadastrado.\n");
        return;
    }

    printf("\n------------------------------------------------\n");
    printf("Nome: %s\n", territorio->nome);
    printf("Cor do exército: %s\n", territorio->cor);
    printf("Quantidade de tropas: %d\n", territorio->tropas);
    printf("------------------------------------------------\n");
}

// busca um territorio na lista encadeada
Territorio *buscarTerritorio(Territorio *no_cabeca, char nome[30])
{
    if (no_cabeca->prox == NULL)
    {
        printf("\nNenhum território cadastrado.\n");
        return;
    }

    Territorio *atual = no_cabeca->prox;
    Territorio **aux = no_cabeca;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) > 0)
        {
            *aux = atual;
            atual = atual->prox;
        }
        else if (strcmp(atual->nome, nome) == 0)
        {
            // retorna territorio encontrado
            return atual;
        }
        else
        {
            printf("\nTerritório não encontrado.\n");
            return NULL;
        }
    }
}

// insere um novo territorio na lista encadeada
Territorio *inserirNaLista(Territorio territorio, Territorio *noCabeca)
{
    // valida se territorio é vazio
    if (territorio.nome[0] == '\0')
    {
        printf("\nTerritório não cadastrado.\n");
        return NULL;
    }

    Territorio *novo = (Territorio *)malloc(sizeof(Territorio));
    strcpy(novo->nome, territorio.nome);
    strcpy(novo->cor, territorio.cor);
    novo->tropas = territorio.tropas;

    // insere o novo territorio no início da lista
    novo->prox = noCabeca->prox;
    noCabeca->prox = novo;

    return noCabeca->prox;
}

// exibe todos os territorios cadastrados
void imprimirLista(Territorio *noCabeca)
{
    if (noCabeca->prox == NULL)
    {
        printf("\nNenhum território cadastrado.\n");
        return;
    }

    Territorio *temp = (Territorio *)malloc(sizeof(Territorio));

    printf("\nExibindo todos os territórios:\n");

    for (temp = noCabeca->prox; temp != NULL; temp = temp->prox)
    {
        exibirTerritorio(temp);
    }

    free(temp);
}

// realiza ataque entre dois territorios
int realizarAtaque(Territorio *atacante, Territorio *defensor)
{
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("\nNão é possível atacar um território da mesma cor.\n");
        return 0;
    }
    if (atacante->tropas < 2)
    {
        printf("\n%s não possui tropas suficientes para atacar. É necessário ter no mínimo 2 tropas.\n", atacante->nome);
        return 0;
    }
    if (defensor->tropas < 1)
    {
        printf("\n%s não possui tropas para defender.\n", defensor->nome);
        return 0;
    }

    // gera numeros aleatorios entre 1 e 6
    int ataque = rand() % 6 + 1;
    int defesa = rand() % 6 + 1;

    printf("\n          *   *   *\n");
    printf("       *     BOOM!    *\n");
    printf("          *   *   *\n");
    printf("\n+*+ %s está atacando %s! +*+", atacante->nome, defensor->nome);
    printf("\n\n%s rolou o dado e tirou: ", atacante->nome);
    printf("%d", ataque);
    printf("\n%s rolou o dado e tirou: ", defensor->nome);
    printf("%d", defesa);

    // se atacante vencer, defensor perde cor do exercito e metade das tropas
    if (ataque > defesa)
    {
        printf("\n\n| #1 | %s venceu o combate! | #1 |", atacante->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
        atacante->tropas = atacante->tropas + defensor->tropas;
        printf("\n\n%s perdeu a cor de seu exército e metade de sua tropa:", defensor->nome);
        exibirTerritorio(defensor);
        exibirTerritorio(atacante);
        return 1;
    }
    // se defensor vencer, atacante perde uma tropa
    else if (defesa > ataque)
    {
        printf("\n\n| #1 | %s venceu o combate! | #1 |", defensor->nome);
        atacante->tropas -= 1;
        defensor->tropas += 1;
        printf("\n\n%s perdeu uma tropa:", atacante->nome);
        exibirTerritorio(atacante);
        exibirTerritorio(defensor);
        return 1;
    }
    // se empatar, nada altera
    else
    {
        printf("\nEmpate! Ninguém perde tropas.\n");
        return 1;
    }
}
// valida se todos os territorios são da mesma cor
int *validarCoresExercitos(Territorio *noCabeca)
{
    Territorio *atual = noCabeca->prox;
    char corReferencia[10];
    strcpy(corReferencia, atual->cor);

    while (atual != NULL)
    {
        //retorna se pelo menos um territorio for de cor diferente
        if (strcmp(atual->cor, corReferencia) != 0)
        {
            return 0;
        }
        atual = atual->prox;
    }
    printf("\nParabéns! Todos os territórios são da cor %s. Você venceu o jogo!\n", corReferencia);
    return 1;
}

void liberarMemoria(Territorio *noCabeca)
{
    Territorio *atual = noCabeca;
    Territorio *proxNo;

    while (atual != NULL)
    {
        proxNo = atual->prox;
        free(atual);
        atual = proxNo;
    }
}

int main(void)
{
    // inicializa variáveis
    char opc = '\0';
    char opcao = 'S';
    int result = 0;
    Territorio territorio = {0};
    Territorio *noCabeca = (Territorio *)malloc(sizeof(Territorio));
    Territorio *novoNo = (Territorio *)malloc(sizeof(Territorio));
    Territorio *atacante = (Territorio *)malloc(sizeof(Territorio));
    Territorio *defensor = (Territorio *)malloc(sizeof(Territorio));
    char atacanteNome[30] = "\0";
    char defensorNome[30] = "\0";
    // inicializa gerador de números aleatórios
    srand(time(NULL));

    printf("\n***********************************************************");
    printf("\n                      Bem-vindo ao War!                   ");

    // laço para menu principal
    do
    {
        printf("\n***********************************************************\n");
        printf("\nSelecione uma opção: \n1. Cadastrar território\n2. Jogar\n3. Ver mapa\n4. Sair");
        printf("\nOpção: ");
        scanf(" %c", &opc);

        switch (opc)
        {
        case '1':
            printf("\n***********************************************************");
            printf("\n                  Cadastro dos territórios                  \n");

            do
            {
                // solicita dados para cadastro do territorio
                territorio = cadastrarTerritorio(territorio);
                // insere o nó na lista encadeada
                novoNo = inserirNaLista(territorio, noCabeca);
                // exibe o territorio cadastrado
                exibirTerritorio(novoNo);

                printf("\nCadastrar novo território? (Digite 'S' para Sim e 'N' para Não): ");
                scanf(" %c", &opcao);

            } while (opcao == 'S' || opcao == 's');

            printf("\nVoltando ao menu anterior...\n");

            break;

        case '2':
            printf("\n***********************************************************");
            printf("\n                   Vamos iniciar o jogo!                   \n");

            do
            {
                do
                {
                    atacanteNome[30] = "\0";
                    defensorNome[30] = "\0";
                    printf("\nSelecione dois territórios para o combate:");
                    printf("\n\n1. Nome do território atacante: ");
                    scanf(" %[^\n]", atacanteNome);
                    printf("2. Nome do território defensor: ");
                    scanf(" %[^\n]", defensorNome);

                    // buscar territorios na lista
                    // repete enquanto nao encontrar atacante ou defensor ou enquanto forem iguais
                    atacante = buscarTerritorio(noCabeca, atacanteNome);
                    defensor = buscarTerritorio(noCabeca, defensorNome);

                    if (strcmp(atacanteNome, defensorNome) == 0)
                    {
                        printf("Atacante e defensor devem ser diferentes.");
                    }
                } while ((atacante == NULL || defensor == NULL) ||
                         (strcmp(atacanteNome, defensorNome) == 0));

                // se encontrou atacante e defensor, realiza ataque
                result = realizarAtaque(atacante, defensor);

                // valida se todos os territorios são da mesma cor
                if(validarCoresExercitos(noCabeca) == 1){
                    // exibe o mapa do jogo
                    imprimirLista(noCabeca);
                    // e sai do jogo
                    opc = '4'; 
                };
            } while (result == 0);

            break;

        case '3':
            printf("\n***********************************************************");
            printf("\n                     Ver mapa do jogo                      \n");
            imprimirLista(noCabeca);
            printf("\nVoltando ao menu anterior...\n");

            break;

        case '4':
            printf("\nEncerrando o jogo...\n\n");

            break;

        default:
            printf("\nOpção inválida.\n");

            break;
        }
    } while (opc != '4');

    // libera memória
    liberarMemoria(noCabeca);

    return 0;
}
