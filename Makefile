# Variáveis de Compilação
CXX = g++
# Flags: C++17, warnings ativados, símbolos de depuração e flags de cobertura obrigatórias
# O makefile deve incluir as flags -ftest-coverage -fprofile-arcs [cite: 88]
CXXFLAGS = -std=c++17 -Wall -Wextra -g -fprofile-arcs -ftest-coverage
# Bibliotecas do Google Test e Threads
LDFLAGS = -lgtest -lgtest_main -lpthread

# Nomes dos arquivos definidos na especificação 
TARGET = testa_monitora_logs
SOURCES = monitora_logs.cpp testa_monitora_logs.cpp
OBJECTS = monitora_logs.o testa_monitora_logs.o

# --- Alvos Principais ---

# Alvo padrão: Compila o executável de testes
all: $(TARGET)

# Linkagem do executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilação dos módulos individuais 
monitora_logs.o: monitora_logs.cpp monitora_logs.hpp
	$(CXX) $(CXXFLAGS) -c monitora_logs.cpp

testa_monitora_logs.o: testa_monitora_logs.cpp monitora_logs.hpp
	$(CXX) $(CXXFLAGS) -c testa_monitora_logs.cpp

# --- Ferramentas de Verificação ---

# 1. Executa os testes unitários [cite: 76]
test: all
	./$(TARGET)

# 2. Gera o relatório de cobertura de código [cite: 89]
# Nota: É necessário rodar 'make test' antes para gerar os dados .gcda
coverage:
	gcov monitora_logs.cpp

# 3. Verificação estática com cppcheck [cite: 93]
cppcheck:
	cppcheck --enable=warning .

# 4. Verificação de estilo com cpplint [cite: 74]
cpplint:
	cpplint --filter=-build/include_subdir monitora_logs.cpp monitora_logs.hpp testa_monitora_logs.cpp
	
# 5. Verificação dinâmica de memória com Valgrind [cite: 97]
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# 6. Abre o depurador GDB [cite: 70]
debug: all
	gdb ./$(TARGET)

# 7. Documentação com Doxygen 
docs:
	doxygen Doxyfile

# --- Limpeza ---

# Remove binários, arquivos temporários de cobertura e pastas geradas pelo Doxygen
clean:
	rm -f *.o *.gcda *.gcno *.gcov $(TARGET)
	rm -rf html/ latex/

.PHONY: all test coverage cppcheck cpplint valgrind debug docs clean
