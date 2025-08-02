#ifndef ALUNO_H
#define ALUNO_H

#include "Pessoa.h"
#include "DatabaseManager.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Aluno : public Pessoa {
private:
    string curso;

public:
    Aluno();

    void inserirAluno();
    string getCurso() const;

    void salvarNoBanco(DatabaseManager& dbManager);

    void matricularEmMateria(DatabaseManager& dbManager, int alunoId);

    void listarMateriasMatriculadas(DatabaseManager& dbManager, int alunoId);

    void verificarNotas(DatabaseManager& dbManager, int alunoId);

    void verificarSituacao(DatabaseManager& dbManager, int alunoId);
};

#endif
