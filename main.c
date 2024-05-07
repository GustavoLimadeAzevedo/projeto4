#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 1000

// Estrutura para representar um cliente
typedef struct {
    char nome[50];
    char cpf[12];
    char tipo_conta[10]; // comum ou plus
    float saldo;
    char senha[20];
} Cliente;

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

        printf("Novo cliente cadastrado com sucesso!\n");
    } else {
        printf("Limite máximo de clientes atingido!\n");
    }
}

// Função para apagar um cliente pelo CPF
void apagarCliente(Cliente clientes[], int *numClientes) {
    char cpfApagar[12];
    printf("Digite o CPF do cliente a ser apagado: ");
    scanf("%s", cpfApagar);

    int encontrado = 0;
    for (int i = 0; i < *numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfApagar) == 0) {
            // Remover o cliente movendo os elementos posteriores uma posição para frente
            for (int j = i; j < *numClientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            (*numClientes)--;
            encontrado = 1;
            printf("Cliente apagado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado!\n");
    }
}

// Função para listar todos os clientes
void listarClientes(Cliente clientes[], int numClientes) {
    printf("--- Lista de Clientes ---\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Tipo de conta: %s\n", clientes[i].tipo_conta);
        printf("Saldo: %.2f\n", clientes[i].saldo);
        printf("------------------------\n");
    }
}

// Função para debitar um valor da conta do cliente
void debitar(Cliente clientes[], int numClientes) {
    char cpf[12];
    char senha[20];
    float valor;

    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    int encontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            printf("Valor a debitar: ");
            scanf("%f", &valor);
            if (clientes[i].saldo >= valor) {
                clientes[i].saldo -= valor;
                printf("Débito realizado com sucesso!\n");
            } else {
                printf("Saldo insuficiente!\n");
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("CPF ou senha incorretos!\n");
    }
}

// Função para depositar um valor na conta do cliente
void depositar(Cliente clientes[], int numClientes) {
    char cpf[12];
    float valor;

    printf("CPF: ");
    scanf("%s", cpf);

    int encontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            printf("Valor a depositar: ");
            scanf("%f", &valor);
            clientes[i].saldo += valor;
            printf("Depósito realizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado!\n");
    }
}

// Função para salvar os clientes em um arquivo binário
void salvarClientes(Cliente clientes[], int numClientes) {
    FILE *arquivo = fopen("clientes.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        exit(1);
    }

    fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
    fclose(arquivo);
}

// Função para carregar os clientes de um arquivo binário
void carregarClientes(Cliente clientes[], int *numClientes) {
    FILE *arquivo = fopen("clientes.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de clientes não encontrado. Iniciando com lista vazia.\n");
        return;
    }

    *numClientes = fread(clientes, sizeof(Cliente), MAX_CLIENTES, arquivo);
    fclose(arquivo);
}

// Função principal
int main() {
    // Declaração de variáveis
    Cliente clientes[MAX_CLIENTES];
    int numClientes = 0;

    // Carregar os clientes do arquivo binário
    carregarClientes(clientes, &numClientes);

    // Loop principal
    int opcao;
    do {
        // Exibir menu
        printf("\n--- Menu de Opções ---\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
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
            case 2:
                apagarCliente(clientes, &numClientes);
                break;
            case 3:
                listarClientes(clientes, numClientes);
                break;
            case 4:
                debitar(clientes, numClientes);
                break;
            case 5:
                depositar(clientes, numClientes);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    // Salvar os clientes no arquivo binário antes de encerrar o programa
    salvarClientes(clientes, numClientes);

    return 0;
}
