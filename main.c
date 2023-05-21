#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

float achar_y(float x, float a, float b);
float *lei_formacao(float x1, float y1, float x2, float y2);
float *extrai_termos_funcao(char *word);
int verifica_funcao(float a[2], float b[2]);
void limpar_tela();
void apresentacao_funcao(float termos[2]);
void apresentacao_pontos(float *f, float *a, float *b);

int main(int argc, char *argv[])
{
	int op;
	float a[3], b[3];
	float *termos = malloc(2 * sizeof(float));

	printf("Achar função dado 2 pontos   [0]\nAchar pontos dado uma função [1]\n");
	scanf("%d", &op);

	switch (op)
	{
	case 0:

		printf("Insira os valores do ponto A\n");

		char xy[3] = {'X', 'Y'};

		for (int i = 0; i < 2; i++)
		{
			printf("%c: ", xy[i]);
			scanf("%f", &a[i]);
		}

		printf("Insira os valores do ponto B\n");
		for (int i = 0; i < 2; i++)
		{
			printf("%c: ", xy[i]);
			scanf("%f", &b[i]);
		}

		if (!verifica_funcao(a, b))
		{
			float *f = lei_formacao(a[0], a[1], b[0], b[1]);

			limpar_tela();
			apresentacao_pontos(f, a, b);

			free(f);
		}
		else
		{
			printf("Não há função!\n");
		}

		break;

	case 1:
		printf("Digite a função: ");

		//limpa o '\n' do buffer
		getchar();
		//ponteiro para armazenar função
		char *func = malloc(20 * sizeof(char));
		fgets(func, 20, stdin);

		//retira a quebra de linha do final
		if (func[strlen(func) - 1] == '\n')
		{
			func[strlen(func) - 1] = '\0';
		}

		termos = extrai_termos_funcao(func);
		free(func);

		limpar_tela();
		//ANSI 65 = 'A'
		int nome_ponto = 65;

		//escreve informações da função no terminal
		apresentacao_funcao(termos);

		while (1)
		{
			printf("\n[0] Achar ponto na reta   [1] Sair\n");

			scanf("%d", &op);
			if (op == 1)
			{
				break;
			}
			else if (op == 0)
			{
				float x, y;

				printf("\nDigite o x da reta: ");
				scanf("%f", &x);

				y = achar_y(x, termos[0], termos[1]);

				printf("%c = {%.2f, %.2f}\n", nome_ponto, x, y);

				//avança uma letra
				if (nome_ponto < 90)
				{
					nome_ponto++;
				}
				else
				{
					nome_ponto = 65;
				}
			}
		}
		break;
	}

	printf("Tenha um bom dia!\n");

	free(termos);
	return 0;
}

int verifica_funcao(float a[2], float b[2])
{
	//x1 == x2
	if (a[0] == b[0])
	{
		return 1;
	}

	return 0;
}

int tamanho_a(char *word)
{
	int size_a;
	int it = 0;
	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i] == 'x')
		{
			if (i == 0)
			{
				size_a = 1;
			}
			else
			{
				size_a = i;
			}
			break;
		}
		else
		{
			//conta a quantidade quando não é x
			it++;
		}
	}
	//verifica se há um x na função
	if (it == strlen(word))
	{
		//se não há x na função
		size_a = -1;
	}

	return size_a;
}

int encontra_a(char *word, char *a)
{
	int j;
	for (j = 0; j < strlen(word); j++)
	{
		if (word[j] == 'x')
		{
			if (j == 0)
			{
				a[j] = '1';
			}
			break;
		}

		a[j] = word[j];
	}
	return j;
}

void encontra_b(char *word, char *b, int final_a)
{
	int c = 0;
	//false
	int decimal = 0;
	for (int i = final_a; i < strlen(word); i++)
	{
		if (word[i] == 43 && c == 0)
		{
			//word[i] = '+'
			b[c] = word[i];
			c++;
		}
		else if (word[i] == 45 && c == 0)
		{
			//word[i] = '-'
			b[c] = word[i];
			c++;
		}
		else if (word[i] == 46 && !decimal)
		{
			//word[i] = '.'
			b[c] = word[i];
			//decimal fica true, isto serve para ter apenas um ponto no número
			decimal = 1;
			c++;
		}
		if (word[i] >= 48 && word[i] < 57)
		{
			b[c] = word[i];
			c++;
		}
	}
}

float *extrai_termos_funcao(char *word)
{
	char *a;
	char *b;

	int size = tamanho_a(word);
	int size_a = (size == -1) ? 1 : size;
	b = malloc(5 * sizeof(char));
	a = malloc((size_a) * sizeof(char));

	//encontra o termo a
	if (size == -1)
	{
		strcpy(a, "0");
	}
	else
	{
		encontra_a(word, a);
	}

	//encontra termo b
	encontra_b(word, b, size + 1);

	float *arr = malloc(2 * sizeof(float));
	arr[0] = atof(a);
	arr[1] = atof(b);
	return arr;
}

float *lei_formacao(float x1, float y1, float x2, float y2)
{
	//lei de formação f(x) = ax + b
	float _x, _y, a, b;

	_x = x1 - x2;
	_y = y1 - y2;

	a = _y / _x;
	b = y1 - (x1 * a);

	float *arr = malloc(2 * sizeof(float));
	arr[0] = a;
	arr[1] = b;

	return arr;
}

float achar_y(float x, float a, float b)
{
	float y = a * x + b;
	return y;
}

void apresentacao_funcao(float termos[2])
{
	float x = -termos[1] / termos[0]; // x = -b / a
	float y;

	printf("\\*************************************************\\\n");
	printf("\nf(x) = ");

	if (termos[0] == -1)
	{
		printf("-x");
	}
	else if (termos[0] == 1)
	{
		printf("x");
	}
	else if (termos[0] != 1 && termos[0] != 0)
	{
		printf("%.2fx", termos[0]);
	}
	if (termos[1] != 0)
	{
		printf(" %c %.2f\n", (termos[1] > 0) ? '+' : '-', (termos[1] < 0) ? termos[1] * -1 : termos[1]);
	}

	if (termos[0] > 0)
	{
		printf("\n\nA reta é crescente.\n");
	}
	else
	{
		printf("\n\nA reta é decrescente.\n");
	}

	if (termos[0] != 0)
	{
		float x = -termos[1] / termos[0]; // x = -b / a
		printf("\nRaiz = {%.2f, 0.00}\n", x);
	}
	else
	{
		printf("\nA função não tem raiz.\n");
	}

	y = achar_y(0, termos[0], termos[1]);

	printf("\nInterseção com eixo y = {0.00, %.2f}\n\n", y);
	printf("\\*************************************************\\\n");
}

void apresentacao_pontos(float *f, float *a, float *b)
{
	printf("\\*************************************************\\\n");

	printf("\nPonto A = { %.2f, %.2f } Ponto B = { %.2f, %.2f }\n", a[0], a[1], b[0], b[1]);

	printf("\nf(x) = ");

	if (a[1] != b[1])
	{
		if (f[0] == -1)
		{
			printf("-x");
		}
		else if (f[0] == 1)
		{
			printf("x");
		}
		else if (f[0] != 1)
		{
			printf("%.2fx", f[0]);
		}
	}
	if (f[1] != 0)
	{
		printf(" %c %.2f\n", (f[1] > 0) ? '+' : '-', (f[1] < 0) ? f[1] * -1 : f[1]);
	}
	printf("\n\\*************************************************\\\n\n");
}

void limpar_tela()
{
#ifdef _WIN32 // _WIN64
	system("cls");

#else
	system("clear");
#endif
}