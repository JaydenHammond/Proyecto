#include <Ventana.hpp>
#include <Dibujo.hpp>
#include <Actualizable.hpp>
#include <Controlador.hpp>
#include <Guy.hpp>
#include <curses.h>
#include <unistd.h>
#include <list>
using namespace std;

int main(int argc, char const *argv[])
{
    Ventana v;
    Guy *Slayer = new Guy(2, 1, "SLAYER");
    Controlador *control = new Controlador();

    Dibujo *d1 = new Dibujo(2, 1, "doom guy");
    Dibujo *d2 = new Dibujo(20, 1, "doom run");
    Dibujo *d3 = new Dibujo(200, 1, "doom shot");

    list<Dibujo *> dibujos;
    dibujos.push_back(d1);
    dibujos.push_back(d2);
    dibujos.push_back(d3);
    dibujos.push_back(Slayer);

    list<Actualizable *> actualizables;
    actualizables.push_back(control);
    actualizables.push_back(Slayer);

    bool ejecucion = true;
    while (ejecucion)
    {
        v.Actualizar(actualizables);
        v.Dibujar(dibujos);
    }

    return 0;
}