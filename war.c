#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STR_SIZE 30
#define MAX_TERRITORIOS 5

// definindo o território
typedef struct {
    char nome[STR_SIZE];
    char cor[STR_SIZE];
    int tropas;
    int id;
} Territorio;

Territorio* territorios;
int territoriosRegistrados;

// limpar buffer do scanf para impedir bugs
void LimparBufferDeEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void RegistrarTerritorio() {
    // se já tiver 5 territórios, desiste e retorna ao menu.
    if (territoriosRegistrados >= MAX_TERRITORIOS) {
        printf("\nNao e possivel registrar mais territorios.\n\n");
        return;
    }    
    printf("________________________\n");
    printf("\nNome do Territorio: ");
    fgets(territorios[territoriosRegistrados].nome, STR_SIZE, stdin);
    printf("\nCor do Territorio: ");
    fgets(territorios[territoriosRegistrados].cor, STR_SIZE, stdin);
    printf("\nNumero de Tropas: ");
    scanf(" %d", &territorios[territoriosRegistrados].tropas);
    
    territorios[territoriosRegistrados].id = territoriosRegistrados;
    territoriosRegistrados++;
    printf("\nTerritorio registrado com sucesso.\n");

}    
void ExibirTerritorios() {
    // se não tiver nada registrado, retorna ao menu.
    if (territoriosRegistrados == 0) {
        printf("\nNenhum territorio registrado.\n");
        return;
    }
    printf("________________________\n");
    printf("\nTERRITORIOS :.\n\n");
    
    for (int i = 0; i < territoriosRegistrados; i++) {
        printf("%i - %s", i + 1, territorios[i].nome);
        printf("Cor: %s", territorios[i].cor);
        printf("Tropas: %i\n\n", territorios[i].tropas);
    }
}

void Atacar(Territorio atacante, Territorio defensor) {
    // verificando validade das escolhas.
    if (atacante.tropas < 1 || defensor.tropas < 1) {
        printf("\nUm ou mais territorios não possuem tropas restantes!\n");
        return;
    }
    else if (atacante.id == defensor.id) {
        printf("\nUm territorio nao pode se atacar.\n");
        return;
    }
    else if (atacante.cor == defensor.cor) {
        printf("\n%s e %s sao aliados, portanto, nao podem se atacar.\n");
        return;
    }

    // rolando dois numeros aleatorios de 1 a 6.
    int dado1 = (rand() % 6) + 1;
    int dado2 = (rand() % 6) + 1;
    
    printf("________________________\n");
    printf("\nO atacante %s rolou um dado e tirou:: %i\n", atacante.nome, dado1);
    printf("\nO defensor %s rolou um dado e tirou:: %i\n", defensor.nome, dado2);

    if (dado1 > dado2) {
        printf("\nVitoria do ATAQUE!\n");
        atacante.tropas /= 2;
        defensor.tropas += atacante.tropas;
        strcpy(defensor.cor, atacante.cor);
    }
    else if (dado1 < dado2) {
        printf("\nVitoria da DEFESA! O atacante %s perdeu 1 tropa.\n", atacante.nome);
        atacante.tropas--;
    }
    else {
        // se empatar, 50% de chance das duas tropas sobreviverem.
        int rng = rand() % 2 == 0;
        if (rng) {
            printf("\nEMPATE! Ambos os territorios perderam 1 tropa.\n");
            defensor.tropas--;
            atacante.tropas--;
        }
        else printf("\nEMPATE! Ambas as tropas sobreviveram.\n");
    }

    printf("\nPressione ENTER para continuar...\n");
    getchar(); 
    LimparBufferDeEntrada();

    territorios[atacante.id] = atacante;
    territorios[defensor.id] = defensor;
}

void ExibirMenuDeAtaque() {
    // executar após o registro dos territorios
    // retornar ao menu principal se não houver ao menos 2 territorios registrados.
    if (territoriosRegistrados < 2) {
        printf("\nNao ha territorios suficientes.\n");
        return;
    }

    int escolha;
    int alvo;
    // exibir opções de territorio e propriedades de cada um.
    ExibirTerritorios();
    
    // pedir pro usuario escolher qual território atacará e qual se defenderá
    printf("\nEscolha qual territorio ira atacar. (Ou digite 0 para sair.)\n");
    scanf("%i", &escolha);
    LimparBufferDeEntrada();
    if (escolha == 0) return; // sair
    printf("\nEscolha o alvo.\n");
    scanf("%i", &alvo);
    LimparBufferDeEntrada();
    
    Atacar(territorios[escolha-1], territorios[alvo-1]);
    ExibirMenuDeAtaque();
}

void ExibirMenu() {
    printf("________________________\n");
    printf("\n1 - Adicionar Territorio\n");
    printf("2 - Exibir Territorios\n");
    printf("3 - Entrar em Fase de Ataque\n");
    printf("0 - Sair\n\n");
    printf("Territorios Registrados: %d\n\n", territoriosRegistrados);
    printf("Digite a opcao desejada: ");
    
    int opcao;
    scanf("%d", &opcao);
    LimparBufferDeEntrada();

    // função recursiva para retornar ao menu ao final da execução das outras fuções.
    switch (opcao) {
        case 1:
            RegistrarTerritorio();
            ExibirMenu();
            break;
        case 2:
            ExibirTerritorios();
            printf("\nPressione Enter para voltar ao menu.\n");
            getchar();
            LimparBufferDeEntrada();
            ExibirMenu();
            break;
        case 3:
            ExibirMenuDeAtaque();
            if (territoriosRegistrados < 2) ExibirMenu();
            break;
        case 0:
            break;
    }
}

void LiberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    territorios = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    
    if (territorios == NULL) {
        printf("Erro na alocação de memoria.");
        return 1;
    }
    srand(time(NULL));
    ExibirMenu();
    LiberarMemoria(territorios);
    return 0;
}