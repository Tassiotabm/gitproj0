#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo �rvore
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		4.00   fvc   23/08/2015 Mudan�a no m�dulo para operar com matrizes
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar Matrizes que armazenam listas duplamente encadeadas
*     A Matriz possui uma cabe�a que cont�m uma refer�ncia para a c�lula 1x1 da
*     matriz e outra para uma c�lula corrente da matriz.
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
               /* Estrutura da Matriz est� errada */

         MAT_CondRetMatrizNaoExiste = 2 ,
               /* �rvore n�o existe */

         MAT_CondRetFaltouMemoria = 3
               /* Faltou mem�ria ao alocar dados */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: MAT Criar Matriz
*
*  $ED Descri��o da fun��o
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
*  $FC Fun��o: MAT Criar Lista
*
*  $ED Descri��o da fun��o
*     Cria uma nova lista que ser� armazenada na matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

    MAT_tpCondRet MAT_CriarLista(LIS_tppLista * pLista);


/***********************************************************************
*
*  $FC Fun��o: MAT Destruir Matriz
*
*  $ED Descri��o da fun��o
*     Destr�i a lista atrelada a cada c�lula da matriz e a pr�pria matriz
*
*  $EP Par�metros
*		M	- Matriz que se deseja destruir.
*
*  $FV Valor retornado
*     MAT_CondRetOK - Destrui sem problemas
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( tppMatriz M ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Inserir Char Antes
*
*  $ED Descri��o da fun��o
*     Insere o char dado na lista que ser� ligada � c�lula da Matriz
*
*  $EP Par�metros
*     $P Valor - Char a ser inserido no novo n�.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirCharAntes( LIS_tppLista lista, char Valor ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Inserir Char Depois
*
*  $ED Descri��o da fun��o
*     Insere o char dado na lista que ser� ligada � c�lula da Matriz
*
*  $EP Par�metros
*     $P Valor - Char a ser inserido no novo n�.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirCharDepois( LIS_tppLista lista, char Valor ) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Obter Valor
*
*  $ED Descri��o da fun��o
*     Obtem o valor do char armazenado no n� corrente da lista
*
*  $EP Par�metros
*     $P Lista - Lista que se deseja obter o valor do n� corrente.
		 Valor - Vari�vel char passada por refer�ncia que receber� o valor do corrente
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValor( LIS_tppLista lista, char* valor) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Avan�ar posi��o

*  $ED Descri��o da fun��o
*     Avan�a a c�lula corrente da matriz para a sua c�lula correspondente a dire��o dada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErro - se n�o possui nenhuma c�lula na dire��o dada
*
***********************************************************************/

   MAT_tpCondRet MAT_Avancar( tppMatriz matriz, char* direcao ) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Inserir a lista na matriz especificada, na linha e coluna especificadas
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
*  $FC Fun��o: MAT Ir para o final da lista
*
*  $ED Descri��o da fun��o
*     Faz o n� corrente da lista do m�dulo matriz apontar para o final
*
*  $EP Par�metros
*     $P lista - A lista que se deseja mduar o n� corrente
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_IrFinal( LIS_tppLista lista ) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Ir Inicio
*
*  $ED Descri��o da fun��o
*      Faz o n� corrente da lista do m�dulo matriz apontar para o o n� de origem
*
*  $EP Par�metros
*     $P lista - A lista que se deseja mudar o n� corrente
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_IrInicio( LIS_tppLista lista ) ;

/***********************************************************************
*
*  $FC Fun��o: MAT  Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetErro		- se numElem for maior que o n�mero de vezes que se pode andar
*
***********************************************************************/

   MAT_tpCondRet MAT_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem );

/***********************************************************************
*
*  $FC Fun��o: MAT  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErro
*
***********************************************************************/

   MAT_tpCondRet MAT_ExcluirElemento( LIS_tppLista pLista ) ;

#undef MATRIZ_EXT

/********** Fim do m�dulo de defini��o: M�dulo Matriz **********/

#else
#endif
