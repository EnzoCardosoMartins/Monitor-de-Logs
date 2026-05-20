#include "monitora_logs.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

vector<string> ler_arq(string arq_path){

    vector<string> logs;

    if(fs::exists(arq_path)){
        ifstream arq(arq_path);
        string linha;

        if(arq.is_open()){
            while(getline(arq, linha)){
                logs.push_back(linha);
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

    ofstream arq("./totais/total_log_teste.txt");

    if(arq.is_open()){
        vector<string> logs = ler_arq(log);
        for(string linha : logs){
            arq << linha << endl;
        }
    } else{
        return "Erro ao escrever no arquivo.";
    }

    arq.close();
    return "./totais/total_log_teste.txt";
}