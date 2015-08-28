#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo árvore
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			fvc - Felipe Vieira Cortes
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		4.00   fvc   23/08/2015 Mudança no módulo para operar com matrizes
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar Matrizes que armazenam listas duplamente encadeadas
*     A Matriz possui uma cabeça que contém uma referência para a célula 1x1 da
*     matriz e outra para uma célula corrente da matriz.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

#include "LISTA.H"

typedef struct tgMatriz * tppMatriz;
/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetErro = 1 ,
               /* Estrutura da Matriz está errada */

         MAT_CondRetMatrizNaoExiste = 2 ,
               /* Árvore não existe */

         MAT_CondRetFaltouMemoria = 3
               /* Faltou memória ao alocar dados */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar Matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

    MAT_tpCondRet MAT_CriarMatriz(int lin, int col, tppMatriz * M);

/***********************************************************************
*
*  $FC Função: MAT Criar Lista
*
*  $ED Descrição da função
*     Cria uma nova lista que será armazenada na matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

    MAT_tpCondRet MAT_CriarLista(LIS_tppLista * pLista);


/***********************************************************************
*
*  $FC Função: MAT Destruir Matriz
*
*  $ED Descrição da função
*     Destrói a lista atrelada a cada célula da matriz e a própria matriz
*
*  $EP Parâmetros
*		M	- Matriz que se deseja destruir.
*
*  $FV Valor retornado
*     MAT_CondRetOK - Destrui sem problemas
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( tppMatriz M ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir Char Antes
*
*  $ED Descrição da função
*     Insere o char dado na lista que será ligada à célula da Matriz
*
*  $EP Parâmetros
*     $P Valor - Char a ser inserido no novo nó.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirCharAntes( LIS_tppLista lista, char Valor ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir Char Depois
*
*  $ED Descrição da função
*     Insere o char dado na lista que será ligada à célula da Matriz
*
*  $EP Parâmetros
*     $P Valor - Char a ser inserido no novo nó.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirCharDepois( LIS_tppLista lista, char Valor ) ;

/***********************************************************************
*
*  $FC Função: MAT Obter Valor
*
*  $ED Descrição da função
*     Obtem o valor do char armazenado no nó corrente da lista
*
*  $EP Parâmetros
*     $P Lista - Lista que se deseja obter o valor do nó corrente.
		 Valor - Variável char passada por referência que receberá o valor do corrente
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValor( LIS_tppLista lista, char* valor) ;

/***********************************************************************
*
*  $FC Função: MAT Avançar posição

*  $ED Descrição da função
*     Avança a célula corrente da matriz para a sua célula correspondente a direção dada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErro - se não possui nenhuma célula na direção dada
*
***********************************************************************/

   MAT_tpCondRet MAT_Avancar( tppMatriz matriz, char* direcao ) ;

/***********************************************************************
*
*  $FC Função: MAT Inserir a lista na matriz especificada, na linha e coluna especificadas
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirLista( tppMatriz matriz, LIS_tppLista pLista, int linha, int coluna ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para o final da lista
*
*  $ED Descrição da função
*     Faz o nó corrente da lista do módulo matriz apontar para o final
*
*  $EP Parâmetros
*     $P lista - A lista que se deseja mduar o nó corrente
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_IrFinal( LIS_tppLista lista ) ;

/***********************************************************************
*
*  $FC Função: MAT Ir Inicio
*
*  $ED Descrição da função
*      Faz o nó corrente da lista do módulo matriz apontar para o o nó de origem
*
*  $EP Parâmetros
*     $P lista - A lista que se deseja mudar o nó corrente
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_IrInicio( LIS_tppLista lista ) ;

/***********************************************************************
*
*  $FC Função: MAT  Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetErro		- se numElem for maior que o número de vezes que se pode andar
*
***********************************************************************/

   MAT_tpCondRet MAT_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem );

/***********************************************************************
*
*  $FC Função: MAT  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_ExcluirElemento( LIS_tppLista pLista ) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo Matriz **********/

#else
#endif
