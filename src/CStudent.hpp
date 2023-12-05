
#ifndef CStudent_hpp
#define CStudent_hpp

     /// classe CStudent
class CStudent
{

  private:
      /// tamanho da amostra(n) menos 1, n > 1
    int graus_liberdade;
      /// Beta
    double Beta();
      /// Beta Beta_regularizada
    double Beta_regularizada(double x);
      /// Funcão gaussiana
    double F(double x);

  public:
      /// Calculo da Probabilidade
    double Probabilidade(double x);
      ///costrutor  default inicializando com ngl.
    CStudent(int ngl);
      /// Construtor de cópia .
    CStudent ( const CStudent & s ): graus_liberdade (s.graus_liberdade  ) { }
      /// Destrutor default.
    ~CStudent();
};
# endif
