
#ifndef CFisher_hpp
#define CFisher_hpp

class CFisher
{
  private:
      
    int d1; /// variavel 1
    int d2; /// variavel 2
      /// Calculo de beta
    double Beta();
      /// calculo de beta regularizado
    double Beta_regularizada(double x);
      /// Calculo da gaussiana
    double F(double x);

  public:
     /// Construtor default .
     CFisher( ) { }
     /// Construtor de cópia .
     CFisher ( const CFisher & f ): d1 (f. d1 ), d2 (f. d2 ) { }
      /// Costrutor sobrecarregado.
    CFisher(int _d1, int _d2);
      /// Calculo da probabilidade
    double Probabilidade(double x);
      /// Destrutor deufault.
    ~CFisher();
};
 # endif
