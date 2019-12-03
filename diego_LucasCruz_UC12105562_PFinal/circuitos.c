#include <stdio.h>
#include "defines.h"
#include "structs.h"
#include "funcoesGenericas.h"

//==============================================================================
// Objetivo   : Apresentar um circuito
// Parâmetros : Estrutura de dados de um circuito
// Retorno    : Nenhum
//==============================================================================
void apresentaUmCircuito(struct Circuito circuito)
{
     FILE *arquivo;
     char str[TAM_NOME_PILOTO];
     struct Piloto piloto;
    
     arquivo=abreArquivo(ARQ_PILOTOS,"rb");
     if(arquivo!=NULL)
     { 
        while(!feof(arquivo))
        {
            if(fread(&piloto,sizeof(Piloto),1,arquivo)==1)
            {
                if(piloto.codigoId==circuito.codPilotoMelhorVolta)
                {
                    strcpy(str,piloto.nome);
                    break;
                }
            }
        }
        fclose(arquivo);
     }
     if(circuito.codPilotoMelhorVolta==0)
     {
         strcpy(str,"Nao ha volta");
     }
     printf("%-4d%-15.15s%-10.10s%-9.2f%-15.15s%02d:%02d.%-05.03d\n",circuito.codigo, 
           circuito.nome, circuito.pais, circuito.tamanhoKm,str,
           circuito.melhorVolta.minutos,circuito.melhorVolta.segundos,circuito.melhorVolta.milisegundos );
}

//==============================================================================
// Objetivo   : Cadastrar um circuito
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void cadastraCircuito()
{
     struct Circuito circuito;
     FILE *arq;
     FILE *arq2;
     char str[TAM_STR];
     int posicaoPais,cont=0;
     
     system("CLS");
     desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
     arq = abreArquivo(ARQ_CIRCUITOS,"ab");
     if(arq!=NULL)
     {
       leValidaString("Nome do circuito: ", "Nome=invalido", circuito.nome, TAM_NOME_CIRCUITO,11,11);
       if(fseek(arq, 0, SEEK_END)==0)
       {
            circuito.codigo = (ftell(arq)/sizeof(circuito))+1;
            posicaoPais=listaPaises();
            arq2 = abreArquivo(ARQ_PAISES,"r");
            if(arq2!=NULL)
            {
                while(!feof(arq2))
                {
                    if(fgets(str,sizeof(str),arq2)!=NULL)
                    {
                        cont++;
                        if(cont==posicaoPais)
                        {
                            tiraTerminador(str);
                            break;
                        }
                    }
                }
                fclose(arq2);
            }
       }
       strcpy(circuito.pais,str);
       system("CLS");
       desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
       gotoxy(11,13);
       printf("Pais=%s",circuito.pais);
       getch();
       circuito.tamanhoKm = leValidaReal("Tamanho do circuito(KM)=", "Tamanho do circuito(KM)= invalido",MIN_CIRCUITO, MAX_CIRCUITO,11,13);
       circuito.codPilotoMelhorVolta=0;
       circuito.melhorVolta.minutos=0;
       circuito.melhorVolta.segundos=0;
       circuito.melhorVolta.milisegundos=0;
       limpaJanela(11,11,19,69,PRETO);
       gotoxy(20,15);
       if(fwrite(&circuito,sizeof(circuito),1,arq)==1)
       {
          apresentaMsg("Circuito cadastrado com sucesso");
       }
       else
       {
          apresentaMsg("Erro no cadastrado");
       }   
       fclose(arq);
     }
     system("CLS");
}
//==============================================================================
// Objetivo   : Apresentar os dados de todos os circuitos
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
int apresentaTodosCircuitos()
{
    FILE *arq;
    struct Circuito *circuitos;
    int verifica=0,cont=0,aux,opcaoMenu;
    char **itensMenu;
    char str[TAM_NOME_PILOTO],dados[TAM_MSG];
    struct Piloto piloto;
    
    system("CLS");
    printf("ESC = VOLTAR");
	circuitos=(Circuito*)obtemDados(&cont,sizeof(Circuito),ARQ_CIRCUITOS);
    itensMenu = (char**) malloc(sizeof(char*)*(cont));
    if(itensMenu != NULL)
    {   
        for(aux=0;aux<cont;aux++)
        {
            arq=abreArquivo(ARQ_PILOTOS,"rb");
            if(arq!=NULL)
            {
                while(!feof(arq))
                {
                    if(fread(&piloto,sizeof(Piloto),1,arq)==1)
                    {
                        if(piloto.codigoId==circuitos[aux].codPilotoMelhorVolta)
                        {
                            strcpy(str,piloto.nome);
                            break;
                        }
                    }
                }
                fclose(arq);
            }
            if(circuitos[aux].codPilotoMelhorVolta==0)
            {
                strcpy(str,"Nao ha volta");
            }
            sprintf(dados,"%-4d%-15.15s%-10.10s%-9.2f%-15.15s%02d:%02d.%-05.03d\n",circuitos[aux].codigo, 
               circuitos[aux].nome, circuitos[aux].pais, circuitos[aux].tamanhoKm,str,
               circuitos[aux].melhorVolta.minutos,circuitos[aux].melhorVolta.segundos,circuitos[aux].melhorVolta.milisegundos );

           itensMenu[aux] = (char*) malloc(sizeof(char)*(100));
           if(itensMenu[aux] != NULL)
           {       
              strcpy(itensMenu[aux],dados);                   
           }
           else
           {
               apresentaMsg("Erro ao alocar memoria para uma string");
           }   
      }
                            
    }
    else
    {
        apresentaMsg("Erro ao alocar memoria");
        return 0;
    }
    if(arq!=NULL)
    {
        if(cont==0)
        {
            apresentaMsg("Nao ha cadastros!");
            opcaoMenu=0;
        }
        else
        {
            gotoxy(5,8);
            printf("%-4.4s%-15.15s%-10.10s%-9.9s%-15.15s%-12.12s\n","COD","NOME","PAIS","TAMANHO","PILOTO", "MELHOR TEMPO");
            desenhaMoldura(7, 4,9,72,PRETO,BRANCO,2,1);
            opcaoMenu = menuVertical(cont,itensMenu,BRANCO,VERMELHO,10,5,1,1,PRETO,BRANCO,2,2);   
        }
    }
    system("CLS");
    return opcaoMenu;
}
//==============================================================================
// Objetivo   : Alterar os dados de um circuito
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void alteraDadosCircuito()
{
     struct Circuito circuito;
     int posicaoArq,posicaoMaxima,opcaoAltera;
     int codRepetido,posicaoPais,cont=0;
     char str[TAM_STR];
     FILE *arq;
     FILE *arq2;
     char opcao,*itensMenu2[]={"Nome","Pais","Tamanho","Salvar e Sair"},strAux[TAM_NOME_PAIS];
    
     do{
         system("CLS");
         gotoxy(68,21);
         printf("ESC=Voltar");
         posicaoArq=apresentaTodosCircuitos();
         arq = abreArquivo(ARQ_CIRCUITOS,"r+b");
         if(arq!=NULL)
         {
            if(fseek(arq,0,SEEK_END)==0)
            {
                posicaoMaxima=ftell(arq)/sizeof(circuito);
                if(posicaoArq!=0)
                {
                    if(fseek(arq,(posicaoArq-1)*sizeof(circuito),SEEK_SET)==0)
                    {
                        if(fread(&circuito,sizeof(circuito),1,arq)==1)
                        {
                           system("CLS");
                           gotoxy(8,12);
                           printf("%-4.4s%-15.15s%-10.10s%-9.9s%-15.15s%-12.12s\n","COD","NOME","PAIS","TAMANHO","PILOTO", "MELHOR TEMPO");
                           desenhaMoldura(10,6,20,75,PRETO,BRANCO,2,1);
                           gotoxy(8,13);
                           apresentaUmCircuito(circuito);
                           opcao=leValidaOpcao("Deseja alterar os dados desse circuito?(S/N)","Opcao invalida!","SN",8,15);
                           if(opcao=='S')
                           {
                              do{
                                  system("CLS");
                                  opcaoAltera=menuVertical(QTDE_ITENS_MENU_CIRCUITOS,itensMenu2,BRANCO,VERMELHO,10,30,1,1,PRETO,BRANCO,2,1);
                                  switch(opcaoAltera)
                                  {
                                        case 1:
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            leValidaString ("Nome=","Nome invalido!",circuito.nome,TAM_NOME_CIRCUITO,11,12);
                                            break;
                                        case 2: 
                                           posicaoPais=listaPaises();
                                            arq2=abreArquivo(ARQ_PAISES,"r");
                                            if(arq2!=NULL)
                                            {
                                                while(!feof(arq2))
                                                {
                                                    if(fgets(str,sizeof(str),arq2)!=NULL)
                                                    {
                                                        cont++;
                                                        if(cont==posicaoPais)
                                                        {
                                                             tiraTerminador(str);
                                                             break;
                                                        }
                                                    }
                                                }
                                                fclose(arq2);
                                            }
                                            strcpy(circuito.pais,str);
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            printf("Pais=%s",circuito.pais);
                                            getch();
                                            break;
                                        case 3:
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            circuito.tamanhoKm=leValidaReal("Tamanho em KM a ser atualizado: ","Tamanho invalido!", MIN_CIRCUITO, MAX_CIRCUITO,11,12);
                                    }
                               }while(opcaoAltera!=QTDE_ITENS_MENU_CIRCUITOS);
                               if(fseek(arq,(posicaoArq-1)*sizeof(circuito),SEEK_SET)==0)
                               {
                                   if(fwrite(&circuito,sizeof(circuito),1,arq)==1)
                                   {
                                        apresentaMsg("Circuito cadastrado com sucesso");
                                   }
                                   else
                                   {
                                        apresentaMsg("Erro no cadastrado");
                                   }
                           }
                        }  
                    } 
                } 
            }
         }
         fclose(arq); 
         }
         system("CLS");
    }while(posicaoArq!=0);  
}
