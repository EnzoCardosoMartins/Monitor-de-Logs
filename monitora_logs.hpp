// Copyright 2026 Enzo Cardoso Martins
#ifndef MONITORA_LOGS_HPP_
#define MONITORA_LOGS_HPP_

#include <filesystem>     // NOLINT(build/c++17)
#include <string>
#include <vector>

using namespace std;      // NOLINT(build/c++17)
namespace fs = std::filesystem;

/**
 * @brief Consolida, ordena cronologicamente e salva os logs novos e antigos em um arquivo totalizador.
 * @param log Caminho do arquivo de log que está sendo monitorado no momento.
 * @return string Caminho do arquivo totalizador gerado.
 */
string escrever_log_total(string log);

/**
 * @brief Lê o conteúdo de um arquivo de log bruto e armazena suas linhas em um vetor.
 * @param arq_path Caminho do arquivo a ser lido.
 * @return vector<string> Vetor contendo as linhas lidas do arquivo.
 */
vector<string> ler_arq(string arq_path);

/**
 * @brief Processa o arquivo mestre contendo a listagem de múltiplos caminhos de logs.
 * @param list_path Caminho para o arquivo mestre (ex: lista_mestra.txt).
 * @return int Retorna 1 se o arquivo foi processado com sucesso, ou 0 se ele não existir.
 */
int processar_lista_mestra(string list_path);

/**
 * @brief Filtra e valida os logs de um arquivo com base em uma expressão regular.
 * @param log_path Caminho do arquivo de log a ser filtrado e validado.
 * @return vector<string> Vetor com os registros que estão estritamente no padrão correto.
 */
vector<string> ler_logs(string log_path);

#endif  // MONITORA_LOGS_HPP_
