#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream fichier("../data/data.txt"); // Ouvrir le fichier en lecture
    if (!fichier.is_open()) {
        std::cerr << "Erreur d'ouverture du fichier." << std::endl;
        return 1;
    }

    std::string ligne;
    std::getline(fichier, ligne); // Lire la première ligne du fichier (ou la ligne contenant le tableau)
    fichier.close();

    // Extraire la sous-chaîne entre les accolades
    std::size_t debut = ligne.find('{');
    std::size_t fin = ligne.find('}');
    if (debut == std::string::npos || fin == std::string::npos) {
        std::cerr << "Format de tableau non trouvé." << std::endl;
        return 1;
    }

    std::string contenu = ligne.substr(debut + 1, fin - debut - 1);

    // Extraire les entiers en les séparant par des virgules
    std::vector<int> tab;
    std::stringstream ss(contenu);
    std::string valeur;

    while (std::getline(ss, valeur, ',')) {
        tab.push_back(std::stoi(valeur));
    }

    // Afficher le tableau extrait
    std::cout << "Tableau extrait : ";
    for (int val : tab) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
