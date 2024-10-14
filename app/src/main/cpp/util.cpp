#include "utils.h"
#include <algorithm>
#include <cmath>

// Implémentation de la fonction Add
int Add(int a, int b) {
    return a + b;
}

// Convertir une chaîne en majuscules
std::string ToUpperCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Calculer la distance entre deux points
float GetDistance(float x1, float y1, float x2, float y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}
