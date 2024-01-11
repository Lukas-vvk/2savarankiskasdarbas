#include "Studentas.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>


// Konstruktorius
Studentas::Studentas(const std::string& v, const std::string& p, const std::vector<int>& nd, int e)
    : vardas(v), pavarde(p), namuDarbai(nd), egzaminas(e) {}

// Priskyrimo-kopijavimo operatorius
Studentas& Studentas::operator=(const Studentas& kitas) {
    if (this != &kitas) {
        vardas = kitas.vardas;
        pavarde = kitas.pavarde;
        namuDarbai = kitas.namuDarbai;
        egzaminas = kitas.egzaminas;
    }
    return *this;
}



// Kopijavimo konstruktorius
Studentas::Studentas(const Studentas& kitas)
    : vardas(kitas.vardas), pavarde(kitas.pavarde), namuDarbai(kitas.namuDarbai), egzaminas(kitas.egzaminas) {}

// Destruktorius
Studentas::~Studentas() {}



// Duomenu ivestimo metodas
void Studentas::IvestiDuomenis() {
    std::cout << "Iveskite studento varda: ";
    std::cin >> vardas;

    std::cout << "Iveskite studento pavarde: ";
    std::cin >> pavarde;

    int ndKiekis;
    std::cout << "Iveskite namu darbu kieki: ";
    std::cin >> ndKiekis;

    namuDarbai.resize(ndKiekis);
    for (int i = 0; i < ndKiekis; ++i) {
        std::cout << "Iveskite " << i + 1 << "-ojo namu darbo rezultata: ";
        std::cin >> namuDarbai[i];
    }

    std::cout << "Iveskite egzamino rezultata: ";
    std::cin >> egzaminas;
}


// Duomenu isvedimo metodas
void Studentas::IsvestiDuomenis(const std::string& baloSkaiciavimoBudas) const {
    std::cout << std::setw(15) << pavarde << std::setw(15) << vardas;

    if (baloSkaiciavimoBudas == "Vid") {
        std::cout << std::setw(25) << SkaiciuotiGalutiniBalaVidurkiu();
    }
    else if (baloSkaiciavimoBudas == "Med") {
        std::cout << std::setw(25) << SkaiciuotiGalutiniBalaMediana();
    }
    else {
        std::cout << "Pasirinkimas neteisingas";
    }

    std::cout << std::endl;
}

// Galutinio pazymio skaiciavimo metodas



double Studentas::SkaiciuotiGalutiniBalaVidurkiu() const {
    double vidurkis = 0.0;
    for (int nd : namuDarbai) {
        vidurkis += nd;
    }
    vidurkis /= namuDarbai.size();
    return 0.4 * vidurkis + 0.6 * egzaminas;
}

double Studentas::SkaiciuotiGalutiniBalaMediana() const {
    std::vector<int> ndKopija = namuDarbai;
    std::sort(ndKopija.begin(), ndKopija.end());

    int dydis = ndKopija.size();

    if (dydis % 2 == 0) {
        return 0.4 * ((ndKopija[dydis / 2 - 1] + ndKopija[dydis / 2]) / 2.0) + 0.6 * egzaminas;
    }
    else {
        return 0.4 * ndKopija[dydis / 2] + 0.6 * egzaminas;
    }
}

