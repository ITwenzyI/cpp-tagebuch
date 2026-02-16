# Digitales Tagebuch (C++)

Ein schlankes, konsolenbasiertes Tagebuch in modernem C++.  
Das Programm erstellt, speichert, bearbeitet, löscht und durchsucht tägliche Einträge in lokalen Textdateien.

## Überblick

- Fokus auf einfache Bedienung in der Konsole
- Lokale Datenspeicherung im Ordner `data/`
- Keine externen Laufzeitabhängigkeiten
- Modulare Architektur (Domain, Storage, Service, UI, App)

## Funktionen

- Neue Einträge erstellen (Datum automatisch im Format `TT.MM.JJJJ`)
- Einträge anzeigen
- Einträge bearbeiten (zeilenbasiert)
- Einträge löschen
- Suche nach Kategorien/Hashtags in einem Datumsbereich (z. B. `Training`, `Geld`)

## Projektstruktur

```text
src/
  app/       # Application/Composition Root
  domain/    # Domänenmodell (Entry)
  service/   # Geschäftsabläufe (EntryService)
  storage/   # Dateizugriff (TagebuchRepository)
  ui/        # Konsolen-Ein/-Ausgabe und Menüsteuerung
  util/      # Hilfsfunktionen (z. B. Datum)
  main.cpp   # Startpunkt
```

## Datenformat

Jeder Eintrag wird als Datei `data/TT.MM.JJJJ.txt` gespeichert.  
Der Inhalt bleibt bewusst einfach und textbasiert, damit er direkt lesbar ist und leicht weiterverarbeitet werden kann.

Beispiel:

```text
       Erstellt von Kilian am 04.05.2025. :)
#Training: 30 Min Laufen
#Essen: gesund, 3 Mahlzeiten
#Schlaf: 7h
#Stimmung: ausgeglichen
#Produktivität: gut
#Freizeit: 2h Netflix
#Geld: 5€ ausgegeben
------------------------------
Zuletzt bearbeitet am: 05.05.2025 (Bearbeitet: #Stimmung)
```

## Technische Hinweise

- Zeichenkodierung: UTF-8 (über `.editorconfig` und Compiler-Flags abgesichert)
- Persistenz: `std::filesystem` + `ifstream`/`ofstream`
- Zielsetzung: einfaches, nachvollziehbares Tagebuch mit stabiler Dateistruktur

## Autor

Entwickelt von **Kilian**.
