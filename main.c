#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100


typedef struct {
    char nome[50];
    char cpf[12];
    char tipo_conta[10]; 
    float saldo;
    char senha[20];
    
} Cliente;


typedef struct {
    char tipo_operacao[20]; 
    float valor;
    
} Operacao;

// Função para adicionar um novo cliente
void novoCliente(Cliente clientes[], int *numClientes) {
    if (*numClientes < MAX_CLIENTES) {
        Cliente novoCliente;
        printf("Nome: ");
        scanf("%s", novoCliente.nome);
        printf("CPF: ");
        scanf("%s", novoCliente.cpf);
        printf("Tipo de conta (comum/plus): ");
        scanf("%s", novoCliente.tipo_conta);
        printf("Valor inicial da conta: ");
        scanf("%f", &novoCliente.saldo);
        printf("Senha: ");
        scanf("%s", novoCliente.senha);

        clientes[*numClientes] = novoCliente;
        (*numClientes)++;

        // Salvar o cliente em arquivo binário
        FILE *arquivo = fopen("clientes.bin", "ab");
        fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);
        fclose(arquivo);

        printf("Novo cliente cadastrado com sucesso!\n");
    } else {
        printf("Limite máximo de clientes atingido!\n");
    }
}

// Função principal
int main() {
    // Declaração de variáveis
    Cliente clientes[MAX_CLIENTES];
    int numClientes = 0;

    // Loop principal
    int opcao;
    do {
        // Exibir menu
        printf("\n--- Menu de Opções ---\n");
        printf("1. Novo cliente\n");
        printf("2. Apaga cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Débito\n");
        printf("5. Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência Entre Contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Executar a opção escolhida
        switch (opcao) {
            case 1:
                novoCliente(clientes, &numClientes);
                break;
            // Adicione os outros casos conforme necessário
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
