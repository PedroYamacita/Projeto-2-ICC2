#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct infos
{
    double comparacoes;
    double movimentos;
    double tempoExec;
} infos;

void BubbleSort(int *vetor, infos *valores, int tamanho);
void SelectionSort();
void InserctionSort();
void ShellShort();
void QuickSort(int *vetor, int inf, int sup, infos *valores);
void HeapSort();
void MergeSort();
void Contagem_Dos_Menores();
void RadixSort();

int main()
{
    int tamanho, metodo, tamanhoEscolhido, estadoInicial;
    infos *valores = (infos *)malloc(1 * sizeof(infos));
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
        BubbleSort(vetor, valores, tamanho);
        break;
    case 5:
        clock_t inicio, fim;
        inicio = clock();
        QuickSort(vetor, 0, tamanho - 1, valores);
        fim = clock();
        valores->tempoExec = ((double)(fim - inicio / CLOCKS_PER_SEC));
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

    printf("Numero de comparacoes: %.0lf.\nNumero de movimentos: %.0lf.\nTempo de Execucao: %lf segundos.", valores->comparacoes, valores->movimentos, valores->tempoExec);
    free(vetor);
    free(valores);
    return 0;
}

void BubbleSort(int *vetor, infos *valores, int tamanho)
{
    clock_t inicio, fim;
    inicio = clock();
    int aux, troca = 1;
    for (int i = 0; i < tamanho && troca; i++)
    {
        troca = 0;
        for (int j = 0; j < tamanho - 1; j++)
        {
            valores->comparacoes++;
            if (vetor[j] > vetor[j + 1])
            {
                troca = 1;
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                valores->movimentos++;
            }
        }
    }
    fim = clock();
    valores->tempoExec = ((double)(fim - inicio) / CLOCKS_PER_SEC);
}

void QuickSort(int *vetor, int inf, int sup, infos *valores)
{
    int meio = (inf + sup) / 2;
    int pivo, aux;
    if (vetor[inf] < vetor[meio] && vetor[meio] < vetor[sup])
    {
        valores->comparacoes += 2;
        pivo = vetor[meio];
    }
    else if (vetor[meio] < vetor[inf] && vetor[inf] < vetor[sup])
    {
        valores->comparacoes += 4;
        pivo = vetor[inf];
    }
    else
    {
        valores->comparacoes += 4;
        pivo = vetor[sup];
    }
    int i = inf;
    int j = sup;

    do
    {
        while (vetor[i] < pivo)
        {
            i++;
            valores->comparacoes++;
        }
        while (vetor[j] > pivo)
            j--;
        if (i <= j)
        {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    } while (i < j);
    if (j > inf)
        QuickSort(vetor, inf, j, valores);
    if (i < sup)
        QuickSort(vetor, i, sup, valores);
}