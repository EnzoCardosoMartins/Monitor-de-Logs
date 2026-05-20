// Copyright 2026 Enzo Cardoso Martins
#ifndef LOGMONITOR_HPP_
#define LOGMONITOR_HPP_
#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

string escrever_log_total(string log);
vector<string> ler_arq(string arq_path);

#endif  // LOGMONITOR_HPP_
