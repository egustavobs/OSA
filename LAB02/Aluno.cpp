#include "Aluno.h"
#include <cstring>

Aluno::Aluno()
    : matricula(0), idade(0), media(0.0f)
{
    std::memset(nome, 0, sizeof(nome));
}

int Aluno::getMatricula() const {
    return matricula;
}

void Aluno::setMatricula(int m) {
    if (m >= 0) {
        matricula = m;
    }
}

const char* Aluno::getNome() const {
    return nome;
}

void Aluno::setNome(const char* n) {
    std::memset(nome, 0, sizeof(nome));

    if (n != nullptr) {
        std::strncpy(nome, n, sizeof(nome) - 1);
        nome[sizeof(nome) - 1] = '\0';
    }
}

int Aluno::getIdade() const {
    return idade;
}

void Aluno::setIdade(int i) {
    if (i >= 0 && i <= 150) {
        idade = i;
    }
}

float Aluno::getMedia() const {
    return media;
}

void Aluno::setMedia(float m) {
    if (m >= 0.0f && m <= 10.0f) {
        media = m;
    }
}

int Aluno::pack(char* buffer) const {
    if (buffer == nullptr) {
        return 0;
    }

    int posicao = 0;

    std::memcpy(buffer + posicao, &matricula, sizeof(matricula));
    posicao += sizeof(matricula);

    std::memcpy(buffer + posicao, nome, sizeof(nome));
    posicao += sizeof(nome);

    std::memcpy(buffer + posicao, &idade, sizeof(idade));
    posicao += sizeof(idade);

    std::memcpy(buffer + posicao, &media, sizeof(media));
    posicao += sizeof(media);

    return posicao;
}

int Aluno::unpack(const char* buffer) {
    if (buffer == nullptr) {
        return 0;
    }

    int posicao = 0;

    std::memcpy(&matricula, buffer + posicao, sizeof(matricula));
    posicao += sizeof(matricula);

    std::memcpy(nome, buffer + posicao, sizeof(nome));
    nome[sizeof(nome) - 1] = '\0';
    posicao += sizeof(nome);

    std::memcpy(&idade, buffer + posicao, sizeof(idade));
    posicao += sizeof(idade);

    std::memcpy(&media, buffer + posicao, sizeof(media));
    posicao += sizeof(media);

    return posicao;
}
