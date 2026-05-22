// Copyright 2026 Enzo Cardoso Martins
/**
 * @file monitora_logs.cpp
 * @brief Implementação das funções do sistema de monitoramento de logs.
 *
 * Descrição detalhada: Este arquivo contém a lógica de negócio para leitura,
 * filtragem por expressões regulares, merge e ordenação cronológica de registros.
 */
#include "monitora_logs.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <filesystem>  // NOLINT(build/c++17)
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <cassert>     // Incluído para a utilização de assertivas

using namespace std;  // NOLINT(build/namespaces)
namespace fs = std::filesystem;

/**
 * @brief Lê o conteúdo de um arquivo de log bruto e armazena suas linhas em um vetor.
 * * Descrição:
 * Esta função verifica se o arquivo informado existe no diretório. Em caso positivo, 
 * tenta abri-lo e extrair todas as suas linhas de forma sequencial. Se o arquivo não puder 
 * ser aberto ou não existir, insere uma mensagem de erro na primeira posição do vetor de retorno.
 * * Parâmetros:
 * @param arq_path Caminho relativo ou absoluto do arquivo a ser lido.
 * * Valor retornado:
 * @return vector<string> Vetor contendo as linhas lidas do arquivo ou uma mensagem de erro.
 * * Assertiva de entrada:
 * - O caminho do arquivo contido em arq_path não deve ser uma string vazia.
 * * Assertiva de saída:
 * - Se o arquivo existir e for aberto com sucesso, o vetor retornado conterá as linhas lidas.
 * - Se o arquivo não existir ou falhar ao abrir, o vetor retornado terá tamanho maior ou igual a 1 
 * e conterá a string "Erro ao abrir o arquivo" na primeira posição.
 */
vector<string> ler_arq(string arq_path) {
    // Assertiva de entrada: garante que o caminho do arquivo não está em branco
    assert(!arq_path.empty() && "O caminho do arquivo nao pode ser vazio.");

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

    // Assertiva de saída: garante que o vetor de retorno nunca sairá completamente vazio
    assert(!logs.empty() && "O vetor de logs retornados nao deve estar vazio.");
    return logs;
}

/**
 * @brief Filtra e valida os logs de um arquivo com base em uma expressão regular.
 * * Descrição:
 * Chama a função ler_arq() para obter as linhas brutas. Se o arquivo retornar erro, 
 * repassa o erro adiante. Caso contrário, valida cada linha segundo a regex que estipula 
 * o formato exato de data, hora e string de até 100 caracteres com o log.
 * * Parâmetros:
 * @param log_path Caminho do arquivo de log a ser filtrado e validado.
 * * Valor retornado:
 * @return vector<string> Vetor com os registros que estão estritamente no padrão correto da regex.
 * * Assertiva de entrada:
 * - O caminho do arquivo contido em log_path não deve ser uma string vazia.
 * * Assertiva de saída:
 * - O vetor retornado deve conter exclusivamente linhas que obedeçam à formatação estrita de data 
 * (DD/MM/AAAA ou D/M/AAAA), hora (HH:MM:SS) e mensagem de texto de até 100 caracteres.
 */
vector<string> ler_logs(string log_path) {
    // Assertiva de entrada: garante que o caminho do log para filtragem não está em branco
    assert(!log_path.empty() && "O caminho do log para filtragem nao pode ser vazio.");

    vector<string> logs = ler_arq(log_path);

    if (logs.at(0) == "Erro ao abrir o arquivo") return logs;

    regex padrao("^(0?[1-9]|[12][0-9]|3[01])/(0?[1-9]|1[0-2])/\\d{4}\\s+([01]?[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]\\s+.{1,100}$");
    vector<string> logs_formatados;
    for (string log : logs) {
        if (regex_match(log, padrao)) logs_formatados.push_back(log);
    }

    return logs_formatados;
}

/**
 * @brief Consolida, ordena cronologicamente e salva os logs novos e antigos em um arquivo totalizador.
 * * Descrição:
 * Esta função lê os novos logs validados do arquivo informado, busca se já existe um histórico 
 * consolidado em `./totais/total_<nome_do_arquivo>` e une os dois conjuntos (merge). Em seguida, 
 * realiza a ordenação temporal correta e reescreve o arquivo consolidado atualizado.
 * * Parâmetros:
 * @param log Caminho do arquivo de log que está sendo monitorado no momento.
 * * Valor retornado:
 * @return string Caminho do arquivo totalizador gerado em formato de string.
 * * Assertiva de entrada:
 * - O argumento string contendo o caminho do log não deve estar vazio.
 * * Assertiva de saída:
 * - O arquivo final resultante "total_" na pasta "./totais" deve conter a união indexada dos 
 * logs antigos e novos, ordenados de forma estritamente cronológica crescente.
 */
string escrever_log_total(string log) {
    // Assertiva de entrada: garante que o argumento de log para consolidação não está vazio
    assert(!log.empty() && "O argumento de log para consolidacao nao pode ser vazio.");

    fs::path log_path = log;
    string str_log_path = log_path.filename().string();
    string string_total_path = ("./totais/total_");
    fs::path total_path = string_total_path + str_log_path;
    fs::create_directories("./totais");
    vector<string> logs = ler_logs(log);
    vector<string> todos_logs;
    todos_logs.insert(todos_logs.end(), logs.begin(), logs.end());

    if (todos_logs.size() == 1 && todos_logs[0] == "Erro ao abrir o arquivo") {
        return "Erro ao escrever no arquivo.";
    }

    if (fs::exists(total_path)) {
        vector<string> logs_antigos = ler_arq(total_path.string());
        todos_logs.insert(todos_logs.end(), logs_antigos.begin(), logs_antigos.end());
    }

    std::sort(todos_logs.begin(), todos_logs.end(), [](const string& a, const string& b) {
        int dA, mA, yA, hA, minA, sA;
        int dB, mB, yB, hB, minB, sB;

        int parsedA = sscanf(a.c_str(), "%d/%d/%d %d:%d:%d", &dA, &mA, &yA, &hA, &minA, &sA);
        int parsedB = sscanf(b.c_str(), "%d/%d/%d %d:%d:%d", &dB, &mB, &yB, &hB, &minB, &sB);

        // Invariante de controle: garante que o sscanf extraiu com sucesso os 6 tokens temporais necessários
        assert(parsedA == 6 && "Falha crítica ao realizar o parsing de data/hora do log A.");
        assert(parsedB == 6 && "Falha crítica ao realizar o parsing de data/hora do log B.");

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
    
    // Assertiva de saída: certifica que o arquivo consolidado foi fisicamente gerado em disco antes do retorno
    assert(fs::exists(total_path) && "O arquivo de totais consolidado deveria existir em disco apos a gravacao.");
    
    return str_arq_path;
}

/**
 * @brief Processa o arquivo mestre contendo a listagem de múltiplos caminhos de logs.
 * * Descrição:
 * Verifica a existência da lista mestra indicada. Se encontrada, extrai as linhas contendo os 
 * caminhos dos logs individuais do sistema e repassa cada um deles sequencialmente para que o merge 
 * e a ordenação em seus respectivos arquivos totais ocorram.
 * * Parâmetros:
 * @param list_path Caminho em string para o arquivo mestre (ex: lista_mestra.txt).
 * * Valor retornado:
 * @return int Retorna 1 se o arquivo de lista mestre foi processado com sucesso, ou 0 se ele não existir.
 * * Assertiva de entrada:
 * - A string contendo o caminho do arquivo list_path não deve ser vazia.
 * * Assertiva de saída:
 * - Retorna 0 imediatamente se a lista mestra não for encontrada fisicamente.
 * - Retorna 1 caso o arquivo mestre tenha sido lido e seus itens encaminhados para a gravação.
 */
int processar_lista_mestra(string list_path) {
    // Assertiva de entrada: garante que o caminho da lista mestra não está em branco
    assert(!list_path.empty() && "O caminho da lista mestra nao pode ser vazio.");

    if (!fs::exists(list_path)) return 0;

    vector<string> logs = ler_arq(list_path);
    for (string log : logs) escrever_log_total(log);

    return 1;
}