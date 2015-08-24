#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo árvore
*
*  Arquivo gerado:              ARVORE.H
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar árvores binárias.
*     A árvore possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     A cada momento o módulo admite no máximo uma única árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     A árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a árvore estiver vazia.
*
***************************************************************************/
 
#if defined( ARVORE_OWN )
   #define ARVORE_EXT
#else
   #define ARVORE_EXT extern
#endif

#include "LISTA.H"

typedef struct tgMatriz * tppMatriz;
/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
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
*
***********************************************************************/

   void ARV_DestruirMatriz( tppMatriz matriz ) ;


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

   MAT_tpCondRet MAT_InserirLista( tppMatriz matriz, int linha, int coluna ) ;


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

#undef ARVORE_EXT

/********** Fim do módulo de definição: Módulo Matriz **********/

#else
#endif
