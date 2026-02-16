#ifndef STORAGE_TAGEBUCHREPOSITORY_HPP
#define STORAGE_TAGEBUCHREPOSITORY_HPP

#include <filesystem>
#include <string>
#include <vector>

class TagebuchRepository {
  public:
    // Stellt sicher, dass der Ablageordner existiert.
    void erstelleDatenOrdner() const;
    [[nodiscard]] bool schreibeNeuenEintrag(
        const std::string& datum, const std::vector<std::string>& zeilen) const;
    [[nodiscard]] bool leseEintrag(
        const std::string& datum, std::vector<std::string>& zeilen) const;
    [[nodiscard]] bool leseDatei(
        const std::filesystem::path& dateiPfad, std::vector<std::string>& zeilen) const;
    [[nodiscard]] bool ueberschreibeEintrag(
        const std::string& datum, const std::vector<std::string>& zeilen) const;
    [[nodiscard]] bool haengeAn(const std::string& datum, const std::string& text) const;
    [[nodiscard]] bool existiertEintrag(const std::string& datum) const;
    [[nodiscard]] bool entferneEintrag(const std::string& datum) const;
    [[nodiscard]] std::vector<std::filesystem::directory_entry> listeDateienImDataOrdner() const;
    [[nodiscard]] std::string eintragPfad(const std::string& datum) const;

  private:
    // Zentraler Einstieg für den Datenordnerpfad.
    static const std::filesystem::path& datenOrdnerPfad();
};

#endif
