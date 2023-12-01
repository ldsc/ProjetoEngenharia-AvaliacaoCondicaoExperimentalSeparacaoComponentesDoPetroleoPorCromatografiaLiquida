#include "CStudent.hpp"
#include <cmath>
#include <iostream>

const double PI = 3.1416;
using namespace std;
    /// Costrutur default.
CStudent::CStudent(int ngl)
{
    graus_liberdade = ngl;
}
    /// Metodo calcular Probalilidade
double CStudent::Probabilidade(double x)
{
    double argumento = (graus_liberdade / (pow(x, 2) + graus_liberdade));
    return Beta_regularizada(argumento);
}
    /// Metodo calcular Beta
double CStudent::Beta()
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
    /// Metodo calcular Beta_regularizada.
double CStudent::Beta_regularizada(double x)
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
double CStudent::F(double x)
{
    double a = graus_liberdade / 2.0;
    double b = 0.5;
    return (pow(x, a - 1.0) * pow(1 - x, b - 1.0));
}
     /// Destrutor
CStudent::~CStudent()
{
}
