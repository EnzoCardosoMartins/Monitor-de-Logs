// Copyright 2026 Enzo Cardoso Martins
#include "monitora_logs.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <filesystem>  // NOLINT(build/c++17)
#include <fstream>
#include <regex>
#include <string>
#include <vector>

using namespace std;  // NOLINT(build/namespaces)
namespace fs = std::filesystem;

vector<string> ler_arq(string arq_path) {
    vector<string> logs;

    if (fs::exists(arq_path)) {
        ifstream arq(arq_path);
        string linha;

        if (arq.is_open()) {
            while (getline(arq, linha)) {
                // if (regex_match(linha, padrao))
                logs.push_back(linha);
            }
            arq.close();
        } else {
            logs.push_back("Erro ao abrir o arquivo");
        }
    } else {
        logs.push_back("Erro ao abrir o arquivo");
    }

    return logs;
}

vector<string> ler_logs(string log_path) {
    vector<string> logs = ler_arq(log_path);

    if (logs.at(0) == "Erro ao abrir o arquivo") return logs;

    regex padrao("^(0?[1-9]|[12][0-9]|3[01])/(0?[1-9]|1[0-2])/\\d{4}\\s+([01]?[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]\\s+.{1,100}$");
    vector<string> logs_formatados;
    for (string log : logs) {
        if (regex_match(log, padrao)) logs_formatados.push_back(log);
    }

    return logs_formatados;
}

string escrever_log_total(string log) {
    fs::path log_path = log;
    string str_log_path = log_path.filename().string();
    string string_total_path = ("./totais/total_");
    fs::path total_path = string_total_path + str_log_path;
    fs::create_directories("./totais");
    vector<string> logs = ler_logs(log);
    vector<string> todos_logs;
    todos_logs.insert(todos_logs.end(), logs.begin(), logs.end());

    if (fs::exists(total_path)) {
        vector<string> logs_antigos = ler_arq(total_path.string());
        todos_logs.insert(todos_logs.end(), logs_antigos.begin(), logs_antigos.end());
    }

    std::sort(todos_logs.begin(), todos_logs.end(), [](const string& a, const string& b) {
        int dA, mA, yA, hA, minA, sA;
        int dB, mB, yB, hB, minB, sB;

        sscanf(a.c_str(), "%d/%d/%d %d:%d:%d", &dA, &mA, &yA, &hA, &minA, &sA);
        sscanf(b.c_str(), "%d/%d/%d %d:%d:%d", &dB, &mB, &yB, &hB, &minB, &sB);

        return std::tie(yA, mA, dA, hA, minA, sA) < std::tie(yB, mB, dB, hB, minB, sB);
    });

    ofstream arq(total_path);
    if (arq.is_open()) {
        for (string linha : todos_logs) {
            arq << linha << endl;
        }
    } else {
        return "Erro ao escrever no arquivo.";
    }

    arq.close();
    string str_arq_path = total_path.string();
    return str_arq_path;
}

int processar_lista_mestra(string list_path) {
    if (!fs::exists(list_path)) return 0;

    vector<string> logs = ler_arq(list_path);
    for (string log : logs) escrever_log_total(log);

    return 1;
}
