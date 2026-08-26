CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET = lab02
OBJS = main.o Aluno.o GerenciadorArquivo.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Aluno.h GerenciadorArquivo.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Aluno.o: Aluno.cpp Aluno.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

GerenciadorArquivo.o: GerenciadorArquivo.cpp GerenciadorArquivo.h Aluno.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) alunos.dat

.PHONY: all clean
