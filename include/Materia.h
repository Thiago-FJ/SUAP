#ifndef MATERIA_H
#define MATERIA_H

#include <string>
#include "DatabaseManager.h"

using namespace std;

class Materia {
private:
    string nome;

public:
    Materia();

    void inserirMateria();
    string getNome() const;

    void salvarNoBanco(DatabaseManager& dbManager);
};

#endif
