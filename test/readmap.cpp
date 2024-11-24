#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

int main() {
    // Ouvrir le fichier JSON
    std::ifstream input_file("map.json");
    if (!input_file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier example.json" << std::endl;
        return 1;
    }

    // Lire le contenu du fichier JSON
    nlohmann::json j;
    input_file >> j;

    // Fermer le fichier
    input_file.close();

    // Accéder aux données JSON
    std::cout << "name: " << j["map"]["name"] << std::endl;
    std::cout << "description: " << j["map"]["description"] << std::endl;
    std::cout << "dimension: " << j["map"]["dimensions"] << std::endl;
    std::cout << "list: ";
    for (const auto& elem : j["map"]["terrain"]) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}