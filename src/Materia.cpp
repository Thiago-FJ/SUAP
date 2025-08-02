#include "Materia.h"
#include <iostream>
#include <limits>

using namespace std;

Materia::Materia() {}

void Materia::inserirMateria() {
    cout << "\t\tInsira o nome da matéria: ";
    getline(cin, nome);
}

string Materia::getNome() const {
    return nome;
}

void Materia::salvarNoBanco(DatabaseManager& dbManager) {
    string sql = "INSERT INTO Materia (nome) VALUES ('" + nome + "');";

    if (!dbManager.executarQuery(sql)) {
        cerr << "\t\tErro ao salvar matéria no banco." << endl;
    } else {
        cout << "\t\tMatéria salva com sucesso." << endl;
    }
}
