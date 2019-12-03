#include <stdio.h>
#include "defines.h"
#include "structs.h"
#include "menus.h"
#include "funcoesGenericas.h"
#include "pilotos.h"
#include "circuitos.h"
#include "melhoresVoltas.h"

//==============================================================================
//Objetivo : Obter os dados do arquivo e coloca na memoria            
//Parâmetros: endereço do contador,tamanho dos dados e endereço da stream do arquivo                    
//Retorno   : endereço do vetor                                          
//============================================================================== 
void *obtemDados(int *cont,int tamanhoDados,char *nomeArq)
{
      
      FILE *arquivo;
      void *vetor;
    
      arquivo=abreArquivo(nomeArq,"rb");
      if(arquivo!=NULL)
      {
         if(fseek(arquivo,0,SEEK_END)==0)
         {
            *cont= ftell(arquivo)/tamanhoDados;
            vetor = (void*) malloc(*cont * tamanhoDados);
            rewind(arquivo);
            if(fread(vetor,tamanhoDados,*cont,arquivo)!=*cont)
            {
               apresentaMsg("Erro na leitura dados");               
            }
         } 
         fclose(arquivo);
      }
      return vetor;
}

/**************************************************************
  Nome      : limpaJanela                                      
  Descricao : limpa uma janela da tela                       
  Parâmetros: linhaInicial - linha inicial da janela         
              colunaInicial - coluna inicial da janela       
              linhaFinal   - linha final da janela           
              colunaFinal - coluna final da janela           
              corFundo - cor do fundo da janela a ser limpa  
  Retorno   : nenhum                                         
**************************************************************/ 
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, 
                     int colFinal,int corFundo)
{
int coluna=0,linha=0;

    for(coluna=colFinal;coluna>=colunaInicial;coluna--)
    {
        for(linha=linhaFinal;linha>=linhaInicial;linha--)        
        {
            textbackground(corFundo);
            gotoxy(coluna,linha);
            printf(" ");

        }
    }
}
//=============================================================================================
// Objetivo   : ler e validar uma string.
// Parâmetros : Endereço da string titulo,endereço da msg de Erro string e endereço da string,além da quantidade máxima de caracteres.
// Retorno    : Nenhum
//===========================================================================================
void leValidaString (char *titulo, char *msgErro, char *str, int max,int coluna,int linha)
{
     int tamanho, cont;
     do{
         fflush(stdin);
         gotoxy(coluna,linha);
         printf("%s", titulo);
         fgets(str, max, stdin);
         tiraTerminador(str);
         tamanho=strlen(str);
         if (tamanho<1 || str[0]==' ')
         {
             gotoxy(coluna,linha);
             printf("%s\n",msgErro);
             getch();
             gotoxy(coluna,linha);
			 limpaJanela(linha,coluna,linha,strlen(msgErro)+coluna,PRETO);
         }
     }while(tamanho<1 || str[0]==' ');
}
//==============================================================================
// Objetivo   : Tirar um terminador
// Parâmetros : Endereços dastring
// Retorno    : Nenhum
//==============================================================================
void tiraTerminador(char *str)
{
     if (str[strlen(str)-1]=='\n')
     {
         str[strlen(str)-1]='\0';
     }
}
/*************************************************************************
  Nome      : desenhaMoldura                                  
  Descricao : Desenha uma moldura na tela                    
  Parâmetros: linhaInicial - linha inicial da moldura        
              colunaInicial - coluna inicial da moldura      
              linhaFinal   - linha final da moldura          
              colunaFinal - coluna final da moldura          
              corFundoAtual - cor do fundo atual             
              corLetra  - cor do fundo atual
              tipo - 1=moldura uma linha - outro=moldura duas linhas 
              fechamento - 1 fechamento simples - outro fechamento inferior                                             *
  Retorno   : nenhum                                         
***************************************************************************/ 
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal,
          int corFundoAtual, int corLetraAtual,int tipo,int fechamento)
{
    int i=0,qtdeLinhas,qtdeColunas;
    
    qtdeLinhas  = linhaFinal - linhaInicial ;
    qtdeColunas = colunaFinal - colunaInicial ;
    textbackground(PRETO);
    textcolor(BRANCO);
    gotoxy(colunaInicial,linhaInicial);
    for(i=0;i<=qtdeColunas;i++)
    {
        if(tipo==1){
           printf("\xC4"); 
        }
        else{
           printf("\xCD");
        }
    }

    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    for(i=0;i<=qtdeColunas;i++)
    {
        if(tipo==1){
           printf("\xC4"); 
        }
        else{
           printf("\xCD");
        }
    }

    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial,linhaInicial+i);
        if(tipo==1){     
           printf("\xB3"); 
        }
        else{
           printf("\xBA");
        }
    }

    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial+qtdeColunas,linhaInicial+i);
        if(tipo==1){
           printf("\xB3"); 
        }
        else{
           printf("\xBA");
        }
    }

    gotoxy(colunaInicial,linhaInicial);
    if(tipo==1){
        printf("\xDA");
    }
    else{
        if(fechamento!=1){
          printf("\xCC");  
        }
        else{
           printf("\xC9");
        }
    }

    gotoxy(colunaInicial+qtdeColunas,linhaInicial);
    if(tipo==1){
        printf("\xBF");
    }
    else{
        if(fechamento!=1){
          printf("\xB9");  
        }
        else{
          printf("\xBB");
        }
    }
    
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    if(tipo==1){
          printf("\xC0");  
    }
    else{      
          printf("\xC8");
    }
 
    gotoxy(colunaInicial+qtdeColunas,linhaInicial+qtdeLinhas);
    if(tipo==1){    
       printf("\xD9");
    }
    else{
       printf("\xBC");
    }
    retornaCor(corFundoAtual, corLetraAtual);
}
//==============================================================================
// Objetivo   : Criar um arquivo se ele nao existir
// Parâmetros : Endereço nome do arquivo
// Retorno    : 1-existe ou 0-nao existe
//==============================================================================
void criaArquivoSeNaoExistir(char *nome)
{
     int vereifcaArq;
     FILE *arquivo;
    
     vereifcaArq=verificaExistenciaArq(nome);
     if(vereifcaArq==0)
     {
        arquivo=abreArquivo(nome,"wb");
        fclose(arquivo); 
     }
}
//==============================================================================                                     
//  Objetivo : Apresentar mensagem de erro          
//  Parâmetros: Referencia a msg                    
//  Retorno   : Nenhum                                          
//============================================================================== 
void apresentaMsg( char *msg)
{
   int colInicial;
   system("CLS");
   colInicial=((80-strlen(msg))/2);
   desenhaMoldura(7,colInicial-1,13,(strlen(msg)+colInicial),PRETO,BRANCO,1,1);
   gotoxy(colInicial,10);
   fprintf(stdout,"%s",msg);
   getch();
}
//==============================================================================
// Objetivo   : Verificar se um arquivo já existe
// Parâmetros : Endereço do nome do arquivo
// Retorno    : 1-existe ou 0-nao existe
//==============================================================================
int verificaExistenciaArq(char *nomeArquivo)
{
    FILE *arquivo;
    int flag;

    if(arquivo = fopen(nomeArquivo, "r"))
    {  
       flag= 1;
      fclose(arquivo);
    }
    else
    {
      flag= 0;
    } 
    return flag;   
}
//==============================================================================
// Objetivo   : Abrir um arquivo
// Parâmetros : Endereco do nome do arquivo e endreco do modo de abertura
// Retorno    : Endereço da stream
//==============================================================================
FILE * abreArquivo (char *nome, char *modo)
{
      FILE *arquivo;
      arquivo = fopen(nome, modo);
      if(arquivo == NULL)
      {
          desenhaMoldura(8,15,15,71,PRETO,BRANCO,2,1);
          gotoxy(17,11);
          printf("Nao foi possivel abrir o arquivo %s - modo %s",nome,modo);
          getch();
          system("CLS");
      }
      return  arquivo; 
}
//===================================================================================================
// Objetivo   : Ler e validar um número inteiro
// Parâmetros : Referência aos titulo,msg de erro, além dos valores min e max, linhas e colunas.
// Retorno    : Número inteiro valido
//===================================================================================================
int leValidaInteiro(char *titulo,char *msgErro,int valorMinimo,int valorMaximo,int coluna,int linha)
{
    
    int nroInteiro,valido;
    do{
        nroInteiro=leInteiro(titulo,coluna,linha);
        valido=validaInteiro(nroInteiro,valorMinimo,valorMaximo);
        if(valido==0)
        {
            gotoxy(coluna,linha);
            printf("%s.(Min %d - Max %d)         ",msgErro,valorMinimo,valorMaximo);
            getch();
            gotoxy(coluna,linha);
			limpaJanela(linha,coluna,linha,strlen(msgErro)+coluna+30,PRETO);
        }
    }while(valido==0);
    return nroInteiro;
    
}
//==============================================================================
// Objetivo   : Ler um numero inteiro
// Parâmetros : Endereço da strig titulo
// Retorno    : Numero inteiro 
//==============================================================================
int leInteiro(char *titulo,int coluna,int linha)
{
   int nroInteiro,ret;
   do{
        gotoxy(coluna,linha);
        printf("%s",titulo);
        fflush(stdin);
        ret = scanf("%i",&nroInteiro);
        if(ret==0){
           gotoxy(coluna,linha);
           printf("Entre com um numero inteiro");
           getch();
           gotoxy(coluna,linha);
           printf("                              ");
        }   
   }while(ret==0);
   return nroInteiro;
} 
//==============================================================================
// Objetivo   : Validar um numero inteiro
// Parâmetros : Numero inteiro,valor minimo e valor maximo.
// Retorno    : 1 - valido ou 0 - invalido
//============================================================================== 
int validaInteiro(int nroInteiro,int valorMinimo,int valorMaximo)
{
    int valido;
    if(nroInteiro<valorMinimo || nroInteiro>valorMaximo)
    {
        valido=0;
    }
    else
    {
        valido=1;
    } 
    return valido;
}
/********************************************************
 Nome       : validaData
 Objetivo   : Efetua a validação de uma data a partir das 
              informações do dia, mes e ano
 Parâmetros : dia, mes e ano   
 Retorno    : 1 - data valida ou 0 - data invalida  
********************************************************/
int validaData(int dia, int mes, int ano,int diaAtual,int mesAtual,int anoAtual)
{
int retorno=1;
    
    if(ano<2014 || mes<1 || mes >12 || dia<1 || dia >31)
       return 0;
    if(ano>anoAtual){
        return 0;
    }
    else{
        if(ano==anoAtual && mes>mesAtual){
            return 0;
       }
       else{
            if(ano==anoAtual && mes==mesAtual && dia>diaAtual){
                return 0;
            }
        }
    }
          
    switch(mes)
    {
       case 4:
       case 6:
       case 9:
       case 11:
            if(dia > 30)
               retorno =0;
            break;
       case 2:
            if((ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0))
            {
               if(dia >29)
                  retorno = 0;
            }      
            else
            {
               if(dia >28)
                  retorno =0;                                      
            }
            break;      
    }      
    return retorno;
}
/**************************************************************
  Nome      : menuVertical                                     
  Descricao : Apresenta um menu vertical e retorna a opcao   
              selecionada                                    
  Parâmetros: n - Numero de itens                            
              imenu - Descrição dos itens                    
              c1 - cor do texto do menu                      
              c2 - cor da marca do item selecionado          
              linha - linha inicial para instalação do menu  
              coluna - coluna inicial para instalação do menu
              ini - número da opção inicial do menu a ser    
                        selecionada                          
              moldura - indicador se deve desenhar o menu    
                 dentro de uma moldura                       
              corFundoAtual - cor do fundo a ser restituida a
                 tela com a retirada do menu                      
              corLetra - cor da letra a ser restituida a     
                 tela com a retirada do menu 
              tipo- tipo de moldura
              fechamento- tipo de fechamento da moldura                     
  Retorno   : número do item do menu selecionado              
**************************************************************/ 
int menuVertical(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini,
                int moldura,int corFundoAtual, int corLetraAtual,int tipo,int fechamento)
{
		int tecla;	
		int sel_b;	
		int sel;
		int i;  		
		int val;							
        int tamMaiorTexto;
        
        if(linha ==1 && moldura)
           linha++;

        if(coluna== 1 && moldura)
           coluna++;
            
		textcolor(c1);	
		if(ini < 1)
		    ini=1;
		else if(ini>n)
           ini=n;
               
		sel=ini-1; 	
		for (i=0;i<=n-1;i++){ 
			if (i==ini-1) textbackground(c2); 
			else textbackground(corFundoAtual);          
			gotoxy(coluna,linha+i);                    
			printf(imenu[i]);
			if(i==0)
			  tamMaiorTexto = strlen(imenu[i]);
			else if(strlen(imenu[i]) > tamMaiorTexto)
			  tamMaiorTexto = strlen(imenu[i]);
                
    	}
		if(moldura){
		   desenhaMoldura(linha-1,coluna-1,linha+n,coluna+tamMaiorTexto+2,
                          corFundoAtual, corLetraAtual,tipo,fechamento);
		}    
		do{
			do{
				tecla=toupper(getch()); 

				if (tecla==72||tecla==75||tecla==65) val=1;
				else 	if (tecla==77||tecla==80||tecla==90) val=1;
						else 	if (tecla==27||tecla==13) val=1;
								else val=0;

			} while (!val);
			sel_b=sel; 
			if (tecla==72||tecla==75||tecla==65) sel--; 
			if (tecla==80||tecla==77||tecla==90) sel++; 
			if (tecla==27) sel_b=-1; 		 
			if (sel<=-1) sel=n-1; 
			if (sel>=n) sel=0; 
			textcolor(c1);
			if (tecla!=13&&tecla!=27){

					gotoxy(coluna,sel_b+linha); textbackground(corFundoAtual); printf(imenu[sel_b]);
					gotoxy(coluna,sel+linha); textbackground(c2); printf(imenu[sel]);
					fflush(stdin);
			}			
		} while (tecla!=13&&tecla!=27);
        if(moldura){
           limpaJanela(linha-2,coluna-1,linha+n,coluna+tamMaiorTexto+2,corFundoAtual);
        }
        else{
           limpaJanela(linha,coluna,linha+n,coluna+tamMaiorTexto,corFundoAtual);
        }

   
		return(sel_b+1); 	
}
//==============================================================================
// Objetivo   : Ler um numero real
// Parâmetros : Endereço do vetor titulo
// Retorno    : Numero real
//==============================================================================
float leReal(char *titulo,int coluna,int linha)
{
      float nroReal;
      int ret;
      do{
          gotoxy(coluna,linha);
          printf("%s",titulo);
          fflush(stdin);
          ret = scanf("%f",&nroReal);
          if(ret==0)
          {
             gotoxy(coluna,linha);
             printf("Entre com um numero real\n");
             getch();
             gotoxy(coluna,linha);
             printf("                              ");          
           }   
      }while(ret==0);
      return nroReal;
}
//==============================================================================
// Objetivo   : Validar um numero real
// Parâmetros : Numero real, valor minimo e valor maximo
// Retorno    : 1-valido ou 0-invalido
//============================================================================== 
float validaReal(float nroReal,float valorMinimo,float valorMaximo)
{
      int flag;
      if(nroReal<valorMinimo || nroReal>valorMaximo)
      {
        flag=0;
      }
      else
      {
        flag=1;
      } 
      return flag;
}
//========================================================================================================
// Objetivo   : Ler e validar um numero real
// Parâmetros : endereço da string titulo,endereço da string msg erro,valor minimo e valor maximo
// Retorno    : numero real valido
//=========================================================================================================   
float leValidaReal(char *titulo, char *erro, float valorMinimo,float valorMaximo,int coluna,int linha)
{
    int nroReal,valido;
    do{
        nroReal=leReal(titulo,coluna,linha);
        valido=validaReal(nroReal,valorMinimo,valorMaximo);
        if(valido==0)
        {
            gotoxy(coluna,linha);
            printf("%s.(Min %.1f - Max %.1f)",erro,valorMinimo,valorMaximo);
            getch();
            gotoxy(coluna,linha);
			limpaJanela(linha,coluna,linha,strlen(erro)+coluna+25,PRETO);
        }
    }while(valido==0);
    return nroReal;
}
//=========================================================================================
// Objetivo   : Ler e validar uma opcao
// Parâmetros : Endereços das strings: titulo,msgErro e string com as opcaoes de validação
// Retorno    : Caracter valido
//=========================================================================================
char leValidaOpcao(char *titulo,char *msgErro,char *str,int coluna,int linha)
{
   
     char opcao;
	 do{
          gotoxy(coluna,linha);
	  	  printf(titulo);
		  fflush(stdin);
		  opcao=getch();
		  opcao=toupper(opcao);
		  if(strchr(str,opcao)==NULL)
          {
             gotoxy(coluna,linha);
 	  		 printf("%s\n",msgErro);
			 getch();
			 gotoxy(coluna,linha);
			 limpaJanela(linha,coluna,linha,strlen(msgErro)+coluna,PRETO);
	      }
	 }while(strchr(str,opcao)==NULL);
	 return opcao;
}     
//==============================================================================                                      
//  Objetivo :   Passa um nome para maiusculo.           
//  Parâmetros:  Endereço da string nome                    
//  Retorno   :  Nenhum                                          
//============================================================================== 
void passaParaMaiusculo(char *nome)
{
     int cont;  
     for(cont=0;cont<strlen(nome);cont++)
     {
         nome[cont]=toupper(nome[cont]);
     }
}
//==============================================================================
// Objetivo   : Ordenar struturas em ordem alfabetica por nome
// Parâmetros : Dois endereços.
// Retorno    : Nenhum
//==============================================================================
int ordenaValores(const void *p1, const void*p2)
{
    int alvo,cont;
    struct Piloto *piloto1,*piloto2;
    
    piloto1=(Piloto*) p1;
    piloto2=(Piloto*) p2;

    return(strcmpi(piloto1->nome,piloto2->nome));
              
}
/**************************************************************
  Nome      : retornaCor                                       
  Descricao : retorna a cor de fundo e de texto              
  Parâmetros: corFundo - cor de fundo                        
              corTexto - cor do texto                        
  Retorno   : nenhum                                          
**************************************************************/ 
void retornaCor(int corFundo,int corTexto)
{
     textbackground(corFundo);
     textcolor(corTexto);
}
/***********************************************************
*  Nome      : validaDataRestrita                          *  
*  Descricao : Efetua a validação de uma data a partir das *
*             informações do dia mes e ano (com seculo)    *
*             na faixa de 01/01/1970 até 31/12/2037        * 
*  Parâmetros:                                             *
*             dia, mes e ano                               *
*  Retorno   :                                             * 
*            1 - data valida                               * 
*            0 - data invalida                             *
************************************************************/ 
int validaDataRestrita(int dia, int mes, int ano)
{
struct tm time_check;


// campos da estrutura tm 
struct tm {
  int tm_sec;   /* Seconds */
  int tm_min;   /* Minutes */
  int tm_hour;  /* Hour (0--23) */
  int tm_mday;  /* Day of month (1--31) */
  int tm_mon;   /* Month (0--11) */
  int tm_year;  /* Year (calendar year minus 1900) */
  int tm_wday;  /* Weekday (0--6; Sunday = 0) */
  int tm_yday;  /* Day of year (0--365) */
  int tm_isdst; /* 0 if daylight savings time is not in effect) */
};    

    
    if(ano < 2014 || ano >2014)
       return 0;
       
    /* carrega a data para a estrutura time_check do tipo tm */
    time_check.tm_year = ano - 1900;
    time_check.tm_mon  = mes - 1;
    time_check.tm_mday = dia;
    time_check.tm_hour = 0;
    time_check.tm_min  = 0;
    time_check.tm_sec  = 1;
    time_check.tm_isdst = -1;

    /*  chama  mktime para criar uma data validando-a */
    if (mktime(&time_check) == -1)
    {
       return 0; // data invalida
    }
    // verifica se data criada é igual a data de entrada 
    else if ((time_check.tm_year != ano - 1900) ||
             (time_check.tm_mon  != mes - 1) ||
             (time_check.tm_mday != dia))
    {
         return 0; // data invalida
    }
    else        
    {
       return 1; // data valida
    }  
}
/***********************************************************
*  Nome      : obtemDataHoraAtual                          *  
*  Descricao : Obtem a data e hora atual do sistema        *
*  Parâmetros:                                             *
*             dia, mes,ano, hora, minutos, segundos        *
*  Retorno   : Nenhum                                      * 
************************************************************/ 
void obtemDataHoraAtual(int *dia, int * mes, int *ano, int *hora, 
                        int *minutos, int *segundos)
{
   time_t t;
   struct tm *dataAtual;
   t = time(NULL);
   dataAtual = localtime(&t);
   
   *dia      = dataAtual->tm_mday;
   *mes      = dataAtual->tm_mon+1;
   *ano      = 1900+dataAtual->tm_year;
   *hora     = dataAtual->tm_hour;
   *minutos  = dataAtual->tm_min;
   *segundos = dataAtual->tm_sec;
}
