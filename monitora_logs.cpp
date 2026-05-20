#include "monitora_logs.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

vector<string> ler_arq(string arq_path){

    if(fs::exists(arq_path)){
        ifstream arq(arq_path);
        string linha;

        if(arq.is_open()){
            getline(arq, linha);
            arq.close();
            return linha;
        } else return "Erro ao abrir o arquivo";     

    } else{
        return "Erro ao abrir o arquivo";
    }
}

string escrever_log_total(string log){

    ofstream arq("./totais/total_log_teste.txt");

    if(arq.is_open()){
        arq << ler_arq(log) << endl;
    } else{
        return "Erro ao escrever no arquivo.";
    }

    return "./totais/total_log_teste.txt";
}