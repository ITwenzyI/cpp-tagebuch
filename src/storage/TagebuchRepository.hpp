#ifndef STORAGE_TAGEBUCHREPOSITORY_HPP
#define STORAGE_TAGEBUCHREPOSITORY_HPP

#include <filesystem>
#include <string>
#include <vector>

class TagebuchRepository {
  public:
    void erstelleDatenOrdner() const;
    bool schreibeNeuenEintrag(const std::string& datum, const std::vector<std::string>& zeilen) const;
    bool leseEintrag(const std::string& datum, std::vector<std::string>& zeilen) const;
    bool ueberschreibeEintrag(const std::string& datum, const std::vector<std::string>& zeilen) const;
    bool haengeAn(const std::string& datum, const std::string& text) const;
    bool existiertEintrag(const std::string& datum) const;
    bool entferneEintrag(const std::string& datum) const;
    std::vector<std::filesystem::directory_entry> listeDateienImDataOrdner() const;
    std::string eintragPfad(const std::string& datum) const;
};

#endif
