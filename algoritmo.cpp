// Algoritmo A*

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm> // Para a função sort
#include <stack>

using namespace std;

class no {
private:
    int a, b, f, g;

public:
    vector<no> pai;
    no() {
        a = 0;
        b = 0;
        f = 0;
        g = 0;
    }

    void set_filhos(no temp_no){
        pai.push_back(temp_no);
    }

    no ret_filho(int j){
        return pai.at(j);
    }

    void set_pos(int x, int y) {
        a = x;
        b = y;
    }

    void set_f(int h) {
        f = g + h;
    }

    void set_g(int custo, int g_ant) {
        g = g_ant + custo;
    }

    int ret_f() const {
        return f;
    }

    int ret_a() const {
        return a;
    }

    int ret_b() const {
        return b;
    }

    int ret_g() const {
        return g;
    }
};

int main() {
    vector<no> aberto, fechado;
    int x, y, h, g_ant, pos;
    const int custo = 1;
    no temp_no, no_final, no_comp;
    char fim = 'n';
    bool existencia = false;
    char result;
    stack<no> volta;

    int labirinto[13][13] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,5,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,1,0,0,0,0,0,1,0,1,0,0},
        {0,0,1,1,1,1,1,1,1,0,1,0,0},
        {0,0,0,0,1,0,0,0,1,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,0,0,1,0,0,0,1,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 13; j++) {
            if(labirinto[i][j] == 5) {
                x = i;
                y = j;
                no_final.set_pos(x, y);
            }
        }
    }

    do {
        cout << "Digite a posição x no labirinto: ";
        cin >> x;
        cout << "Digite a posição y no labirinto: ";
        cin >> y;

        if(x < 0 || x >= 13 || y < 0 || y >= 13 || labirinto[x][y] == 0 || labirinto[x][y] == 5) {
            cout << "Posição inválida\n";
            result = 'n';
        } else {
            temp_no.set_pos(x, y);
            result = 's';
        }

    } while(result == 'n');

    aberto.push_back(temp_no);

    while(fim == 'n') {
        if(!aberto.empty()) {
            fechado.push_back(aberto.back());
            aberto.pop_back();
        }

        x = fechado.back().ret_a();
        y = fechado.back().ret_b();

        // Verificações para movimentos possíveis

        // Movimento para esquerda
        if(y > 0 && (labirinto[x][y - 1] == 1 || labirinto[x][y - 1] == 5)) {
            existencia = false;
            for(int i = 0; i < fechado.size(); i++) {
                if(fechado[i].ret_a() == x && fechado[i].ret_b() == y - 1) {
                    existencia = true;
                    break;
                }
            }
            if(!existencia) {
                temp_no.set_pos(x, y - 1);
                h = abs(no_final.ret_a() - temp_no.ret_a()) + abs(no_final.ret_b() - temp_no.ret_b());
                g_ant = fechado.back().ret_g();
                temp_no.set_g(custo, g_ant);
                temp_no.set_f(h);
                aberto.push_back(temp_no);
                fechado.back().set_filhos(temp_no);
            }
        }

        // Movimento para direita
        if(y < 12 && (labirinto[x][y + 1] == 1 || labirinto[x][y + 1] == 5)) {
            existencia = false;
            for(int i = 0; i < fechado.size(); i++) {
                if(fechado[i].ret_a() == x && fechado[i].ret_b() == y + 1) {
                    existencia = true;
                    break;
                }
            }
            if(!existencia) {
                temp_no.set_pos(x, y + 1);
                h = abs(no_final.ret_a() - temp_no.ret_a()) + abs(no_final.ret_b() - temp_no.ret_b());
                g_ant = fechado.back().ret_g();
                temp_no.set_g(custo, g_ant);
                temp_no.set_f(h);
                aberto.push_back(temp_no);
                fechado.back().set_filhos(temp_no);
            }
        }

        // Movimento para cima
        if(x > 0 && (labirinto[x - 1][y] == 1 || labirinto[x - 1][y] == 5)) {
            existencia = false;
            for(int i = 0; i < fechado.size(); i++) {
                if(fechado[i].ret_a() == x - 1 && fechado[i].ret_b() == y) {
                    existencia = true;
                    break;
                }
            }
            if(!existencia) {
                temp_no.set_pos(x - 1, y);
                h = abs(no_final.ret_a() - temp_no.ret_a()) + abs(no_final.ret_b() - temp_no.ret_b());
                g_ant = fechado.back().ret_g();
                temp_no.set_g(custo, g_ant);
                temp_no.set_f(h);
                aberto.push_back(temp_no);
                fechado.back().set_filhos(temp_no);
            }
        }

        // Movimento para baixo
        if(x < 12 && (labirinto[x + 1][y] == 1 || labirinto[x + 1][y] == 5)) {
            existencia = false;
            for(int i = 0; i < fechado.size(); i++) {
                if(fechado[i].ret_a() == x + 1 && fechado[i].ret_b() == y) {
                    existencia = true;
                    break;
                }
            }
            if(!existencia) {
                temp_no.set_pos(x + 1, y);
                h = abs(no_final.ret_a() - temp_no.ret_a()) + abs(no_final.ret_b() - temp_no.ret_b());
                g_ant = fechado.back().ret_g();
                temp_no.set_g(custo, g_ant);
                temp_no.set_f(h);
                aberto.push_back(temp_no);
                fechado.back().set_filhos(temp_no);
            }
        }

        // Verifica se atingiu o objetivo
        for(int i = 0; i < aberto.size(); i++) {
            if(aberto[i].ret_a() == no_final.ret_a() && aberto[i].ret_b() == no_final.ret_b()) {
                fim = 's';
                fechado.push_back(aberto[i]);
                break;
            }
        }

        // Ordena vetor aberto por menor f
        sort(aberto.begin(), aberto.end(), [](const no& n1, const no& n2) {
            return n1.ret_f() < n2.ret_f();
        });
    }

    // Imprime caminho encontrado
    if(fim == 's') {
        
        // ajuste apartir daqui
        
        volta.push(no_final);
        temp_no = no_final;

        cout << "Caminho encontrado com menor custo: "; 
        while (!volta.empty()) {
            no current_no = volta.top();
            volta.pop();
            cout << " (" << current_no.ret_a() << ";" << current_no.ret_b() << ") ";

            for (int j = 0; j < fechado.size(); j++) {
                if (!fechado[j].pai.empty()) {
                    for (int k = 0; k < fechado[j].pai.size(); k++) {
                        if (fechado[j].ret_filho(k).ret_a() == current_no.ret_a() && fechado[j].ret_filho(k).ret_b() == current_no.ret_b()) {
                            volta.push(fechado[j]);
                            break;
                        }
                    }
                }
            }
        }
        cout << endl;
    } else {
        cout << "Não foi possível encontrar um caminho válido.\n";
    }

    return 0;
}
