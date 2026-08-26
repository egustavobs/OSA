#include "GerenciadorArquivo.h"
#include <fstream>

namespace {
    constexpr int TAMANHO_REGISTRO = 36;
}

GerenciadorArquivo::GerenciadorArquivo(const std::string& nome)
    : nomeArquivo(nome)
{
}

bool GerenciadorArquivo::escreverNoRegistro(int rrn, const Aluno& aluno) {
    if (rrn < 0) {
        return false;
    }

    char buffer[TAMANHO_REGISTRO];

    if (aluno.pack(buffer) != TAMANHO_REGISTRO) {
        return false;
    }

    std::fstream arquivo(
        nomeArquivo,
        std::ios::in | std::ios::out | std::ios::binary
    );

    if (!arquivo.is_open()) {
        arquivo.open(
            nomeArquivo,
            std::ios::out | std::ios::binary
        );
        arquivo.close();

        arquivo.open(
            nomeArquivo,
            std::ios::in | std::ios::out | std::ios::binary
        );
    }

    if (!arquivo.is_open()) {
        return false;
    }

    std::streamoff offset =
        static_cast<std::streamoff>(rrn) * TAMANHO_REGISTRO;

    arquivo.seekp(offset, std::ios::beg);

    if (!arquivo.good()) {
        return false;
    }

    arquivo.write(buffer, TAMANHO_REGISTRO);

    return arquivo.good();
}

bool GerenciadorArquivo::lerDoRegistro(int rrn, Aluno& aluno) {
    if (rrn < 0) {
        return false;
    }

    std::ifstream arquivo(nomeArquivo, std::ios::binary);

    if (!arquivo.is_open()) {
        return false;
    }

    char buffer[TAMANHO_REGISTRO];

    std::streamoff offset =
        static_cast<std::streamoff>(rrn) * TAMANHO_REGISTRO;

    arquivo.seekg(offset, std::ios::beg);

    if (!arquivo.good()) {
        return false;
    }

    arquivo.read(buffer, TAMANHO_REGISTRO);

    if (arquivo.gcount() != TAMANHO_REGISTRO) {
        return false;
    }

    return aluno.unpack(buffer) == TAMANHO_REGISTRO;
}
