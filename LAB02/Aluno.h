#ifndef ALUNO_H
#define ALUNO_H

class Aluno {
private:
    int matricula;
    char nome[24];
    int idade;
    float media;

public:
    Aluno();

    int getMatricula() const;
    void setMatricula(int m);

    const char* getNome() const;
    void setNome(const char* n);

    int getIdade() const;
    void setIdade(int i);

    float getMedia() const;
    void setMedia(float m);

    int pack(char* buffer) const;
    int unpack(const char* buffer);
};

#endif
