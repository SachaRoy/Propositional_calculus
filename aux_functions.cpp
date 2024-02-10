#include "calc_prop.hpp"


// #################################### Fonctions auxiliaires ####################################

int quick_exp(int n, int k) {
    // Renvoie "n" exposant "k"
    if(k == 0) return 1;
    else if(k == 1) return n;
    else if(k%2 == 1) return quick_exp(n, k-1)*n;
    else return quick_exp(n, k/2)*quick_exp(n, k/2);
}

bool is_in(std::vector<std::string> tab, std::string e) {
    // Renvoie si la chaîne "e" est dans le tableau "tab"
    bool rep{false};
    for(std::string v: tab) {
        if(v == e) {
            rep = true;
            break;
        }
    }
    return rep;
}

bool char_to_bool(char c) {
    // "c" est soit '1', soit '0'
    // Converti "c" en booléen
    if (c == '1') return true;
    else return false;
}

char bool_to_char(bool b) {
    // Converti le booléen "b" en char
    if (b) return '1';
    else return '0';
}

std::string cut_string(std::string str, int n1, int n2) {
    // Tronque le chaîne de caractères "str" et renvoie la sous-chaine [n1:n2]
    std::string rep{};
    for(int i{n1}; i < n2-1; i++) {
        rep += str[i];
    }
    return rep;
}

int fin_formule(std::string f, int n) {
    // Renvoie l'indice de la fin de la formule "f"
    int len = std::size(f);
    int c{1};
    while(c != 0) {
        n++;
        if (n >= len) {
            return -1;
            break;
        }
        else {
            if (f[n] == '(') c++;
        else if (f[n] == ')') c--;
        }
    }
    return n+1;
}