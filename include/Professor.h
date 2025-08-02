#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Pessoa.h"
#include "DatabaseManager.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Professor : public Pessoa {
private:
    string titulacao;

public:
    Professor();

    void inserirProfessor();
    string getTitulacao() const;

    void salvarNoBanco(DatabaseManager& dbManager);

    void lancarNota(DatabaseManager& dbManager, int professorId);

    void verMateriasLecionadas(DatabaseManager& dbManager, int professorId);
};

#endif
