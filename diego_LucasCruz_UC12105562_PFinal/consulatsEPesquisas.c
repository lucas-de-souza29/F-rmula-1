#include <stdio.h>
#include "defines.h"
#include "structs.h"
#include "funcoesGenericas.h"

//==============================================================================
// Objetivo   : Listar os paises cadastrados
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
int listaPaises()
{
    FILE *arquivo;
    char str[TAM_STR];
    char **itensMenu2=NULL;
    int cont,cont2=0,opcaoMenu;
    
    system("CLS");
    gotoxy(68,21);
    printf("ESC=Voltar");
    arquivo=abreArquivo(ARQ_PAISES,"rb");
    if(arquivo!=NULL)
    {
        
        while(!feof(arquivo))
        {
            if(fgets(str,sizeof(str),arquivo)!=NULL)
            {
                itensMenu2=(char**)realloc(itensMenu2,sizeof(char*)*(cont2+1));  
                if(itensMenu2 != NULL)
                  {
                       itensMenu2[cont2] = (char*)malloc(sizeof(char)*sizeof(str));
                       if(itensMenu2[cont2] != NULL)
                       {       
                          strcpy(itensMenu2[cont2],str);                   
                       }
                       else
                       {
                           apresentaMsg("Erro ao alocar memoria");
                       }
                       cont2++;   
                  } 
            }
        }
        fclose(arquivo);
        system("CLS");
    }
    if(itensMenu2!=NULL)
    {
        gotoxy(28,8);
        printf("PAISES CADASTRADOS\n\n");
        opcaoMenu = menuVertical(cont2,itensMenu2,BRANCO,VERMELHO,10,25,1,1,PRETO,BRANCO,2,1);
        for(cont=0;cont<cont2;cont++)
        {
           free(itensMenu2[cont]);
        }
        free(itensMenu2);
        return opcaoMenu;
    }
    else
    {
        opcaoMenu=0;
    } 
    system("CLS");
    return opcaoMenu;   
}
//==============================================================================
// Objetivo   : Verifica se a string pais existe dentro de um arquivo
// Parâmetros : Endereço da string e nome do arquivo
// Retorno    : 1 - existe ou 0 - nao
//==============================================================================
int verificaPais(char *str,char *nomeArquivo)
{
    FILE *arquivo;
    struct Piloto piloto;
    int flag = 0;

    arquivo = abreArquivo(nomeArquivo,"rb");
    if(arquivo != NULL)
    {
       while(!feof(arquivo))
       {
             if(fscanf(arquivo,"%s\n",piloto.paisOrigem)==1)
             {
                 if(stricmp(piloto.paisOrigem,str)==0)
                 {
                    flag = 1;
                    break;
                 }
                
             }
       }
       fclose(arquivo);
    }
    return flag;
}
//==============================================================================
// Objetivo   : Pesquisar os pilotos que correram em um circuito em uma data
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void pesquisaPilotoPorCircuitoData()
{
     FILE *arqCircuito;
     FILE *arqVoltas;
     FILE *arqPilotos;
     struct Circuito circuito;
     struct MelhorVolta volta;
     struct Piloto piloto;
     struct Data data;
     int nro,opcao,dataValida,cont=0,cont2=0,opcaoMenu,flag=0,flag2=0;
     char **itensMenu=NULL,**itensMenu2=NULL,dados[TAM_MSG];
     int  dia,mes,ano,horas,minutos,segundos;
    
     //R2
     system("CLS");
     printf("ESC=Voltar");
     nro=apresentaTodosCircuitos();
     if(nro==0)
     {
        return;
     }
     opcao=leValidaOpcao("Deseja pesquisar em uma data especifica?(S/N)","opcao invalida","SN",11,12);
     system("CLS");
     if(opcao=='S')
     {
        do{
            system("CLS");
            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
            gotoxy(11,12);
            printf("Data=");
            data.dia=leInteiro("",17,12);
            data.mes=leInteiro("/",19,12);
            data.ano=leInteiro("/",22,12);
            obtemDataHoraAtual(&dia,&mes,&ano,&horas,&minutos,&segundos);
            dataValida=validaData(data.dia,data.mes,data.ano,dia,mes,ano);
            if(dataValida==0)
            {
                gotoxy(11,12);
                printf("Data=invalida       ");
                getch();
                gotoxy(11,12);
                limpaJanela(12,11,12,50,PRETO);
            }
        }while(dataValida==0);
    }
    system("CLS");
    arqVoltas = abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
    arqPilotos = abreArquivo(ARQ_PILOTOS,"rb");
    if(arqVoltas!=NULL && arqPilotos!=NULL)
    {
        while(!feof(arqVoltas))
        {
            flag=0;
            if(fread(&volta,sizeof(MelhorVolta),1,arqVoltas)==1)
            {  
                flag2=1;
                rewind(arqPilotos);
                if(opcao=='S')
                {
                    if(nro == volta.codCircuito && data.ano==volta.data.ano && data.mes==volta.data.mes && data.dia == volta.data.dia)
                    {
                     
                       while(!feof(arqPilotos))
                       {
                          if(fread(&piloto,sizeof(Piloto),1,arqPilotos)==1)
                          { 
                             if(volta.codPiloto==piloto.codigoId)
                             {
                                sprintf(dados,"%-15.15s%-10.10s%02d:%02d.%-05.03d\n",piloto.nome,volta.nomeEquipe,volta.tempo.minutos,volta.tempo.segundos,volta.tempo.milisegundos);
                                flag=1;
                                break;
                             }
                          }
                       }
                    }
                }
                else
                {
                    if(nro == volta.codCircuito)
                    {
                        while(!feof(arqPilotos))
                        {
                              if(fread(&piloto,sizeof(Piloto),1,arqPilotos)==1)
                              { 
                                 if(volta.codPiloto==piloto.codigoId)
                                 {
                                    sprintf(dados,"%-15.15s%-10.10s%02d:%02d.%-05.03d\n",piloto.nome,volta.nomeEquipe,volta.tempo.minutos,volta.tempo.segundos,volta.tempo.milisegundos);
                                    flag=1;
                                    break;
                                 }
                              }
                        }
                    }
                }
                if(flag==1)
                {
                    itensMenu2=(char**)realloc(itensMenu2,sizeof(char*)*(cont2+1));
                    if(itensMenu2 != NULL)
                    {
                           itensMenu2[cont2] = (char*) malloc(sizeof(char)*sizeof(dados));
                           if(itensMenu2[cont2] != NULL)
                           {       
                              strcpy(itensMenu2[cont2],dados);  
                              cont2++;                 
                           }
                           else
                           {
                               apresentaMsg("Erro ao alocar memoria para uma string");
                           }
                              
                    } 
                }
            }
            
        }
        fclose(arqVoltas);
        fclose(arqPilotos);
        if(flag2==0)
        {
               apresentaMsg("Nenhum piloto encontrado!");
               opcaoMenu=0;
        }
        else
        {
               if(itensMenu2 != NULL)
               {
                    gotoxy(10,8);
                    printf("%-15.15s%-10.10s%-11.11s","NOME","EQUIPE","TEMPO");
                    desenhaMoldura(7, 9,9,49,PRETO,BRANCO,2,1);
                    opcaoMenu = menuVertical(cont2,itensMenu2,BRANCO,VERMELHO,10,10,1,1,PRETO,BRANCO,2,2);
                    for(cont=0;cont<cont2;cont++)
                    {
                        free(itensMenu2[cont2]);
                    }
                    free(itensMenu2);
               }
               else
               {
                    apresentaMsg("Erro ao alocar memoria para o menu!");
               }
        }
    }
}

//==========================================================================================
// Objetivo   : Pesquisar as informações de um circuito atraves de parte do nome ou codigo
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==========================================================================================
void pesquisaCircuitoPorNomeOuCod()
{
     FILE *arquivo;
     FILE *arquivo2;
     char str[TAM_NOME_PILOTO];
     struct Piloto piloto;
     struct Circuito circuito,*circuitos=NULL;
     int verifica=0,cont=0,codigoPesquisa,qtdeCircuitos,opcao,flag,cont2=0,opcaoMenu;
     char nomePesquisa[TAM_NOME_CIRCUITO],dados[TAM_MSG];
     char nomeAux[TAM_NOME_CIRCUITO],nomeAux2[TAM_NOME_CIRCUITO];
     char *itensMenu[]={"Pesquisa por nome","Pesquisa por Codigo"};
     char **itensMenu2=NULL;
    
     system("CLS");
     printf("ESC = VOLTAR");
     arquivo=abreArquivo(ARQ_CIRCUITOS,"rb");
     if(arquivo!=NULL)
     {
        opcao = menuVertical(2,itensMenu,BRANCO,VERMELHO,13,30,1,1,PRETO,BRANCO,2,1);
        system("CLS");
        if(opcao==1)
        {
            desenhaMoldura(11, 10,15,49,PRETO,BRANCO,2,1);
            leValidaString("Nome=","nome invalido!",nomePesquisa,TAM_NOME_CIRCUITO,11,12);
        }
        else
        {
            if(opcao==2)
            {
                desenhaMoldura(11, 10,15,49,PRETO,BRANCO,2,1);
               codigoPesquisa=leInteiro("Codigo=",11,13);
            }
            else
            {
                if(opcao==0)
                {
                    fclose(arquivo);
                    return;
                }
            }
        }
        while(!feof(arquivo))
        {
            flag=0;
	        if(fread(&circuito,sizeof(Circuito),1,arquivo) == 1)
            {     
                    if(opcao==1)
                    {
                        strcpy(nomeAux,circuito.nome);
                        passaParaMaiusculo(nomeAux);
                        strcpy(nomeAux2,nomePesquisa);
                        passaParaMaiusculo(nomeAux2);
                        if(strstr(nomeAux,nomeAux2)){
     
                            circuitos=(Circuito*)realloc(circuitos,((cont+1)*sizeof(Circuito)));//R4
                            if(circuitos!=NULL)
                            {
                                circuitos[cont]=circuito;
                                verifica=1;
                                flag=1;
                            }
                        }                         
                    }
                    else
                    {
                        if(opcao==2)
                        {
                            if(circuito.codigo==codigoPesquisa)
                            {
                                circuitos=(Circuito*)realloc(circuitos,((cont+1)*sizeof(Circuito)));//R4
                                if(circuitos!=NULL)
                                {
                                    circuitos[cont]=circuito;
                                    verifica=1;
                                    flag=1;
                                }
                            }
                        }      
                    }
                    if(flag==1)
                    {
                        arquivo2=abreArquivo(ARQ_PILOTOS,"rb");
                        if(arquivo2!=NULL)
                        {
                            while(!feof(arquivo2))
                            {
                                if(fread(&piloto,sizeof(Piloto),1,arquivo2)==1)
                                {
                                    if(piloto.codigoId==circuitos[cont].codPilotoMelhorVolta)
                                    {
                                        strcpy(str,piloto.nome);
                                        break;
                                    }
                                }
                            }
                            fclose(arquivo2);
                        }
                        if(circuitos[cont].codPilotoMelhorVolta==0)
                        {
                            strcpy(str,"Nao ha volta");
                        }
                        sprintf(dados,"%-4d%-15.15s%-10.10s%-9.2f%-15.15s%02d:%02d.%-05.03d",circuitos[cont].codigo, 
                               circuitos[cont].nome, circuitos[cont].pais, circuitos[cont].tamanhoKm,str,
                               circuitos[cont].melhorVolta.minutos,circuitos[cont].melhorVolta.segundos,circuitos[cont].melhorVolta.milisegundos );
                       
                        cont++;
                        itensMenu2=(char**)realloc(itensMenu2,sizeof(char*)*(cont2+1));
                        if(itensMenu2 != NULL)
                        {
                               itensMenu2[cont2] = (char*)malloc(sizeof(char)*sizeof(dados));
                               if(itensMenu2[cont2] != NULL)
                               {       
                                  strcpy(itensMenu2[cont2],dados);                   
                               }
                               else
                               {
                                   apresentaMsg("Erro ao alocar memoria para um elemento");
                               }
                               cont2++;   
                          } 
                        
                    }
            }
        }
        if(circuitos!=NULL)
        {
           free(circuitos);
        }
        fclose(arquivo);
    }
    
    system("CLS");
    if(itensMenu2!=NULL)
    {
        gotoxy(9,8);
        printf("%-4.4s%-15.15s%-10.10s%-9.9s%-15.15s%-12.12s\n","COD","NOME","PAIS","TAMANHO","PILOTO", "MELHOR TEMPO");
        desenhaMoldura(7, 9,9,76,PRETO,BRANCO,2,1);
        opcaoMenu = menuVertical(cont2,itensMenu2,BRANCO,VERMELHO,10,10,1,1,PRETO,BRANCO,2,2);
        for(cont=0;cont<cont2;cont++)
        {
           free(itensMenu2[cont]);
        }
        free(itensMenu2);
    }
    else
    {
         if(verifica==0)
         {
            apresentaMsg("Nenhum registro encontrado!");
         }
    }   
}

//===================================================================
// Objetivo   : Listar todos os pilotos de uma equipe em um periodo     
// Parâmetros : Nenhum
// Retorno    : Nenhum
//===================================================================
void listaPilotosEquipePorPeriodo()
{
     FILE *arquivoVoltas;
     FILE *arquivoPilotos;
     FILE *arquivoCircuitos;
     struct MelhorVolta volta;
     struct Piloto piloto,*pilotos;
     struct Circuito circuito;
     char **itensMenu2=NULL;
     int qtdePilotos,cont=0,cont2=0,dataValida,invalido,flag=0,flag2,flagEquipe=0,opcaoMenu;
     char nomePesquisa[TAM_NOME_EQUIPE],dados[TAM_MSG],str[TAM_NOME_CIRCUITO],msg[TAM_MSG];
     struct Data data1,data2;
     float auxData,auxData1,auxData2;
     int  dia,mes,ano,horas,minutos,segundos;
    
     system("CLS");
     printf("ESC=VOLTAR");
     arquivoVoltas=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
     arquivoPilotos=abreArquivo(ARQ_PILOTOS,"rb");
     arquivoCircuitos=abreArquivo(ARQ_CIRCUITOS,"rb");
     if(arquivoVoltas!=NULL && arquivoPilotos!=NULL && arquivoCircuitos!=NULL)
     {
        if(fseek(arquivoPilotos,0,SEEK_END)==0)
        {
           qtdePilotos=ftell(arquivoPilotos)/sizeof(Piloto);
           pilotos=(Piloto*)malloc(qtdePilotos*sizeof(Piloto));
           if(pilotos!=NULL)
           {
               rewind(arquivoPilotos);
               while(!feof(arquivoPilotos))
               {
        	        if(fread(&pilotos[cont],sizeof(Piloto),1,arquivoPilotos) == 1)
                    {
                        cont++;
                    }
               }
               qsort(pilotos,qtdePilotos,sizeof(Piloto),ordenaValores);
               system("CLS");
               desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
               leValidaString("Nome Equipe=","nome invalido!",nomePesquisa,TAM_NOME_EQUIPE,11,12);
               do{
                    system("CLS");
                    desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                    gotoxy(11,12);
                    printf("Data=");
                    data1.dia=leInteiro("",17,12);
                    data1.mes=leInteiro("/",19,12);
                    data1.ano=leInteiro("/",22,12);
                    obtemDataHoraAtual(&dia,&mes,&ano,&horas,&minutos,&segundos);
                    dataValida=validaData(data1.dia,data1.mes,data1.ano,dia,mes,ano);
                    if(dataValida==0)
                    {
                        gotoxy(11,12);
                        printf("Data=invalida       ");
                        getch();
                        limpaJanela(12,11,12,50,PRETO);
                    }
                }while(dataValida==0);
                auxData1=(data1.dia/365.0)+(float)(data1.mes/12.0)+(float)data1.ano;
                do{
                    gotoxy(28,12);
                    printf("Ate:");
                    data2.dia=leInteiro("",33,12);
                    data2.mes=leInteiro("/",35,12);
                    data2.ano=leInteiro("/",38,12);
                    dataValida=validaData(data2.dia,data2.mes,data2.ano,dia,mes,ano);
                    if(dataValida==0)
                    {
                        gotoxy(28,12);
                        printf("Data=invalida       ");
                        getch();
                        limpaJanela(12,28,12,50,PRETO);
                    }
                }while(dataValida==0);
                auxData2=(data2.dia/365.0)+(float)(data2.mes/12.0)+(float)data2.ano;
                system("CLS");
    
                for(cont=0;cont<qtdePilotos;cont++)
                {  
                    rewind(arquivoVoltas); 
                    while(!feof(arquivoVoltas))
                    {
                        flag=0;
                        if(fread(&volta,sizeof(MelhorVolta),1,arquivoVoltas) == 1)
                        {                         
                            if((stricmp(nomePesquisa,volta.nomeEquipe)==0) && volta.codPiloto==pilotos[cont].codigoId)
                            {
                                    flagEquipe=1;
                                    auxData=(volta.data.dia/365.0)+(volta.data.mes/12.0)+(float)volta.data.ano;
                                    if((auxData>=auxData1 && auxData<=auxData2) ||(auxData>=auxData2 && auxData<=auxData1))
                                    {
                                        flag=1;
                                    }
                            }
                            if(flag==1)
                            {
                                rewind(arquivoCircuitos);
                                while(!feof(arquivoCircuitos))
                                {
                    	            if(fread(&circuito,sizeof(Circuito),1,arquivoCircuitos) == 1)
                                    {
                                        if(volta.codCircuito==circuito.codigo)
                                        {
                                            strcpy(str,circuito.nome);
                                        }
                                    }
                                }
                                sprintf(dados,"%-4d%-15.15s%-02.2d/%-02.2d/%-6d%-15.15s",pilotos[cont].codigoId,pilotos[cont].nome,
                                        volta.data.dia,volta.data.mes,volta.data.ano,str);
                                itensMenu2=(char**)realloc(itensMenu2,sizeof(char*)*(cont2+1));
                                if(itensMenu2 != NULL)
                                {
                                       itensMenu2[cont2] = (char*)malloc(sizeof(char)*sizeof(dados));
                                       if(itensMenu2[cont2] != NULL)
                                       {       
                                          strcpy(itensMenu2[cont2],dados); 
                                          cont2++;                  
                                       }
                                       else
                                       {
                                           apresentaMsg("Erro ao alocar memoria para uma string!");
                                       }
                                          
                                } 
                            }
                        }
                    }
           }
                 if(flagEquipe==0)
                 {
                    apresentaMsg("Essa equipe nao existe!");
                 }
                 else
                 {
                       if(cont2==0)
                       {
                            sprintf(msg,"nenhum piloto correu por essa equipe entre %02d/%02d/%4d e %02d/%02d/%4d",data1.dia,data1.mes,data1.ano,
                                   data2.dia,data2.mes,data2.ano);
                            apresentaMsg(msg);
                       }
                       else
                       {
                            if(itensMenu2!=NULL)
                            {
                                gotoxy(16,6);
                                printf("De:%02d/%02d/%4d Ate:%02d/%02d/%4d\n",data1.dia,data1.mes,data1.ano,
                                       data2.dia,data2.mes,data2.ano);
                                gotoxy(10,8);
                                printf("%-4.4s%-15.15s%-12.12s%-15.15s\n","COD","NOME","DATA","CIRCUITO"); 
                                desenhaMoldura(7, 9,9,58,PRETO,BRANCO,2,1);
                                opcaoMenu = menuVertical(cont2,itensMenu2,BRANCO,VERMELHO,10,10,1,1,PRETO,BRANCO,2,2);
                                for(cont=0;cont<cont2;cont++) 
                                {
                                    free(itensMenu2[cont]);
                                }
                                free(itensMenu2);
                            }
                        }            
                 }              
            }  
        }
    }       
}
//========================================================================
//Objetivo: Apresentar dados a partir de um tempo informado pelo usuario
//Parâmetros: Nenhum.
//Retorno:  Nenhum.
//======================================================================== 
void apresentaTudoPorTempo()
{
     FILE *arqPilotos;
     FILE *arqCircuitos;
     FILE *arqVoltas;
     int flag,flag2=0,cont,cont2=0,opcaoMenu;
     struct MelhorVolta voltaAux;
     struct Volta volta;
     struct Piloto piloto;
     struct Circuito circuito;
     char dados[TAM_MSG];
     char **itensMenu2=NULL;
  
     arqPilotos = abreArquivo("pilotos.txt", "rb");
     arqCircuitos = abreArquivo("circuitos.txt", "rb");
     arqVoltas = abreArquivo("melhoresVoltas.txt", "rb");
     if(arqPilotos != NULL && arqCircuitos != NULL && arqVoltas != NULL)
     {
        desenhaMoldura(12, 9,18,49,PRETO,BRANCO,2,1);
        gotoxy(11,15);
        printf("Tempo=");
        volta.minutos = leValidaInteiro("", "Minutos invalidos ", 0, 59,17,15);
        gotoxy(19,15);printf("'");
        volta.segundos = leValidaInteiro("", "Segundos invalidos ", 0, 59,20,15);
        gotoxy(22,15);printf("''");
        volta.milisegundos = leValidaInteiro("", "Milissegundos invalidos ", 0, 999,24,15);
        system("CLS"); 
        while(!feof(arqVoltas))
        {
           flag = 0;
           if(fread(&voltaAux, sizeof(MelhorVolta), 1, arqVoltas)==1)
           {
              if(volta.minutos > voltaAux.tempo.minutos) 
              {
                 flag=1;                   
              }
           else
           {
              if(volta.minutos == voltaAux.tempo.minutos && volta.segundos > voltaAux.tempo.segundos)
              {
                  flag=1;
              }
              else
              {
                if(volta.minutos == voltaAux.tempo.minutos && volta.segundos == voltaAux.tempo.segundos && volta.milisegundos >= voltaAux.tempo.milisegundos)
                {
                   flag=1;
                }
              }
           }
        }
        if(flag==1)
        {
           flag2=1;
           rewind(arqPilotos);
           while(!feof(arqPilotos))
           {
                if(fread(&piloto, sizeof(Piloto), 1, arqPilotos)==1)
                {
                   if(voltaAux.codPiloto == piloto.codigoId)
                   {
                      break;
                   }
                }
           }
           rewind(arqCircuitos);
           while(!feof(arqCircuitos))
           {
                 if(fread(&circuito, sizeof(Circuito), 1, arqCircuitos)==1)
                 {
                    if(voltaAux.codCircuito == circuito.codigo)
                    {
                       break;
                    }
                 }
           }
           sprintf(dados,"%-15.15s%-10.10s%-10.10s%-02.2d'%-02.2d''%-03.3d",piloto.nome,voltaAux.nomeEquipe,circuito.nome,
                   voltaAux.tempo.minutos,voltaAux.tempo.segundos,voltaAux.tempo.milisegundos);
           itensMenu2=(char**)realloc(itensMenu2,sizeof(char*)*(cont2+1));  
           if(itensMenu2 != NULL)
           {
               itensMenu2[cont2] = (char*)malloc(sizeof(char)*sizeof(dados));
               if(itensMenu2[cont2] != NULL)
               {       
                  strcpy(itensMenu2[cont2],dados);                   
               }
               else
               {
                   apresentaMsg("Erro ao alocar memoria para um elemento");
               }
               cont2++;   
          } 
      }
     }  
          if(itensMenu2!=NULL)
          {
             gotoxy(13,6);
             printf("TEMPOS MENORES OU IGUAIS A :%02d'%02d''%03d\n",volta.minutos,volta.segundos,volta.milisegundos); 
             gotoxy(10,8);
             printf("%-15.15s%-10.10s%-10.10s%-10.10s\n", "NOME", "EQUIPE", "CIRCUITO","TEMPO");
             desenhaMoldura(7,9,9,57,PRETO,BRANCO,2,1);
             opcaoMenu = menuVertical(cont2,itensMenu2,BRANCO,VERMELHO,10,10,1,1,PRETO,BRANCO,2,2);
             for(cont=0;cont<cont2;cont++)
             {
                 free(itensMenu2[cont]);
             } 
             free(itensMenu2);
          }
          if(flag2 == 0)
          {
             apresentaMsg("Nao foi encontrado nenhum dado");
          }
          fclose(arqVoltas);
          fclose(arqCircuitos);
          fclose(arqPilotos);
    }
    system("CLS");
}
