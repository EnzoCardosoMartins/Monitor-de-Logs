// Copyright 2026 Enzo Cardoso Martins
#ifndef MONITORA_LOGS_HPP_
#define MONITORA_LOGS_HPP_
#include <bits/stdc++.h>  // NOLINT(build/c++17)
#include <filesystem>  // NOLINT(build/c++17)
#include <string>
#include <vector>
using namespace std;  // NOLINT(build/c++17)
namespace fs = std::filesystem;

string escrever_log_total(string log);
vector<string> ler_arq(string arq_path);
int processar_lista_mestra(string list_path);
vector<string> ler_logs(string log_path);

#endif  // MONITORA_LOGS_HPP_
