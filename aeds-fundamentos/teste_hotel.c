#include <munit/munit.h>
#include "hotel.c"
#include "hotel.h"

// Teste para cadastrar cliente
static MunitResult test_cadastrar_cliente(const MunitParameter params[], void* data) {
    contador_clientes = 0;
    cadastrarCliente();
    munit_assert_string_equal(clientes[0].nome, "Cliente1");
    return MUNIT_OK;
}

// Teste para cadastrar funcionario
static MunitResult test_cadastrar_funcionario(const MunitParameter params[], void* data) {
    contador_funcionarios = 0;
    cadastrarFuncionario();
    munit_assert_string_equal(funcionarios[0].nome, "Funcionario1");
    return MUNIT_OK;
}

// Teste para cadastrar quarto
static MunitResult test_cadastrar_quarto(const MunitParameter params[], void* data) {
    contador_quartos = 0;
    cadastrarQuarto();
    munit_assert_int(quartos[0].numero, ==, 1);
    return MUNIT_OK;
}

// Teste para cadastrar estadia
static MunitResult test_cadastrar_estadia(const MunitParameter params[], void* data) {
    contador_estadias = 0;  // Reset contador
    cadastrarEstadia();
    munit_assert_int(estadias[0].codigo, ==, 1);
    return MUNIT_OK;
}

// Teste para calcular valor da estadia
static MunitResult test_calcular_valor_estadia(const MunitParameter params[], void* data) {
    contador_estadias = 0;
    calcularValorEstadia();
    munit_assert_double_equal(valor_total, 300.0, 0.001);
    return MUNIT_OK;
}

// Definindo os testes
static MunitTest tests[] = {
    { "/test_cadastrar_cliente", test_cadastrar_cliente, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_cadastrar_funcionario", test_cadastrar_funcionario, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_cadastrar_quarto", test_cadastrar_quarto, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_cadastrar_estadia", test_cadastrar_estadia, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_calcular_valor_estadia", test_calcular_valor_estadia, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};


static const MunitSuite suite = {
    "/hotel_tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, (void*) "munit", argc, argv);
}
