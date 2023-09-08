#include <iostream>
#include <Mascota.hpp>
int main(int argc, char const *argv[])
{
    std::cout << "Juego de Mascota" << std::endl;
    Mascota m1("El Niño")
    m1.jugar();
    m1.jugar();
    m1.jugar();

    std::cout << m1.Decirnombre() << "Tiene" << m1.Decirnombre() << "de hambre" << std::endl;

    m1.comer(5);
    return 0;
}