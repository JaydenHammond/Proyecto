#pragma once
#include <Actualizable.hpp>
#include <curses.h>

class Controlador : public Actualizable
{
private:
    /* data */
public:
    Controlador(/* args */) {}
    ~Controlador() {}
    void Actualizar()
    {
        if (getch() == 'q')
        {
            ejecucion = false;
        }
        if (getch() == 'd')
        {
            d1.AvanzarX(1);
        }
        if (getch() == 'a')
        {
            d1.RetrocederX(1);
        }
        if (getch() == 'w')
        {
            d1.AvanzarY(1);
        }
        if (getch() == 's')
        {
            d1.RetrocederY(1);
        }
        if (getch() == 'f')
        {
            d1.disparar(1);
        }
        if (getch() == KEY_RIGHT)
        {
            d2.AvanzarX(1);
        }
        if (getch() == KEY_LEFT)
        {
            d2.RetrocederX(1);
        }
        if (getch() == KEY_UP)
        {
            d2.AvanzarX(1);
        }
        if (getch() == KEY_DOWN)
        {
            d2.RetrocederX(1);
        }
    }
};