#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_FUNCIONARIOS 100
#define MAX_ESTADIAS 100
#define MAX_QUARTOS 100

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
} Cliente;

typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
    char cargo[30];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidade_hospedes;
    float valor_diaria;
    char status[20];
} Quarto;

typedef struct {
    int codigo;
    int codigo_cliente;
    int codigo_funcionario;
    int numero_quarto;
    int quantidade_hospedes;
    int num_diarias;
    struct tm data_entrada;
    struct tm data_saida;
} Estadia;

Cliente clientes[MAX_CLIENTES];
Funcionario funcionarios[MAX_FUNCIONARIOS];
Quarto quartos[MAX_QUARTOS];
Estadia estadias[MAX_ESTADIAS];

int contador_clientes = 0;
int contador_funcionarios = 0;
int contador_quartos = 0;
int contador_estadias = 0;

void salvarClientes() {
    FILE *file = fopen("clientes.dat", "wb");
    fwrite(clientes, sizeof(Cliente), contador_clientes, file);
    fclose(file);
}

void carregarClientes() {
    FILE *file = fopen("clientes.dat", "rb");
    if (file) {
        contador_clientes = fread(clientes, sizeof(Cliente), MAX_CLIENTES, file);
        fclose(file);
    }
}

void salvarFuncionarios() {
    FILE *file = fopen("funcionarios.dat", "wb");
    fwrite(funcionarios, sizeof(Funcionario), contador_funcionarios, file);
    fclose(file);
}

void carregarFuncionarios() {
    FILE *file = fopen("funcionarios.dat", "rb");
    if (file) {
        contador_funcionarios = fread(funcionarios, sizeof(Funcionario), MAX_FUNCIONARIOS, file);
        fclose(file);
    }
}

void salvarQuartos() {
    FILE *file = fopen("quartos.dat", "wb");
    fwrite(quartos, sizeof(Quarto), contador_quartos, file);
    fclose(file);
}

void carregarQuartos() {
    FILE *file = fopen("quartos.dat", "rb");
    if (file) {
        contador_quartos = fread(quartos, sizeof(Quarto), MAX_QUARTOS, file);
        fclose(file);
    }
}

void salvarEstadias() {
    FILE *file = fopen("estadias.dat", "wb");
    fwrite(estadias, sizeof(Estadia), contador_estadias, file);
    fclose(file);
}

void carregarEstadias() {
    FILE *file = fopen("estadias.dat", "rb");
    if (file) {
        contador_estadias = fread(estadias, sizeof(Estadia), MAX_ESTADIAS, file);
        fclose(file);
    }
}

int gerarCodigo() {
    return rand() % 10000;
}

void cadastrarCliente() {
    if (contador_clientes < MAX_CLIENTES) {
        Cliente novo_cliente;
        novo_cliente.codigo = gerarCodigo();
        printf("\nNome do cliente: ");
        scanf("%s", novo_cliente.nome);
        printf("Endereco do cliente: ");
        scanf("%s", novo_cliente.endereco);
        fflush(stdin);
        printf("Telefone do cliente: ");
        scanf("%s", novo_cliente.telefone);
        clientes[contador_clientes++] = novo_cliente;
        salvarClientes();
        printf("Cliente cadastrado com sucesso! Codigo: %d\n", novo_cliente.codigo);
    } else {
        printf("Limite de clientes atingido.\n");
    }
}

void cadastrarFuncionario() {
    if (contador_funcionarios < MAX_FUNCIONARIOS) {
        Funcionario novo_funcionario;
        novo_funcionario.codigo = gerarCodigo();
        printf("\nNome do funcionario: ");
        scanf("%s", novo_funcionario.nome);
        printf("Telefone do funcionario: ");
        scanf("%s", novo_funcionario.telefone);
        printf("Cargo do funcionario: ");
        scanf("%s", novo_funcionario.cargo);
        printf("Salario do funcionario: ");
        scanf("%f", &novo_funcionario.salario);
        funcionarios[contador_funcionarios++] = novo_funcionario;
        salvarFuncionarios();
        printf("Funcionario cadastrado com sucesso! Codigo: %d\n", novo_funcionario.codigo);
    } else {
        printf("Limite de funcionarios atingido.\n");
    }
}

void cadastrarQuarto() {
    if (contador_quartos < MAX_QUARTOS) {
        Quarto novo_quarto;
        printf("\nNumero do quarto: ");
        scanf("%d", &novo_quarto.numero);
        printf("Quantidade de hospedes: ");
        scanf("%d", &novo_quarto.quantidade_hospedes);
        printf("Valor da diaria: ");
        scanf("%f", &novo_quarto.valor_diaria);
        strcpy(novo_quarto.status, "desocupado");
        quartos[contador_quartos++] = novo_quarto;
        salvarQuartos();
        printf("Quarto cadastrado com sucesso!\n");
    } else {
        printf("Limite de quartos atingido.\n");
    }
}

int verificarCliente(int codigo_cliente) {
    for (int i = 0; i < contador_clientes; i++) {
        if (clientes[i].codigo == codigo_cliente) {
            return 1; // Cliente encontrado
        }
    }
    return 0; // Cliente não encontrado
}

int verificarFuncionario(int codigo_funcionario) {
    for (int i = 0; i < contador_funcionarios; i++) {
        if (funcionarios[i].codigo == codigo_funcionario) {
            return 1; // Funcionario encontrado
        }
    }
    return 0; // Funcionario não encontrado
}

void cadastrarEstadia() {
    if (contador_estadias < MAX_ESTADIAS) {
        Estadia nova_estadia;
        nova_estadia.codigo = gerarCodigo();
        printf("\nCodigo do cliente: ");
        scanf("%d", &nova_estadia.codigo_cliente);
        if (!verificarCliente(nova_estadia.codigo_cliente)) {
            printf("Cliente nao encontrado.\n");
            return;
        }

        printf("Codigo do funcionario: ");
        scanf("%d", &nova_estadia.codigo_funcionario);
        if (!verificarFuncionario(nova_estadia.codigo_funcionario)) {
            printf("Funcionario nao encontrado.\n");
            return;
        }

        printf("Quantidade de hospedes: ");
        scanf("%d", &nova_estadia.quantidade_hospedes);

        // Verificar a disponibilidade do quarto
        int quarto_disponivel = -1;
        for (int i = 0; i < contador_quartos; i++) {
            if (quartos[i].quantidade_hospedes >= nova_estadia.quantidade_hospedes &&
                strcmp(quartos[i].status, "desocupado") == 0) {
                quarto_disponivel = quartos[i].numero;
                strcpy(quartos[i].status, "ocupado");
                break;
            }
        }

        if (quarto_disponivel == -1) {
            printf("Nao ha quarto disponivel para a quantidade de hospedes.\n");
            return;
        }

        nova_estadia.numero_quarto = quarto_disponivel;

        printf("Data de entrada (dd mm yyyy): ");
        scanf("%d %d %d", &nova_estadia.data_entrada.tm_mday, &nova_estadia.data_entrada.tm_mon, &nova_estadia.data_entrada.tm_year);
        nova_estadia.data_entrada.tm_mon--;  // Ajuste do mês
        nova_estadia.data_entrada.tm_year -= 1900;  // Ajuste do ano
        printf("Data de saida (dd mm yyyy): ");
        scanf("%d %d %d", &nova_estadia.data_saida.tm_mday, &nova_estadia.data_saida.tm_mon, &nova_estadia.data_saida.tm_year);
        nova_estadia.data_saida.tm_mon--;  // Ajuste do mês
        nova_estadia.data_saida.tm_year -= 1900;  // Ajuste do ano

        // Calculando a quantidade de diárias automaticamente para referência
        time_t entrada = mktime(&nova_estadia.data_entrada);
        time_t saida = mktime(&nova_estadia.data_saida);
        int dias_calculados = (difftime(saida, entrada) / (60 * 60 * 24)) + 1;

        // Cadastro manual das diárias
        printf("Quantidade de diarias: ");
        scanf("%d", &nova_estadia.num_diarias);

        estadias[contador_estadias++] = nova_estadia;
        salvarEstadias();
        salvarQuartos();
        printf("Estadia cadastrada com sucesso!\n");
    } else {
        printf("Limite de estadias atingido.\n");
    }
}

void calcularValorEstadia() {
    int codigo_cliente;
    printf("\nCodigo do cliente: ");
    scanf("%d", &codigo_cliente);

    float valor_total = 0.0;
    for (int i = 0; i < contador_estadias; i++) {
        if (estadias[i].codigo_cliente == codigo_cliente) {
            for (int j = 0; j < contador_quartos; j++) {
                if (quartos[j].numero == estadias[i].numero_quarto) {
                    valor_total = quartos[j].valor_diaria * estadias[i].num_diarias;
                    break;
                }
            }
        }
    }

    printf("Valor total da estadia: %.2f\n", valor_total);
}


void pesquisarCliente() {
    int codigo;
    printf("\nCodigo do cliente: ");
    scanf("%d", &codigo);

    for (int i = 0; i < contador_clientes; i++) {
        if (clientes[i].codigo == codigo) {
            printf("Codigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n",
                   clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
            return;
        }
    }

    printf("Cliente nao encontrado.\n");
}

void pesquisarFuncionario() {
    int codigo;
    printf("\nCodigo do funcionario: ");
    scanf("%d", &codigo);

    for (int i = 0; i < contador_funcionarios; i++) {
        if (funcionarios[i].codigo == codigo) {
            printf("Codigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n",
                   funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
            return;
        }
    }

    printf("Funcionario nao encontrado.\n");
}

void mostrarEstadiasCliente() {
    int codigo_cliente;
    printf("Codigo do cliente: ");
    scanf("%d", &codigo_cliente);

    printf("Estadias do cliente %d:\n", codigo_cliente);
    for (int i = 0; i < contador_estadias; i++) {
        if (estadias[i].codigo_cliente == codigo_cliente) {
            printf("Estadia %d - Quarto: %d - Diarias: %d\n",
                   estadias[i].codigo, estadias[i].numero_quarto, estadias[i].num_diarias);
        }
    }
}

void menu() {
    int opcao;
    do {
        printf("\n1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia\n");
        printf("5. Dar Baixa em Estadia\n");
        printf("6. Pesquisar Cliente\n");
        printf("7. Pesquisar Funcionario\n");
        printf("8. Mostrar Estadias de Cliente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarCliente(); break;
            case 2: cadastrarFuncionario(); break;
            case 3: cadastrarQuarto(); break;
            case 4: cadastrarEstadia(); break;
            case 5: calcularValorEstadia(); break;
            case 6: pesquisarCliente(); break;
            case 7: pesquisarFuncionario(); break;
            case 8: mostrarEstadiasCliente(); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main() {
    srand(time(NULL));
    carregarClientes();
    carregarFuncionarios();
    carregarQuartos();
    carregarEstadias();

    // Testes manuais
    //printf("Executando testes manuais...\n");

    // Teste 1: Cadastro de cliente
    //Cliente c1 = { .codigo = 1, .nome = "Cliente1", .endereco = "Endereco1", .telefone = "123456789" };
    //clientes[contador_clientes++] = c1;
    //printf("Teste Cadastro Cliente: %s\n", clientes[0].nome);

    // Teste 2: Cadastro de funcionario
    //Funcionario f1 = { .codigo = 1, .nome = "Funcionario1", .telefone = "987654321", .cargo = "Recepcionista", .salario = 2000.0 };
    //funcionarios[contador_funcionarios++] = f1;
    //printf("Teste Cadastro Funcionario: %s\n", funcionarios[0].nome);

    // Teste 3: Cadastro de quarto
    //Quarto q1 = { .numero = 1, .quantidade_hospedes = 2, .valor_diaria = 100.0, .status = "desocupado" };
    //quartos[contador_quartos++] = q1;
    //printf("Teste Cadastro Quarto: Quarto %d\n", quartos[0].numero);

    // Teste 4: Cadastro de estadia
    //Estadia e1 = { .codigo = 1, .codigo_cliente = 1, .codigo_funcionario = 1, .numero_quarto = 1, .quantidade_hospedes = 2, .num_diarias = 3 };
    //estadias[contador_estadias++] = e1;
    //printf("Teste Cadastro Estadia: Estadia %d\n", estadias[0].codigo);

    // Teste 5: Calcular valor da estadia
    //calcularValorEstadia();  // Aqui, você pode ajustar para testar a função manualmente

    menu();
    return 0;
}
