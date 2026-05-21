// Copyright 2026 Enzo Cardoso Martins
#include "gtest/gtest.h"
#include "monitora_logs.hpp"

TEST(MonitorLog, LerLog) {
    vector<string> log_teste = {"Teste"};
    EXPECT_EQ(ler_arq("./logs/log_teste.txt"), log_teste);
}

TEST(MonitorLog, LerLogIniexistente) {
    vector<string> log_teste = {"Erro ao abrir o arquivo"};
    EXPECT_EQ(ler_arq("log_inexistente.txt"), log_teste);
}

TEST(MonitorLog, EscreverLogTotal) {
    vector<string> log_teste = {"Teste"};
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste.txt")), log_teste);
}

TEST(MonitorLog, LerLogVariasLinhas) {
    vector<string> logs = {"Teste1", "Teste2", "Teste3"};
    EXPECT_EQ(ler_arq("./logs/log_teste_multiplas_linhas.txt"), logs);
}

TEST(MonitorLog, EscreverArquivoInexistente) {
    vector<string> logs = {"TesteArquivoIn1", "TesteArquivoIn2", "TesteArquivoIn3"};
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste_arq_in.txt")), logs);
}