// Copyright 2026 Enzo Cardoso Martins
#include "gtest/gtest.h"
#include "monitora_logs.hpp"

TEST(MonitorLog, LerLog) {
    EXPECT_EQ(ler_log("log_teste.txt"), "Teste");
}

TEST(MonitorLog, LerLogIniexistente) {
    EXPECT_EQ(ler_log("log_inexistente.txt"), "Erro ao abrir o arquivo");
}