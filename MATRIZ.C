/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
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
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   "LISTA.H"

#define ARVORE_OWNq
#include "MATRIZ.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da Matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoMatriz {

	     LIS_tppLista LIS ;
               /* Nó da lista da Matriz */

         struct tgNoMatriz * N ;
               /* Ponteiro para o nó localizado a 0 graus do nó atual
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó está localizado na última coluna da matriz*/

         struct tgNoMatriz * NE ;
               /* Ponteiro para o nó localizado a 45 graus do nó atual
               *
               *$EED Assertivas estruturais
               *	É NULL sse o nó está localizado na extremo canto superior direito da matriz*/

         struct tgNoMatriz * E ;
				/* Ponteiro para o nó localizado a 90 graus do nó atual

               *$EED Assertivas estruturais
               *   É NULL sse o nó está localizado na primeira linha da matriz */

		 struct tgNoMatriz * SE ;
				/* Ponteiro para o nó localizado a 135 graus do nó atual

               *$EED Assertivas estruturais
               *   É NULL sse o nó está localizado no extremo canto superior esquerdo da matriz */

		 struct tgNoMatriz * S ;
				/* Ponteiro para o nó localizado a 180 graus do nó atual

               *$EED Assertivas estruturais
               *   É NULL sse o nó está localizado na primeira coluna da matriz*/

		 struct tgNoMatriz * SO ;
				/* Ponteiro para o nó localizado a 225 graus do nó atual

               *$EED Assertivas estruturais
               *   É NULL sse o nó está localizado no extremo canto inferior esquerdo da matriz*/

		 struct tgNoMatriz * O ;
				/* Ponteiro para o nó localizado a 270 graus do nó atual

               *$EED Assertivas estruturais
               *   É NULL sse o nó está localizado na ultima linha da matriz */

		 struct tgNoMatriz * NO ;
				/* Ponteiro para o nó localizado a 315 graus do nó atual

               *$EED Assertivas estruturais
               *   É NULL sse o nó está localizado no extremo canto inferior direito da matriz */
		 
		 int linha;
			/* Inteiro que representa a linha na qual o nó está localizado */

		 int coluna;
			/* Inteiro que representa a coluna na qual o nó está localizado */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça da Matriz
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/


   /*	Bolar uma estrutura para a matriz... vetor? lista de lista?
		Cada célula da matriz já armazena uma lista, qual seria a funcionalidade da matriz?
			seria andar pelas células pois cada uma tem acesso aos seus adjacentes...
	*/

   typedef struct tgMatriz {

		int qtdLinha;
			/* Quantidade de linhas na matriz*/

		int qtdColuna;
			/* Quantidade de colunas na matriz*/

		struct tgNoMatriz * Origem;
			/* Ponteiro para a primeira célula da matriz*/

		struct tgNoMatriz * Corrente;
			/* Ponteiro para a célula corrente da lista */


   } tpMatriz ;

/*****  Dados encapsulados no módulo  *****/

      //static tpMatriz * pMatriz = NULL ;
            /* Ponteiro para a cabe‡a da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

   //static tpNoMatriz * CriarNo( ) ;

   static void MAT_LiberaMatriz(tpNoMatriz ** Matriz);

  // static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/
   MAT_tpCondRet MAT_CriarMatriz(int lin, int col, tppMatriz * M)
   {
	   int i,j;

	   struct tgNoMatriz *** Mat;

	   struct tgNoMatriz  * temp;

	   Mat = (tpNoMatriz***)malloc(lin*sizeof(tpNoMatriz**));

	   for(i = 0; i < col; i++)
	   {
		   Mat[i] = (tpNoMatriz**)malloc(col*sizeof(tpNoMatriz*));
	   }
	   for(i = 0; i < lin; i++)
	   {
		   for(j = 0; j < col; j++)
		   {
			   temp = (tgNoMatriz*)malloc(sizeof(tpNoMatriz));
			   Mat[i][j] = temp;
			   /*
			   M->Matriz[i][j].coluna = j;
			   M->Matriz[i][j].No = NULL;
			   M->Matriz[i][j].pNo0 = (j==n-1)? NULL : &M->Matriz[i][j+1];
			   M->Matriz[i][j].pNo45 = (i==0 || j==n-1)? NULL : &M->Matriz[i-1][j+1];
			   M->Matriz[i][j].pNo90 = (i==0)? NULL : &M->Matriz[i-1][j];
			   M->Matriz[i][j].pNo135 = (i==0 || j==0)? NULL : &M->Matriz[i-1][j-1];
			   M->Matriz[i][j].pNo180 = (j==0)? NULL : &M->Matriz[i][j-1];
			   M->Matriz[i][j].pNo225 = (i==n-1|| j==0)? NULL : &M->Matriz[i+1][j-1];
			   M->Matriz[i][j].pNo270 = (i==n-1)? NULL : &M->Matriz[i+1][j];
			   M->Matriz[i][j].pNo315 = (i==n-1 || j==n-1)? NULL : &M->Matriz[i+1][j+1];*/
		   }
	   }
	   for(i = 0; i < lin; i++)
	   {
		   for(j = 0; j < col; j++)
		   {
			   Mat[i][j]->E = (j==col-1)? NULL : Mat[i][j+1];
			   Mat[i][j]->SE = (i==0 || j==col-1)? NULL : Mat[i-1][j+1];
			   Mat[i][j]->S = (i==0)? NULL : Mat[i-1][j];
			   Mat[i][j]->SO = (i==0 || j==0)? NULL : Mat[i-1][j-1];
			   Mat[i][j]->O = (j==0)? NULL : Mat[i][j-1];
			   Mat[i][j]->NO = (i==lin-1|| j==0)? NULL : Mat[i+1][j-1];
			   Mat[i][j]->N = (i==lin-1)? NULL : Mat[i+1][j];
			   Mat[i][j]->NE = (i==lin-1 || j==col-1)? NULL : Mat[i+1][j+1];
		   }
	   }
	   /* Criar cabeça da matriz */
	   *M = (tppMatriz)malloc(sizeof(tpMatriz));
	   (*M)->Corrente = Mat[0][0];
	   (*M)->Origem = Mat[0][0];
	   (*M)->qtdColuna = col;
	   (*M)->qtdLinha = lin;
	   for(i = 0; i < lin; i++)
		   free(Mat[i]);
	   free(Mat);
	   return MAT_CondRetOK;
   }
/***************************************************************************
*
*  Função: ARV Destruir Matriz
*  ****/

   void MAT_DestruirMatriz( tppMatriz M )
   {
	   MAT_LiberaMatriz(M);
	   free(&M);

   } /* Fim função: ARV Destruir Matriz */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

   MAT_tpCondRet MATnserirEsquerda( char ValorParm )
   {

      MAT_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != MAT_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MAT_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return MAT_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   MAT_tpCondRet ARV_InserirDireita( char ValorParm )
   {

      MAT_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != MAT_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MAT_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return MAT_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   MAT_tpCondRet ARV_IrPai( void )
   {

      if ( pArvore == NULL )
      {
         return MAT_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return MAT_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return MAT_CondRetOK ;
      } else {
         return MAT_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   MAT_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pArvore == NULL )
      {
         return MAT_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return MAT_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return MAT_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return MAT_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   MAT_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pArvore == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return MAT_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return MAT_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return MAT_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   MAT_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return MAT_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return MAT_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Valor ;

      return MAT_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoCriouRaiz
*
***********************************************************************/

   void MAT_LiberaMatriz(tpNoMatriz ** Matriz, int n)
   {
		int i;
		for(i=0; i < n; i++)
		{
			free(Matriz[i]);
		}
	free(Matriz);
} /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: ARV Destruir a estrutura da árvore */

/********** Fim do módulo de implementação: Módulo árvore **********/

