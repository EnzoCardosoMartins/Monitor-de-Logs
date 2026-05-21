#include "monitora_logs.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
#include <regex>
using namespace std;
namespace fs = std::filesystem;

vector<string> ler_arq(string arq_path){

    vector<string> logs;

    regex padrao("^(0?[1-9]|[12][0-9]|3[01])/(0?[1-9]|1[0-2])/\\d{4}\\s+([01]?[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]\\s+.{1,100}$");

    if(fs::exists(arq_path)){
        ifstream arq(arq_path);
        string linha;

        if(arq.is_open()){
            while(getline(arq, linha)){
                if(regex_match(linha, padrao)) logs.push_back(linha);
            }
            arq.close();
        } else{
            logs.push_back("Erro ao abrir o arquivo");
        }      

    } else{
        logs.push_back("Erro ao abrir o arquivo");
    }

    return logs;
}




string escrever_log_total(string log){

    fs::path log_path = log;
    string str_log_path = log_path.filename().string();
    string string_total_path = ("./totais/total_");
    fs::path total_path = string_total_path+str_log_path;
    ofstream arq(total_path);
    

    if(arq.is_open()){
        vector<string> logs = ler_arq(log);
        for(string linha : logs){
            arq << linha << endl;
        }
    } else{
        return "Erro ao escrever no arquivo.";
    }

    arq.close();
    string str_arq_path = total_path.string();
    return str_arq_path;
}


int processar_lista_mestra(string list_path){

    if(!fs::exists(list_path)) return 0;

    vector<string> logs = ler_arq(list_path);
    for(string log : logs) escrever_log_total(log);

    return 1;
}