#include "UI.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <iomanip>

using namespace std;

UI::UI(DatabaseManager& dbManager) : dbManager(dbManager) {}

void UI::Logo() {
    cout << R"(   +######+   -+++.        .+++   -+######+-     +++-  .+#####+.
  #####++###- +###-        -###.  #####++#####+    ###############+
 ####         +###-        -###.          ####-   +#####-      #####
 ####         +###-        -###.            ###+   +####          +###+
 -#####+      +###-        -###.    -##########   +###.          ####
   +#######-  +###-        -###.  +#############   +###            +###
         -##### +###-        +###. ####.      ####   +###            ####
           +###. -###+        ####. +###.      ####   +###+          +###+
           +###.  ####-      #####. +###-      #####   +####+        +####
.###########+    ###############.  +##############   +###############+
 +########.        .#######. ###-    .#######- ###   +### +#######.
                                                     +###
                                                     +###
                                                     +###
                                                     +###
                                                     +###
                                                     +###
                                                     +###
                                                     +###
)" << endl;
}

int UI::TelaPrincipal() {
    int op = -1;
    LimpaTela();
    Logo();
    cout << "\n\t\t-------- ESCOLHA O PORTAL --------" << endl;
    cout << "\t\t1. Professor" << endl;
    cout << "\t\t2. Aluno" << endl;
    cout << "\t\t3. Diretoria" << endl;
    cout << "\t\t0. Sair" << endl;
    cout << "\t\t----------------------------------" << endl;
    cout << "\t\tEscolha uma opcao: ";

    op = Validar(0, 3);

    return op;
}

int UI::selecionarAluno() {
    vector<map<string,string>> alunos = dbManager.executarSelect(
        "SELECT alunoid, prontuario, nome, sobrenome FROM Aluno;"
    );

    if (alunos.empty()) {
        cout << "\t\tNenhum aluno cadastrado.\n";
        system("pause");
        return -1;
    }

    cout << "\t\tEscolha seu aluno:\n";
    for (size_t i = 0; i < alunos.size(); i++) {
        cout << "\t\t" << i+1 << ". " << alunos[i]["prontuario"] << " - "
             << alunos[i]["nome"] << " " << alunos[i]["sobrenome"] << "\n";
    }

    cout << "\t\tDigite o número correspondente: ";
    int escolha = Validar(1, (int)alunos.size());

    return stoi(alunos[escolha-1]["alunoid"]);
}

int UI::selecionarProfessor() {
    vector<map<string,string>> professores = dbManager.executarSelect(
        "SELECT professorid, prontuario, nome, sobrenome FROM Professor;"
    );

    if (professores.empty()) {
        cout << "\t\tNenhum professor cadastrado.\n";
        system("pause");
        return -1;
    }

    cout << "\t\tEscolha seu professor:\n";
    for (size_t i = 0; i < professores.size(); i++) {
        cout << "\t\t" << i+1 << ". " << professores[i]["prontuario"] << " - "
             << professores[i]["nome"] << " " << professores[i]["sobrenome"] << "\n";
    }

    cout << "\t\tDigite o número correspondente: ";
    int escolha = Validar(1, (int)professores.size());

    return stoi(professores[escolha-1]["professorid"]);
}

int UI::OpProfessor() {
    int professorId = selecionarProfessor();
    if (professorId == -1) {
        return 0;
    }

    int op = -1;
    do {
        LimpaTela();
        cout << "\n\t\t-------- PROFESSOR --------" << endl;
        cout << "\t\t1. Lancar Nota" << endl;
        cout << "\t\t2. Ver Alunos" << endl;
        cout << "\t\t3. Ver Materias que Leciona" << endl;
        cout << "\t\t0. Voltar" << endl;
        cout << "\t\t----------------------------" << endl;
        cout << "\t\tEscolha uma opcao: ";

        op = Validar(0, 3);

        switch (op) {
            case 1: {
                LimpaTela();
                cout << "\t\t[Professor] Funcionalidade: Lançar Nota\n";
                Professor p;
                p.lancarNota(dbManager, professorId);
                system("pause");
                break;
            }
            case 2:
                LimpaTela();
                cout << "\t\t[Professor] Funcionalidade: Ver Alunos\n";
                listarAlunos();
                system("pause");
                break;
            case 3: {
                LimpaTela();
                cout << "\t\t[Professor] Funcionalidade: Ver Matérias que Leciona\n";
                Professor p;
                p.verMateriasLecionadas(dbManager, professorId);
                system("pause");
                break;
            }
        }
    } while (op != 0);
    return 0;
}

int UI::OpAluno() {
    int alunoId = selecionarAluno();
    if (alunoId == -1) {
        return 0;
    }

    int op = -1;
    do {
        LimpaTela();
        cout << "\n\t\t-------- ALUNO --------" << endl;
        cout << "\t\t1. Verificar Notas" << endl;
        cout << "\t\t2. Verificar Materias Matriculadas" << endl;
        cout << "\t\t3. Verificar Situacao (Media Geral)" << endl;
        cout << "\t\t4. Matricular em Materia" << endl;
        cout << "\t\t0. Voltar" << endl;
        cout << "\t\t------------------------" << endl;
        cout << "\t\tEscolha uma opcao: ";

        op = Validar(0, 4);

        switch (op) {
            case 1: {
                LimpaTela();
                cout << "\t\t[Aluno] Funcionalidade: Ver Notas\n";
                Aluno a;
                a.verificarNotas(dbManager, alunoId);
                system("pause");
                break;
            }
            case 2: {
                LimpaTela();
                cout << "\t\t[Aluno] Funcionalidade: Ver Matérias Matriculadas\n";
                Aluno a;
                a.listarMateriasMatriculadas(dbManager, alunoId);
                system("pause");
                break;
            }
            case 3: {
                LimpaTela();
                cout << "\t\t[Aluno] Funcionalidade: Ver Situação (Média Geral)\n";
                Aluno a;
                a.verificarSituacao(dbManager, alunoId);
                system("pause");
                break;
            }
            case 4: {
                LimpaTela();
                cout << "\t\t[Aluno] Funcionalidade: Matricular em Matéria\n";
                Aluno a;
                a.matricularEmMateria(dbManager, alunoId);
                system("pause");
                break;
            }
        }
    } while (op != 0);
    return 0;
}

int UI::OpDiretoria() {
    int op = -1;
    do {
        LimpaTela();
        cout << "\n\t\t-------- DIRETORIA --------" << endl;
        cout << "\t\t1. Ver Professores" << endl;
        cout << "\t\t2. Ver Alunos" << endl;
        cout << "\t\t3. Ver Materias" << endl;
        cout << "\t\t4. Adicionar Professor" << endl;
        cout << "\t\t5. Adicionar Aluno" << endl;
        cout << "\t\t6. Adicionar Materia" << endl;
        cout << "\t\t7. Excluir Aluno" << endl;
        cout << "\t\t8. Associar Professor a Materia" << endl;
        cout << "\t\t0. Voltar" << endl;
        cout << "\t\t----------------------------" << endl;
        cout << "\t\tEscolha uma opcao: ";

        op = Validar(0, 8);

        switch (op) {
            case 1:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Ver Professores\n";
                listarProfessores();
                system("pause");
                break;
            case 2:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Ver Alunos\n";
                listarAlunos();
                system("pause");
                break;
            case 3:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Ver Matérias\n";
                listarMaterias();
                system("pause");
                break;
            case 4:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Adicionar Professor\n";
                adicionarProfessor();
                system("pause");
                break;
            case 5:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Adicionar Aluno\n";
                adicionarAluno();
                system("pause");
                break;
            case 6:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Adicionar Matéria\n";
                adicionarMateria();
                system("pause");
                break;
            case 7:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Excluir Aluno\n";
                excluirAluno();
                system("pause");
                break;
            case 8:
                LimpaTela();
                cout << "\t\t[Diretoria] Funcionalidade: Associar Professor a Matéria\n";
                associarProfessorMateria();
                system("pause");
                break;
        }
    } while (op != 0);
    return 0;
}

void UI::LimpaTela() {
    system("cls");

}

int UI::Validar(int min, int max) {
    int esc;
    cin >> esc;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return esc;
}

void UI::listarProfessores() {
    vector<map<string,string>> professores = dbManager.executarSelect(
        "SELECT prontuario, nome, sobrenome, titulacao, email FROM Professor;"
    );

    if (professores.empty()) {
        cout << "\t\tNenhum professor cadastrado.\n";
        return;
    }

    cout << "\n\t\t--- Lista de Professores ---\n";
    for (const auto& prof : professores) {
        cout << "\t\tProntuario: " << prof.at("prontuario")
             << ", Nome: " << prof.at("nome") << " " << prof.at("sobrenome")
             << ", Titulacao: " << prof.at("titulacao")
             << ", Email: " << prof.at("email") << "\n";
    }
    cout << "\t\t----------------------------\n";
}

void UI::listarAlunos() {
    vector<map<string,string>> alunos = dbManager.executarSelect(
        "SELECT prontuario, nome, sobrenome, curso, email FROM Aluno;"
    );

    if (alunos.empty()) {
        cout << "\t\tNenhum aluno cadastrado.\n";
        return;
    }

    cout << "\t\t\n--- Lista de Alunos ---\n";
    for (const auto& aluno : alunos) {
        cout << "\t\tProntuario: " << aluno.at("prontuario")
             << ", Nome: " << aluno.at("nome") << " " << aluno.at("sobrenome")
             << ", Curso: " << aluno.at("curso")
             << ", Email: " << aluno.at("email") << "\n";
    }
    cout << "\t\t-----------------------\n";
}

void UI::listarMaterias() {
    vector<map<string,string>> materias = dbManager.executarSelect(
        "SELECT nome FROM Materia;"
    );

    if (materias.empty()) {
        cout << "\t\tNenhuma matéria cadastrada.\n";
        return;
    }

    cout << "\t\t\n--- Lista de Matérias ---\n";
    for (const auto& mat : materias) {
        cout << "\t\t- " << mat.at("nome") << "\n";
    }
    cout << "\t\t-------------------------\n";
}

void UI::adicionarProfessor() {
    Professor novoProfessor;
    novoProfessor.inserirProfessor();
    novoProfessor.salvarNoBanco(dbManager);
}

void UI::adicionarAluno() {
    Aluno novoAluno;
    novoAluno.inserirAluno();
    novoAluno.salvarNoBanco(dbManager);
}

void UI::adicionarMateria() {
    Materia novaMateria;
    novaMateria.inserirMateria();
    novaMateria.salvarNoBanco(dbManager);
}

void UI::excluirAluno() {
    vector<map<string,string>> alunos = dbManager.executarSelect(
        "SELECT alunoid, prontuario, nome, sobrenome FROM Aluno;"
    );

    if (alunos.empty()) {
        cout << "\t\tNenhum aluno cadastrado para exclusão.\n";
        return;
    }

    cout << "\t\t\n--- Excluir Aluno ---\n";
    for (size_t i = 0; i < alunos.size(); i++) {
        cout << "\t\t" << i+1 << ". " << alunos[i]["prontuario"] << " - "
             << alunos[i]["nome"] << " " << alunos[i]["sobrenome"] << "\n";
    }
    cout << "\t\t0. Cancelar\n";
    cout << "\t\tDigite o número do aluno a ser excluído: ";
    int escolha = Validar(0, (int)alunos.size());

    if (escolha == 0) {
        cout << "\t\tOperação de exclusão cancelada.\n";
        return;
    }

    int alunoId = stoi(alunos[escolha-1]["alunoid"]);
    string nomeAluno = alunos[escolha-1]["nome"] + " " + alunos[escolha-1]["sobrenome"];

    string sqlDeleteNotas = "DELETE FROM Nota WHERE alunoid = " + to_string(alunoId) + ";";
    dbManager.executarQuery(sqlDeleteNotas);

    string sqlDeleteMatriculas = "DELETE FROM Aluno_Materia WHERE alunoid = " + to_string(alunoId) + ";";
    dbManager.executarQuery(sqlDeleteMatriculas);

    string sqlDeleteAluno = "DELETE FROM Aluno WHERE alunoid = " + to_string(alunoId) + ";";
    if (dbManager.executarQuery(sqlDeleteAluno)) {
        cout << "\t\tAluno '" << nomeAluno << "' excluído com sucesso.\n";
    } else {
        cout << "\t\tErro ao excluir o aluno '" << nomeAluno << "'.\n";
    }
}

void UI::associarProfessorMateria() {
    vector<map<string,string>> professores = dbManager.executarSelect(
        "SELECT professorid, prontuario, nome, sobrenome FROM Professor;"
    );

    if (professores.empty()) {
        cout << "\t\tNenhum professor cadastrado para associar.\n";
        return;
    }

    cout << "\t\t\n--- Associar Professor a Matéria ---\n";
    cout << "\t\tEscolha o professor:\n";
    for (size_t i = 0; i < professores.size(); i++) {
        cout << "\t\t" << i+1 << ". " << professores[i]["prontuario"] << " - "
             << professores[i]["nome"] << " " << professores[i]["sobrenome"] << "\n";
    }
    cout << "\t\t0. Cancelar\n";
    cout << "\t\tDigite o número correspondente ao professor: ";
    int escolhaProf = Validar(0, (int)professores.size());

    if (escolhaProf == 0) {
        cout << "\t\tOperação cancelada.\n";
        return;
    }
    int professorId = stoi(professores[escolhaProf-1]["professorid"]);
    string nomeProf = professores[escolhaProf-1]["nome"] + " " + professores[escolhaProf-1]["sobrenome"];

    vector<map<string,string>> materias = dbManager.executarSelect(
        "SELECT materiaid, nome FROM Materia;"
    );

    if (materias.empty()) {
        cout << "\t\tNenhuma matéria cadastrada para associar.\n";
        return;
    }

    cout << "\t\t\nEscolha a matéria:\n";
    for (size_t i = 0; i < materias.size(); i++) {
        cout << "\t\t" << i+1 << ". " << materias[i]["nome"] << "\n";
    }
    cout << "\t\t0. Cancelar\n";
    cout << "\t\tDigite o número correspondente à matéria: ";
    int escolhaMat = Validar(0, (int)materias.size());

    if (escolhaMat == 0) {
        cout << "\t\tOperação cancelada.\n";
        return;
    }
    int materiaId = stoi(materias[escolhaMat-1]["materiaid"]);
    string nomeMat = materias[escolhaMat-1]["nome"];

    string checkSql = "SELECT COUNT(*) FROM Materia_Professor WHERE materiaid = " + to_string(materiaId) +
                      " AND professorid = " + to_string(professorId) + ";";
    auto result = dbManager.executarSelect(checkSql);
    if (!result.empty() && stoi(result[0].at("COUNT(*)")) > 0) {
        cout << "\t\tO professor '" << nomeProf << "' já está associado à matéria '" << nomeMat << "'.\n";
        return;
    }

    string sql = "INSERT INTO Materia_Professor (materiaid, professorid) VALUES (" +
                 to_string(materiaId) + ", " + to_string(professorId) + ");";

    if (dbManager.executarQuery(sql)) {
        cout << "\t\tProfessor '" << nomeProf << "' associado à matéria '" << nomeMat << "' com sucesso!\n";
    } else {
        cout << "\t\tErro ao associar professor à matéria.\n";
    }
}
