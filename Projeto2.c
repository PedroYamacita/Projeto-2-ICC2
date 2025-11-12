// Objetivo: implementar os diferentes algoritmos de sorting especificados
// e testá-los empiricamente complementando suas análises de complexidade teóricas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct infos
{
    double comparacoes;
    double movimentos;
    double tempoExec;
    clock_t inicio;
    clock_t fim;
} infos;

void swap(int *vetor, int i, int j);
void calcularTempo(infos *valores);

void BubbleSort(int *vetor, infos *valores, int tamanho);
void SelectionSort(int *vetor, infos *valores, int tamanho);
void InsertionSort(int *vetor, infos *valores, int tamanho);
void ShellSort(int *vetor, infos *valores, int tamanho);
void QuickSort(int *vetor, int inf, int sup, infos *valores);
void HeapSort();
void MergeSort();
void Contagem_Dos_Menores(int *vetor, infos *valores, int tamanho);
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

    printf("Escolha o metodo de ordenacao:\n1: BubbleSort.\n2: SelectionSort.\n3: InsertionSort.\n4: ShellSort.\n5: QuickSort.\n6: HeapSort.\n7: MergeSort.\n8: Contagem dos Menores.\n9: RadixSort.\n");

    scanf(" %d", &metodo);

    switch (metodo)
    {
    case 1:
        BubbleSort(vetor, valores, tamanho);
        break;
    case 2:
        SelectionSort(vetor, valores, tamanho);
        break;
    case 3:
        InsertionSort(vetor, valores, tamanho);
        break;
    case 4:
        ShellSort(vetor, valores, tamanho);
    case 5:
        valores->inicio = clock();
        QuickSort(vetor, 0, tamanho - 1, valores);
        calcularTempo(valores);
    /*case 6:
        HeapSort();
        break;
    case 7:
        MergeSort();
        break;*/
    case 8:
        Contagem_Dos_Menores(vetor, valores, tamanho);
        break;
    //case 9:
       // RadixSort();
        //break;
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

    printf("Numero de comparacoes: %.0lf.\nNumero de movimentos: %.0lf.\nTempo de Execucao: %lf segundos.\n", valores->comparacoes, valores->movimentos, valores->tempoExec);
    free(vetor);
    free(valores);
    return 0;
}

void swap(int *vetor, int i, int j)
{
    int aux;
    aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}
void calcularTempo(infos *valores)
{
    valores->fim = clock();
    valores->tempoExec = ((double)((valores->fim - valores->inicio) / CLOCKS_PER_SEC));
}

void BubbleSort(int *vetor, infos *valores, int tamanho)
{
    valores->inicio = clock();
    int troca = 1;
    for (int i = 0; i < tamanho && troca; i++)
    {
        troca = 0;
        for (int j = 0; j < tamanho - 1; j++)
        {
            valores->comparacoes++;
            if (vetor[j] > vetor[j + 1])
            {
                troca = 1;
                swap(vetor, j, j + 1);
                valores->movimentos++;
            }
        }
    }
    calcularTempo(valores);
}

void SelectionSort(int *vetor, infos *valores, int tamanho)
{
    valores->inicio = clock();
    int minimo;
    for (int i = 0; i < tamanho - 1; i++)
    {
        minimo = i;
        for (int j = i + 1; j < tamanho; j++)
        {
            valores->comparacoes++;
            if (vetor[j] < vetor[minimo])
            {
                minimo = j;
            }
        }
        if (i != minimo)
        {
            valores->movimentos++;
            swap(vetor, i, minimo);
        }
    }
    calcularTempo(valores);
}

void InsertionSort(int *vetor, infos *valores, int tamanho)
{
    valores->inicio = clock();
    int elemento, j;
    for (int i = 1; i < tamanho; i++)
    {
        elemento = vetor[i];
        for (j = i - 1; j >= 0 && elemento < vetor[j]; j--)
        {
            vetor[j + 1] = vetor[j];
            valores->movimentos++;
            valores->comparacoes++;
        }
        vetor[j + 1] = elemento;
        valores->comparacoes++;
        valores->movimentos++;
    }
    calcularTempo(valores);
}

void ShellSort(int *vetor, infos *valores, int tamanho)
{
    valores->inicio = clock();
    int numeroIncrementos = 0;
    int incrementos[32];
    for (int i = tamanho / 2; i >= 1; i /= 2)
    {
        incrementos[numeroIncrementos++] = i;
    }
    for (int j = 0; j < numeroIncrementos; j++)
    {
        int h = incrementos[j];

        for (int k = h; k < tamanho; k++)
        {
            int aux = vetor[k];
            int l = k;

            while (l >= h)
            {
                valores->comparacoes++;
                if (vetor[l - h] > aux)
                {
                    vetor[l] = vetor[l - h];
                    valores->movimentos++;
                    l -= h;
                }
                else
                {
                    break;
                }
            }
            if (l != k)
            {
                vetor[l] = aux;
                valores->movimentos++;
            }
        }
    }
    calcularTempo(valores);
}

void QuickSort(int *vetor, int inf, int sup, infos *valores)
{
    int meio = (inf + sup) / 2;
    int pivo;
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
        {
            j--;
            valores->comparacoes++;
        }
        if (i <= j)
        {
            swap(vetor, i, j);
            valores->movimentos++;
            i++;
            j--;
        }
    } while (i < j);
    if (j > inf)
        QuickSort(vetor, inf, j, valores);
    if (i < sup)
        QuickSort(vetor, i, sup, valores);
}

void Contagem_Dos_Menores(int *vetor, infos *valores, int tamanho){
    int *aux = (int *)calloc(tamanho, sizeof(int));
    int *aux2 = (int *)calloc(tamanho, sizeof(int));

    for(int i = 1; i < tamanho; i++){
        for(int j = i - 1; j >= 0; j--){
            valores->comparacoes++;
            if(vetor[i] < vetor[j]){
                aux[j]++;
            }
            else{
                aux[i]++;
            }
        }
    }
    for(int i = 0; i < tamanho; i++){
        valores->movimentos++;
        aux2[aux[i]] = vetor[i];
    }
    for(int i = 0; i < tamanho; i++){
        valores->movimentos++;
        vetor[i] = aux2[i];
    }
    free(aux);
    free(aux2);
}