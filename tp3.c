/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */
void le_vet(struct racional **vet, int n)
{
  long numerador, denominador;
  for (int i = 0; i < n; i++)
  {
    scanf("%ld", &numerador);
    scanf("%ld", &denominador);
    vet[i] = cria_r(numerador, denominador);
  }
}

void troca_nan(struct racional **vet, int n)
{
  struct racional *aux;
  for (int i = 0; i < n; i++)
  {
    int tam = n;
    // Compara o primeiro índice do vetor com o último para ver se algum deles é inválido
    if (compara_r(vet[i], vet[tam - 1]) == -2)
    {
      // Verifica se on primeiro é pivô é inválido, se for ele troca o número do pivo com o último número válido do vetor
      if (!valido_r(vet[i]))
      {
        /*Entra em looping para se certificar de pegar o primeiro válido de trás para frente
          a condição de parada é se ele encontrar o número válido ou chegar no pivô (que significa q não existe número válido depois dele);
          "tam - 1" representa o índice do ultimo número válido*/
        while (!valido_r(vet[tam - 1]) && (tam - 1 > i))
          tam--;
        // Se saiu do loop com o indice do número valido maior do que o do pivô, então ele troca eles de lugar
        if (i < tam - 1)
        {
          aux = vet[i];
          vet[i] = vet[tam - 1];
          vet[tam - 1] = aux;
        }
      }
    }
  }
}

void elimina_nan(struct racional **vet, int *n)
{
  for (int i = *n - 1; i >= 0; i--)
  {
    if (!valido_r(vet[i]))
    {

      destroi_r(vet[i]);
      vet[i] = NULL;
      (*n)--;
    }
  }
}

void ordena_vet(struct racional **vet, int n)
{
  struct racional *aux;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      /*chama a função compara_r para verificar se o número no indice i do vetor é maior que o do indice j,
        se for então ele troca os endereços de lugar*/
      if ((compara_r(vet[i], vet[j])) == 1)
      {
        aux = vet[j];
        vet[j] = vet[i];
        vet[i] = aux;
      }
    }
  }
}

/* programa principal */
int main()
{
  /* a completar! */

  return 0;
}
