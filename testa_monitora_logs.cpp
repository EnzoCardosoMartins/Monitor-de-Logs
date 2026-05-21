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

TEST(MonitorLog, LeituraListaMestra) {
    //analisar a lista mestra
    EXPECT_EQ(processar_lista_mestra("./lista_mestra.txt"), 1);
}

TEST(MonitorLog, LeituraListaMestra2) {
    vector<string> logs = {"./logs/Log1.txt", "./logs/Log2.txt", "./logs/Log3.txt"};
    vector<string> log1 = {"TesteLog11", "TesteLog12", "TesteLog13"};
    vector<string> log2 = {"TesteLog21", "TesteLog22", "TesteLog23"};
    vector<string> log3 = {"TesteLog31", "TesteLog32", "TesteLog33"};
    
    //Analisar os logs
    EXPECT_EQ(ler_arq(logs.at(0)), log1);    
    EXPECT_EQ(ler_arq(logs.at(1)), log2);    
    EXPECT_EQ(ler_arq(logs.at(2)), log3);
}

TEST(MonitorLog, LeituraListaMestra3) {
    vector<string> logs = {"./logs/Log1.txt", "./logs/Log2.txt", "./logs/Log3.txt"};
    vector<string> log1 = {"TesteLog11", "TesteLog12", "TesteLog13"};
    vector<string> log2 = {"TesteLog21", "TesteLog22", "TesteLog23"};
    vector<string> log3 = {"TesteLog31", "TesteLog32", "TesteLog33"};

    //Analisar a escrita dos totais
    EXPECT_EQ(ler_arq(escrever_log_total(logs.at(0))), log1);    
    EXPECT_EQ(ler_arq(escrever_log_total(logs.at(1))), log2);    
    EXPECT_EQ(ler_arq(escrever_log_total(logs.at(2))), log3);
}

TEST(MonitorLog, FormatacaoDeData) {
    vector<string> logs = {"19/10/2006 TesteArquivoIn1", "19/10/2006 TesteArquivoIn2", "19/10/2006 TesteArquivoIn3"};
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste_arq_in.txt")), logs);
}