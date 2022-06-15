#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"


void sjf_calculate_time(Process *p, int len)
{
	int i, j;

	int curr_time = 0;

	int min = 0;



	p[0].completed = TRUE;
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].burst - p[0].arrive_time;
	p[0].waiting_time = 0;
	
	curr_time = p[0].burst;



	for(i = 1; i < len; i++)
	{

		for (j = 1; j < len; j++)
		{

			if (p[j].completed == TRUE)
				continue;

			else
			{
				min = j;

				break;

			}
		}


		for (j = 1; j < len; j++)
		{

			if ((p[j].completed == FALSE)
					&& (p[j].arrive_time <= curr_time)
						&& (p[j].burst < p[min].burst))
			{
				min = j;

			}
		}

		p[min].waiting_time = curr_time - p[min].arrive_time;

		p[min].completed = TRUE;


		curr_time += p[min].burst;


		p[min].return_time = curr_time;

		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;

	}
}


void sjf_print_gantt_chart(Process *p, int len)
{
	int i, j;


	printf("\t ");


	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t|");


	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n\t ");


	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t");

	printf("0");


	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("  ");

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);
	}

	printf("\n");
}


void SJF(Process *p, int len){
    int i;
    int temp_espera = 0;
    int temp_retorno = 0;
    int temp_resposta = 0;

	// inicializando o processo
	process_init(p,len);

	// Função para ordenar por ordem de chegada
	merge_sort_by_arrive_time(p,0,len);

	//Clacular o tempo sjf
	sjf_calculate_time(p,len);

	for(i=0;i<len;i++){
		p[i].return_time = p[i].turnaround_time + p[i].arrive_time;
		p[i].response_time = p[i].waiting_time;
		temp_espera = temp_espera + p[i].waiting_time;
		temp_retorno += p[i].turnaround_time;
		temp_resposta += p[i].response_time;
	}
	 printf(" Algoritmo SJF\n");

	 quick_sort_by_return_time(p,len);

	 //Fução para mostar o gráfico de gantt
	 sjf_print_gantt_chart(p,len);

	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)temp_espera / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)temp_resposta / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)temp_retorno / (double)len);

	//Imprime a tabela
	print_table(p,len);

}

#endif
