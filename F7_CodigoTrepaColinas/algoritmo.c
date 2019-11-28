#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    for(i=0; i<n; i++)
        b[i]=a[i];
	// Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
	// Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 1);
	// Troca
    b[p1] = 1;
    b[p2] = 0;
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    float max = 100, min = 5;
    int *nova_sol, custo, custo_viz, i;
    int *nova_sol2, custo_viz2;
    int *temp_sol;
    float erro, temp = max, p_aceitar;

	nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    nova_sol2 = malloc(sizeof(int)*vert);
    if(nova_sol2 == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

	// Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
        //Exfriamento
        temp -= ((float) max - min)/num_iter;
        if(temp <= min)
            break;

		// Gera vizinho
		gera_vizinho(sol, nova_sol, vert);
		gera_vizinho(sol, nova_sol2, vert);

		// Avalia vizinho
		custo_viz = calcula_fit(nova_sol, mat, vert);
		custo_viz2 = calcula_fit(nova_sol2, mat, vert);

		temp_sol = nova_sol;
		if(custo_viz > custo_viz2)
        {
            custo_viz = custo_viz2;
            temp_sol = nova_sol2;
        }

		// Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz <= custo)
        {
			substitui(sol, temp_sol, vert);
			custo = custo_viz;
        }
        //Exfriamento
        else
        {
            erro = custo - custo_viz; //Minimizar
            p_aceitar = exp(erro /(float) temp);

            if(p_aceitar > rand_01()){
                substitui(sol,temp_sol, vert);
            }
        }
    }

    free(nova_sol);
    free(nova_sol2);

    return custo;
}
