#include <iostream>

#define MAX 1000

using namespace std;

// Definir a struct de Curso
struct Curso {
    int codigo;
    string nome;
    int carga;
    int vagas;
};

// Definir a struct para armazenar o ID do curso vinculado aos alunos
struct Id {
    int codigo;
};

// Definir a struct de Aluno fazendo o vínculo com a struct Id
struct Aluno {
    int matricula;
    string nome;
    int idade;
    Id curso;
};

// Procedimento para exibir o menu de opções
void mostrarMenu(){
    cout << "#################### MENU ####################\n";
    cout << "1 - Cadastrar curso\n";
    cout << "2 - Cadastrar aluno\n";
    cout << "3 - Listar os cursos cadastrados\n";
    cout << "4 - Listar os alunos matriculados\n";
    cout << "5 - Buscar alunos por curso\n";
    cout << "6 - Relatorio geral\n";
    cout << "7 - Sair\n";
    cout << "##############################################\n\n";
    cout << "Digite sua opcao: ";
}

// Procedimento para cadastrar um novo curso
void cadastrarCurso(Curso vet[], int i, int nCursosAtuais){
    cout << "Digite o codigo do curso: ";
    cin >> vet[i].codigo;

    // Impede que dois cursos tenham o mesmo código
    for (int j = 0; j < nCursosAtuais; j++) {
        if (vet[j].codigo == vet[i].codigo) {
            cout << "Erro: Ja existe um curso cadastrado com este codigo!\n\n";
            return;
        }
    }

    cin.ignore();
    cout << "Digite o nome do curso: ";
    getline(cin, vet[i].nome);
    cout << "Digite a carga horaria total: ";
    cin >> vet[i].carga;
    cout << "Digite a quantidade de vagas: ";
    cin >> vet[i].vagas;
    cout << "Curso cadastrado com sucesso!\n\n";
}

// Procedimento para mostrar os cursos cadastrados
void mostrarCursos(Curso vet[], int n){
    cout << "\n--- Cursos Cadastrados ---\n";
    if (n == 0) {
        cout << "Nenhum curso cadastrado.\n";
    }
    for (int i = 0; i < n; i++){
        cout << "-----------------------------------------------\n";
        cout << "[" << i + 1 << "] Codigo: " << vet[i].codigo << endl;
        cout << "Nome: " << vet[i].nome << endl;
        cout << "Carga Horaria: " << vet[i].carga << "h\n";
        cout << "Vagas: " << vet[i].vagas << endl;
    }
    cout << "-----------------------------------------------\n\n";
}

// Procedimento para cadastrar Aluno
void cadastrarAluno(Aluno vetAluno[], int iAluno, Curso vetCurso[], int nCurso) {
    cout << "Digite o numero da matricula: ";
    cin >> vetAluno[iAluno].matricula;
    cin.ignore();
    cout << "Digite o nome completo: ";
    getline(cin, vetAluno[iAluno].nome);
    cout << "Digite a idade: ";
    cin >> vetAluno[iAluno].idade;

    // Exibimos os cursos disponíveis numerados para o usuário escolher
    mostrarCursos(vetCurso, nCurso);

    int escolha;
    do {
        cout << "Digite o numero correspondente ao curso do aluno (1 a " << nCurso << "): ";
        cin >> escolha;
        if (escolha < 1 || escolha > nCurso) {
            cout << "Opcao invalida! Tente novamente.\n";
        }
    } while (escolha < 1 || escolha > nCurso);

    // CORREÇÃO: Salvamos o código do curso escolhido dentro da struct Id do aluno
    vetAluno[iAluno].curso.codigo = vetCurso[escolha - 1].codigo;

    cout << "Aluno cadastrado e vinculado ao curso com sucesso!\n\n";
}

// Procedimento para mostrar Alunos e seus cursos
void mostrarAlunos(Aluno vetAluno[], int nAluno, Curso vetCurso[], int nCurso) {
    cout << "\n--- Alunos Matriculados ---\n";
    if (nAluno == 0) {
        cout << "Nenhum aluno cadastrado.\n";
    }
    for (int i = 0; i < nAluno; i++) {
        // Encontrar o nome do curso baseado no código armazenado
        string nomeCurso = "Desconhecido";
        for (int j = 0; j < nCurso; j++) {
            if (vetCurso[j].codigo == vetAluno[i].curso.codigo) {
                nomeCurso = vetCurso[j].nome;
                break;
            }
        }

        cout << "-----------------------------------------------\n";
        cout << "Matricula: " << vetAluno[i].matricula << endl;
        cout << "Nome: " << vetAluno[i].nome << endl;
        cout << "Idade: " << vetAluno[i].idade << endl;
        cout << "Curso Matriculado: " << nomeCurso
             << " (Codigo: " << vetAluno[i].curso.codigo << ")" << endl;
    }
    cout << "-----------------------------------------------\n\n";
}

// Procedimento para buscar alunos por curso usando o código
void buscarAlunosPorCurso(Aluno vetAluno[], int nAluno, Curso vetCurso[], int nCurso) {
    if (nCurso == 0) {
        cout << "Nenhum curso cadastrado.\n\n";
        return;
    }

    mostrarCursos(vetCurso, nCurso);
    int codigoBusca;
    cout << "Digite o codigo do curso que deseja filtrar: ";
    cin >> codigoBusca;

    cout << "\n--- Alunos matriculados no curso (Codigo: " << codigoBusca << ") ---\n";
    bool encontrou = false;
    for (int i = 0; i < nAluno; i++) {
        if (vetAluno[i].curso.codigo == codigoBusca) {
            cout << "-----------------------------------------------\n";
            cout << "Matricula: " << vetAluno[i].matricula << endl;
            cout << "Nome: " << vetAluno[i].nome << endl;
            cout << "Idade: " << vetAluno[i].idade << endl;
            encontrou = true;
        }
    }
    if (!encontrou) {
        cout << "Nenhum aluno matriculado neste curso.\n";
    }
    cout << "-----------------------------------------------\n\n";
}

// Procedimento para o Relatório Geral
void relatorioGeral(Curso vetCurso[], int nCurso, Aluno vetAluno[], int nAluno) {
    cout << "\n================ RELATORIO GERAL ================\n";
    if (nCurso == 0) {
        cout << "Nenhum curso cadastrado.\n";
        cout << "=================================================\n\n";
        return;
    }

    for (int i = 0; i < nCurso; i++) {
        int contMatriculados = 0;
        for (int j = 0; j < nAluno; j++) {
            if (vetAluno[j].curso.codigo == vetCurso[i].codigo) {
                contMatriculados++;
            }
        }
        cout << "Curso: " << vetCurso[i].nome << " (Codigo: " << vetCurso[i].codigo << ")\n";
        cout << " - Vagas Totais: " << vetCurso[i].vagas << "\n";
        cout << " - Alunos Matriculados: " << contMatriculados << "\n";
        cout << "-------------------------------------------------\n";
    }
    cout << "\n";
}

int main(){
    Curso listaCurso[MAX];
    int contCursos = 0;

    Aluno listaAluno[MAX];
    int contAlunos = 0;

    int opcao;

    while(true){
        mostrarMenu();
        cin >> opcao;

        if(opcao == 7)
            break;

        switch(opcao){
            case 1:
                if (contCursos < MAX) {
                    cadastrarCurso(listaCurso, contCursos, contCursos);
                    contCursos++;
                } else {
                    cout << "Limite de cursos atingido!\n\n";
                }
                break;
            case 2:
                if (contAlunos < MAX) {
                    if (contCursos == 0) {
                        cout << "Atencao: Cadastre pelo menos um curso antes de matricular alunos!\n\n";
                    } else {
                        cadastrarAluno(listaAluno, contAlunos, listaCurso, contCursos);
                        contAlunos++;
                    }
                } else {
                    cout << "Limite de alunos atingido!\n\n";
                }
                break;
            case 3:
                mostrarCursos(listaCurso, contCursos);
                break;
            case 4:
                mostrarAlunos(listaAluno, contAlunos, listaCurso, contCursos);
                break;
            case 5:
                buscarAlunosPorCurso(listaAluno, contAlunos, listaCurso, contCursos);
                break;
            case 6:
                relatorioGeral(listaCurso, contCursos, listaAluno, contAlunos);
                break;
            default:
                cout << "Opcao Invalida! Digite novamente.\n\n";
        }
    }

    cout << "\nAcesso encerrado!\n";
    return 0;
}
