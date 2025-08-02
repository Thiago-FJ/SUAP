#ifndef PESSOA_H
#define PESSOA_H

#include <string>

using namespace std;

class Pessoa {
protected:
    string nome;
    string sobrenome;
    string prontuario;
    string email;

public:
    Pessoa();

    void inserirPessoa();

    string getNome() const;
    string getSobrenome() const;
    string getProntuario() const;
    string getEmail() const;
};

#endif
