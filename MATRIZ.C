/***************************************************************************
*  $MCI Módulo de implementação: Módulo Matriz
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
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
		4.00					Mudança no módulo para operar matrizes
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
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
*  $TC Tipo de dados: ARV Descritor do nó da Matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgCelulaMatriz {

	     LIS_tppLista lista ;
               /* Nó da lista da Matriz */

         struct tgCelulaMatriz * N ;
               /* Ponteiro para a célula localizado ao Norte  da célula atual
               *
               *$EED Assertivas estruturais
               *   É NULL sse a célula está localizado na última coluna da matriz*/

         struct tgCelulaMatriz * NE ;
               /* Ponteiro para a célula localizado a Nordeste da célula atual
               *
               *$EED Assertivas estruturais
               *	É NULL sse a célula está localizado na extremo canto superior direito da matriz*/

         struct tgCelulaMatriz * E ;
				/* Ponteiro para a célula localizado a 9o Leste da célula atual

               *$EED Assertivas estruturais
               *   É NULL sse a célula está localizado na primeira linha da matriz */

		 struct tgCelulaMatriz * SE ;
				/* Ponteiro para a célula localizado ao Sudeste da célula atual

               *$EED Assertivas estruturais
               *   É NULL sse a célula está localizado no extremo canto superior esquerdo da matriz */

		 struct tgCelulaMatriz * S ;
				/* Ponteiro para a célula localizado ao SUl da célula atual

               *$EED Assertivas estruturais
               *   É NULL sse a célula está localizado na primeira coluna da matriz*/

		 struct tgCelulaMatriz * SO ;
				/* Ponteiro para a célula localizado ao Sudoeste da célula atual

               *$EED Assertivas estruturais
               *   É NULL sse a célula está localizado no extremo canto inferior esquerdo da matriz*/

		 struct tgCelulaMatriz * O ;
				/* Ponteiro para a célula localizado ao Oeste da célula atual

               *$EED Assertivas estruturais
               *   É NULL sse a célula está localizado na ultima linha da matriz */

		 struct tgCelulaMatriz * NO ;
				/* Ponteiro para a célula localizado ao Noroeste da célula atual

               *$EED Assertivas estruturais
               *   É NULL sse a célula está localizado no extremo canto inferior direito da matriz */
		 
		 int linha;
			/* Inteiro que representa a linha na qual a célula está localizado */

		 int coluna;
			/* Inteiro que representa a coluna na qual a célula está localizado */

   } tpCelulaMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça da Matriz
*
*
*  $ED Descrição do tipo
*	Tipo Cabeça de Matriz é o tipo estruturado para acessar a quantidade de linhas 
	e colunas da matriz, um ponteiro para a célula origem (linha 1 x coluna 1)
	e ponteiro para uma célula corrente
	
*
***********************************************************************/

   typedef struct tgMatriz {

		int qtdLinha;
			/* Quantidade de linhas na matriz*/

		int qtdColuna;
			/* Quantidade de colunas na matriz*/

		struct tgCelulaMatriz * Origem;
			/* Ponteiro para a primeira célula da matriz*/

		struct tgCelulaMatriz * Corrente;
			/* Ponteiro para a célula corrente da lista */

		LIS_tppLista listaAux ;
		

   } tpMatriz ;

/*****  Dados encapsulados no módulo  *****/


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar Matriz
*  ****/
   MAT_tpCondRet MAT_CriarMatriz(int lin, int col, tppMatriz * M)
   {
	   int i,j;

	   struct tgCelulaMatriz *** Mat;

	   struct tgCelulaMatriz  * temp;

	   Mat = (tpCelulaMatriz***)malloc(lin*sizeof(tpCelulaMatriz**));

	   for(i = 0; i < col; i++)
	   {
		   Mat[i] = (tpCelulaMatriz**)malloc(col*sizeof(tpCelulaMatriz*));
	   }
	   for(i = 0; i < lin; i++)
	   {
		   for(j = 0; j < col; j++)
		   {
			   temp = (tgCelulaMatriz*)malloc(sizeof(tpCelulaMatriz));
			   Mat[i][j] = temp;
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
	   (*M)->listaAux = LIS_CriarLista( );
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
   }
/***************************************************************************
*
*  Função: MAT Destruir Matriz
*  ****/

   void MAT_DestruirMatriz( tppMatriz M )
   {
	   int i, j;
	   int tam = (M->qtdLinha) * (M->qtdColuna) ;
	   struct tgCelulaMatriz * cel;
	   IrInicioLista(M->listaAux);
	   cel = (struct tgCelulaMatriz*)LIS_ObterValor(M->listaAux);
	   for( i = 0; i < tam ; i++)
	   {
		   cel->N = NULL;
		   cel->NE = NULL;
		   cel->E = NULL;
		   cel->SE = NULL;
		   cel->S = NULL;
		   cel->SO = NULL;
		   cel->O = NULL;
		   cel->NO = NULL;
		   LIS_DestruirLista(cel->lista);
		   free(cel);
		   LIS_AvancarElementoCorrente(M->listaAux, 1);
	   }
	    LIS_DestruirLista(M->listaAux);
		free(M);

   } /* Fim função: MAT Destruir Matriz */

/***************************************************************************
*
*  Função: MAT Inserir Char Depois do Corrente
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

} /* Fim função: MAT Inserir Char Depois do Corrente */

/***************************************************************************
*
*  Função: MAT Inserir Char Antes do Corrente
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

} /* Fim função: MAT Inserir Char Antes do Corrente */

/***************************************************************************
*
*  Função: MAT Obter Valor da lista
*  ****/

  MAT_tpCondRet MAT_ObterValor( LIS_tppLista lista, char* valor)
  {
	 valor = (char*)LIS_ObterValor( lista );

	 return MAT_CondRetOK;
  }

/***************************************************************************
*
*  Função: MAT Avançar célula corrente
*  ****/

   MAT_tpCondRet MAT_Avancar( tppMatriz matriz, char* direcao )
   {
	   /* fazer um switch case
			case (strcmp("Norte", direcao))
				matriz->corrente->origem = matriz->corrente->N
				...
				...
				...
		*/
	   return MAT_CondRetOK;
   }

/***************************************************************************
*
*  Função: MAT INserir lista na célula da matriz
*  ****/

   MAT_tpCondRet MAT_InserirLista( tppMatriz matriz, LIS_tppLista pLista, int linha, int coluna )
   {
	   return MAT_CondRetOK;
   }

/***************************************************************************
*
*  Função: ARMAT Ir final da lista
*  ****/

  MAT_tpCondRet MAT_IrFinal( LIS_tppLista lista )
  {
	 IrFinalLista( lista );

	 return MAT_CondRetOK;
  }

/***************************************************************************
*
*  Função: MAT Ir inicio da lista
*  ****/

  MAT_tpCondRet MAT_IrInicio( LIS_tppLista lista )
  {
	 IrInicioLista( lista );

	 return MAT_CondRetOK;
  }


MAT_tpCondRet MAT_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
{
	if(LIS_AvancarElementoCorrente( pLista , numElem )!=LIS_CondRetOK)
		return MAT_CondRetErro;

	return MAT_CondRetOK;
}

 MAT_tpCondRet MAT_ExcluirElemento( LIS_tppLista pLista )
 {
	 if(LIS_ExcluirElemento( pLista )!=LIS_CondRetOK)
		 return MAT_CondRetErro;

	 return MAT_CondRetOK;

}

/********** Fim do módulo de implementação: Módulo árvore **********/

