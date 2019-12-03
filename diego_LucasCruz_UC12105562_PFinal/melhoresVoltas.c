#include <stdio.h>
#include "defines.h"
#include "structs.h"
#include "menus.h"
#include "funcoesGenericas.h"
#include "pilotos.h"
#include "circuitos.h"

//==============================================================================
// Objetivo   : Apresentar os dados de uma melhor volta
// Parâmetros : Dados da estrutura melhor volta
// Retorno    : Nenhum
//==============================================================================
void apresentaUmaMelhorVolta(struct MelhorVolta melhorVolta)
{
     FILE *arq;
     FILE *arq2;
     struct Piloto piloto;
     struct Circuito circuito;
    
    
     arq = abreArquivo(ARQ_PILOTOS,"rb");
     arq2 = abreArquivo(ARQ_CIRCUITOS,"rb");
     if(arq!=NULL && arq2!=NULL)
     {
        while(!feof(arq))
        {
            if(fread(&piloto,sizeof(Piloto),1,arq)==1)
            {
                if(piloto.codigoId==melhorVolta.codPiloto)
                {
                    break;
                }
            }
        }
        while(!feof(arq2))
        {
            if(fread(&circuito,sizeof(Circuito),1,arq2)==1)
            {
                if(circuito.codigo==melhorVolta.codCircuito)
                {
                    break;
                }
            }
        }
        printf("%-20.20s%-15.15s%-15.15s%02d/%02d/%-6d%-02.02d:%-02.02d.%-03.03d\n",piloto.nome,circuito.nome,melhorVolta.nomeEquipe,
               melhorVolta.data.dia,melhorVolta.data.mes,melhorVolta.data.ano,melhorVolta.tempo.minutos,
               melhorVolta.tempo.segundos,melhorVolta.tempo.milisegundos);
       fclose(arq);
       fclose(arq2);
     }
}
//==============================================================================
// Objetivo   : Atualizar o tempo de um circuito
// Parâmetros : Endereço do vetor de estruturas da melhor volta daquela circuito
// Retorno    : Nenhum
//==============================================================================
void atualizaTempoCircuito(struct MelhorVolta menorTempo)
{
     FILE *arq;
     struct Circuito circuito;
    
     arq = abreArquivo(ARQ_CIRCUITOS,"r+b");
     if(arq!=NULL)
     {
        fseek(arq,(menorTempo.codCircuito-1)*sizeof(Circuito),SEEK_SET);
        if(fread(&circuito,sizeof(Circuito),1,arq)==1)
        {
            circuito.codPilotoMelhorVolta=menorTempo.codPiloto;
            circuito.melhorVolta=menorTempo.tempo;
        }
        if(fseek(arq,(menorTempo.codCircuito-1)*sizeof(Circuito),SEEK_SET)==0)
        {
           if(fwrite(&circuito,sizeof(Circuito),1,arq)!=1)
           {
                apresentaMsg("Erro ao atualizado tempo do circuito");
           }
        }
        fclose(arq); 
     }
}

//==============================================================================
// Objetivo   : Verificar o menor tempo dentro do arquivo voltas
// Parâmetros : Codigo do circuito
// Retorno    : Menor tempo de um cirucito
//==============================================================================
struct MelhorVolta verificaMenorTempo(int codCircuito)
{
       FILE *arquivo;
       int alvo,cont1=0;
       struct MelhorVolta *auxiliar,menorTempo,auxCont;
       float auxTempo1,auxTempo2;
    
       auxTempo1=60.0+60.0/60+1000.0/60000;
       arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
       if(arquivo!=NULL)
       {
          while(!feof(arquivo))
          {
              if(fread(&auxCont,sizeof(MelhorVolta),1,arquivo) == 1)
              {
                 if(auxCont.codCircuito==codCircuito)
                 {
                    auxTempo2=(float)auxCont.tempo.minutos+auxCont.tempo.segundos/60.0+auxCont.tempo.milisegundos/60000;
                    cont1++;
                    if(auxTempo2<auxTempo1)
                    {
                        auxTempo1=auxTempo2;
                        menorTempo=auxCont;
                    }
                 }
              }
           }
           fclose(arquivo);
       }
       if(cont1 == 0)
       {
          menorTempo.codCircuito=codCircuito;  
          menorTempo.codPiloto=0;
          menorTempo.tempo.minutos=0;
          menorTempo.tempo.segundos=0;
          menorTempo.tempo.milisegundos=0;
       }
       return menorTempo; 
}
//==============================================================================
// Objetivo   : Cadastrar a melhor volta de um piloto em um circuito
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void cadastraMelhorVolta()
{
     struct MelhorVolta voltaRapida,voltaRapidaCircuito;
     struct Circuito circuito;
     struct Piloto piloto;
     FILE *arquivo;
     FILE *arquivo2;
     FILE *arquivo3;
     int verificaCodigoPiloto,dataValida,verificaCodCircuito,
        verificaVoltaCircuito,posicaoArq,flag=0,dataAtual;
     int  dia,mes,ano,horas,minutos,segundos;
    
     system("CLS");
     arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"ab");
     if(arquivo!=NULL)
     {
        posicaoArq=apresentaTodosPilotos();
        arquivo2=abreArquivo(ARQ_PILOTOS,"rb");
        if(arquivo2!=NULL)
        {
            if(fseek(arquivo2,0,SEEK_END)==0)
            {
                if(posicaoArq!=0)
                {
                    fseek(arquivo2,(posicaoArq-1)*sizeof(piloto),SEEK_SET);
                    if(fread(&piloto,sizeof(piloto),1,arquivo2)==1)
                    {
                        voltaRapida.codPiloto=piloto.codigoId;
                    }
                }
            }
            fclose(arquivo2);
            
            verificaCodigoPiloto=verificaCodPilotoEmArquivo(voltaRapida.codPiloto,ARQ_PILOTOS);
            if(verificaCodigoPiloto==0)
            {
                apresentaMsg("Nenhum piloto tem esse codigo");
            }
            else
            {
                posicaoArq=apresentaTodosCircuitos();
                arquivo3=abreArquivo(ARQ_CIRCUITOS,"rb");
                if(arquivo3!=NULL)
                {
                    if(fseek(arquivo,0,SEEK_END)==0)
                    {
                        if(posicaoArq!=0)
                        {
                            fseek(arquivo3,(posicaoArq-1)*sizeof(circuito),SEEK_SET);
                            if(fread(&circuito,sizeof(circuito),1,arquivo3)==1)
                            {
                               voltaRapida.codCircuito=circuito.codigo;
                            }
                        }
                    }
                    fclose(arquivo3);
                    desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                    leValidaString ("Nome Equipe=","Nome Equipe=invalido!",voltaRapida.nomeEquipe,TAM_NOME_EQUIPE,11,13);
                    do{
                        gotoxy(11,14);
                        printf("Data=");
                        voltaRapida.data.dia=leInteiro("",16,14);
                        voltaRapida.data.mes=leInteiro("/",19,14);
                        voltaRapida.data.ano=leInteiro("/",22,14);      
                        obtemDataHoraAtual(&dia,&mes,&ano,&horas,&minutos,&segundos);
                        dataValida=validaData(voltaRapida.data.dia,voltaRapida.data.mes,voltaRapida.data.ano,dia,mes,ano);
                        if(dataValida==0)
                        {
                            gotoxy(11,14);
                            printf("Data=invalida(Minimo 2014       ");
                            getch();
                            gotoxy(11,14);
                            limpaJanela(14,11,14,50,PRETO);
                        }
                    }while(dataValida==0);
                    gotoxy(11,15);
                    printf("Tempo=");
                    voltaRapida.tempo.minutos=leValidaInteiro("","Valor invalido",0,59,17,15);
                    gotoxy(19,15);printf("'");
                    voltaRapida.tempo.segundos=leValidaInteiro("","Valor invalido",0,59,20,15);
                    gotoxy(22,15);printf("''");     
                    voltaRapida.tempo.milisegundos=leValidaInteiro("","Valor invalido",0,999,24,15);
                    limpaJanela(11,11,19,69,PRETO);
                    gotoxy(20,15);
                    if(fwrite(&voltaRapida,sizeof(voltaRapida),1,arquivo)==1)
                    {
                        apresentaMsg("Melhor volta cadastrada com sucesso");
                    }
                    else
                    {
                        apresentaMsg("Erro no cadastrado");
                    }
                    if(fclose(arquivo)==0)
                    {
                        voltaRapidaCircuito=verificaMenorTempo(voltaRapida.codCircuito);
                        atualizaTempoCircuito(voltaRapidaCircuito);                              
                        flag=1;
                    }
                    else
                    {
                        apresentaMsg("Erro ao fechar arquivo melhores voltas");
                    }                    
                }         
        }
     }
     if(flag==0)
     {
          if(fclose(arquivo)!=0)
          {
              apresentaMsg("Erro ao fechar arquivo melhores voltas");
          }
      } 
   }
}
//==============================================================================
// Objetivo   : Apresentar todas as melhores voltas
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
int apresentaMelhoresVoltas()
{
    FILE *arquivo;
    FILE *arquivo2;
    struct MelhorVolta *melhorVoltas;
    struct Piloto piloto;
    struct Circuito circuito;
    int aux,cont=0;
    char dados[TAM_MSG],**itensMenu=NULL,opcaoMenu;
   
    melhorVoltas=(MelhorVolta*)obtemDados(&cont,sizeof(MelhorVolta),ARQ_MELHORES_VOLTAS);
    itensMenu = (char**) malloc(sizeof(char*)*(cont));
    if(itensMenu != NULL)
    {
       for(aux=0;aux<cont;aux++)
       {
            arquivo=abreArquivo(ARQ_PILOTOS,"rb");
            arquivo2=abreArquivo(ARQ_CIRCUITOS,"rb");
            if(arquivo!=NULL && arquivo2!=NULL)
            {
               while(!feof(arquivo))
               {
                    if(fread(&piloto,sizeof(Piloto),1,arquivo)==1)
                    {
                        if(piloto.codigoId==melhorVoltas[aux].codPiloto)
                        {
                            break;
                        }
                    }
               }
               while(!feof(arquivo2))
               {
                    if(fread(&circuito,sizeof(Circuito),1,arquivo2)==1)
                    {
                        if(circuito.codigo==melhorVoltas[aux].codCircuito)
                        {
                            break;
                        }
                    }
               }
               sprintf(dados,"%-20.20s%-15.15s%-15.15s%02d/%02d/%-6d%02d:%02d.%-05.03d\n",piloto.nome,circuito.nome,melhorVoltas[aux].nomeEquipe,
                       melhorVoltas[aux].data.dia,melhorVoltas[aux].data.mes,melhorVoltas[aux].data.ano,melhorVoltas[aux].tempo.minutos,
                       melhorVoltas[aux].tempo.segundos,melhorVoltas[aux].tempo.milisegundos);
               fclose(arquivo);
               fclose(arquivo2);
            }
            itensMenu[aux] = (char*) malloc(sizeof(char)*sizeof(dados));
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
    if(itensMenu != NULL)
    {
        if(cont==0)
        {
            apresentaMsg("Nao ha cadastros!");
            opcaoMenu=0;
        }
        else
        {
            gotoxy(3,8);
            printf("%-20.20s%-15.15s%-15.15s%-12.12s%-11.11s\n","PILOTO","CIRCUITO","EQUIPE","DATA","TEMPO");
            desenhaMoldura(7, 2,9,79,PRETO,BRANCO,2,1);
            opcaoMenu = menuVertical(cont,itensMenu,BRANCO,VERMELHO,10,3,1,1,PRETO,BRANCO,2,2);
        }
        for(aux=0;aux<cont;aux++)
        {
           free(itensMenu[aux]);
        }
        free(itensMenu);    
        
    }
    return opcaoMenu;    
}

//==============================================================================
// Objetivo   : Alterar os dados de uma melhor volta
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void alteraDadosMelhorVolta()
{
     
     struct MelhorVolta melhorVolta;
     struct MelhorVolta voltaRapidaCircuito;
     int posicaoArq,posicaoMaxima,opcaoAltera;
     int codRepetido,dataValida,flag=0;
     FILE *arquivo;
     char opcao,*itensMenu2[]={"Nome Equipe","Data","Tempo","Salvar e Sair"};
     int  dia,mes,ano,horas,minutos,segundos;
     do{
         flag=0;
         system("CLS");
         gotoxy(68,21);
         printf("ESC=Voltar");
         posicaoArq=apresentaMelhoresVoltas();
         arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"r+b");
         if(arquivo!=NULL)
         {
            if(fseek(arquivo,0,SEEK_END)==0)
            {
               posicaoMaxima=ftell(arquivo)/sizeof(MelhorVolta);
               if(posicaoArq!=0)
               {
                  if(fseek(arquivo,(posicaoArq-1)*sizeof(MelhorVolta),SEEK_SET)==0)
                  {
                      if(fread(&melhorVolta,sizeof(MelhorVolta),1,arquivo)==1)
                      {
                         system("CLS");
                         gotoxy(6,12);
                         printf("%-20.20s%-15.15s%-15.15s%-12.12s%-11.11s\n","PILOTO","CIRCUITO","EQUIPE","DATA","TEMPO");
                         desenhaMoldura(10,4,20,78,PRETO,BRANCO,2,1);
                         gotoxy(6,13);
                         apresentaUmaMelhorVolta(melhorVolta);
                         opcao=leValidaOpcao("Deseja alterar os dados dessa Volta?(S/N)","Opcao invalida!","SN",6,15);
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
                                        leValidaString ("Nome Equipe=","Nome invalido!",melhorVolta.nomeEquipe,TAM_NOME_EQUIPE,11,12);
                                        break;
                                    
                                    case 2:
                                        do{
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            gotoxy(11,12);
                                            printf("Data=");
                                            melhorVolta.data.dia=leInteiro("",17,12);
                                            melhorVolta.data.mes=leInteiro("/",19,12);
                                            melhorVolta.data.ano=leInteiro("/",22,12);
                                            obtemDataHoraAtual(&dia,&mes,&ano,&horas,&minutos,&segundos);
                                            dataValida=validaData(melhorVolta.data.dia,melhorVolta.data.mes,melhorVolta.data.ano,dia,mes,ano);
                                            if(dataValida==0)
                                            {
                                                gotoxy(11,12);
                                                printf("Data=invalida       ");
                                                getch();
                                                gotoxy(11,12);
                                                limpaJanela(12,11,12,50,PRETO);
                                            }
                                        }while(dataValida==0);
                                        break;
                                        
                                    case 3:
                                        system("CLS");
                                        desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);                            
                                        gotoxy(11,12);
                                        printf("Tempo=");
                                        melhorVolta.tempo.minutos=leValidaInteiro("","Valor invalido",0,59,17,12);
                                        gotoxy(19,12);printf("'");
                                        melhorVolta.tempo.segundos=leValidaInteiro("","Valor invalido",0,59,20,12);
                                        gotoxy(22,12);printf("''");     
                                        melhorVolta.tempo.milisegundos=leValidaInteiro("","Valor invalido",0,999,24,12);
                                        limpaJanela(11,11,19,69,PRETO);
                                } 
                           }while(opcaoAltera!=QTDE_ITENS_MENU_CIRCUITOS);
                           if(fseek(arquivo,(posicaoArq-1)*sizeof(MelhorVolta),SEEK_SET)==0)
                           {
                                desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);            
                                if(fwrite(&melhorVolta,sizeof(MelhorVolta),1,arquivo)==1)
                                {
                                    if(fclose(arquivo)==0)
                                    {
                                       apresentaMsg("Volta alterada com sucesso");
                                       flag=1;
                                       voltaRapidaCircuito=verificaMenorTempo(melhorVolta.codCircuito);
                                       atualizaTempoCircuito(voltaRapidaCircuito);
                                    }
                                    else
                                    {
                                       apresentaMsg("Erro ao fechar arquivo melhores voltas");
                                    }       
                                }
                                else
                                {
                                    apresentaMsg("Erro na alteracao");
                                }
                           }
                        }
                     } 
                 }  
              }
          }
          if(flag==0)
          {
              if(fclose(arquivo)!=0)
              {
                  apresentaMsg("Erro ao fechar arquivo melhores voltas");
              }
          }
       }
       system("CLS");
    }while(posicaoArq!=0);
}
//==============================================================================
// Objetivo   : Excluir uma volta de arquivo
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void excluiMelhorVolta()
{
     struct MelhorVolta melhorVolta,voltaRapidaCircuito,melhorVoltaAux;
     FILE *arquivo;
     FILE *arquivoTemp;
     char opcao;
     int posicaoMaxima,posicaoArq,cont,verificaVolta,flag=0;
    
     do{
         flag=0;
         cont = 0;
         gotoxy(68,21);
         printf("ESC=Voltar");
         posicaoArq=apresentaMelhoresVoltas();
         arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
         if(arquivo!=NULL)
         {
            if(fseek(arquivo,0,SEEK_END)==0)
            {
                posicaoMaxima=ftell(arquivo)/sizeof(MelhorVolta);
                if(posicaoArq!=0)
                {
                    if(fseek(arquivo,(posicaoArq-1)*sizeof(MelhorVolta),SEEK_SET)==0)
                    {
                        if(fread(&melhorVolta,sizeof(MelhorVolta),1,arquivo)==1)
                        {
                           system("CLS");
                           gotoxy(6,12);
                           printf("%-20.20s%-15.15s%-15.15s%-12.12s%-11.11s\n","PILOTO","CIRCUITO","EQUIPE","DATA","TEMPO");
                           desenhaMoldura(10,4,20,78,PRETO,BRANCO,2,1);
                           gotoxy(6,13);
                           apresentaUmaMelhorVolta(melhorVolta);
                           opcao=leValidaOpcao("Deseja excluir os dados dessa Volta?(S/N)","Opcao invalida!","SN",6,15);
                           if(opcao=='S')
                           {
                              arquivoTemp=abreArquivo(ARQ_MELHORES_VOLTAS_TEMP,"wb");
                              if(arquivoTemp!=NULL)
                              {
                                  rewind(arquivo);
                                  while(!feof(arquivo))
                                  {
                                        if(fread(&melhorVoltaAux,sizeof(MelhorVolta),1,arquivo)==1)
                                        {
                                           cont++;
                                           if(cont != posicaoArq)
                                           {
                                              if(fwrite(&melhorVoltaAux,sizeof(MelhorVolta),1,arquivoTemp)!=1)
                                              {
                                                 apresentaMsg("Erro ao gravar dados para copia ");
                                              }
                                           } 
                                        } 
                                  }
                                  if(fclose(arquivo) !=0)
                                  {
                                      apresentaMsg("Erro ao fechar arquivo");
                                  }
                                  else
                                  {
                                      flag=1;    
                                      if(fclose(arquivoTemp) != 0)
                                      {
                                         apresentaMsg("Erro ao fechar arquivo temporario");
                                      }
                                      else
                                      {
                                         if(remove(ARQ_MELHORES_VOLTAS) != 0)
                                         {
                                            apresentaMsg("Erro ao remover arquivo voltas");
                                         }
                                         else
                                         {   
                                            if(rename(ARQ_MELHORES_VOLTAS_TEMP,ARQ_MELHORES_VOLTAS)!=0)
                                            {
                                               apresentaMsg("Erro ao renomear arquivo");
                                            }
                                            else
                                            {
                                               apresentaMsg("Exclusao realizada com sucesso");
                                            }
                                      }
                                  }
                              }
                                  voltaRapidaCircuito=verificaMenorTempo(melhorVolta.codCircuito);
                                  atualizaTempoCircuito(voltaRapidaCircuito);
                              }            
                           }
                        } 
                    }
                }
            }
            if(flag==0)
            {
                if(fclose(arquivo) !=0)
                {
                   apresentaMsg("Erro ao fechar arquivo");
                }
            }
       }
       system("CLS");   
    }while(posicaoArq!=0);
}
//=================================================================================
// Objetivo   : Verificar se um piloto tem registro de alguma volta em um circuito
// Parâmetros : Codigo de id do piloto
// Retorno    : 1-se tiver ou 2-se tiver no circuito informado ou 0-se não tiver
//=================================================================================
int verificaSeTemVolta(int codigoPiloto,int codigoCircuito)
{
    FILE *arquivo;
    struct MelhorVolta melhorVolta;
    int flag=0;
    
    arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
    if(arquivo != NULL)
    {
       while(!feof(arquivo))
       {
          if(fread(&melhorVolta,sizeof(melhorVolta),1,arquivo)==1)
          {
              if(melhorVolta.codPiloto==codigoPiloto)
              {
                 flag = 1;
                 if(melhorVolta.codCircuito==codigoCircuito)
                 {
                    flag=2;
                 }
                 break;
              }    
          }
       }
       fclose(arquivo);
    }
    return flag;
}
