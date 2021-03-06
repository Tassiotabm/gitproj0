/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico

*	M�dulo modificado para operar matrizes que armazenam listas!
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TMAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
			fvc	- Felipe Vieira Cortes
*			tbm - T�ssio Borges de Miranda
*			db  - Daniela Braz�o
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
		4.00   fvc	 23/08/2015 M�dulo modificado para operar matrizes
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo Matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo Matriz:
*
*     =criarmatriz		<inxmat>	<linha>		<coluna>	<CondRet> - Chama a fun��o MAT_CriarMatriz( linha, coluna, vtMatriz[inxmat])
*	  =criarlista		<CondRet>									  - Chama a fun��o MAT_CriarLista( lista )
*     =avancar			<Dire��o>	<inxmat>	<CondRet>			  - Chama a fun��o MAT_Avancar(vtMatriz[inxmat], direcao )
*																		e avan�a a c�lula corrente da matriz de acordo com a dire��o dada.
																		as dire��es s�o: norte, nordeste, leste, sudeste, sul, sudoeste, oeste e noroeste
*     =inscharantes"	<Char>		<CondRet>						  - Chama a fun��o MAT_InserirCharAntes( lista ) e insere o char na posi��o posterior ao corrente
*     =inschardepois"	<Char>		<CondRet>						  - Chama a fun��o MAT_InserirCharDepois( lista ) e insere o char na posi��o anterior ao corrente
*     "=inslista"		<inxmat>	<linha>		<coluna>	<CondRet> - chama a fun��o MAT_InserirLista(vtMatriz[inxmat], linha, coluna )
																		e insere a lista na posi��o linhaXcoluna da matriz
*     "=excluirelem"    <CondRet>									  - Chama a fun��o MAT_ExcluirElemento( lista ) e exclui o elemento corrente da lista
*     "=irinicio"		<CondRet>									  - chama a fun��o MAT_IrInicio( lista )
*     "=irfinal"		<CondRet>									  - chama a fun��o MAT_IrIFinal( lista )
*     "=obtervalorelem" <Char>		<CondRet>						  - Chama a fun��o  MAT_ObterValor( lista, charRecebido )
																		e compara o charRecebido com o valor <Char>
*     "=avancarelem"	<numElem>	<CondRet>					 	  - chama a fun��o MAT_AvancarElementoCorrente( lista, numElem )
*
*	  "=destruirmatriz" <inxmat>	<CondRet>						  - Chama a fun��o  MAT_DestruirMatriz( vtMatriz[inxmat] )
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "matriz.h"
#include	"LISTA.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_MAT_CMD       "=criarmatriz"
#define     AVANCAR_CMD         "=avancar"
#define		DESTRUIR_CMD		"=destruirmatriz"
#define		INS_CHAR_ANTES_CMD	"=inscharantes"
#define		INS_CHAR_DEPOIS_CMD	"=inschardepois"
#define		INS_LISTA_CMD		"=inslista"  
#define		CRIAR_LISTA_CMD		"=criarlista"       
#define		OBTER_VALOR_CMD		"=obtervalorelem" 
#define		EXC_ELEM_CMD		"=excluirelem"    
#define		IR_INICIO_CMD		"=irinicio"       
#define		IR_FIM_CMD			"=irfinal"        
#define		AVANCAR_ELEM_CMD	"=avancarelem"    

#define DIM_VT_MATRIZ 10
#define DIM_VALOR     100

/* Vetor de Matrizes */
tppMatriz vtMatriz[DIM_VT_MATRIZ] ;

/* Lista auxiliar */
LIS_tppLista	lista;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( void * pValor ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     �rvore sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int CondRetObtido   = MAT_CondRetOK ;
      int CondRetEsperada = MAT_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char   StringDado[ DIM_VALOR ] ;
	  char * pDado;

      int  NumLidos = -1 ;
	  int inxmat = -1, colunaRecebida, linhaRecebida;
	  int numElem;

      TST_tpCondRet Ret ;

      /* Testar MAT Criar Matriz */

         if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iiii" ,
                               &inxmat, &linhaRecebida, &colunaRecebida, &CondRetEsperada ) ;
            if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_CriarMatriz(linhaRecebida, colunaRecebida, &vtMatriz[inxmat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar a Matriz." );

         } /* fim ativa: Testar MAT Criar Matriz */

		  /* Testar  MAT Criar Lista  */

		  else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                       &CondRetEsperada) ;

            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

          CondRetObtido =  MAT_CriarLista(&lista);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar a Lista." );
         } /* fim ativa: Testar Criar Lista */

      /* Testar MAT Inserir lista na Matriz */

         else if ( strcmp( ComandoTeste , DESTRUIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxmat, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido =  MAT_DestruirMatriz(vtMatriz[inxmat]) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir a lista na matriz" );

         } /* fim ativa: Testar MAT Inserir lista na matriz*/

      /* Testar  MAT Avancar c�lula da matriz  */

         else if ( strcmp( ComandoTeste , AVANCAR_CMD  ) == 0 )
         {

            NumLidos = LER_LerParametros( "sii" ,
                               StringDado , &inxmat, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

		    pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;

            CondRetObtido = MAT_Avancar( vtMatriz[inxmat], pDado ) ;

			if ( CondRetObtido != MAT_CondRetOK )
            {
               free( pDado ) ;
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao avancar nesta direcao da matriz" );

         } /* fim ativa: Testar MAT Avancar c�lula da matriz */

      /* Testar MAT Inserir Char antes do corrente */

         else if ( strcmp( ComandoTeste , INS_CHAR_ANTES_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_InserirCharAntes(lista, ValorDado) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir char antes do corrente" );

         } /* fim ativa: Testar MAT Inserir Char Depois do corrente */

         else if ( strcmp( ComandoTeste , INS_CHAR_DEPOIS_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_InserirCharDepois(lista, ValorDado) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir char depois do corrente" );

         } /* fim ativa: Testar MAT Inserir Char Depois do corrente */

      /* Testar MAT Inserir lista na Matriz */

         else if ( strcmp( ComandoTeste , INS_LISTA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iiii" ,
                               &inxmat, &linhaRecebida, &colunaRecebida, &CondRetEsperada ) ;
            if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido =  MAT_InserirLista(vtMatriz[inxmat], lista, linhaRecebida, colunaRecebida) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir a lista na matriz" );

         } /* fim ativa: Testar MAT Inserir lista na matriz*/

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
								&ValorDado , &CondRetEsperada) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ObterValor( lista, &ValorObtido ) ;


            Ret = TST_CompararChar( ValorDado , ValorObtido ,
                         "Valor do elemento errado, diferente do esperado" ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			return TST_CompararInt(CondRetObtido, CondRetEsperada, "Retorno errado ao obter valor do elemento");


         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar MAT Ir para n� origem */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrInicio( lista ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para o inicio da lista" );

         } /* fim ativa: Testar MAT Ir para n� origem */

      /* Testar MAT Ir para n� final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrFinal( lista ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para o fim da lista." );

         } /* fim ativa: Testar MAT Ir para n� final */

      /* Testar MAT Avan�ar elemento corrente */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &numElem , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_AvancarElementoCorrente( lista, numElem ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao avancar o elemento corrente da lista." );

         } /* fim ativa: Testar MAT Avan�ar elemento corrente */

      /* Testar MAT Excluir elemento */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
									&CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ExcluirElemento( lista ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao excluir o elemento da lista." );

         } /* fim ativa: Testar MAT Excluir elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TMAT Efetuar opera��es de teste espec�ficas para �rvore */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */