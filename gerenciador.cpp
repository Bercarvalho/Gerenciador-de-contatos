#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void addcontato() {
    string nome, telefone;
    ofstream arquivo;
    arquivo.open("contatos.txt", ios::app);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar o contato." << endl;
        return;
    }
    cout << "Digite o nome do contato: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer
    getline(cin, nome);
    cout << "Digite o número do contato: ";
    cin >> telefone;

    if (telefone.length() != 12 || !all_of(telefone.begin(), telefone.end(), ::isdigit)) {
        cout << "Número inválido. O número deve ter 12 dígitos." << endl;
        return;
    }

    arquivo << nome << " " << telefone << endl;
    arquivo.close();
    cout << "Contato adicionado com sucesso!" << endl;
}

void exibircontatos() {
    string linha;
    ifstream arquivo;
    arquivo.open("contatos.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para leitura." << endl;
        return;
    }

    cout << "Lista de contatos:\n";
    while (getline(arquivo, linha)) {
        cout << linha << endl;
    }
    arquivo.close();
}

void excluircontato() {
    string nome, linha;
    ifstream arquivo("contatos.txt");
    ofstream temp("temp.txt");
    if (!arquivo.is_open() || !temp.is_open()) {
        cout << "Erro ao abrir os arquivos para exclusão." << endl;
        return;
    }

    cout << "Digite o nome do contato que deseja excluir: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer
    getline(cin, nome);

    while (getline(arquivo, linha)) {
        if (linha.find(nome) == string::npos) {
            temp << linha << endl;
        }
    }
    arquivo.close();
    temp.close();

    remove("contatos.txt");
    rename("temp.txt", "contatos.txt");
    cout << "Contato excluído com sucesso (se existente)." << endl;
}

int main() {
    int opcao;
    do {
        cout << "========================\n"
             << "1 - Adicionar contato\n"
             << "2 - Exibir contatos\n"
             << "3 - Excluir contato\n"
             << "4 - Sair\n"
             << "========================\n"
             << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                addcontato();
                break;
            case 2:
                exibircontatos();
                break;
            case 3:
                excluircontato();
                break;
            case 4:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 4);

    return 0;
}
