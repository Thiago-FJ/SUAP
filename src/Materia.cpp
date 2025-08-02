#include "Materia.h"
#include <iostream>
#include <limits>

using namespace std;

Materia::Materia() {}

void Materia::inserirMateria() {
    cout << "\t\tInsira o nome da mat�ria: ";
    getline(cin, nome);
}

string Materia::getNome() const {
    return nome;
}

void Materia::salvarNoBanco(DatabaseManager& dbManager) {
    string sql = "INSERT INTO Materia (nome) VALUES ('" + nome + "');";

    if (!dbManager.executarQuery(sql)) {
        cerr << "\t\tErro ao salvar mat�ria no banco." << endl;
    } else {
        cout << "\t\tMat�ria salva com sucesso." << endl;
    }
}
