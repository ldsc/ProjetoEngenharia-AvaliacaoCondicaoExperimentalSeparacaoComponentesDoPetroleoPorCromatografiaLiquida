#include "CFisher.hpp"
#include <math.h>
#include <iostream>

const double PI = 3.1416;
using namespace std;

    /// Costrutor sobrecarregado.
CFisher::CFisher(int _d1, int _d2)
{
    d1 = _d1;
    d2 = _d2;
}
    /// Metodo get.
double CFisher::Probabilidade(double x)
{
    double argumento = (d1 * x / (d1 * x + d2));
    return 1 - Beta_regularizada(argumento);
}
    /// Metodo calcular Beta
double CFisher::Beta()
{
    int n = 1000;
    double largura = 1.0 / n;
    double integral = 0.0;
    double centro = largura / 2.0;
    for (int i = 1; i < n; i++)
    {
        integral += largura * F(centro);
        centro += largura;
    }
    return integral;
}
      /// Metodo calcular Beta_regulizada.
double CFisher::Beta_regularizada(double x)
{
    int n = 1000;
    double largura = x / n;
    double integral = 0.0;
    double centro = largura / 2.0;
    for (int i = 1; i < n; i++)
    {
        integral += largura * F(centro);
        centro += largura;
    }
    return integral / Beta();
}
     /// Metodo calcular F
double CFisher::F(double x)
{
    double a = d1 / 2.0;
    double b = d2 / 2.0;
    return (pow(x, a - 1.0) * pow(1 - x, b - 1.0));
}
       ///Destrutor
CFisher::~CFisher()
{
}
