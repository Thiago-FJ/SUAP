#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <map>
#include "DatabaseManager.h"
#include "Professor.h"
#include "Aluno.h"
#include "Materia.h"

using namespace std;

class UI {
public:
    UI(DatabaseManager& dbManager);

    void Logo();
    int TelaPrincipal();

    int OpProfessor();
    int OpAluno();
    int OpDiretoria();

    void LimpaTela();
    int Validar(int min, int max);

    void listarProfessores();
    void listarAlunos();
    void listarMaterias();
    void adicionarProfessor();
    void adicionarAluno();
    void adicionarMateria();
    void excluirAluno();
    void associarProfessorMateria();


private:
    int selecionarAluno();
    int selecionarProfessor();

    DatabaseManager& dbManager;
};

#endif
