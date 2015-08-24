/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Matriz
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
		4.00					Mudan�a no m�dulo para operar matrizes
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   "LISTA.H"

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do n� da Matriz
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoMatriz {

	     LIS_tppLista LIS ;
               /* N� da lista da Matriz */

         struct tgNoMatriz * N ;
               /* Ponteiro para o n� localizado a 0 graus do n� atual
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� est� localizado na �ltima coluna da matriz*/

         struct tgNoMatriz * NE ;
               /* Ponteiro para o n� localizado a 45 graus do n� atual
               *
               *$EED Assertivas estruturais
               *	� NULL sse o n� est� localizado na extremo canto superior direito da matriz*/

         struct tgNoMatriz * E ;
				/* Ponteiro para o n� localizado a 90 graus do n� atual

               *$EED Assertivas estruturais
               *   � NULL sse o n� est� localizado na primeira linha da matriz */

		 struct tgNoMatriz * SE ;
				/* Ponteiro para o n� localizado a 135 graus do n� atual

               *$EED Assertivas estruturais
               *   � NULL sse o n� est� localizado no extremo canto superior esquerdo da matriz */

		 struct tgNoMatriz * S ;
				/* Ponteiro para o n� localizado a 180 graus do n� atual

               *$EED Assertivas estruturais
               *   � NULL sse o n� est� localizado na primeira coluna da matriz*/

		 struct tgNoMatriz * SO ;
				/* Ponteiro para o n� localizado a 225 graus do n� atual

               *$EED Assertivas estruturais
               *   � NULL sse o n� est� localizado no extremo canto inferior esquerdo da matriz*/

		 struct tgNoMatriz * O ;
				/* Ponteiro para o n� localizado a 270 graus do n� atual

               *$EED Assertivas estruturais
               *   � NULL sse o n� est� localizado na ultima linha da matriz */

		 struct tgNoMatriz * NO ;
				/* Ponteiro para o n� localizado a 315 graus do n� atual

               *$EED Assertivas estruturais
               *   � NULL sse o n� est� localizado no extremo canto inferior direito da matriz */
		 
		 int linha;
			/* Inteiro que representa a linha na qual o n� est� localizado */

		 int coluna;
			/* Inteiro que representa a coluna na qual o n� est� localizado */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a da Matriz
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a �rvore em forma de co-rotina.
*
***********************************************************************/


   /*	Bolar uma estrutura para a matriz... vetor? lista de lista?
		Cada c�lula da matriz j� armazena uma lista, qual seria a funcionalidade da matriz?
			seria andar pelas c�lulas pois cada uma tem acesso aos seus adjacentes...
	*/

   typedef struct tgMatriz {

		int qtdLinha;
			/* Quantidade de linhas na matriz*/

		int qtdColuna;
			/* Quantidade de colunas na matriz*/

		struct tgNoMatriz * Origem;
			/* Ponteiro para a primeira c�lula da matriz*/

		struct tgNoMatriz * Corrente;
			/* Ponteiro para a c�lula corrente da lista */


   } tpMatriz ;

/*****  Dados encapsulados no m�dulo  *****/

      //static tpMatriz * pMatriz = NULL ;
            /* Ponteiro para a cabe�a da �rvore */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   //static tpNoMatriz * CriarNo( ) ;

   static void MAT_LiberaMatriz(tpNoMatriz ** Matriz);

  // static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ARV Criar �rvore
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
	   /* Criar cabe�a da matriz */
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
*  Fun��o: ARV Destruir Matriz
*  ****/

   void MAT_DestruirMatriz( tppMatriz M )
   {
	   MAT_LiberaMatriz(M);
	   free(&M);

   } /* Fim fun��o: ARV Destruir Matriz */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � esquerda
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

      /* Criar n� � esquerda de folha */

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

      /* Tratar n�o folha � esquerda */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � direita
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

      /* Criar n� � direita de folha */

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

      /* Tratar n�o folha � direita */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � direita */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� pai
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

   } /* Fim fun��o: ARV Ir para n� pai */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � esquerda
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

   } /* Fim fun��o: ARV Ir para n� � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � direita
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

   } /* Fim fun��o: ARV Ir para n� � direita */

/***************************************************************************
*
*  Fun��o: ARV Obter valor corrente
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

   } /* Fim fun��o: ARV Obter valor corrente */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� da �rvore
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
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

   } /* Fim fun��o: ARV Criar n� da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� raiz da �rvore
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
} /* Fim fun��o: ARV Criar n� raiz da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da �rvore
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

   } /* Fim fun��o: ARV Destruir a estrutura da �rvore */

/********** Fim do m�dulo de implementa��o: M�dulo �rvore **********/
