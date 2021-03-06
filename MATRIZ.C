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
*			fvc - Felipe Vieira C�rtes
*			tbm - T�ssio Borges de Miranda
*			db  - Daniela Braz�o
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		4.00   fvc	 28/08/2015	Mudan�a no m�dulo para operar matrizes
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es do m�dulo Matriz.
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>
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

   typedef struct tgCelulaMatriz {

	     LIS_tppLista lista ;
               /* N� da lista da Matriz */

         struct tgCelulaMatriz * N ;
               /* Ponteiro para a c�lula localizado ao Norte  da c�lula atual
               *
               *$EED Assertivas estruturais
               *   � NULL sse a c�lula est� localizado na �ltima coluna da matriz*/

         struct tgCelulaMatriz * NE ;
               /* Ponteiro para a c�lula localizado a Nordeste da c�lula atual
               *
               *$EED Assertivas estruturais
               *	� NULL sse a c�lula est� localizado na extremo canto superior direito da matriz*/

         struct tgCelulaMatriz * E ;
				/* Ponteiro para a c�lula localizado a 9o Leste da c�lula atual

               *$EED Assertivas estruturais
               *   � NULL sse a c�lula est� localizado na primeira linha da matriz */

		 struct tgCelulaMatriz * SE ;
				/* Ponteiro para a c�lula localizado ao Sudeste da c�lula atual

               *$EED Assertivas estruturais
               *   � NULL sse a c�lula est� localizado no extremo canto superior esquerdo da matriz */

		 struct tgCelulaMatriz * S ;
				/* Ponteiro para a c�lula localizado ao SUl da c�lula atual

               *$EED Assertivas estruturais
               *   � NULL sse a c�lula est� localizado na primeira coluna da matriz*/

		 struct tgCelulaMatriz * SO ;
				/* Ponteiro para a c�lula localizado ao Sudoeste da c�lula atual

               *$EED Assertivas estruturais
               *   � NULL sse a c�lula est� localizado no extremo canto inferior esquerdo da matriz*/

		 struct tgCelulaMatriz * O ;
				/* Ponteiro para a c�lula localizado ao Oeste da c�lula atual

               *$EED Assertivas estruturais
               *   � NULL sse a c�lula est� localizado na ultima linha da matriz */

		 struct tgCelulaMatriz * NO ;
				/* Ponteiro para a c�lula localizado ao Noroeste da c�lula atual

               *$EED Assertivas estruturais
               *   � NULL sse a c�lula est� localizado no extremo canto inferior direito da matriz */
		 
		 int linha;
			/* Inteiro que representa a linha na qual a c�lula est� localizado */

		 int coluna;
			/* Inteiro que representa a coluna na qual a c�lula est� localizado */

   } tpCelulaMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabe�a da Matriz
*
*
*  $ED Descri��o do tipo
*	Tipo Cabe�a de Matriz � o tipo estruturado para acessar a quantidade de linhas 
	e colunas da matriz, um ponteiro para a c�lula origem (linha 1 x coluna 1)
	e ponteiro para uma c�lula corrente
	
*
***********************************************************************/

   typedef struct tgMatriz {

		int qtdLinha;
			/* Quantidade de linhas na matriz*/

		int qtdColuna;
			/* Quantidade de colunas na matriz*/

		struct tgCelulaMatriz * Origem;
			/* Ponteiro para a primeira c�lula da matriz*/

		struct tgCelulaMatriz * Corrente;
			/* Ponteiro para a c�lula corrente da lista */

		LIS_tppLista listaAux ;
		

   } tpMatriz ;

/*****  Dados encapsulados no m�dulo  *****/


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: MAT Criar Matriz
*  ****/
   MAT_tpCondRet MAT_CriarMatriz(int lin, int col, tppMatriz * M)
   {
	   int i,j;

	   struct tgCelulaMatriz *** Mat;

	   struct tgCelulaMatriz  * temp;

	   	   /* checa a dimens�o da matriz */
	   if(lin < 0 || col < 0)
		   return MAT_CondRetErro;

	   Mat = (tpCelulaMatriz***)malloc(lin*sizeof(tpCelulaMatriz**));

	   for(i = 0; i < lin; i++)
	   {
		   Mat[i] = (tpCelulaMatriz**)malloc(col*sizeof(tpCelulaMatriz*));
	   }
	   for(i = 0; i < lin; i++)
	   {
		   for(j = 0; j < col; j++)
		   {
			   temp = (tpCelulaMatriz*)malloc(sizeof(tpCelulaMatriz));
			   Mat[i][j] = temp;
		   }
	   }
	   for(i = 0; i < lin; i++)
	   {
		   for(j = 0; j < col; j++)
		   {
			   Mat[i][j]->E = (j==col-1)? NULL : Mat[i][j+1];
			   Mat[i][j]->SE = (i==lin-1 || j==col-1)? NULL : Mat[i+1][j+1];
			   Mat[i][j]->S = (i==lin-1)? NULL : Mat[i+1][j];
			   Mat[i][j]->SO = (i==lin-1 || j==0)? NULL : Mat[i+1][j-1];
			   Mat[i][j]->O = (j==0)? NULL : Mat[i][j-1];
			   Mat[i][j]->NO = (i==0 || j==0)? NULL : Mat[i-1][j-1];
			   Mat[i][j]->N = (i==0)? NULL : Mat[i-1][j];
			   Mat[i][j]->NE = (i==0 || j==col-1)? NULL : Mat[i-1][j+1];
			   Mat[i][j]->coluna = j+1;
			   Mat[i][j]->linha = i+1;
			   Mat[i][j]->lista = NULL;
		   }
	   }

	   /* Criar cabe�a da matriz */
	   *M = (tppMatriz)malloc(sizeof(tpMatriz));
	   (*M)->Corrente = Mat[0][0];
	   (*M)->Origem = Mat[0][0];
	   (*M)->qtdColuna = col;
	   (*M)->qtdLinha = lin;
	   (*M)->listaAux = LIS_CriarLista(NULL);
	   for(i = 0; i < lin; i++)
	   {
		   for(j=0; j < col; j++)
		   {
			   LIS_InserirElementoApos((*M)->listaAux, Mat[i][j]);
		   }
	   }
	   for(i = 0; i < lin; i++)
		   free(Mat[i]);
	   free(Mat);
	   return MAT_CondRetOK;
   } /* Fim fun��o: MAT Criar Matriz */

/***************************************************************************
*
*  Fun��o: MAT Destruir Matriz
*  ****/

   MAT_tpCondRet MAT_DestruirMatriz( tppMatriz M )
   {
	   int i;
	   int tam = (M->qtdLinha) * (M->qtdColuna) ;
	   struct tgCelulaMatriz * cel;
	   IrInicioLista(M->listaAux);
	   for( i = 0; i < tam ; i++)
	   {
		   cel = (struct tgCelulaMatriz*)LIS_ObterValor(M->listaAux);
		   cel->N = NULL;
		   cel->NE = NULL;
		   cel->E = NULL;
		   cel->SE = NULL;
		   cel->S = NULL;
		   cel->SO = NULL;
		   cel->O = NULL;
		   cel->NO = NULL;

		   if(cel->lista != NULL)
				LIS_DestruirLista(cel->lista);

		   free(cel);
		   LIS_AvancarElementoCorrente(M->listaAux, 1);
	   }
	    LIS_DestruirLista(M->listaAux);
		free(M);

		return MAT_CondRetOK;

   } /* Fim fun��o: MAT Destruir Matriz */

MAT_tpCondRet MAT_CriarLista(LIS_tppLista * pLista)
{
	*pLista = LIS_CriarLista(NULL);

	return MAT_CondRetOK;
}


/***************************************************************************
*
*  Fun��o: MAT Inserir Char Depois do Corrente
*  ****/

 MAT_tpCondRet MAT_InserirCharDepois( LIS_tppLista lista, char Valor )
{
	char * c = (char*)malloc(1);
	if(c == NULL)
		return MAT_CondRetFaltouMemoria;
	*c = Valor;
	if(LIS_InserirElementoApos(lista, c)!= LIS_CondRetOK)
		return MAT_CondRetErro;

	return MAT_CondRetOK;

} /* Fim fun��o: MAT Inserir Char Depois do Corrente */

/***************************************************************************
*
*  Fun��o: MAT Inserir Char Antes do Corrente
*  ****/

 MAT_tpCondRet MAT_InserirCharAntes( LIS_tppLista lista, char Valor )
{
	char * c = (char*)malloc(1);
	if(c == NULL)
		return MAT_CondRetFaltouMemoria;
	*c = Valor;
	if(LIS_InserirElementoAntes(lista, c)!= LIS_CondRetOK)
		return MAT_CondRetErro;

	return MAT_CondRetOK;

} /* Fim fun��o: MAT Inserir Char Antes do Corrente */

/***************************************************************************
*
*  Fun��o: MAT Obter Valor da lista
*  ****/

  MAT_tpCondRet MAT_ObterValor( LIS_tppLista lista, char* valor)
  {
	  char * o;
	 o = (char*)LIS_ObterValor( lista );
	 *valor = *o;

	 return MAT_CondRetOK;
  } /* Fim fun��o: MAT Obter Valor da lista */

/***************************************************************************
*
*  Fun��o: MAT Avan�ar c�lula corrente
*  ****/

   MAT_tpCondRet MAT_Avancar( tppMatriz matriz, char* direcao )
   {
	   if(strcmp("Norte", direcao) == 0)
	   {
		   if(matriz->Corrente->N == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->N;
	   }
	   else if(strcmp("Nordeste", direcao) == 0)
	   {
		   if(matriz->Corrente->NE == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->NE;
	   }
	   else if(strcmp("Leste", direcao) == 0)
	   {
		   if(matriz->Corrente->E == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->E;
	   }
	   else if(strcmp("Sudeste", direcao) == 0)
	   {
		   if(matriz->Corrente->SE == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->SE;
	   }
	   else if(strcmp("Sul", direcao) == 0)
	   {
		   if(matriz->Corrente->S == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->S;
	   }
	   else if(strcmp("Sudoeste", direcao) == 0)
	   {
		   if(matriz->Corrente->SO == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->SO;
	   }
	   else if(strcmp("Oeste", direcao) == 0)
	   {
		   if(matriz->Corrente->O == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->O;
	   }
	   else if(strcmp("Noroeste", direcao) == 0)
	   {
		   if(matriz->Corrente->NO == NULL)
			   return MAT_CondRetErro;
		   matriz->Corrente = matriz->Corrente->NO;
	   }

	   return MAT_CondRetOK;
   } /* Fim fun��o: MAT Avan�ar c�lula corrente */

/***************************************************************************
*
*  Fun��o: MAT INserir lista na c�lula da matriz
*  ****/

   MAT_tpCondRet MAT_InserirLista( tppMatriz matriz, LIS_tppLista pLista, int linha, int coluna )
   {
	   int i = matriz->qtdLinha, j = matriz->qtdColuna;
	   /* calculo para descobrir a posi��o do elemento que se deseja obter na lista auxiliar
		  dependendo da linha e coluna desejada */
	   int avancar = j*linha - ( j - coluna ); 
	   tpCelulaMatriz * cel;
	   IrInicioLista(matriz->listaAux);
	   LIS_AvancarElementoCorrente(matriz->listaAux, avancar - 1);
	   cel = (tpCelulaMatriz*)LIS_ObterValor(matriz->listaAux);

	   if(cel->lista != NULL)
		   return MAT_CondRetErro;

	   cel->lista = pLista;

	   return MAT_CondRetOK;
   } /* Fim fun��o: MAT INserir lista na c�lula da matriz */

/***************************************************************************
*
*  Fun��o: MAT Ir final da lista
*  ****/

  MAT_tpCondRet MAT_IrFinal( LIS_tppLista lista )
  {
	 IrFinalLista( lista );

	 return MAT_CondRetOK;
  } /* Fim fun��o:  MAT Ir final da lista */

/***************************************************************************
*
*  Fun��o: MAT Ir inicio da lista
*  ****/

  MAT_tpCondRet MAT_IrInicio( LIS_tppLista lista )
  {
	 IrInicioLista( lista );

	 return MAT_CondRetOK;
  } /* Fim fun��o:  MAT Ir inicio da lista */

  /***************************************************************************
  *
  *  Fun��o: MAT Avancar o elemento corrente da lista
  *  ****/
MAT_tpCondRet MAT_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
{
	if(LIS_AvancarElementoCorrente( pLista , numElem )!=LIS_CondRetOK)
		return MAT_CondRetErro;

	return MAT_CondRetOK;
} /* Fim fun��o:  MAT Avancar o elemento corrente da lista */

/***************************************************************************
*
*  Fun��o: MAT Excluir o elemento da lista
*  ****/
 MAT_tpCondRet MAT_ExcluirElemento( LIS_tppLista pLista )
 {
	 if(LIS_ExcluirElemento( pLista )!=LIS_CondRetOK)
		 return MAT_CondRetErro;

	 return MAT_CondRetOK;

} /* Fim fun��o:  MATExcluir o elemento da lista */

/********** Fim do m�dulo de implementa��o: M�dulo Matriz **********/

