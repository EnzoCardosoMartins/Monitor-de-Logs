// Copyright 2026 Enzo Cardoso Martins
#include "gtest/gtest.h"
#include "monitora_logs.hpp"

TEST(MonitorLog, LerLog) {
    EXPECT_EQ(ler_arq("./logs/log_teste.txt"), "Teste");
}

TEST(MonitorLog, LerLogIniexistente) {
    EXPECT_EQ(ler_arq("log_inexistente.txt"), "Erro ao abrir o arquivo");
}

TEST(MonitorLog, EscreverLogTotal) {
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste.txt")), "Teste");
}

TEST(MonitorLog, LerLogVariasLinhas) {
    vector<string> logs = {"Teste1", "Teste2", "Teste3"};
    EXPECT_EQ(ler_arq("./logs/log_teste_multiplas_linhas.txt"), logs);
}