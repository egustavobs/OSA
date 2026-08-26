#include <iostream>
#include <iomanip>
#include <cstring>
#include "Aluno.h"
#include "GerenciadorArquivo.h"

constexpr int TAMANHO_REGISTRO = 36;

void exibirAluno(const Aluno& aluno, int rrn) {
    std::cout << "\n---------------------------------------------\n";
    std::cout << "RRN       : " << rrn << '\n';
    std::cout << "Matricula : " << aluno.getMatricula() << '\n';
    std::cout << "Nome      : " << aluno.getNome() << '\n';
    std::cout << "Idade     : " << aluno.getIdade() << '\n';
    std::cout << "Media     : "
              << std::fixed << std::setprecision(2)
              << aluno.getMedia() << '\n';
    std::cout << "---------------------------------------------\n";
}

void exibirTabela(const Aluno alunos[], int quantidade) {
    std::cout << '\n';
    std::cout << std::left
              << std::setw(8) << "RRN"
              << std::setw(12) << "Matricula"
              << std::setw(25) << "Nome"
              << std::setw(8) << "Idade"
              << std::setw(8) << "Media"
              << '\n';

    std::cout << std::setfill('-')
              << std::setw(61) << ""
              << std::setfill(' ') << '\n';

    for (int i = 0; i < quantidade; ++i) {
        std::cout << std::left
                  << std::setw(8) << i
                  << std::setw(12) << alunos[i].getMatricula()
                  << std::setw(25) << alunos[i].getNome()
                  << std::setw(8) << alunos[i].getIdade()
                  << std::setw(8) << std::fixed
                  << std::setprecision(2) << alunos[i].getMedia()
                  << '\n';
    }
}

bool testeCompatibilidade(const Aluno& aluno) {
    char buffer[TAMANHO_REGISTRO];

    int bytesPack = aluno.pack(buffer);

    Aluno copia;
    int bytesUnpack = copia.unpack(buffer);

    bool tamanhoCorreto = bytesPack == TAMANHO_REGISTRO &&
                          bytesUnpack == TAMANHO_REGISTRO;

    bool dadosIguais =
        aluno.getMatricula() == copia.getMatricula() &&
        std::strcmp(aluno.getNome(), copia.getNome()) == 0 &&
        aluno.getIdade() == copia.getIdade() &&
        aluno.getMedia() == copia.getMedia();

    return tamanhoCorreto && dadosIguais;
}

int main() {
    const std::string nomeArquivo = "alunos.dat";

    GerenciadorArquivo gerenciador(nomeArquivo);

    Aluno alunos[5];

    alunos[0].setMatricula(1001);
    alunos[0].setNome("Ana Silva");
    alunos[0].setIdade(20);
    alunos[0].setMedia(8.5f);

    alunos[1].setMatricula(1002);
    alunos[1].setNome("Bruno Santos");
    alunos[1].setIdade(22);
    alunos[1].setMedia(7.8f);

    alunos[2].setMatricula(1003);
    alunos[2].setNome("Carlos Oliveira");
    alunos[2].setIdade(19);
    alunos[2].setMedia(9.2f);

    alunos[3].setMatricula(1004);
    alunos[3].setNome("Daniela Souza");
    alunos[3].setIdade(21);
    alunos[3].setMedia(6.9f);

    alunos[4].setMatricula(1005);
    alunos[4].setNome("Eduardo Lima");
    alunos[4].setIdade(24);
    alunos[4].setMedia(8.0f);

    std::cout << "=============================================\n";
    std::cout << "        LABORATORIO 02 - ARQUIVOS\n";
    std::cout << "=============================================\n";

    std::cout << "\nGravando alunos no arquivo...\n";

    bool gravacaoOK = true;

    for (int i = 0; i < 5; ++i) {
        if (gerenciador.escreverNoRegistro(i, alunos[i])) {
            std::cout << "RRN " << i << " gravado com sucesso.\n";
        } else {
            std::cout << "Erro ao gravar o RRN " << i << ".\n";
            gravacaoOK = false;
        }
    }

    if (!gravacaoOK) {
        std::cout << "\nNao foi possivel concluir a gravacao.\n";
        return 1;
    }

    std::cout << "\nBase de teste criada:\n";
    exibirTabela(alunos, 5);

    std::cout << "\nTeste de compatibilidade de serializacao: ";

    if (testeCompatibilidade(alunos[0])) {
        std::cout << "OK\n";
        std::cout << "Pack/Unpack preservaram os dados e os 36 bytes.\n";
    } else {
        std::cout << "FALHOU\n";
    }

    std::cout << "\n=============================================\n";
    std::cout << "          BUSCA POR RRN\n";
    std::cout << "=============================================\n";

    int rrn;

    while (true) {
        std::cout << "\nDigite o RRN (0 a 4) ou -1 para sair: ";
        std::cin >> rrn;

        if (!std::cin) {
            std::cout << "Entrada invalida.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (rrn == -1) {
            break;
        }

        if (rrn < 0 || rrn > 4) {
            std::cout << "RRN inexistente. Informe um valor entre 0 e 4.\n";
            continue;
        }

        Aluno alunoLido;

        if (gerenciador.lerDoRegistro(rrn, alunoLido)) {
            exibirAluno(alunoLido, rrn);
        } else {
            std::cout << "Erro ao ler o registro solicitado.\n";
        }
    }

    std::cout << "\nPrograma encerrado.\n";

    return 0;
}
