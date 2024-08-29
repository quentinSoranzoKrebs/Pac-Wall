/*
 * Copyright (C) 2024 Quentin Soranzo Krebs
 *
 * This file is part of Pac-Wall.
 *
 * [Nom de ton projet] is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Pac-Wall is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Pac-Wall. If not, see <http://www.gnu.org/licenses/>.
 */
 
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
