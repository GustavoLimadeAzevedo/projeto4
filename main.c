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

            // Verificar o tipo de conta e aplicar as regras correspondentes
            if (strcmp(clientes[i].tipo_conta, "comum") == 0) {
                if (clientes[i].saldo - valor >= -1000) {
                    clientes[i].saldo -= valor * 1.05; // Taxa de 5% para conta comum
                    printf("Débito realizado com sucesso!\n");
                } else {
                    printf("Saldo insuficiente!\n");
                }
            } else if (strcmp(clientes[i].tipo_conta, "plus") == 0) {
                if (clientes[i].saldo - valor >= -5000) {
                    clientes[i].saldo -= valor * 1.03; // Taxa de 3% para conta plus
                    printf("Débito realizado com sucesso!\n");
                } else {
                    printf("Saldo insuficiente!\n");
                }
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
// Função para mostrar o extrato de transações de um cliente e criar um arquivo de texto com o extrato
void extrato(Cliente clientes[], int numClientes) {
    char cpf[12];
    char senha[20];

    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    int encontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            printf("--- Extrato ---\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Tipo de conta: %s\n", clientes[i].tipo_conta);
            printf("Saldo: %.2f\n", clientes[i].saldo);

            // Criar o arquivo de extrato
            FILE *extratoFile = fopen("extrato.txt", "w");
            if (extratoFile == NULL) {
                printf("Erro ao criar o arquivo de extrato!\n");
                return;
            }
            fprintf(extratoFile, "--- Extrato ---\n");
            fprintf(extratoFile, "Nome: %s\n", clientes[i].nome);
            fprintf(extratoFile, "CPF: %s\n", clientes[i].cpf);
            fprintf(extratoFile, "Tipo de conta: %s\n", clientes[i].tipo_conta);
            fprintf(extratoFile, "Saldo: %.2f\n", clientes[i].saldo);
            fclose(extratoFile);

            printf("Extrato salvo no arquivo 'extrato.txt'.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("CPF ou senha incorretos!\n");
    }
}



// Função para registrar as transferências em um arquivo de texto
void registrarTransferencia(const char *cpfOrigem, const char *cpfDestino, float valor) {
    FILE *arquivo = fopen("transferencias.txt", "a"); // "a" para abrir o arquivo em modo de adição (append)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de transferências para escrita!\n");
        return;
    }

    // Escrever os detalhes da transferência no arquivo
    fprintf(arquivo, "Transferência de %s para %s no valor de %.2f\n", cpfOrigem, cpfDestino, valor);
    fclose(arquivo);
}

// Função para transferir dinheiro entre contas
void transferencia(Cliente clientes[], int numClientes) {
    char cpfOrigem[12];
    char cpfDestino[12];
    char senha[20];
    float valor;

    printf("CPF (origem): ");
    scanf("%s", cpfOrigem);
    printf("Senha: ");
    scanf("%s", senha);

    int encontradoOrigem = 0;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfOrigem) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            encontradoOrigem = 1;

            printf("CPF (destino): ");
            scanf("%s", cpfDestino);

            int encontradoDestino = 0;
            for (int j = 0; j < numClientes; j++) {
                if (strcmp(clientes[j].cpf, cpfDestino) == 0) {
                    encontradoDestino = 1;
                    break;
                }
            }

            if (!encontradoDestino) {
                printf("CPF de destino não encontrado!\n");
                return;
            }

            printf("Valor a transferir: ");
            scanf("%f", &valor);

            // Verificar se o saldo na conta de origem é suficiente para a transferência
            if (clientes[i].saldo >= valor) {
                // Realizar a transferência
                for (int k = 0; k < numClientes; k++) {
                    if (strcmp(clientes[k].cpf, cpfDestino) == 0) {
                        clientes[i].saldo -= valor;
                        clientes[k].saldo += valor;
                        printf("Transferência realizada com sucesso!\n");

                        // Registrar a transferência em um arquivo de texto
                        registrarTransferencia(cpfOrigem, cpfDestino, valor);
                        return;
                    }
                }
            } else {
                printf("Saldo insuficiente para a transferência!\n");
                return;
            }
        }
    }

    if (!encontradoOrigem) {
        printf("CPF ou senha incorretos!\n");
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
            case 6:
                extrato(clientes, numClientes);
                break;
            case 7:
                transferencia(clientes, numClientes);
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
