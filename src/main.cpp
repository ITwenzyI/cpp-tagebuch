#include "app/Application.hpp"

int main() {
    // Einstiegspunkt: delegiert den gesamten Ablauf an die Application.
    Application app;
    return app.starte();
}
