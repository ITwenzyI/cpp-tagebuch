# 📘 C++ Tagebuch – Persönliches C++-Journal

Ein persönliches Tagebuch-Tool in C++, das tägliche Einträge über Training, Essen, Schlaf, Stimmung, Produktivität, Freizeit und Finanzen erfasst, speichert, bearbeitet und durchsucht.  
Das Projekt dient sowohl als Lernprojekt für Datei-I/O, Zeitfunktionen, Strings und std::filesystem als auch als praktisches Tool für mich selbst.

---

## ✨ Features

- 📅 Neue Einträge erstellen (Datum wird automatisch erkannt)
- ✏️ Bestehende Einträge gezielt bearbeiten (zeilenbasiert)
- 📂 Einträge als `.txt` in einem `data/`-Ordner speichern
- 👀 Einträge anzeigen lassen mit Rückfrage zur Bearbeitung
- 🗑 Einträge gezielt löschen
- 🔎 Einträge nach #Kategorien (z. B. `#Training`, `#Geld`) in einem Zeitbereich durchsuchen

---

## 🧠 Was man dabei lernt

- Umgang mit `std::filesystem` zum Dateimanagement
- Lesen & Schreiben von Dateien mit `ifstream`/`ofstream`
- Umgang mit Datum/Zeit via `<ctime>` und `<iomanip>`
- Eingabe mit `std::getline`, `std::cin`, `std::ignore`
- saubere Trennung von Funktionen (OOP mit `EntryManager`)

---

## 📂 Beispiel-Datei (data/04.05.2025.txt)

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

---

## 📌 Hinweise
Das Projekt speichert alle Daten lokal im data/-Ordner.

Es ist bewusst textbasiert, um Einblick in einfache Benutzerführung und Dateisysteme zu geben.

Ideal für Einsteiger*innen, die C++ praxisnah üben möchten.

## 🧑‍💻 Author
**Kilian – Student Medizinische Informatik | OTH Regensburg**
