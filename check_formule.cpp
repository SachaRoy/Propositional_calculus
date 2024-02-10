#include "calc_prop.hpp"


// ####################################  Fonctions principales  ####################################

std::array<int, 2> operateur_check(std::string f) {
    // Renvoie l'opérateur de la formule "f" et son emplacement, les opérateurs des sous-formules ne sont pas pris en compte
    std::array<int, 2> rep{};
    int c{0}, len = std::size(f);
    for (int i{0}; i < len-1; i++) {
        if (f[i] == '(') {
            c++;
        }
        else if (f[i] == ')') {
            c--;
        }
        if (c == 0) {
            rep[0] = f[i];
            rep[1] = i;
        }
    }
    return rep;
}

bool check_formule(std::string f) {
    // Renvoie si la formule "f" est syntaxiquement correcte

    // Vérifie les cas de base
    int len = std::size(f);
    if (len < 2) {
        return false;
    }
    else if (len == 2) {
        if (f[0] == 'p' && (f[1] > 48 && f[1] < 58)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (len < 5) {
        return false;
    }

    // Vérifie le parenthèsage via la fonction "fin_formule" et divise la formule s'il est correct
    else {
        std::array<int, 2> op = operateur_check(f);
        switch (char(op[0])) {
            case '-': {
                int fin = fin_formule(f, 1);
                if (fin == -1) {
                    return false;
                }
                else {
                    return check_formule(cut_string(f, 2, fin));
                }
            }
            case 'v': {
                int fin1{fin_formule(f, 0)}, fin2{fin_formule(f, op[1]+1)};
                if (fin1 == -1 || fin2 == -1) {
                    return false;
                }
                else {
                    return check_formule(cut_string(f, 1, fin1)) && check_formule(cut_string(f, op[1]+2, fin2));
                }
            }
            case 'a': {
                int fin1{fin_formule(f, 0)}, fin2{fin_formule(f, op[1]+1)};
                if (fin1 == -1 || fin2 == -1) {
                    return false;
                }
                else {
                    return check_formule(cut_string(f, 1, fin1)) && check_formule(cut_string(f, op[1]+2, fin2));
                }
            }
        }
        return false;
    }
}
