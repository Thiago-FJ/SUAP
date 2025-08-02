#include "Professor.h"
#include <iostream>
#include <limits>

using namespace std;

Professor::Professor() : Pessoa() {}

void Professor::inserirProfessor() {
    inserirPessoa();
    cout << "\t\tInsira a titulação (ex: Mestre, Doutor): ";
    getline(cin, titulacao);
}

string Professor::getTitulacao() const {
    return titulacao;
}

void Professor::salvarNoBanco(DatabaseManager& dbManager) {
    string sql = "INSERT INTO Professor (titulacao, prontuario, nome, sobrenome, email) VALUES ('" +
                 titulacao + "', '" + getProntuario() + "', '" + getNome() + "', '" + getSobrenome() + "', '" + getEmail() + "');";

    if (!dbManager.executarQuery(sql)) {
        cerr << "\t\tFalha ao salvar professor no banco." << endl;
    } else {
        cout << "\t\tProfessor salvo com sucesso no banco." << endl;
    }
}

void Professor::lancarNota(DatabaseManager& dbManager, int professorId) {
    auto alunos = dbManager.executarSelect("SELECT alunoid, nome, sobrenome FROM Aluno;");
    if (alunos.empty()) {
        cout << "\t\tNenhum aluno cadastrado." << endl;
        return;
    }

    cout << "\t\tAlunos disponiveis:\n";
    for (size_t i = 0; i < alunos.size(); ++i) {
        cout << "\t\t" << i + 1 << ". " << alunos[i]["nome"] << " " << alunos[i]["sobrenome"] << "\n";
    }
    cout << "\t\tEscolha o aluno (0 para cancelar): ";
    int escolhaAluno;
    cin >> escolhaAluno;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (escolhaAluno <= 0 || escolhaAluno > (int)alunos.size()) {
        cout << "\t\tOperacao cancelada." << endl;
        return;
    }
    int alunoId = stoi(alunos[escolhaAluno - 1]["alunoid"]);

    string sqlMateriasLecionadas = "SELECT M.materiaid, M.nome FROM Materia M "
                                   "JOIN Materia_Professor MP ON M.materiaid = MP.materiaid "
                                   "WHERE MP.professorid = " + to_string(professorId) + ";";
    auto materias = dbManager.executarSelect(sqlMateriasLecionadas);

    if (materias.empty()) {
        cout << "\t\tVocê não está associado a nenhuma matéria para lançar notas." << endl;
        return;
    }

    cout << "\t\tMaterias que você leciona:\n";
    for (size_t i = 0; i < materias.size(); ++i) {
        cout << "\t\t" << i + 1 << ". " << materias[i]["nome"] << "\n";
    }
    cout << "\t\tEscolha a materia (0 para cancelar): ";
    int escolhaMateria;
    cin >> escolhaMateria;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (escolhaMateria <= 0 || escolhaMateria > (int)materias.size()) {
        cout << "\t\tOperacao cancelada." << endl;
        return;
    }
    int materiaId = stoi(materias[escolhaMateria - 1]["materiaid"]);

    double nota;
    cout << "\t\tDigite a nota: ";
    cin >> nota;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string checkMatriculaSql = "SELECT COUNT(*) FROM Aluno_Materia WHERE alunoid = " + to_string(alunoId) +
                               " AND materiaid = " + to_string(materiaId) + ";";
    auto matriculaCheck = dbManager.executarSelect(checkMatriculaSql);
    if (matriculaCheck.empty() || stoi(matriculaCheck[0].at("COUNT(*)")) == 0) {
        cout << "\t\tO aluno nao esta matriculado nesta materia. Nao e possivel lançar a nota." << endl;
        return;
    }

    string checkNotaSql = "SELECT notaid FROM Nota WHERE alunoid = " + to_string(alunoId) +
                          " AND materiaid = " + to_string(materiaId) +
                          " AND professorid = " + to_string(professorId) + ";";
    auto existingNote = dbManager.executarSelect(checkNotaSql);

    string sql;
    if (!existingNote.empty()) {
        sql = "UPDATE Nota SET valornota = " + to_string(nota) +
              " WHERE notaid = " + existingNote[0].at("notaid") + ";";
    } else {
        sql = "INSERT INTO Nota (alunoid, materiaid, professorid, valornota) VALUES (" +
              to_string(alunoId) + ", " + to_string(materiaId) + ", " + to_string(professorId) + ", " + to_string(nota) + ");";
    }

    if (dbManager.executarQuery(sql)) {
        cout << "\t\tNota lancada/atualizada com sucesso!" << endl;
    } else {
        cout << "\t\tErro ao lancar/atualizar nota." << endl;
    }
}

void Professor::verMateriasLecionadas(DatabaseManager& dbManager, int professorId) {
    string sql = "SELECT M.nome FROM Materia M "
                 "JOIN Materia_Professor MP ON M.materiaid = MP.materiaid "
                 "WHERE MP.professorid = " + to_string(professorId) + ";";

    auto materias = dbManager.executarSelect(sql);
    if (materias.empty()) {
        cout << "\t\tVocê nao leciona nenhuma matéria." << endl;
        return;
    }

    cout << "\t\t\nMaterias que voce leciona:\n";
    for (const auto& mat : materias) {
        cout << "\t\t- " << mat.at("nome") << endl;
    }
}
