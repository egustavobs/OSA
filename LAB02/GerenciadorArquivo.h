#ifndef GERENCIADORARQUIVO_H
#define GERENCIADORARQUIVO_H

#include <string>
#include "Aluno.h"

class GerenciadorArquivo {
private:
    std::string nomeArquivo;

public:
    GerenciadorArquivo(const std::string& nome);

    bool escreverNoRegistro(int rrn, const Aluno& aluno);
    bool lerDoRegistro(int rrn, Aluno& aluno);
};

#endif
