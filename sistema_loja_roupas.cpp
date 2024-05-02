#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Definição da classe Marca
class Marca {
    string nome;

public:
    // Construtor que inicializa o nome da marca
    Marca(const string& nome) : nome(nome) {}

    // Método para obter o nome da marca
    string get_nome() const {
        return nome;
    }
};

// Definição da classe abstrata Roupa
class Roupa {
    string tipo;
    vector<Marca*> marcas;
    string tamanho;

public:
    // Construtor que inicializa o tipo e tamanho da roupa
    Roupa(const string& tipo, const string& tamanho) : tipo(tipo), tamanho(tamanho) {}

    // Métodos para definir o tipo e tamanho da roupa
    void set_tipo(const string& novo_tipo) {
        tipo = novo_tipo;
    }

    void set_tamanho(const string& novo_tamanho) {
        tamanho = novo_tamanho;
    }

    // Métodos para obter o tipo, tamanho e marcas da roupa
    string get_tipo() const {
        return tipo;
    }

    vector<Marca*> get_marcas() const {
        return marcas;
    }

    string get_tamanho() const {
        return tamanho;
    }

    // Método para adicionar uma marca à roupa
    void adicionar_marca(Marca* nova_marca) {
        marcas.push_back(nova_marca);
    }

    // Método para remover uma marca da roupa
    void remover_marca(const string& nome_marca) {
        for (auto it = marcas.begin(); it != marcas.end(); ++it) {
            if ((*it)->get_nome() == nome_marca) {
                marcas.erase(it);
                break;
            }
        }
    }

    // Método virtual puro para imprimir informações da roupa (deve ser implementado nas classes derivadas)
    virtual void imprimir_info() const = 0;
};

// Definição da classe RoupaAdulta, derivada de Roupa
class RoupaAdulta : public Roupa {
    string tipo_tecido;

public:
    // Construtor que inicializa o tipo, tamanho e tipo de tecido da roupa adulta
    RoupaAdulta(const string& tipo, const string& tamanho, const string& tipo_tecido) : Roupa(tipo, tamanho), tipo_tecido(tipo_tecido) {}

    // Método para definir o tipo de tecido
    void set_tipo_tecido(const string& novo_tipo_tecido) {
        tipo_tecido = novo_tipo_tecido;
    }

    // Método para obter o tipo de tecido
    string get_tipo_tecido() const {
        return tipo_tecido;
    }

    // Implementação do método virtual para imprimir informações da roupa adulta
    void imprimir_info() const override {
        cout << "Tipo: " << get_tipo() << ", Tamanho: " << get_tamanho() << ", Tipo de Tecido: " << tipo_tecido << endl;
    }
};

// Definição da classe RoupaInfantil, derivada de Roupa
class RoupaInfantil : public Roupa {
    string faixa_etaria;

public:
    // Construtor que inicializa o tipo, tamanho e faixa etária da roupa infantil
    RoupaInfantil(const string& tipo, const string& tamanho, const string& faixa_etaria) : Roupa(tipo, tamanho), faixa_etaria(faixa_etaria) {}

    // Método para definir a faixa etária
    void set_faixa_etaria(const string& nova_faixa_etaria) {
        faixa_etaria = nova_faixa_etaria;
    }

    // Método para obter a faixa etária
    string get_faixa_etaria() const {
        return faixa_etaria;
    }

    // Implementação do método virtual para imprimir informações da roupa infantil
    void imprimir_info() const override {
        cout << "Tipo: " << get_tipo() << ", Tamanho: " << get_tamanho() << ", Faixa Etária: " << faixa_etaria << endl;
    }
};

// Definição da classe Loja
class Loja {
    vector<Roupa*> roupas;

public:
    // Destrutor que libera a memória alocada para cada objeto de roupa
    ~Loja() {
        for (auto& roupa : roupas) {
            delete roupa; // Libera a memória alocada para cada objeto de roupa
            roupa = nullptr; // Define o ponteiro como nulo após a exclusão
        }
    }

    // Operador para adicionar uma roupa à loja
    void operator+=(Roupa* nova_roupa) {
        roupas.push_back(nova_roupa);
    }

    // Operador para remover uma roupa da loja com base no índice
    void operator-=(int indice) {
        if (indice >= 0 && indice < roupas.size()) {
            delete roupas[indice]; // Libera a memória alocada para a roupa no índice especificado
            roupas.erase(roupas.begin() + indice); // Remove a roupa do vetor de roupas
        }
    }

    // Método para listar as roupas disponíveis na loja
    void listar_roupas() const {
        for (const auto& roupa : roupas) {
            if (roupa != nullptr) { // Verifica se o ponteiro é válido
                cout << "Roupa: ";
                roupa->imprimir_info(); // Imprime informações da roupa
            }
        }
    }
};

// Função para exibir o menu
void exibir_menu() {
    cout << "MENU:" << endl;
    cout << "1. Adicionar roupa adulta" << endl;
    cout << "2. Adicionar roupa infantil" << endl;
    cout << "3. Listar roupas da loja" << endl;
    cout << "4. Retirar roupa da loja" << endl; // Nova opção
    cout << "5. Sair" << endl;
}

// Função principal
int main() {
    Loja loja; // Cria um objeto da classe Loja

    int opcao; // Variável para armazenar a opção do menu
    do {
        exibir_menu(); // Exibe o menu
        cout << "Escolha uma opção: ";
        cin >> opcao; // Lê a opção do usuário

        switch (opcao) {
            case 1: { // Opção para adicionar roupa adulta
                string tipo, tamanho, tipo_tecido; // Variáveis para armazenar os dados da roupa adulta
                cout << "Digite o tipo da roupa adulta: ";
                cin >> tipo;
                cout << "Digite o tamanho da roupa adulta: ";
                cin >> tamanho;
                cout << "Digite o tipo de tecido da roupa adulta: ";
                cin >> tipo_tecido;

                RoupaAdulta* nova_roupa = new RoupaAdulta(tipo, tamanho, tipo_tecido); // Cria um objeto da classe RoupaAdulta
                loja += nova_roupa; // Adiciona a roupa à loja

                break;
            }
            case 2: { // Opção para adicionar roupa infantil
                string tipo, tamanho, faixa_etaria; // Variáveis para armazenar os dados da roupa infantil
                cout << "Digite o tipo da roupa infantil: ";
                cin >> tipo;
                cout << "Digite o tamanho da roupa infantil: ";
                cin >> tamanho;
                cout << "Digite a faixa etária da roupa infantil: ";
                cin >> faixa_etaria;

                RoupaInfantil* nova_roupa = new RoupaInfantil(tipo, tamanho, faixa_etaria); // Cria um objeto da classe RoupaInfantil
                loja += nova_roupa; // Adiciona a roupa à loja

                break;
            }
            case 3: // Opção para listar as roupas da loja
                cout << "Roupas disponíveis na loja:" << endl;
                loja.listar_roupas(); // Lista as roupas disponíveis na loja
                break;
            case 4: { // Opção para retirar roupa da loja
                int indice; // Variável para armazenar o índice da roupa que será retirada
                cout << "Digite o índice da roupa que deseja retirar: ";
                cin >> indice;

                loja -= indice; // Remove a roupa da loja com base no índice

                break;
            }
            case 5: // Opção para sair do programa
                cout << "Saindo..." << endl;
                break;
            default: // Opção inválida
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    } while (opcao != 5); // Repete o loop até que o usuário escolha a opção de sair

    return 0;
}
