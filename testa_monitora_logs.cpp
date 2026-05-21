// Copyright 2026 Enzo Cardoso Martins
#include "gtest/gtest.h"
#include "monitora_logs.hpp"

TEST(MonitorLog, LerLog) {
    vector<string> log_teste = {"19/10/2006 10:07:23 Teste"};
    EXPECT_EQ(ler_logs("./logs/log_teste.txt"), log_teste);
}

TEST(MonitorLog, LerLogIniexistente) {
    vector<string> log_teste = {"Erro ao abrir o arquivo"};
    EXPECT_EQ(ler_logs("log_inexistente.txt"), log_teste);
}

TEST(MonitorLog, EscreverLogTotal) {
    vector<string> log_teste = {"19/10/2006 10:07:23 Teste"};
    EXPECT_EQ(ler_arq(escrever_log_total("./logs/log_teste.txt")), log_teste);
}

TEST(MonitorLog, LerLogVariasLinhas) {
    vector<string> logs = {"19/10/2006 10:07:23 Teste1", "19/10/2006 10:07:23 Teste2", "19/10/2006 10:07:23 Teste3"};
    EXPECT_EQ(ler_logs("./logs/log_teste_multiplas_linhas.txt"), logs);
}

TEST(MonitorLog, EscreverArquivoInexistente) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteArquivoIn1", "19/10/2006 10:07:23 TesteArquivoIn2", "19/10/2006 10:07:23 TesteArquivoIn3"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_arq_in.txt")), logs);
}

TEST(MonitorLog, LeituraListaMestra) {
    //analisar a lista mestra
    EXPECT_EQ(processar_lista_mestra("./lista_mestra.txt"), 1);
}

TEST(MonitorLog, LeituraListaMestra2) {
    vector<string> logs = {"./logs/Log1.txt", "./logs/Log2.txt", "./logs/Log3.txt"};
    vector<string> log1 = {"19/10/2006 10:07:23 TesteLog11", "19/10/2006 10:07:23 TesteLog12", "19/10/2006 10:07:23 TesteLog13"};
    vector<string> log2 = {"19/10/2006 10:07:23 TesteLog21", "19/10/2006 10:07:23 TesteLog22", "19/10/2006 10:07:23 TesteLog23"};
    vector<string> log3 = {"19/10/2006 10:07:23 TesteLog31", "19/10/2006 10:07:23 TesteLog32", "19/10/2006 10:07:23 TesteLog33"};
    
    //Analisar os logs
    EXPECT_EQ(ler_logs(logs.at(0)), log1);    
    EXPECT_EQ(ler_logs(logs.at(1)), log2);    
    EXPECT_EQ(ler_logs(logs.at(2)), log3);
}

TEST(MonitorLog, LeituraListaMestra3) {
    vector<string> logs = {"./logs/Log1.txt", "./logs/Log2.txt", "./logs/Log3.txt"};
    vector<string> log1 = {"19/10/2006 10:07:23 TesteLog11", "19/10/2006 10:07:23 TesteLog12", "19/10/2006 10:07:23 TesteLog13"};
    vector<string> log2 = {"19/10/2006 10:07:23 TesteLog21", "19/10/2006 10:07:23 TesteLog22", "19/10/2006 10:07:23 TesteLog23"};
    vector<string> log3 = {"19/10/2006 10:07:23 TesteLog31", "19/10/2006 10:07:23 TesteLog32", "19/10/2006 10:07:23 TesteLog33"};

    //Analisar a escrita dos totais
    EXPECT_EQ(ler_logs(escrever_log_total(logs.at(0))), log1);    
    EXPECT_EQ(ler_logs(escrever_log_total(logs.at(1))), log2);    
    EXPECT_EQ(ler_logs(escrever_log_total(logs.at(2))), log3);
}

TEST(MonitorLog, FormatacaoDeData) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteData3"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_data.txt")), logs);
}

TEST(MonitorLog, FormatacaoDeHora) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteData3"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_hora.txt")), logs);
}

TEST(MonitorLog, FormatacaoTamanho) {
    vector<string> logs = {"19/10/2006 10:07:23 TesteTamanho2"};
    EXPECT_EQ(ler_logs(escrever_log_total("./logs/log_teste_tamanho.txt")), logs);
}