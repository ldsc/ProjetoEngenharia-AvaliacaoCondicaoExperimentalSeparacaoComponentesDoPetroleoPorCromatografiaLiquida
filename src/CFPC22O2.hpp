
#ifndef CFPC22_O2_hpp
#define CFPC22_O2_hpp

#include <string>

using namespace std;
  /// Classe CFPC22_02 para calcular planejamento Fatorial de 2^2
class CFPC22_O2
{
private:
  double respostas[7]; //< Vetor de respostas obida laboratório
  double XtY[4];  //< Matriz do planejamento transposta vezes o vetor resposta
  double b[4]; //< vetor de regressã
  double tcalc[4]; //< distribuição de Student
  double p_coeficientes[4]; //< valor estatitico amostral de stundent
  const double erro[4] = {0.378, 0.5, 0.5, 0.5}; //< Matriz erro aleatório associado ao modelo
  const double XXinv[4] = {0.143, 0.25, 0.25, 0.25}; //< Matriz do planejamento vezes sua inversa
  const double nivel_significancia = 0.05; //< significa que a probabilidade de erro e de 0,05
  double media = 0; //< mediada das resposta encontrada no laboratório
  double media_pcentral = 0; //< Media do ponto central para calculos dos erros
  double media_estimados = 0; //< media estimada do Y estimado pelo modelo
  double y_estimado[7];//< Vetor de respostas estimado
  double residuos[7]; //< residos gerado pelo modelo ex; (Yi lab) -( Yi estimado)
  double ANOVA_reg[7]; //< quadratica da regressao
  double ANOVA_total[7];//< quadrática da variação total
  double ANOVA_falt[7]; //< quadrática da falta de ajusta (discrepancia)
  double ANOVA_errpuro[7]; //<erro puro no laboratorio
  double soma_quadratica[4]; //< soma quadratica
  double media_quadratica[4]; //< soma quadratica da media
  double Fcalc[2]; //< calcular  F distribuição de Fisher.
  double p_variancia[2]; //< valor estatitico amostral
  double n_graus_liberdade[4] = {3, 3, 1, 2}; //< graus de liberdade
  double var_explicada; //<Analise de variancia
  double max_var_explicada; //<Analise de variancia maxima
  bool significativo[2]; //< mostra se foi ou nao significativo
  double ANOVA_reg_soma = 0; //< soma quadratica da regressao
  double ANOVA_total_soma = 0; //<soma quadrática da variação tota
  double ANOVA_falt_soma = 0; //< soma quadrática da falta de ajusta (discrepancia)
  double ANOVA_errpuro_soma = 0; //< somatorio do erro puro no laboratorio

public:
   /// costrutor default
  CFPC22_O2();
   /// o usuario estrara com os valores manualmente obitidos em laboratorio .
  void Entrada_manual();
   /// o usuario informara o arquivo com os dados obitidos em laboratorio.
  void Ler_arquivo(string arquivo);
   /// ler dados para plot
  void get_resposta(double _resp[7]);
   /// ler dados para plot
  void get_yestimado(double _yresp[7]);
   /// o programa ira realizar uma seguencia de calculos estatiticos para ANOVA.
  void Calcular();
   /// Mostrar na tela os valores caulculados da ANOVA.
  void Mostrar_calculos();
   ///  mostrar os coeficientes referente a sua equação.
  void Tabela_coeficientes();
   /// Salvar os aquivos em .txt
  void Arquivo_saida();
   ///  mostrar a tabela da ANOVA
  void Tabela_variancia();
   /// Destrutor default.
  ~CFPC22_O2();
};
# endif
