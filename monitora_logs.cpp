#include "monitora_logs.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

string ler_log(string arq_name){

    fs::path caminho = "./logs";
    fs::path log_path = caminho / arq_name;

    if(fs::exists(log_path)){
        ifstream log(log_path);
        string linha;

        if(log.is_open()){
            getline(log, linha);
            log.close();
            return linha;
        } else return "Erro ao abrir o arquivo";     

    } else{
        return "Erro ao abrir o arquivo";
    }
}

string ler_arq(string arq_path){
    return "";
}

string escrever_log_total(string log){
    return "";
}