/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 * Atualizado em 09/09/2025 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* aqui vem a struct racional propriamente dita, nao modifique! */
struct racional
{
  long num; /* numerador   */
  long den; /* denominador */
};

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
 */

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc(long a, long b)
{
  long aux;
  // Utiliza a função labs para retornar o valor absoluto de a e b.
  a = labs(a);
  b = labs(b);
  // Certifica-se de que o a seja maior do que o b.
  if (a < b)
  {
    aux = a;
    a = b;
    b = aux;
  }
  // Realiza a operação do algoritimo pegando o modulo da divisão do maior pelo menor, até o modulo ser 0.
  while (b > 0)
  {
    aux = a % b;
    a = b;
    b = aux;
  }
  return a;
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc(long a, long b)
{
  long m;
  m = (a * b) / mdc(a, b);
  return m;
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r(struct racional *r)
{
  long simp;
  // Primeiro verica se o numero é válido para poder ser simplificado.
  if (valido_r(r) && r != NULL)
  {
    simp = mdc(r->num, r->den);
    // Simplifica dividindo numerador e denominador pelo mdc guardado pela variável "simp".
    r->num = r->num / simp;
    r->den = r->den / simp;
    // Caso numerador e denominador sejam negativos retorna uma fração positiva.
    if ((r->num < 0) && (r->den < 0))
    {
      r->num = -r->num;
      r->den = -r->den;
    }
    else
    {
      // Caso somente o denominador seja negativo, inverte os sinais.
      if ((r->num > 0) && (r->den < 0))
      {
        r->num = -r->num;
        r->den = -r->den;
      }
    }
    return 1;
  }
  return 0;
}

/* implemente as demais funções de racional.h aqui */
long numerador_r(struct racional *r)
{
  long n;
  n = r->num;
  return n;
}

/* Retorna o denominador do racional r */
long denominador_r(struct racional *r)
{
  long d;
  d = r->den;
  return d;
}

/* Cria um número racional com o numerador e denominador indicados
 * e retorna um ponteiro que aponta para ele.
 * A memória para o número racional deve ser alocada dinamicamente
 * por esta função. Retorna NULL se não conseguiu alocar a memória. */
struct racional *cria_r(long numerador, long denominador)
{
  struct racional *r = malloc(sizeof(struct racional));
  if (!r)
    return NULL;
  r->num = numerador;
  r->den = denominador;
  return r;
}

/* Libera a memória alocada para o racional apontado por r */
void destroi_r(struct racional **r)
{
  free(r);
  r = NULL;
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. Um racional
 * é inválido se o denominador for zero ou se ele não tiver sido alocado. */
int valido_r(struct racional *r)
{
  int val = 0;
  if (r->den != 0 || !r)
    val = 1;
  return val;
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve estar na forma simplificada;
   - não use espacos em branco e não mude de linha;
   - o formato de saída deve ser "num/den", a menos dos casos abaixo;
     - se o ponteiro for nulo, imprime a mensagem "NULL";
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal é impresso antes do número;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r(struct racional *r)
{
  if (r != NULL)
  {
    if (!valido_r(r))
      printf("NaN");
    else
    {
      if ((r->num != 0) && (r->den != 1))
        printf("%ld/%ld", r->num, r->den);
      if ((r->den == 0) || (r->den == 1))
        printf("%ld", r->num);
    }
  }
  else
    printf("NULL");
}

struct racional iguala_r(struct racional r, long m)
{
  r.num = r.num * (m / r.den);
  r.den = m;
  return r;
}

/* Compara dois números racionais r1 e r2.
 * Retorna -2 se r1 ou r2 for inválido ou se o respectivo ponteiro for nulo.
 * Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2.
 * Atenção: faça a comparação normalizando os denominadores pelo MMC.
 * Fazer a comparação baseado na divisão do numerador pelo denominador
 * pode gerar erro de arredondamento e falsear o resultado. */
int compara_r(struct racional *r1, struct racional *r2)
{
  int m;
  struct racional rac1, rac2;
  if (!valido_r(r1) || !valido_r(r2))
    return -2;
  if (r1 == NULL || r2 == NULL)
    return -2;
  m = mmc(r1->den, r2->den);
  rac1 = iguala_r(*r1, m);
  rac2 = iguala_r(*r2, m);

  if (rac1.num < rac2.num)
    return -1;
  if (rac1.num == rac2.num)
    return 0;
  if (rac1.num > rac2.num)
    return 1;
}

/* Coloca em *r3 a soma simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int soma_r(struct racional *r1, struct racional *r2, struct racional *r3)
{

  long m;
  if ((!valido_r(r1)) || (!valido_r(r2)) || (r3 == NULL))
    return 0;
  // Verifica o mmc das frações para poder encontrar frações equivalentes com o mesmo denominador.
  m = mmc(r1->den, r2->den);
  iguala_r(*r1, m);
  iguala_r(*r2, m);

  // Realiza a soma dos numeradores.
  r3->num = r1->num + r2->num;
  r3->den = m;
  simplifica_r(r3);
  return 1;
}

/* Coloca em *r3 a diferença simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  long m;
  if (!valido_r(r1) || !valido_r(r2) || !r3)
    return 0;
  // Verifica o mmc das frações para poder encontrar frações equivalentes com o mesmo denominador.
  m = mmc(r1->den, r2->den);
  iguala_r(*r1, m);
  iguala_r(*r2, m);
  // Realiza a subtração dos numeradores e simplifica.
  r3->num = r1->num - r2->num;
  r3->den = m;
  simplifica_r(r3);
  return 1;
}

/* Coloca em *r3 o produto simplificado dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int multiplica_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  // Simplismente multiplica numerador por denominador e simplifica.
  r3->num = r1->num * r2->num;
  r3->den = r1->den * r2->den;
  simplifica_r(r3);
  return 0;
}

/* Coloca em *r3 a divisão simplificada do racional *r1 por *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int divide_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  r3->num = r1->num * r2->den;
  r3->den = r1->den * r2->num;
  simplifica_r(r3);
  return 0;
}
