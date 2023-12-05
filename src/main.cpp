#include <iostream>
#include "CFPC22_O2.hpp"
#include <string>
#include "CFisher.hpp"
#include "CStudent.hpp"
#include "CGnuplot.h"
#include "vector"
#include <fstream>

using namespace std;


int main()
{
    double tmp1[7],tmp2[7]; //vetor no estilo de C
    vector <double> tmp11, tmp21; //vetor no estilo de C++

	int entrada = 0;
	CFPC22_O2 planejamento; // objeto planejamento
	
	cout << "\n\n###### PLANEJAMENTO FATORIAL v1.0 ######\nAutor: Jhonny Carvalho; LENEP-UENF (2019)\n-----------------------------------------\n"; // Título em tela

	while (entrada != 1 && entrada != 2)
	{
		cout << "Selecione o modo de entrada de dados:\n1 - Utilizar um arquivo de entrada\n2 - Entrada manual\n";
		cin >> entrada; cin.get();
	}
	if (entrada == 1)
	{
		string arquivo;
		cout << "Lista de arquivos.txt): ";
		system("ls *.txt"); // lista dos arquivos txt
		cout << "Digite o nome do arquivo (sem .txt): ";
		cin >> arquivo; cin.get();
		planejamento.Ler_arquivo(arquivo); // le dados do arquivo
	}
	else
	{
		planejamento.Entrada_manual(); // entrada manual
	}

	planejamento.Tabela_coeficientes(); //calcula coef
	planejamento.Tabela_variancia(); //calcula variancia
	planejamento.Arquivo_saida();/// salvar arquivos
        planejamento.get_resposta(tmp1);
        planejamento.get_yestimado(tmp2);

    for (int i=0;i<7;i++)
    {
        tmp11.push_back(tmp1[i]);
        tmp21.push_back(tmp2[i]);
        //cout << tmp1[i] << "," << tmp2[i] << endl; //vetor c
        cout << tmp11[i] << "," << tmp21[i] << endl;//vetor c++
    }

cout << "size=" << tmp11.size() << ", size=" << tmp21.size() << endl;//vetor c++

// Plot do grafico utilizando CGnuplot:

    //Gnuplot::set_GNUPlotPath("C:/program files/gnuplot/bin"); //setando Gnuplot no Windows
    //Gnuplot::Terminal("win"); //Utilizando terminal do Windows

    CGnuplot gp("points"); //Define o estilo do gráfico
    gp.Grid(); // Habilitar grid do gráfico ploatada
    gp.set_pointsize (2.0); //Setando tamanho do ponto
    gp.set_title ("Plot: Observados VS Estimados"); // Definindo título para o gráfico
    gp.set_ylabel("Estimados"); //Definindo nome do Eixo Y
    gp.set_xlabel("Observados"); //Definindo nome do Eixo X
    gp.set_yautoscale (); // Seta automaticamente os limites para o eixo Y
    gp.set_xautoscale (); // Seta automaticamente os limites para o eixo X
    gp.PlotVector(tmp11,tmp21,"Dados"); // Plotando vetor de dados (observados vs estimados)
    
cout << "Digite 'enter' para encerrar.\n";

   /// ofstream data ("resultados.txt", ofstream::out | ios::app ); // Costruindo a saída de dados p/ arquivo     
   /// data << tmp1;  
   /// data.close();
    gp.SaveTo("grafico_Obs-VS-Estm","png"); // Salvando sessão do gnuplot para um arquivo 
    cin.get();
cin.get();

return 0;
}

