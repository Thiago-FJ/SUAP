#include "Pessoa.h"
#include <iostream>
#include <limits>

using namespace std;

Pessoa::Pessoa() {}

void Pessoa::inserirPessoa() {
    cout << "\t\tInsira o nome: ";
    getline(cin, nome);
    cout << "\t\tInsira o sobrenome: ";
    getline(cin, sobrenome);
    cout << "\t\tInsira o prontuário (ex: 1234): ";
    getline(cin, prontuario);

    email = nome + "." + sobrenome + "@edu.com";
}

string Pessoa::getNome() const { return nome; }
string Pessoa::getSobrenome() const { return sobrenome; }
string Pessoa::getProntuario() const { return "SJ" + prontuario; }
string Pessoa::getEmail() const { return email; }

