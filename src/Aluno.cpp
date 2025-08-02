#include "Aluno.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

Aluno::Aluno() : Pessoa() {}

void Aluno::inserirAluno() {
    inserirPessoa();
    cout << "\t\tInsira o curso: ";
    getline(cin, curso);
}

string Aluno::getCurso() const {
    return curso;
}

void Aluno::salvarNoBanco(DatabaseManager& dbManager) {
    string sql = "INSERT INTO Aluno (curso, prontuario, nome, sobrenome, email) VALUES ('" +
                 curso + "', '" + getProntuario() + "', '" + getNome() + "', '" + getSobrenome() + "', '" + getEmail() + "');";

    if (!dbManager.executarQuery(sql)) {
        cerr << "\t\tFalha ao salvar aluno no banco." << endl;
    } else {
        cout << "\t\tAluno salvo com sucesso no banco." << endl;
    }
}

void Aluno::matricularEmMateria(DatabaseManager& dbManager, int alunoId) {
    auto materias = dbManager.executarSelect("SELECT materiaid, nome FROM Materia;");
    if (materias.empty()) {
        cout << "\t\tNenhuma matéria cadastrada para matrícula." << endl;
        return;
    }

    cout << "\t\tMatérias disponíveis para matrícula:\n";
    for (size_t i = 0; i < materias.size(); ++i) {
        cout << "\t\t" << i + 1 << ". " << materias[i]["nome"] << "\n";
    }

    cout << "\t\tEscolha o número da matéria para matricular (0 para cancelar): ";
    int escolha;
    cin >> escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (escolha <= 0 || escolha > (int)materias.size()) {
        cout << "\t\tOperação cancelada." << endl;
        return;
    }

    int materiaId = stoi(materias[escolha - 1]["materiaid"]);
    string nomeMateria = materias[escolha - 1]["nome"];

    string checkSql = "SELECT COUNT(*) FROM Aluno_Materia WHERE alunoid = " + to_string(alunoId) +
                      " AND materiaid = " + to_string(materiaId) + ";";
    auto result = dbManager.executarSelect(checkSql);
    if (!result.empty() && stoi(result[0].at("COUNT(*)")) > 0) {
        cout << "\t\tVocê já está matriculado na matéria '" << nomeMateria << "'.\n";
        return;
    }

    string sql = "INSERT INTO Aluno_Materia (alunoid, materiaid) VALUES (" +
                 to_string(alunoId) + ", " + to_string(materiaId) + ");";

    if (dbManager.executarQuery(sql)) {
        cout << "\t\tMatrícula em '" << nomeMateria << "' realizada com sucesso!" << endl;
    } else {
        cout << "\t\tErro ao matricular aluno na matéria." << endl;
    }
}

void Aluno::listarMateriasMatriculadas(DatabaseManager& dbManager, int alunoId) {
    string sql = "SELECT M.nome FROM Materia M "
                 "JOIN Aluno_Materia AM ON M.materiaid = AM.materiaid "
                 "WHERE AM.alunoid = " + to_string(alunoId) + ";";

    auto materias = dbManager.executarSelect(sql);
    if (materias.empty()) {
        cout << "\t\tVocê não está matriculado em nenhuma matéria." << endl;
        return;
    }

    cout << "\t\t\nMatérias matriculadas:\n";
    for (auto& mat : materias) {
        cout << "\t\t- " << mat["nome"] << endl;
    }
}

void Aluno::verificarNotas(DatabaseManager& dbManager, int alunoId) {
    string sql = "SELECT M.nome AS Materia, N.valornota AS Nota, P.nome AS ProfessorNome, P.sobrenome AS ProfessorSobrenome "
                 "FROM Nota N "
                 "JOIN Materia M ON N.materiaid = M.materiaid "
                 "JOIN Professor P ON N.professorid = P.professorid "
                 "WHERE N.alunoid = " + to_string(alunoId) + ";";

    auto notas = dbManager.executarSelect(sql);
    if (notas.empty()) {
        cout << "\t\tVocê não possui notas lançadas ainda." << endl;
        return;
    }

    cout << "\t\t\n--- Suas Notas ---\n";
    cout << fixed << setprecision(2);
    for (const auto& nota : notas) {
        cout << "\t\tMatéria: " << nota.at("Materia")
             << ", Nota: " << nota.at("Nota")
             << ", Professor: " << nota.at("ProfessorNome") << " " << nota.at("ProfessorSobrenome") << "\n";
    }
    cout << "\t\t------------------\n";
}

void Aluno::verificarSituacao(DatabaseManager& dbManager, int alunoId) {
    string sql = "SELECT AVG(valornota) AS MediaGeral FROM Nota WHERE alunoid = " + to_string(alunoId) + ";";

    auto resultado = dbManager.executarSelect(sql);
    if (resultado.empty() || resultado[0].at("MediaGeral").empty()) {
        cout << "\t\tNão há notas suficientes para calcular a média geral." << endl;
        return;
    }

    double media = stod(resultado[0].at("MediaGeral"));
    cout << "\t\t\n--- Sua Situação ---\n";
    cout << fixed << setprecision(2);
    cout << "\t\tMédia Geral: " << media << "\n";

    if (media >= 6.0) {
        cout << "\t\tSituação: Aprovado!\n";
    } else {
        cout << "\t\tSituação: Reprovado. Necessita de mais esforço.\n";
    }
    cout << "\t\t--------------------\n";
}
