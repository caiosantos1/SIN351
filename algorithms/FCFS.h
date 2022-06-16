#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"


void fcfs_print_gantt_chart(Process *p, int len)
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

        if (p[i].return_time > 9)
            printf("\b");

        printf("%d", p[i].return_time);

    }

    printf("\n");
}


void FCFS(Process *p, int len)
{
    //Declaração de Variáveis
    int i;
    int temp_espera = 0;
    int temp_retorno = 0;
    int temp_resposta = 0;
    int tem_return = 0;
    
    // inicializando o processo
    process_init(p,len);

    // Função para ordenar por ordem de chegada
    merge_sort_by_arrive_time(p,0,len);

    p[0].response_time = p[0].burst;
    p[0].turnaround_time = p[0].return_time;
    p[0].response_time = 0;
    p[0].waiting_time = 0;

    temp_espera += p[0].response_time;
    temp_espera += p[0].waiting_time;
    temp_retorno += p[0].turnaround_time;
    tem_return += p[0].burst;

    for(i=0;i<len;i++){
       
        tem_return += p[i].burst;
        temp_espera += p[i].waiting_time;
        temp_retorno += p[i].turnaround_time;
        temp_resposta += p[i].response_time;

    }

    printf("FCFS\n");

    //Fução para mostar o gráfico de gantt
    fcfs_print_gantt_chart(p,len);

    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)temp_espera / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)temp_resposta / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)temp_retorno / (double)len);

    //Imprime a tabela
	print_table(p, len);
}

#endif
