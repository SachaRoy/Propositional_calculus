#include <iostream>
#include <string>
#include <vector>
#include <array>


// #################################### Fonctions auxiliaires ####################################

int quick_exp(int n, int k); // Renvoie "n" exposant "k"
bool is_in(std::vector<std::string> tab, std::string e); // Renvoie si la chaîne "e" est dans le tableau "tab"
bool char_to_bool(char c); // Converti "c" en booléen
char bool_to_char(bool b); // Converti le booléen "b" en char
std::string cut_string(std::string str, int n1, int n2); // Tronque le chaîne de caractères "str" et renvoie la sous-chaine [n1:n2]
int fin_formule(std::string f, int n); // Renvoie l'indice de la fin de la formule "f"


// ####################################  Fonctions principales  ####################################

void aff_table(std::vector<std::vector<std::string>> val); // Affiche la table de la valuation "val"
std::vector<std::vector<std::string>> valuations(std::string f); // Calcule une valuation de "f"

bool check_formule(std::string f); // Renvoie si la formule "f" est syntaxiquement correcte
