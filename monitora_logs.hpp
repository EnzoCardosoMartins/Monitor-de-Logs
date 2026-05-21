// Copyright 2026 Enzo Cardoso Martins
#ifndef LOGMONITOR_HPP_
#define LOGMONITOR_HPP_
#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

string escrever_log_total(string log);
vector<string> ler_arq(string arq_path);
int processar_lista_mestra(string list_path);
vector<string> ler_logs(string log_path);
vector<string> sort_logs(vector<string>);

#endif  // LOGMONITOR_HPP_
