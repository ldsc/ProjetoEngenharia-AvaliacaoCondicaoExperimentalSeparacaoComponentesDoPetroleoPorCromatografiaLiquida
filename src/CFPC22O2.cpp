#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

#include "CFPC22_O2.hpp"
#include "CStudent.hpp"
#include "CFisher.hpp"

using namespace std;

CFPC22_O2::CFPC22_O2()
{
}
     /// o usuario informara o arquivo com os dados obitidos em laboratorio.
void CFPC22_O2::Ler_arquivo(string arquivo)
{
    ifstream entrada("./" + arquivo + ".txt"); /// ler aquivo em formato .txt

    for (int i = 0; i < 7; i++) /// percorre os valores de i=0 ate i=6
    {
        entrada >> respostas[i];
    }
    this->Calcular(); /// ponteiro para ter acesso a Calcular
}
     /// o usuario estrara com os valores manualmente obitidos em laboratorio .
void CFPC22_O2::Entrada_manual()
{
    cout << "\nDigite o valor de y para x1 =-1, x2 =-1: "; /// o usuario entarar com o primeiro valor do lab.
    cin >> respostas[0]; /// amarzenar respostas 0
    cout << "Digite o valor de y para x1 = 1, x2 =-1: ";/// o usuario entarar com o segundo valor do lab.
    cin >> respostas[1]; /// amarzenar respostas 0
    cout << "Digite o valor de y para x1 =-1, x2 = 1: ";/// o usuario entarar com o terceiro valor do lab.
    cin >> respostas[2];  /// amarzenar respostas 0
    cout << "Digite o valor de y para x1 = 1, x2 = 1: ";/// o usuario entarar com o quarto valor do lab.
    cin >> respostas[3]; /// amarzenar respostas 0
    for (int i = 4; i < 7; i++)
    {
        cout << "Digite o valor de y do ponto central (" << i - 3 << "/3): "; /// valores do ponto central
        cin >> respostas[i];/// armazena os valores do ponto central
    }
    this->Calcular();
}
    /// o programa ira realizar uma seguencia de calculos estatiticos para ANOVA.
void CFPC22_O2::Calcular()
{
    double soma = 0;
    for (int i = 0; i < 7; i++)
    {
        soma += respostas[i];
    }

    media = (soma / 7); ///soma das respostas dividido pela quantidade de amostras
    media_pcentral = ((respostas[4] + respostas[5] + respostas[6]) / 3); /// media do ponto central

    XtY[0] = soma;
    XtY[1] = (respostas[1] + respostas[3] - respostas[0] - respostas[2]);
    XtY[2] = (respostas[2] + respostas[3] - respostas[0] - respostas[1]);
    XtY[3] = (respostas[0] + respostas[3] - respostas[1] - respostas[2]);

	CStudent student(2);
    for (int i = 0; i < 4; i++)
    {
        b[i] = XXinv[i] * XtY[i];
        tcalc[i] = b[i] / erro[i];
		p_coeficientes[i] = student.Probabilidade(tcalc[i]);
    }

    y_estimado[0] = b[0] - b[1] - b[2] + b[3];
    y_estimado[1] = b[0] + b[1] - b[2] - b[3];
    y_estimado[2] = b[0] - b[1] + b[2] - b[3];
    y_estimado[3] = b[0] + b[1] + b[2] + b[3];
    y_estimado[4] = b[0];
    y_estimado[5] = b[0];
    y_estimado[6] = b[0];
    for (int i = 0; i < 7; i++)
    {
        media_estimados += y_estimado[i];
    }
    media_estimados /= 7;

    for (int i = 0; i < 7; i++)
    {
        residuos[i] = respostas[i] - y_estimado[i];
    }

    for (int i = 0; i < 7; i++)
    {
        ANOVA_reg[i] = pow(y_estimado[i] - media, 2);
        ANOVA_reg_soma += ANOVA_reg[i];
    }

    for (int i = 0; i < 7; i++)
    {
        ANOVA_total[i] = pow(respostas[i] - media, 2);
        ANOVA_total_soma += ANOVA_total[i];
    }

    for (int i = 0; i < 4; i++)
    {
        ANOVA_falt[i] = pow(y_estimado[i] - respostas[i], 2);
        ANOVA_falt_soma += ANOVA_falt[i];
    }
    for (int i = 4; i < 7; i++)
    {
        ANOVA_falt[i] = pow(y_estimado[i] - media_pcentral, 2);
        ANOVA_falt_soma += ANOVA_falt[i];
    }
    for (int i = 0; i < 4; i++)
    {
        ANOVA_errpuro[i] = pow(respostas[i] - respostas[i], 2);
        ANOVA_errpuro_soma += ANOVA_errpuro[i];
    }
    for (int i = 4; i < 7; i++)
    {
        ANOVA_errpuro[i] = pow(respostas[i] - media_pcentral, 2);
        ANOVA_errpuro_soma += ANOVA_errpuro[i];
    }

    soma_quadratica[0] = ANOVA_reg_soma;
    soma_quadratica[1] = ANOVA_falt_soma + ANOVA_errpuro_soma;
    soma_quadratica[2] = ANOVA_falt_soma;
    soma_quadratica[3] = ANOVA_errpuro_soma;

    for (int i = 0; i < 4; i++)
    {
        media_quadratica[i] = soma_quadratica[i] / n_graus_liberdade[i];
    }
    Fcalc[0] = media_quadratica[0] / media_quadratica[1];
    Fcalc[1] = media_quadratica[2] / media_quadratica[3];

	CFisher fisher1(n_graus_liberdade[0], n_graus_liberdade[1]);
	p_variancia[0] = fisher1.Probabilidade(Fcalc[0]);

	CFisher fisher2(n_graus_liberdade[2], n_graus_liberdade[3]);
	p_variancia[1] = fisher2.Probabilidade(Fcalc[1]);
	for (int i = 0; i < 2; i++)
	{
		if (p_variancia[i] < nivel_significancia) {
			significativo[i] = true;
		}
		else {
			significativo[i] = false;
		}
	}

    var_explicada = 100 * (soma_quadratica[0] / ANOVA_total_soma);
    max_var_explicada = 100 * ((ANOVA_total_soma - soma_quadratica[3]) / ANOVA_total_soma);
}
      /// Mostrar na tela os valores caulculados da ANOVA.
void CFPC22_O2::Mostrar_calculos()
{
    cout << "media:" << media << endl;
    cout << "media pc:" << media_pcentral << endl;
    cout << "Xy - " << XtY[0] << " | " << XtY[1] << " | " << XtY[2] << " | " << XtY[3] << " | \n";
    for (int i = 0; i < 4; i++)
    {
        cout << "b - " << b[i] << "\nt - " << tcalc[i] << endl;
    }
    for (int i = 0; i < 7; i++)
    {
        cout << endl
             << "y estimado - " << y_estimado[i];
    }
    for (int i = 0; i < 7; i++)
    {
        cout << endl
             << "residuo - " << residuos[i];
    }
    cout << "Media estimados - " << media_estimados << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << endl
             << "ANOVA reg. - " << ANOVA_reg[i];
    }
    for (int i = 0; i < 7; i++)
    {
        cout << endl
             << "ANOVA total - " << ANOVA_total[i];
    }
    for (int i = 0; i < 7; i++)
    {
        cout << endl
             << "ANOVA falt - " << ANOVA_falt[i];
    }
    for (int i = 0; i < 7; i++)
    {
        cout << endl
             << "ANOVA errpuro - " << ANOVA_errpuro[i];
    }
    cout << endl
         << "ANOVA reg soma - " << ANOVA_reg_soma;
    cout << endl
         << "ANOVA total soma - " << ANOVA_total_soma;
    cout << endl
         << "ANOVA falt soma - " << ANOVA_falt_soma;
    cout << endl
         << "ANOVA errpuro soma - " << ANOVA_errpuro_soma;
    for (int i = 0; i < 4; i++)
    {
        cout << "\nmedia " << i << ": " << media_quadratica[i];
    }
    cout << "\nFcalc1 - " << Fcalc[0] << "\np - " << p_variancia[0];
	cout << "\nFcalc2 - " << Fcalc[1] << "\np - " << p_variancia[1];
    cout << "\nVariacao explicada - " << var_explicada;
    cout << "\nmax variacao explicada - " << max_var_explicada;
}
      ///  mostrar os coeficientes referente a sua equação.
void CFPC22_O2::Tabela_coeficientes()
{
    cout << endl
         << "Tabela de coeficientes";
    cout << endl
         << "---------------------------------------------";
    cout << endl
         << '\t' << "Efeitos\tErro\tt(2)\tp" << endl;
    cout << "Media\t" << b[0] << '\t' << erro[0] << '\t' << tcalc[0] << '\t' << p_coeficientes[0] << endl;
    cout << "X1\t" << 2 * b[1] << '\t' << 2 * erro[1] << '\t' << tcalc[1] << '\t' << p_coeficientes[1] << endl;
    cout << "X2\t" << 2 * b[2] << '\t' << 2 * erro[2] << '\t' << tcalc[2] << '\t' << p_coeficientes[2] << endl;
    cout << "X12\t" << 2 * b[3] << '\t' << 2 * erro[3] << '\t' << tcalc[3] << '\t' << p_coeficientes[3] << endl;
    cout << "---------------------------------------------" << endl;
}
     ///  mostrar a tabela da ANOVA
void CFPC22_O2::Tabela_variancia()
{
    cout << endl
         << "Analise de variancia";
    cout << endl
         << "--------------------------------------------------------------------";
    cout << endl
         << "FV\t\t" << "SQ\t" << "nGL\t" << "MQ\t" << "Fcalc.\t" << "p" << endl;
    cout << "Regressão\t" << soma_quadratica[0] << '\t' << n_graus_liberdade[0] << '\t' << media_quadratica[0] << '\t' << Fcalc[0] << '\t' << p_variancia[0] << endl;
    cout << "Residuos\t" << soma_quadratica[1] << '\t' << n_graus_liberdade[1] << '\t' << media_quadratica[1] << endl;
    cout << "F. Ajuste\t" << soma_quadratica[2] << '\t' << n_graus_liberdade[2] << '\t' << media_quadratica[2] << '\t' << Fcalc[1] << '\t' << p_variancia[1] << endl;
    cout << "Erro Puro\t" << soma_quadratica[3] << "\t" << n_graus_liberdade[3] << '\t' << media_quadratica[3] << endl;
    cout << "Total\t\t" << ANOVA_total_soma << '\t' << 6 << endl;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "- Regressão ";
	if (!significativo[0]) {
		cout << "não";
	}
	cout << " Significativa" << endl;
	cout << "- F. Ajuste ";
	if (!significativo[1]) {
		cout << "não";
	}
	cout << " Significativa" << endl;
    cout << "variação explicada\t\t " << var_explicada << '%' << endl;
    cout << "máx. de variação explicável\t " << max_var_explicada << '%' << endl;
}
      /// salvar arquivo em .txt
void CFPC22_O2::Arquivo_saida(){
    FILE *saida;
    saida=fopen("dadosaida.txt", "wb");
    fstream fout;
    fout.open("dadosaida.txt");
    
    fout << endl;
    fout << "Tabela de coeficientes";
    fout << endl;
        fout  << "---------------------------------------------";
    fout << endl;
    fout << '\t' << "Efeitos\tErro\tt(2)\tp" << endl;
    fout << "Media\t" << b[0] << '\t' << erro[0] << '\t' << tcalc[0] << '\t' << p_coeficientes[0] << endl;
    fout << "X1\t" << 2 * b[1] << '\t' << 2 * erro[1] << '\t' << tcalc[1] << '\t' << p_coeficientes[1] << endl;
    fout << "X2\t" << 2 * b[2] << '\t' << 2 * erro[2] << '\t' << tcalc[2] << '\t' << p_coeficientes[2] << endl;
    fout << "X12\t" << 2 * b[3] << '\t' << 2 * erro[3] << '\t' << tcalc[3] << '\t' << p_coeficientes[3] << endl;
    fout << "---------------------------------------------" << endl;
    
    fout << " Analises da variancia e os coeficientes significativos"<<endl;
    fout << "FV\t\t" << "SQ\t" << "nGL\t" << "MQ\t" << "Fcalc.\t" << "p" << endl;
    fout << "Regressão\t" << soma_quadratica[0] << '\t' << n_graus_liberdade[0] << '\t' << media_quadratica[0] << '\t' << Fcalc[0] << '\t' << p_variancia[0] << endl;
    fout << "Residuos\t" << soma_quadratica[1] << '\t' << n_graus_liberdade[1] << '\t' << media_quadratica[1] << endl;
    fout << "F. Ajuste\t" << soma_quadratica[2] << '\t' << n_graus_liberdade[2] << '\t' << media_quadratica[2] << '\t' << Fcalc[1] << '\t' << p_variancia[1] << endl;
    fout << "Erro Puro\t" << soma_quadratica[3] << "\t" << n_graus_liberdade[3] << '\t' << media_quadratica[3] << endl;
    fout << "Total\t\t" << ANOVA_total_soma << '\t' << 6 << endl;
	fout << "--------------------------------------------------------------------" << endl;
	fout << "- Regressão ";
	if (!significativo[0]) {
		cout << "não";
	}
	fout << " Significativa" << endl;
	fout << "- F. Ajuste ";
	if (!significativo[1]) {
		cout << "não";
	}
	fout << " Significativa" << endl;
    fout << "variação explicada\t\t " << var_explicada << '%' << endl;
    fout << "máx. de variação explicável\t " << max_var_explicada << '%' << endl;
    
    fout.close();
  }
     /// redefinindo vetor respostas
void CFPC22_O2::get_resposta(double _resp[7])
{
    for (int i=0;i<7;i++)
    {
        _resp[i]=respostas[i];
    }
};
    /// redefinindo y_estimado
void CFPC22_O2::get_yestimado(double _yresp[7])
{
  for (int i=0;i<7;i++)
    {
        _yresp[i]=y_estimado[i];
    }  
};
/// Destrutor default.
CFPC22_O2::~CFPC22_O2()
{
}

