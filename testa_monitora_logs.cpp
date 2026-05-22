// Copyright 2026 Enzo Cardoso Martins
/**
 * @file testa_monitora_logs.cpp
 * @brief Arquivo de testes unitários automatizados para o sistema de monitoramento de logs.
 * * Contém os cenários de teste baseados na tabela de decisão do sistema e na cobertura
 * de validação por expressões regulares, utilizando o framework Google Test.
 */

#include "gtest/gtest.h"
#include "monitora_logs.hpp"
#include <string>
#include <vector>

using namespace std;  // NOLINT(build/namespaces)

/**
 * @title Teste de Leitura de Log Válido Simples
 * @dev Verifica se o sistema lê e valida corretamente um arquivo contendo um único log formatado.
 */
TEST(MonitorLog, LerLog) {
    vector<string> log_teste = {"19/10/2006 10:07:23 Teste"};
    EXPECT_EQ(ler_logs("./logs/log_teste.txt"), log_teste);
}

/**
 * @title Teste de Comportamento para Arquivo de Log Inexistente
 * @dev Garante que o sistema capture o erro de arquivo ausente e retorne a mensagem estipulada.
 */
TEST(MonitorLog, LerLogIniexistente) {
    vector<string> log_teste = {"Erro ao abrir o arquivo"};
    EXPECT_EQ(ler_logs("log_inexistente.txt"), log_teste);
}

/**
 * @title Teste de Escrita Primária em Arquivo de Totais
 * @dev Avalia a criação inicial de um arquivo totalizador a partir de uma origem válida.
 */
TEST(MonitorLog, EscreverLogTotal) {
    vector<string> log_teste = {"19/10/2006 10:07:23 Teste"};
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste.txt")), log_teste);
    std::filesystem::remove_all("./totais");
}

/**
 * @title Teste de Leitura de Múltiplas Linhas Válidas
 * @dev Certifica que o interpretador processa arquivos de log com mais de um registro em sequência.
 */
TEST(MonitorLog, LerLogVariasLinhas) {
    vector<string> logs = {"19/10/2006 10:07:23 Teste1", "19/10/2006 10:07:23 Teste2", "19/10/2006 10:07:23 Teste3"};
    EXPECT_EQ(ler_logs("./logs/log_teste_multiplas_linhas.txt"), logs);
}

/**
 * @title Teste de Comportamento para Escrita Baseada em Origem Inexistente
 * @dev Verifica o tratamento do sistema ao tentar unificar um log cujo arquivo físico não existe.
 */
TEST(MonitorLog, EscreverArquivoInexistente) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteArquivoIn1", "19/10/2006 10:07:23 TesteArquivoIn2", "19/10/2006 10:07:23 TesteArquivoIn3"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_arq_in.txt")), logs);
    std::filesystem::remove_all("./totais");
}

/**
 * @title Teste de Execução da Lista Mestra
 * @dev Valida se a função gerenciadora processa e aceita um arquivo de índices mestre válido.
 */
TEST(MonitorLog, LeituraListaMestra) {
    // analisar a lista mestra
    EXPECT_EQ(processar_lista_mestra("./lista_mestra.txt"), 1);
    std::filesystem::remove_all("./totais");
}

/**
 * @title Teste de Consistência Interna de Logs da Lista Mestra
 * @dev Avalia se os logs lidos individualmente através dos caminhos mapeados coincidem com o esperado.
 */
TEST(MonitorLog, LeituraListaMestra2) {
    vector<string> logs = {"./logs/Log1.txt", "./logs/Log2.txt", "./logs/Log3.txt"};
    vector<string> log1 = {"19/10/2006 10:07:23 TesteLog11", "19/10/2006 10:07:23 TesteLog12", "19/10/2006 10:07:23 TesteLog13"};
    vector<string> log2 = {"19/10/2006 10:07:23 TesteLog21", "19/10/2006 10:07:23 TesteLog22", "19/10/2006 10:07:23 TesteLog23"};
    vector<string> log3 = {"19/10/2006 10:07:23 TesteLog31", "19/10/2006 10:07:23 TesteLog32", "19/10/2006 10:07:23 TesteLog33"};
    
    // Analisar os logs
    EXPECT_EQ(ler_logs(logs.at(0)), log1);
    EXPECT_EQ(ler_logs(logs.at(1)), log2);
    EXPECT_EQ(ler_logs(logs.at(2)), log3);
}

/**
 * @title Teste de Geração Coletiva de Totais por Lista Mestra
 * @dev Garante que todos os arquivos indexados na lista mestre geram seus respectivos arquivos totais unificados.
 */
TEST(MonitorLog, LeituraListaMestra3) {
    vector<string> logs = {"./logs/Log1.txt", "./logs/Log2.txt", "./logs/Log3.txt"};
    vector<string> log1 = {"19/10/2006 10:07:23 TesteLog11", "19/10/2006 10:07:23 TesteLog12", "19/10/2006 10:07:23 TesteLog13"};
    vector<string> log2 = {"19/10/2006 10:07:23 TesteLog21", "19/10/2006 10:07:23 TesteLog22", "19/10/2006 10:07:23 TesteLog23"};
    vector<string> log3 = {"19/10/2006 10:07:23 TesteLog31", "19/10/2006 10:07:23 TesteLog32", "19/10/2006 10:07:23 TesteLog33"};

    // Analisar a escrita dos totais
    EXPECT_EQ(ler_logs(escrever_log_total(logs.at(0))), log1);
    EXPECT_EQ(ler_logs(escrever_log_total(logs.at(1))), log2);
    EXPECT_EQ(ler_logs(escrever_log_total(logs.at(2))), log3);
    std::filesystem::remove_all("./totais");
}

/**
 * @title Teste de Cobertura de Caixa Aberta: Validação de Data
 * @dev Valida o comportamento da expressão regular frente a filtros e limites de calendário da data.
 */
TEST(MonitorLog, FormatacaoDeData) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteData3"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_data.txt")), logs);
    std::filesystem::remove_all("./totais");
}

/**
 * @title Teste de Cobertura de Caixa Aberta: Validação de Hora
 * @dev Avalia se a expressão de validação rejeita horários impossíveis ou mal formatados no relógio.
 */
TEST(MonitorLog, FormatacaoDeHora) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteData3"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_hora.txt")), logs);
    std::filesystem::remove_all("./totais");
}

/**
 * @title Teste de Cobertura de Caixa Aberta: Validação de Comprimento da String
 * @dev Garante a restrição estrita de captura de mensagens que possuam entre 1 e 100 caracteres.
 */
TEST(MonitorLog, FormatacaoTamanho) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteTamanho2"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_tamanho.txt")), logs);
    std::filesystem::remove_all("./totais");
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste_tamanho.txt")), logs);
    std::filesystem::remove_all("./totais");
}

/**
 * @title Teste do Mecanismo de Merge e Ordenação Cronológica Crescente
 * @dev Comprova que, após a leitura combinada, o arquivo consolidado organiza os registros estritamente pelo tempo.
 */
TEST(MonitorLog, OrdenacaoDosLogs) {
    vector<string> logs = {"18/10/2006 10:07:23 TesteTamanho4", "18/10/2006 10:07:24 TesteTamanho3", "19/10/2006 10:07:23 TesteTamanho2", "20/10/2006 10:07:23 TesteTamanho1"};
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste_ordenacao.txt")), logs);
    std::filesystem::remove_all("./totais");
}
