#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include "Studentas.h"

Studentas generateRandomStudent(int index);

// Function to generate random student data
Studentas generateRandomStudent(int index) {
    std::string vardas = "Vardas" + std::to_string(index);
    std::string pavarde = "Pavarde" + std::to_string(index);

    std::vector<int> namuDarbai;
    int ndCount = 5; // Assuming 5 homework assignments
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> ndDistribution(1, 10);

    for (int i = 0; i < ndCount; ++i) {
        namuDarbai.push_back(ndDistribution(gen));
    }

    int egzaminas = ndDistribution(gen);

    return Studentas(vardas, pavarde, namuDarbai, egzaminas);
}

int main() {
    int choice;
    std::cout << "Pasirinkite:\n";
    std::cout << "1. Ivesti studentu informacija ranka\n";
    std::cout << "2. Nuskaityti studentu informacija is failo\n";
    std::cout << "3. Generuoti atsitiktinius studentu duomenis\n";
    std::cout << "Jusu pasirinkimas: ";
    std::cin >> choice;

    std::vector<Studentas> studentai;

    if (choice == 1) {
        // Manual input of student information
        int studentuSkaicius;
        std::cout << "Iveskite studentu skaiciu: ";
        std::cin >> studentuSkaicius;

        studentai.reserve(studentuSkaicius);

        for (int i = 0; i < studentuSkaicius; ++i) {
            Studentas naujasStudentas("", "", {}, 0);
            naujasStudentas.IvestiDuomenis();
            studentai.push_back(naujasStudentas);
        }
    }
    else if (choice == 2) {
        // Read student information from a file
        std::string inputFile;
        std::cout << "Iveskite duomenu failo pavadinima (pvz., kursiokai.txt): ";
        std::cin >> inputFile;

        std::ifstream input(inputFile);

        if (!input.is_open()) {
            std::cerr << "Nepavyko atidaryti failo " << inputFile << std::endl;
            return 1; // Exit with an error code
        }

        // Read and discard the header line
        std::string header;
        std::getline(input, header);

        // Read data from the file
        while (true) {
            std::string line;
            std::getline(input, line);

            // Check if we reached the end of the file
            if (input.eof()) {
                break;
            }

            // Skip empty lines
            if (line.empty()) {
                continue;
            }

            std::istringstream iss(line);
            std::string pavarde, vardas;
            std::vector<int> namuDarbai;
            int egzaminas;

            // Read data from the line
            iss >> pavarde >> vardas;
            int nd;
            while (iss >> nd) {
                namuDarbai.push_back(nd);
            }
            egzaminas = namuDarbai.back(); // Assuming the last number is the exam grade

            // Create a new Studentas object and add it to the vector
            Studentas naujasStudentas(vardas, pavarde, namuDarbai, egzaminas);
            studentai.push_back(naujasStudentas);
        }

        input.close();
    }
    else if (choice == 3) {
        
        int recordCounts[] = { 1000, 10000, 100000, 1000000, 10000000 };

        for (int i = 0; i < 5; ++i) {
            std::string fileName = "studentai_" + std::to_string(recordCounts[i]) + ".txt";
            std::ofstream output(fileName);

            for (int j = 0; j < recordCounts[i]; ++j) {
                Studentas randomStudent = generateRandomStudent(j + 1);
                output << randomStudent.GetPavarde() << " " << randomStudent.GetVardas();

                for (int nd : randomStudent.GetNamuDarbai()) {
                    output << " " << nd;
                }

                output << " " << randomStudent.GetEgzaminas() << std::endl;

                studentai.push_back(randomStudent); // Add random student to the vector
            }

            output.close();
            std::cout << "Atsitiktiniai duomenys sugeneruoti ir issaugoti faile '" << fileName << "'" << std::endl << std::flush;
        }
    }
    else {
        std::cerr << "Pasirinkimas neteisingas\n";
        return 1; // Exit with an error code
    }

    // Pasirinkimas tarp vidurkio ir medianos
    std::string baloSkaiciavimoBudas;
    std::cout << "Pasirinkite balo skaiciavimo buda (Vid/Med): ";
    std::cin >> baloSkaiciavimoBudas;

    // Isvesti rezultatus lenteleje
    std::cout << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(25) << "Galutinis (" << baloSkaiciavimoBudas << ")" << std::endl;
    std::cout << std::setfill('-') << std::setw(60) << "-" << std::setfill(' ') << std::endl;

    for (const auto& studentas : studentai) {
        studentas.IsvestiDuomenis(baloSkaiciavimoBudas);
    }

    // Sort the generated random students
    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.SkaiciuotiGalutiniBalaVidurkiu() < b.SkaiciuotiGalutiniBalaVidurkiu();
        });

    // Separate students into two categories
    std::vector<Studentas> vargsiukai;
    std::vector<Studentas> kietiakiai;

    for (const auto& studentas : studentai) {
        if (studentas.SkaiciuotiGalutiniBalaVidurkiu() < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }

    // Write vargsiukai to a file
    std::ofstream vargsiukaiFile("vargsiukai.txt");
    for (const auto& studentas : vargsiukai) {
        vargsiukaiFile << studentas.GetPavarde() << " " << studentas.GetVardas() << " "
            << studentas.SkaiciuotiGalutiniBalaVidurkiu() << std::endl;
    }
    vargsiukaiFile.close();

    // Write kietiakiai to a file
    std::ofstream kietiakiaiFile("kietiakiai.txt");
    for (const auto& studentas : kietiakiai) {
        kietiakiaiFile << studentas.GetPavarde() << " " << studentas.GetVardas() << " "
            << studentas.SkaiciuotiGalutiniBalaVidurkiu() << std::endl;
    }
    kietiakiaiFile.close();

    std::cout << "Studentai surusiuoti ir issaugoti i atskirus failus.\n";

    return 0;
}
