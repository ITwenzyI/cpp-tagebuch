#ifndef UI_CONSOLERENDERER_HPP
#define UI_CONSOLERENDERER_HPP

class ConsoleRenderer {
  public:
    // Gibt das Hauptmenü aus.
    void zeigeHauptmenue() const;
    // Gibt das Untermenü für Tagebuchaktionen aus.
    void zeigeAlltagMenue() const;
    // Einheitliche Abschlussmeldung des Programms.
    void zeigeDanke() const;
};

#endif
