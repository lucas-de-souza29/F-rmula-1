#include <stdio.h>
#include "defines.h"
#include "structs.h"
#include "menus.h"
#include "funcoesGenericas.h"
#include "pilotos.h"
#include "circuitos.h"

//==============================================================================
// Objetivo   : Cadastrar um piloto
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void cadastraPiloto()
{
    struct Piloto piloto;
    char str[TAM_STR];
    FILE *arquivo;
    FILE *arquivo2;
    int codRepetido,posicaoPais,cont=0;
    
    system("CLS");
    desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
    arquivo=abreArquivo(ARQ_PILOTOS,"ab");
    if(arquivo!=NULL)
    {
       gotoxy(11,11);
       piloto.codigoId=leValidaInteiro("Codigo de Identificacao=","Codigo=Invalido!",COD_PILOTO_MIN,COD_PILOTO_MAX,11,11);
       codRepetido=verificaCodPilotoEmArquivo(piloto.codigoId,ARQ_PILOTOS);
       if(codRepetido==1)
       {
            gotoxy(11,11);
            printf("Codigo de Identificacao Repetido!");
            getch();
            system("CLS");
            fclose(arquivo); 
            return;
        }
        leValidaString ("Nome=","Nome=invalido!",piloto.nome,TAM_NOME_PILOTO,11,12);
        piloto.idade=leValidaInteiro("Idade=","Idade=Invalida!",IDADE_MIN,IDADE_MAX,11,13);
        piloto.sexo=leValidaOpcao("Sexo=","Sexo=invalido!","MF",11,14);
        piloto.sexo=='M'? printf("Masculino\n"): printf("Feminino\n");
        posicaoPais=listaPaises();
        arquivo2=abreArquivo(ARQ_PAISES,"r");
        if(arquivo2!=NULL)
        {
            while(!feof(arquivo2))
            {
                if(fgets(str,sizeof(str),arquivo2)!=NULL)
                {
                    cont++;
                    if(cont==posicaoPais)
                    {
                        tiraTerminador(str);
                        break;
                    }
                }
            }
            fclose(arquivo2);
        }
        strcpy(piloto.paisOrigem,str);
        system("CLS");
        desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
        gotoxy(11,14);
        printf("Pais=%s",piloto.paisOrigem);
        getch();
        limpaJanela(11,11,19,69,PRETO);
        gotoxy(20,15);
        if(fwrite(&piloto,sizeof(piloto),1,arquivo)==1)
        {
            apresentaMsg("Piloto cadastrado com sucesso");
        }
        else
        {
            apresentaMsg("Erro no cadastrado");
        }  
        fclose(arquivo);   
    }
    system("CLS");
}
//==============================================================================
// Objetivo   : Verifica se codigo piloto é repetido dentro de um arquivo
// Parâmetros : Numero a ser comparado e nome do arquivo
// Retorno    : 1 - existe ou 0 - nao existe
//==============================================================================
int verificaCodPilotoEmArquivo(int numero,char *nomeArquivo)
{
    FILE *arq;
    struct Piloto piloto;
    int flag = 0;

    arq = abreArquivo(nomeArquivo,"rb");
    if(arq != NULL)
    {
       while(!feof(arq))
       {
           if(fread(&piloto,sizeof(piloto),1,arq)==1)
           {
              if(piloto.codigoId == numero)
              {
                 flag = 1;
                 break;
              }
                
           }
       }
       fclose(arq);
    }
    return flag;
}
//==============================================================================
// Objetivo   : Apresentar todos os pilotos cadastrados
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
int apresentaTodosPilotos()
{
    FILE *arquivo;
    struct Piloto *pilotos;
    int verifica=0,cont=0,aux,opcaoMenu;
    char **itensMenu=NULL;
    char dados[TAM_MSG],*sexoExtenso;
     
    pilotos=(Piloto*)obtemDados(&cont,sizeof(Piloto),ARQ_PILOTOS);
    itensMenu = (char**) malloc(sizeof(char*)*(cont));
    if(itensMenu != NULL)
    { 
      for(aux=0;aux<cont;aux++)
      {
          pilotos[aux].sexo=='M' ? (sexoExtenso="Masculino" ): (sexoExtenso="Feminino");
          sprintf(dados,"%-7d%-15.15s%-6d%-11.11s%-15.15s\n", pilotos[aux].codigoId,pilotos[aux].nome, pilotos[aux].idade,sexoExtenso, pilotos[aux].paisOrigem);
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
    
    if(itensMenu != NULL){
        if(cont==0){
           apresentaMsg("Nao ha cadastros!");
           opcaoMenu=0;
        }
        else{
            gotoxy(5,8);
            printf("%-5.5s%-7.7s%-15.15s%-6.6s%-11.11s%-15.15s\n"," ","COD","NOME","IDADE","SEXO","PAIS");
            desenhaMoldura(7, 9,9,67,PRETO,BRANCO,2,1);
            opcaoMenu = menuVertical(cont,itensMenu,BRANCO,VERMELHO,10,10,1,1,PRETO,BRANCO,2,2);
        }
        for(aux=0;aux<cont;aux++)
        {
           free(itensMenu[aux]);
        }
        free(itensMenu);
    }    
    system("CLS");
    return opcaoMenu;
}
//==============================================================================
// Objetivo   : Alterar dados de um piloto
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void alteraDadosPiloto()
{
    struct Piloto piloto;
    int posicaoArq,posicaoMaxima,opcaoAltera;
    int codRepetido,posicaoPais,cont=0;
    FILE *arquivo;
    FILE *arquivo2;
    char str[TAM_STR];
    char opcao,*itensMenu2[]={" Nome"," Pais"," Sexo"," Idade"," Salvar e Sair"},strAux[TAM_NOME_PAIS];
    
    do{
        system("CLS");
        gotoxy(68,21);
        printf("ESC=Voltar");
        posicaoArq=apresentaTodosPilotos();
        arquivo=abreArquivo(ARQ_PILOTOS,"r+b");
        if(arquivo!=NULL)
        {
            if(fseek(arquivo,0,SEEK_END)==0)
            {
                posicaoMaxima=ftell(arquivo)/sizeof(piloto);
                if(posicaoArq!=0)
                {
                    if(fseek(arquivo,(posicaoArq-1)*sizeof(piloto),SEEK_SET)==0)
                    {
                        if(fread(&piloto,sizeof(piloto),1,arquivo)==1)
                        {
                           system("CLS");
                           gotoxy(10,12);
                           printf("%-5.5s%-7.7s%-15.15s%-6.6s%-11.11s%-15.15s\n"," ","COD","NOME","IDADE","SEXO","PAIS");
                           desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                           gotoxy(15,13);
                           apresentaUmPiloto(piloto);
                           opcao=leValidaOpcao("Deseja alterar os dados desse piloto?(S/N)","Opcao invalida!","SN",15,15);
                           if(opcao=='S')
                           {
                              do{
                                  system("CLS");
                                  opcaoAltera= menuVertical(5,itensMenu2,BRANCO,VERMELHO,10,30,1,1,PRETO,BRANCO,2,1);
                                  switch(opcaoAltera)
                                  {
                                        case 1:
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            leValidaString ("Nome=","Nome=invalido!",piloto.nome,TAM_NOME_PILOTO,11,12);
                                            break;
                 
                                        case 2:
                                            posicaoPais=listaPaises();
                                            arquivo2=abreArquivo(ARQ_PAISES,"r");
                                            if(arquivo2!=NULL)
                                            {
                                                while(!feof(arquivo2))
                                                {
                                                    if(fgets(str,sizeof(str),arquivo2)!=NULL)
                                                    {
                                                        cont++;
                                                        if(cont==posicaoPais)
                                                        {
                                                            tiraTerminador(str);
                                                            break;
                                                        }
                                                    }
                                                }
                                                fclose(arquivo2);
                                            }
                                            strcpy(piloto.paisOrigem,str);
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            gotoxy(11,14);
                                            printf("Pais=%s",piloto.paisOrigem);
                                            break;
                 
                                        case 3:
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            piloto.sexo=leValidaOpcao("Sexo=","Sexo invalido!","MF",11,12);
                                            gotoxy(17,12);
                                            piloto.sexo=='M'? printf("Masculino\n"): printf("Feminino\n");
                                            getch();
                                            break;
                 
                                        case 4:
                                            system("CLS");
                                            desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                            piloto.idade=leValidaInteiro("Idade=","Idade Invalido!",IDADE_MIN,IDADE_MAX,11,12);                          
                                    }
                                    
                               }while(opcaoAltera!=QTDE_ITENS_MENU_PILOTOS);
                               if(fseek(arquivo,(posicaoArq-1)*sizeof(piloto),SEEK_SET)==0)
                               {
                                   if(fwrite(&piloto,sizeof(piloto),1,arquivo)==1)
                                   {
                                        apresentaMsg("Dados salvos sucesso");
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
        fclose(arquivo); 
        }
        system("CLS");
    }while(posicaoArq!=0);  
}
//==============================================================================
// Objetivo   : Excluir um piloto do arquivo
// Parâmetros : nenhum
// Retorno    : nenhum
//==============================================================================
void excluiPiloto()
{
    struct Piloto piloto;
    FILE *arquivo;
    FILE *arquivoTemp;
    char opcao;
    int posicaoMaxima,posicaoArq,cont,verificaVolta,flag=0;
    
    do{
        cont = 0;
        gotoxy(68,21);
        printf("ESC=Voltar");
        posicaoArq=apresentaTodosPilotos();
        arquivo=abreArquivo(ARQ_PILOTOS,"rb");
        if(arquivo!=NULL)
        {
            if(fseek(arquivo,0,SEEK_END)==0)
            {
                posicaoMaxima=ftell(arquivo)/sizeof(Piloto);
                if(posicaoArq!=0)
                {
                    if(fseek(arquivo,(posicaoArq-1)*sizeof(Piloto),SEEK_SET)==0)
                    {
                        if(fread(&piloto,sizeof(Piloto),1,arquivo)==1)
                        {
                           verificaVolta=verificaSeTemVolta(piloto.codigoId,0);
                           system("CLS");
                           gotoxy(10,12);
                           printf("%-5.5s%-7.7s%-15.15s%-6.6s%-11.11s%-15.15s\n"," ","COD","NOME","IDADE","SEXO","PAIS");
                           desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                           gotoxy(15,13);
                           apresentaUmPiloto(piloto);
                           opcao=leValidaOpcao("Deseja excluir os dados desse piloto?(S/N)","Opcao invalida!","SN",15,15);
                           if(opcao=='S' && verificaVolta==0)
                           {
                              arquivoTemp = abreArquivo(ARQ_PILOTOS_TEMP,"wb");
                              if(arquivoTemp!=NULL)
                              {
                                  rewind(arquivo);
                                  while(!feof(arquivo))
                                  {
                                    if(fread(&piloto,sizeof(piloto),1,arquivo)==1)
                                    {
                                        cont++;
                                        if(cont != posicaoArq)
                                        {
                                          if(fwrite(&piloto,sizeof(piloto),1,arquivoTemp)!=1)
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
                                          if(remove(ARQ_PILOTOS) != 0)
                                          {
                                             apresentaMsg("Erro ao remover arquivo pilotos "); 
                                          }
                                          else
                                          {   
                                            if(rename(ARQ_PILOTOS_TEMP,ARQ_PILOTOS)!=0)
                                            {
                                                apresentaMsg("Erro ao renomear arquivo"); 
                                            }
                                            else
                                            {
                                               apresentaMsg("Exclusao realizada com sucesso!\n");
                                               system("pause"); 
                                            }
                                          }
                                       }
                                   }            
                              }
                           }
                           else
                           {
                              if(verificaVolta==1)
                              {
                                  apresentaMsg("Esse piloto nao pode ser excluido pois ja tem um registro de uma volta!\n");
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
                    apresentaMsg("Erro ao fechar arquivo"); 
                }
            }
       }
       system("CLS");
    }while(posicaoArq!=0);   
}
//==============================================================================
// Objetivo   : Apresentar os dados de um piloto
// Parâmetros : Dados de uma estrutura
// Retorno    : Nenhum
//==============================================================================
void apresentaUmPiloto(struct Piloto piloto)
{
      char *sexoExtenso;   
    
      piloto.sexo=='M' ? (sexoExtenso="Masculino" ): (sexoExtenso="Feminino");
      printf("%-7d%-15.15s%-6d%-11.11s%-15.15s\n",piloto.codigoId,piloto.nome,piloto.idade,sexoExtenso,piloto.paisOrigem);
}
//==============================================================================
// Objetivo   : Pesquisar um piloto pelo nome ou id
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void pesquisaPilotoPorNome()
{
    FILE *arquivo;
    struct Piloto piloto,*pilotos=NULL;
    int qtdePilotos,cont=0,cont3,verifica=0,codigoPesquisa,opcao,flag,cont2=0;
    int opcaoMenu;
    char nomePesquisa[TAM_NOME_PILOTO],*sexoExtenso,dados[TAM_MSG];
    char nomeAux[TAM_NOME_PILOTO],nomeAux2[TAM_NOME_PILOTO];
    char *itensMenu[]={"Pesquisa por nome","Pesquisa por ID"};
    char **itensMenu2=NULL;
    
    system("CLS");
    arquivo=abreArquivo(ARQ_PILOTOS,"rb");
    if(arquivo!=NULL)
    {
        opcao=menuVertical(2,itensMenu,BRANCO,VERMELHO,10,30,1,1,PRETO,BRANCO,2,1);
        system("CLS");
        desenhaMoldura(10,6,20,75,PRETO,BRANCO,2,1);
        if(opcao==1)
        {
            leValidaString("Nome =","nome invalido!",nomePesquisa,TAM_NOME_PILOTO,11,12);
        }
        else
        {
            if(opcao==2)
            {
               codigoPesquisa=leInteiro("Codigo Id=",11,13);
            }
        }
        system("CLS");
    	while(!feof(arquivo))
        {
	        if(fread(&piloto,sizeof(Piloto),1,arquivo) == 1)
            {
                pilotos=(Piloto*)realloc(pilotos,sizeof(Piloto)*(cont+1));
                if(pilotos!=NULL)
                {
                   pilotos[cont]=piloto; 
                   cont++;
                }
                else
                {
                    fclose(arquivo);
                    apresentaMsg("Erro na alocacao de memoria");
                    return;
                }
            }
        }
        fclose(arquivo);
        
        qsort(pilotos,cont,sizeof(Piloto),ordenaValores);
        for(cont3=0;cont3<cont;cont3++)
        {
            flag=0;
            if(opcao==1)
            {
                strcpy(nomeAux,pilotos[cont3].nome);
                passaParaMaiusculo(nomeAux);
                strcpy(nomeAux2,nomePesquisa);
                passaParaMaiusculo(nomeAux2);
                if(strstr(nomeAux,nomeAux2))
                {
                    pilotos[cont3].sexo=='M' ? (sexoExtenso="Masculino" ): (sexoExtenso="Feminino");
                    verifica=1;
                    flag=1;
                }                         
            }
            else
            {
                if(opcao==2)
                {
                    if(pilotos[cont3].codigoId==codigoPesquisa)
                    {
                        verifica=1;
                         flag=1;
                    } 
                }     
            }
            if(flag==1)
            {
               sprintf(dados,"%-7d%-15.15s%-6d%-11.11s%-15.15s",pilotos[cont3].codigoId,pilotos[cont3].nome,pilotos[cont3].idade,
                        sexoExtenso,pilotos[cont3].paisOrigem);
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
                            apresentaMsg("Erro ao alocar memoria para uma string");
                       }
                       cont2++;   
                }
                else
                {
                      apresentaMsg("Erro ao alocar memoria menu");
                      free(pilotos);
                      pilotos=NULL;
                      return;        
                }       
            }
                              
        }
        if(itensMenu2!=NULL)
        {
            gotoxy(5,8);    
            printf("%-5.5s%-7.7s%-15.15s%-6.6s%-11.11s%-15.15s\n"," ","COD","NOME","IDADE","SEXO","PAIS");
            desenhaMoldura(7, 9,9,66,PRETO,BRANCO,2,1);
            opcaoMenu = menuVertical(cont2,itensMenu2,BRANCO,VERMELHO,10,10,1,1,PRETO,BRANCO,2,2);
            for(cont=0;cont<cont2;cont++)
            {
               free(itensMenu2[cont]);
            }
            free(itensMenu2);
        }   
        if(cont==0)
        {
            apresentaMsg("Nao ha cadastros!");
        }
        else
        {
            if(verifica==0 && (opcao==1 || opcao==2))
            {
                apresentaMsg("Nenhum piloto encontrado!");
            }
        }
        free(pilotos);
        pilotos=NULL;
    }
}
