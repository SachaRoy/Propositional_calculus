#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <bitset>


// Fonctions auxiliaires
int quick_exp(int n, int k) {
    // Renvoie n exposant k
    if(k == 0) return 1;
    else if(k == 1) return n;
    else if(k%2 == 1) return quick_exp(n, k-1)*n;
    else return quick_exp(n, k/2)*quick_exp(n, k/2);
}

bool is_in(std::vector<std::string> tab, std::string e) {
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
    if (c == '1') return true;
    else return false;
}

char bool_to_char(bool b) {
    if (b) return '1';
    else return '0';
}

// Affichage de tableaux
void print_tab(std::vector<std::string> tab) {
    int len = std::size(tab);
    std::cout << "[";
    for(int i{0}; i < len; i++) {
        std::cout << " " << tab[i];
        if(i != len-1) std::cout << ',';
    }
    std::cout << "]" << std::endl;
}

void print_tab(std::vector<int> tab) {
    int len = std::size(tab);
    std::cout << "[";
    for(int i{0}; i < len; i++) {
        std::cout << " " << tab[i];
        if(i != len-1) std::cout << ',';
    }
    std::cout << "]" << std::endl;
}

void print_tab(std::vector<bool> tab) {
    int len = std::size(tab);
    std::cout << "[";
    for(int i{0}; i < len; i++) {
        std::cout << " " << tab[i];
        if(i != len-1) std::cout << ',';
    }
    std::cout << "]" << std::endl;
}

void print_tab(std::array<int, 2> tab) {
    std::cout << "[" << tab[0] << ", " << tab[1] << "]" << std::endl;
}


// Troncaténation de chaines de caractères
std::string cut_string(std::string str, int n1, int n2) {
    std::string rep{};
    for(int i{n1}; i < n2-1; i++) {
        rep += str[i];
    }
    return rep;
}

int fin_formule(std::string f, int n) {
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



// #############################  Fonctions principales  ####################################
void affiche_table(std::vector<std::vector<std::string>> val) {
    int len = std::size(val[0])-1;

    // Affichage de l'entête
    for(int i{0}; i < len; i++) std::cout << "___";
    std::cout << "_____\n";
    for(int i{1}; i <= len; i++) std::cout << "|v" << i;
    std::cout << "| f |\n";
    for(int i{0}; i < len; i++) std::cout << "|--";
    std::cout << "|---|\n";

    // Affichage du reste de la table
    for(int i{0}; i < quick_exp(2, len); i++) {
        for(int j{0}; j < len; j++) {
            std::cout << "| " << val[i][j];
        }
        std::cout << "| " << val[i][len] << " |\n";
    }
    for(int i{0}; i < len; i++) std::cout << "|__";
    std::cout << "|___|" << std::endl;
}



void sous_f_rec(std::string f, std::vector<std::string> &rep) {
    int len = std::size(f);
    for(int i{0}; i < len; i++) {
        if (f[i] == '(') {
            std::string sous_f{cut_string(f, i+1, fin_formule(f, i))};
            if(not is_in(rep, sous_f)) {
                rep.push_back(sous_f);
            }
            sous_f_rec(sous_f, rep);
            sous_f_rec(cut_string(f, fin_formule(f, i), std::size(f)+1), rep);
            break;
        }
    }
}

std::vector<std::string> sous_formules(std::string f) {
    // Revoie l'ensemble des sous-formules d'une formule f
    std::vector<std::string> rep{f};
    sous_f_rec(f, rep);
    return rep;
}

std::vector<std::string> variables_of(std::string f) {
    // Renvoie les variables propositionnelles contenues dans f
    std::vector<std::string> rep{};
    for(std::string str: sous_formules(f)) {
        if (std::size(str) == 2) {
            rep.push_back(str);
        }
    }
    return rep;
}

std::array<int, 2> operateur(std::string f) {
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

bool calc_val(std::string f, std::vector<bool> &val) {
    int len = std::size(f);
    if (len == 2) {
        int i{f[1]-49};
        bool rep{val[i]};
        return rep;
    }
    else {
        std::array<int, 2> op = operateur(f);
        switch (char(op[0])) {
            case '-': {
                return not calc_val(cut_string(f, 2, fin_formule(f, 1)), val);             
            }
            case 'v': {
                return calc_val(cut_string(f, 1, op[1]), val) || calc_val(cut_string(f, op[1]+2, fin_formule(f, op[1]+1)), val);
            }
            case 'a': {
                return calc_val(cut_string(f, 1, op[1]), val) && calc_val(cut_string(f, op[1]+2, fin_formule(f, op[1]+1)), val);
            }
        }
        return false;
    }
}


std::vector<std::vector<std::string>> init_tab_val(int len) {
    // Initialise une matrice de taille (2^len)*(len+1)
    std::vector<std::vector<std::string>> rep{};

    for(int i{0}; i < quick_exp(2, len); i++) {
        std::vector<std::string> ligne{};
        for(int i{0}; i <= len; i++) {
            ligne.push_back("");
        }
        rep.push_back(ligne);
    }
    return rep;
}

std::vector<std::vector<std::string>> valuations(std::string f) {
    const int len = std::size(variables_of(f));
    std::vector<std::vector<std::string>> rep{init_tab_val(len)};
    std::vector<bool> val{};

    for(int i{0}; i < quick_exp(2, len); i++) {
        std::string binaire{std::bitset<16>(i).to_string()};

        for(int j{0}; j < len; j++) {
            rep[i][len-j-1] = binaire[15-j];            
            val.insert(val.begin(), char_to_bool(binaire[15-j]));
        }
        rep[i][len] = bool_to_char(calc_val(f, val));
        val.clear();
    }
    return rep;
}


bool check_formule(std::string f) {
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

    // Vérifie le parenthèsage via la fonction 'fin_formule' et divise la formule s'il est correct
    else {
        std::array<int, 2> op = operateur(f);
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






int main() {
    
    return 0;
}