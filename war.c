#include <stdio.h>
#include <string.h>

#define STR_SIZE 40
#define MAX_TERRITORIOS 5

// definindo o território
typedef struct {
    char nome[STR_SIZE];
    char cor[STR_SIZE];
    int tropas; 
} Territorio;

Territorio territorios[MAX_TERRITORIOS];
int territoriosRegistrados;

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
    
    territoriosRegistrados++;
    printf("\nTerritorio registrado com sucesso.\n");
}
// limpar buffer do scanf para impedir bugs
void LimparBufferDeEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ExibirTerritorios() {
    // se não tiver nada registrado, retorna ao menu.
    if (territoriosRegistrados == 0) {
        printf("\nNenhum territorio registrado.\n\n");
        return;
    }
    printf("________________________\n");
    printf("\nTERRITORIOS :.\n\n");
    
    for (int i = 0; i < territoriosRegistrados; i++) {
        printf("- %s", territorios[i].nome);
        printf("Cor: %s", territorios[i].cor);
        printf("Tropas: %i\n\n", territorios[i].tropas);
    }
    
    printf("\nVoltar ao menu? (Insira uma letra para confirmar)\n");
    scanf(" ");
    LimparBufferDeEntrada();
}

void ExibirMenu() {
    printf("________________________\n");
    printf("\n1 - Adicionar Territorio\n");
    printf("2 - Exibir Territorios\n");
    printf("3 - Sair\n\n");
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
            ExibirMenu();
            break;
        case 3:
            break;
    }
}

int main() {
    ExibirMenu();
    return 0;
}