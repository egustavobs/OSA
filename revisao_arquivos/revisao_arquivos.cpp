#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Aluno {
private:
    int matricula;
    string nome;
    string cidade;

public:

Aluno(int matricula, string nome, string cidade){
    this ->matricula = matricula;
    this -> nome = nome;
    this -> cidade = cidade;
}

int getMatricula() const{
    return matricula;
}

string getNome() const{
    return nome;
}

string getCidade() const{
    return cidade;
}

public: 
    string paraLinha() const {
        return to_string(matricula) + ";" + nome + ";" + cidade;
    }

    
};

void gravarAlunos(const vector<Aluno>& alunos, const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if(!arquivo){
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }

    for (const Aluno& aluno : alunos) {
        arquivo << aluno.paraLinha() << endl;
    }

    arquivo.close();
}

vector<Aluno> lerAlunos(const string& nomeArquivo){
    vector<Aluno> alunos;
    ifstream arquivo(nomeArquivo);

    string linha;

    while(getline(arquivo,linha)){

    stringstream ss(linha);

    string matricula;
    string nome;
    string cidade;

    getline(ss, matricula, ';');
    getline(ss, nome, ';');
    getline(ss, cidade, ';');

    alunos.push_back(Aluno(stoi(matricula), nome, cidade));
    }
    arquivo.close();
    return alunos;
}

Aluno* buscarPorMatricula(vector<Aluno>& alunos, int matricula){
    for (Aluno& aluno : alunos) {
        if (aluno.getMatricula() == matricula) {
            return &aluno;
        }
    }
    return nullptr;
}

int main(){

    int matriculaBusca;

    vector<Aluno> alunos;

    alunos.push_back(Aluno(1, "Edson", "Montes Claros"));
    alunos.push_back(Aluno(2, "João", "Montes Claros"));
    alunos.push_back(Aluno(3, "Helena", "Belo Horizonte"));

    gravarAlunos(alunos, "alunos.txt");
    vector<Aluno> alunosLidos = lerAlunos("alunos.txt");

    cout << "Digite a matrícula do aluno que deseja buscar: ";
    cin >> matriculaBusca;

    Aluno* encontrado = buscarPorMatricula(alunosLidos, matriculaBusca);

    if(encontrado != nullptr){
        cout << "Aluno encontrado: " << encontrado->getNome() <<endl;
        cout << "Cidade: " << encontrado->getCidade() << endl;
    } else {
        cout << "Matricula nao localizada." << endl;
    }

    return 0;
}
