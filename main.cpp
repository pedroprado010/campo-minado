#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <queue>

#define um 49

using namespace std;

typedef struct dif{
	int Linha;
	int Coluna;
	int Minas;
	dif(int a,int b,int c)
	{
		Linha=(a),Coluna=(b),Minas=(c);
	}
}Dificuldade;

Dificuldade Easy(8,8,10);
Dificuldade Medium(16,16,40);
Dificuldade Hard(30,16,99);



char **geraCampo(int nLinhas,int nColunas,int nMinas);
void novoJogo(Dificuldade D);
bool FimdeJogo(bool **mask,Dificuldade D);
void MostraCampo(char **campo,bool **mascara,Dificuldade D);
bool Marcar(int x,int y,bool **mascara, char **campo,Dificuldade D);

int main()
{

	srand(time(NULL));

	novoJogo(Easy);
	return 0;
}

void novoJogo(Dificuldade D)
{
	char **campo = geraCampo(D.Linha, D.Coluna,D.Minas);
	bool **mascara = new bool*[D.Linha];

	for(int i = 0; i< D.Linha ;++i)
		mascara[i] = new bool[D.Coluna];

	for(int i = 0; i< D.Linha ;++i)
		for(int j = 0; j< D.Coluna; ++j)
			mascara[i][j] = false;

	int x,y;

	while(1)
	{

		 MostraCampo(campo,mascara,D);// Mostrando o jogo
		//--------------Ler a posição
		cin>>x;
		cin>>y;

		//--------------

		system("clear");

		if(!Marcar(x,y,mascara,campo,D)) return;

		//-------------
		if(FimdeJogo( mascara , D))//Verifica se apenas sobraram as minas.
		{
			cout << "Fim de Jogo" << endl;
			return;
		}
	}
}

bool Marcar(int x,int y,bool **mascara, char **campo,Dificuldade D)
{

	if(mascara[x][y]) return true;
	else//Verifica se a posição já não foi marcada.
	{
		mascara[x][y] = true;

		if(campo[x][y] == '*')
		{
			cout << "Você marcou uma mina!\n\t\tFim de Jogo\n" << endl;
			return false;
		}
		if(campo[x][y] == ' ')
		{
			queue<int> py;
			queue<int> px;
			/*
			 * abrindo os espaços em branco adjacentes ao marcado.
			 * Empilhando todos e repetindo o processo conforme sao
			 * encontrados.
			 */
			py.push(y);
			px.push(x);
			while(!px.empty() && !py.empty())
			{
				int L,C;
				L = px.front();
				C = py.front();

				px.pop();
				py.pop();

				for(int i=-1 ; i < 2 ; ++i)
					for(int j=-1 ; j < 2 ; ++j)
					{
						if( ((i+L) < D.Linha && (i+L) >=0) && ((j+C) < D.Coluna && (j+C) >= 0) )
						{
							if(i==0 && j == 0)continue;

							if(!mascara[L+i][C+j])
							{
								mascara[L+i][C+j] = true;
								if(campo[L+i][C+j] == ' ')
								{
									px.push(L+i);
									py.push(C+j);
								}
							}
						}
					}
			}
		}
	}
	return true;
}

void MostraCampo(char **campo,bool **mascara,Dificuldade D)
{
	for(int i = 0; i < D.Linha ; ++i)// Mostrando os espaços da matriz.
		{
			for(int j = 0; j < D.Coluna ; ++j)
			{
				mascara[i][j]? cout <<" "<<campo[i][j] : cout<<" " << '#';//Se já foi marcado mostra o campo real, caso contrario a mascara.
			}
		cout << endl;
		}
}

bool FimdeJogo(bool **mask,Dificuldade D)
{
	int nEspacoRestante = 0;

	for(int i = 0 ; i < D.Linha ; ++i)
		for(int j = 0; j < D.Coluna ; ++j)
			if(mask[i][j]) nEspacoRestante++;

	if(nEspacoRestante == D.Minas) return true;
	return false;

}

char **geraCampo(int nLinhas,int nColunas,int nMinas)
{
	char **campo = new char*[nColunas];
	for(int i = 0; i < nLinhas ;++i)
		campo[i] = new char[nColunas];

	struct xy
	{
		int px;
		int py;
	} posicao[nMinas];//Guarda as posições das minas.

	for(int i = 0; i< nLinhas ; ++i)
		for(int j = 0;j < nColunas; ++j)
			campo[i][j] = ' ';// Resetando os espaços do campo.

	for(int i=0 ; i < nMinas; ++i)//Distribui as minas em posições aleatórias.
	{
		int x,y;
		x = rand() % nLinhas;
		y = rand() % nColunas;
		campo[x][y] = '*' ;
		posicao[i].px = x;
		posicao[i].py = y;
	}

	for(int i=0 ; i < nMinas; ++i)//Marca os numeros no campo.
	{
		for(int j = -1; j<2; ++j)
			for(int k = -1; k<2 ; ++k)
			{
				if( ( posicao[i].px+(j) < nLinhas && posicao[i].px+(j)>=0 ) && ( posicao[i].py+(k) >= 0 && posicao[i].py+(k) < nColunas))
				{
					if(campo[posicao[i].px+(j)][posicao[i].py+(k)] != '*')
					{
						if(campo[posicao[i].px+(j)][posicao[i].py+(k)] == ' ')campo[posicao[i].px+(j)][posicao[i].py+(k)] = um;
						else campo[posicao[i].px+(j)][posicao[i].py+(k)] ++;
					}
				}
			}
	}
    /*
	for(int i = 0 ; i < nLinhas ; ++i)
	{
		for(int j = 0 ; j < nColunas ; ++j)
			cout <<' '<<campo[i][j];
		cout << endl;
	}*/
	return campo;
}
