#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#ifndef <SolProf>
#define SolucaoProf 0
#else
#define SolucaoProf 1
#endif


// Calcula a qualidade de uma solu��o
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, int mat[][2], int *v)
{
	int     i;
	float   sum_weight, sum_profit;
	float   penality, ro_temp = -1;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
            // Actualiza o peso total
			sum_weight += mat[i][0];
            // Actualiza o lucro total
			sum_profit += mat[i][1];

			ro_temp = (mat[i][1]/mat[i][1]) > ro_temp? (mat[i][1]/mat[i][1]) : ro_temp;
		}
	}

	if (sum_weight > d.capacity)
	{
        // Solucao inv�lida
        *v = 1;

        if(SolucaoProf)
            d.ro = sum_profit/sum_weight;
        else
            d.ro = ro_temp;

        penality = d.ro * (sum_weight - d.capacity);

		return sum_weight - penality;
	}
	else
	{
        // Solucao v�lida
        *v = 1;
        d.ro = 0;
        penality = d.ro * (sum_weight - d.capacity);

		return sum_profit - penality;
	}
}

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate(pchrom pop, struct info d, int mat[][2])
{
	int i;

	for (i=0; i<d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
}
