#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int *vetor, double *comparacoes, double *movimentos, double *tempoExec, int tamanho);
void SelectionSort();
void InserctionSort();
void ShellShort();
void QuickSort();
void HeapSort();
void MergeSort();
void Contagem_Dos_Menores();
void RadixSort();

int main()
{
    int tamanho, metodo, tamanhoEscolhido, estadoInicial;
    double ncomparacoes = 0, nmovimentos = 0;
    double *comparacoes = &ncomparacoes;
    double *movimentos = &nmovimentos;
    double tempo = 0;
    double *tempoExec = &tempo;
    printf("Escolha o tamanho do vetor:\n1: 100 elementos.\n2: 1.000 elementos.\n3: 10.000 elementos.\n4: 100.000 elementos.\n");
    scanf(" %d", &tamanhoEscolhido);

    switch (tamanhoEscolhido)
    {
    case 1:
        tamanho = 100;
        break;
    case 2:
        tamanho = 1000;
        break;
    case 3:
        tamanho = 10000;
        break;
    case 4:
        tamanho = 100000;
        break;
    default:
        printf("Esse não é um dos valores a ser escolhido.");
        return 1;
    }

    int *vetor = (int *)calloc(tamanho, sizeof(int));
    if (!vetor)
    {
        printf("Erro na alocacao de memoria.");
        return 1;
    }
    printf("Escolha o estado inicial do vetor:\n1: Ordenado.\n2: Inversamente ordenado.\n3: Aleatorio.\n");
    scanf(" %d", &estadoInicial);

    switch (estadoInicial)
    {
    case 1:
        for (int i = 0; i < tamanho; i++)
        {
            vetor[i] = i;
        }
        break;
    case 2:
        for (int i = 0; i < tamanho; i++)
        {
            vetor[i] = tamanho - 1 - i;
        }
        break;
    case 3:
        srand(time(NULL));
        for (int i = 0; i < tamanho; i++)
        {
            vetor[i] = rand();
        }
        break;
    default:
        printf("Esse não é um dos valores a ser escolhido.");
        free(vetor);
        return 1;
    }

    printf("Os 10 primeiros termos do vetor estao da seguinte forma:\n[");
    for (int i = 0; i < 10; i++)
    {
        printf("%d", vetor[i]);
        if (i != 9)
        {
            printf(" - ");
        }
    }
    printf("]\n\n");

    printf("Escolha o metodo de ordenacao:\n1: BubbleSort.\n2: SelectionSort.\n3: InsertionSort.\n4: ShellSort.\n5: QuickSort.\n6: HeapSort.\n7: MergeSort.\n8: Contagem do minimos.\n9: RadixSort.\n");

    scanf(" %d", &metodo);

    switch (metodo)
    {
    case 1:
        BubbleSort(vetor, comparacoes, movimentos, tempoExec, tamanho);
        break;

    default:
        break;
    }
    printf("Primeiros 100 valores do vetor ordenado\n[");
    for (int i = 0; i < 100; i++)
    {
        printf("%d", vetor[i]);
        if (i != 99)
        {
            printf(" - ");
        }
    }
    printf("]\n");

    printf("Numero de comparacoes: %.0lf.\nNumero de movimentos: %.0lf.\nTempo de Execucao: %lf segundos.", *comparacoes, *movimentos, *tempoExec);
    free(vetor);
    return 0;
}

void BubbleSort(int *vetor, double *comparacoes, double *movimentos, double *tempoExec, int tamanho)
{
    clock_t inicio, fim;
    inicio = clock();
    int aux, troca = 1;
    for (int i = 0; i < tamanho && troca; i++)
    {
        troca = 0;
        for (int j = 0; j < tamanho - 1; j++)
        {
            (*comparacoes)++;
            if (vetor[j] > vetor[j + 1])
            {
                troca = 1;
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                (*movimentos)++;
            }
        }
    }
    fim = clock();
    *tempoExec = ((double)(fim - inicio) / CLOCKS_PER_SEC);
}