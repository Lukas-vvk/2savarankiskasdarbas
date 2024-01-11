#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> namuDarbai;
    int egzaminas;

public:
    Studentas(const std::string& v, const std::string& p, const std::vector<int>& nd, int e);
    Studentas& operator=(const Studentas& kitas);
    Studentas(const Studentas& kitas);
    ~Studentas();
    std::string GetVardas() const { return vardas; }
    std::string GetPavarde() const { return pavarde; }
    std::vector<int> GetNamuDarbai() const { return namuDarbai; }
    int GetEgzaminas() const { return egzaminas; }

    void IvestiDuomenis();
    void IsvestiDuomenis(const std::string& baloSkaiciavimoBudas) const;
    double SkaiciuotiGalutiniBalaVidurkiu() const;
    double SkaiciuotiGalutiniBalaMediana() const;
};

#endif // STUDENTAS_H
