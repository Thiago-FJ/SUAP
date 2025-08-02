#include <iostream>
#include "DatabaseManager.h"
#include "Professor.h"
#include "Aluno.h"
#include "Materia.h"
#include "UI.h"

using namespace std;

int main() {
    DatabaseManager db;
    UI ui(db);

    int opcao;

    do {
        opcao = ui.TelaPrincipal();
        switch (opcao) {
            case 1:
                ui.OpProfessor();
                break;
            case 2:
                ui.OpAluno();
                break;
            case 3:
                ui.OpDiretoria();
                break;
            case 0:
                cout << "\t\t\nEncerrando o programa...\n";
                system("pause");
                return 0;
            default:
                cout << "\t\tOpção inválida. Tente novamente.\n";
                system("pause");
                break;
        }
    } while (true);

    return 0;
}
