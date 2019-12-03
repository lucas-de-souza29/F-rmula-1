// Aluno : Lucas de Souza Cruz

// Sintese
//   Objetivo: Gerenciar os dados dos pilotos e as provas da Fórmula 1
//   Entrada : Dados dos pilotos,circuitos, voltas.
//   Saida   :  Todos os dados.


#include <stdio.h>
#include <conio.c>

#define QTDE_ITENS_MENU_CIRCUITOS 4
#define QTDE_ITENS_MENU_PRINCIPAL 6
#define QTDE_ITENS_MENU_RELATORIOS 5
#define QTDE_ITENS_MENU_VOLTAS 5
#define QTDE_ITENS_MENU_PILOTOS 5
#define QTDE_ITENS_MENU_PILOTOS_FONTE 6 
#define TAM_NOME_PILOTO 30
#define TAM_NOME_PAIS 30
#define TAM_NOME_CIRCUITO 30
#define TAM_NOME_EQUIPE 30
#define TAM_MSG 100
#define TAM_STR 50
#define ARQ_PAISES "paises.txt"
#define ARQ_PILOTOS "pilotos.txt"
#define ARQ_PILOTOS_TEMP "pilotosTemp.txt"
#define ARQ_CIRCUITOS "circuitos.txt"
#define ARQ_MELHORES_VOLTAS "melhoresVoltas.txt"
#define ARQ_MELHORES_VOLTAS_TEMP "melhoresVoltasTemp.txt"
#define COD_PILOTO_MIN 101
#define COD_PILOTO_MAX 901 
#define IDADE_MIN 18
#define IDADE_MAX 50
#define MIN_CIRCUITO 3000
#define MAX_CIRCUITO 7000
#define BRANCO    15
#define PRETO      0
#define VERMELHO   4
#define AMARELO   14
#define AZUL       3

typedef struct Data
{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Volta
{
    int minutos;
    int segundos;
    int milisegundos;
}Volta;

typedef struct Piloto
{
    int codigoId;
    char nome[TAM_NOME_PILOTO];
    int idade;
    char sexo;
    char paisOrigem[TAM_NOME_PAIS];
    
}Piloto;

typedef struct Circuito
{
    int codigo;
    char nome[TAM_NOME_CIRCUITO];
    char pais[TAM_NOME_PAIS];
    float tamanhoKm;
    struct Volta melhorVolta;
    int codPilotoMelhorVolta;
}Circuito;

typedef struct MelhorVolta
{
    int codPiloto;
    int codCircuito;
    char nomeEquipe[TAM_NOME_EQUIPE];
    struct Data data;
    struct Volta tempo;
}MelhorVolta;

void controlePilotos();
void controleCircuitos();
void controleVoltas();
void consultasPesquisas();
void cadastraPiloto();
void cadastraCircuito();
void cadastraMelhorVolta();
int verificaCodPilotoEmArquivo(int numero,char *nomeArquivo);
int apresentaTodosPilotos();
int apresentaMelhoresVoltas();
int apresentaTodosCircuitos();
void alteraDadosPiloto();
void alteraDadosMelhorVolta();
void alteraDadosCircuito();
void excluiPiloto();
void excluiMelhorVolta();
void apresentaUmPiloto(struct Piloto piloto);
void apresentaUmCircuito(struct Circuito circuito);
void apresentaUmaMelhorVolta(struct MelhorVolta melhorVolta);
void* obtemDados(int *cont,int tamanhoDados,char *nomeArq);

void pesquisaPilotoPorNome();
void pesquisaPilotoPorCircuitoData();
void pesquisaCircuitoPorNomeOuCod();
void apresentaTudoPorTempo();
void listaPilotosEquipePorPeriodo();
void listaPaises();
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, 
                  int colFinal,int corFundo);
void leValidaString (char *titulo, char *msgErro, char *str, int max,int coluna,int linha);
void tiraTerminador(char *str);
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal,
                    int corFundoAtual, int corLetraAtual,int tipo,int fechamento);
void criaArquivoSeNaoExistir(char *nome);



void atualizaTempoCircuito(struct MelhorVolta menorTempo);



void apresentaMsg( char *msg);
struct MelhorVolta ordenaCrescente(struct MelhorVolta *auxiliar,int qtdeRegistros);
struct MelhorVolta verificaMenorTempo(int codCircuito);
int verificaSeTemVolta(int codigoPiloto,int codigoCircuito);
int verificaPais(char *str,char *nomeArquivo);
int verificaExistenciaArq(char *nomeArquivo);
FILE * abreArquivo (char *nome, char *modo);
int leValidaInteiro(char *titulo,char *msgErro,int valorMinimo,int valorMaximo,int coluna,int linha);
int leInteiro(char *titulo,int coluna,int linha);
int validaInteiro(int nroInteiro,int valorMinimo,int valorMaximo);
int validaData(int dia, int mes, int ano);
int menuVertical(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini,
                 int moldura,int corFundoAtual, int corLetraAtual,int tipo,int fechamento);
float leReal(char *titulo,int coluna,int linha);
float validaReal(float nroReal,float valorMinimo,float valorMaximo);
float leValidaReal(char *titulo, char *erro, float valorMinimo,float valorMaximo,int coluna,int linha);
char leValidaOpcao(char *titulo,char *msgErro,char *str,int coluna,int linha);
void passaParaMaiusculo(char *nome);
void ordenaValores(struct Piloto *pilotos,int qtdeElementos);
void retornaCor(int corFundo,int corTexto);
void obtemDataHoraAtual(int *dia, int * mes, int *ano, int *hora,int *minutos, int *segundos);
//=====================================================================================================
int main(void)
{
// Declaracoes
   int dia,mes,ano,horas,minutos,segundos;
   char opcaoMenu;
   char *itensMenu[]={ "Pilotos",
                       "Circuitos",
                       "Voltas",
                       "Pesquisas e consultas",
                       "Paises cadastrados",
                       "Encerrar programa"
                     };
   
// Instrucoes

   criaArquivoSeNaoExistir(ARQ_PILOTOS);
   criaArquivoSeNaoExistir(ARQ_CIRCUITOS);  
   criaArquivoSeNaoExistir(ARQ_MELHORES_VOLTAS);

   do{
        
        gotoxy(34,8);
        printf("MENU PRINCIPAL");
        opcaoMenu = menuVertical(QTDE_ITENS_MENU_PRINCIPAL,itensMenu,BRANCO,VERMELHO,10,30,1,1,PRETO,BRANCO,2,1);
        switch(opcaoMenu)
        {
            case 1:
                controlePilotos();
                break;
                
            case 2:
                controleCircuitos();
                break;
            
            case 3:
               controleVoltas();
                break;
            
            case 4:
                consultasPesquisas();
                 break;
            
            case 5:
                listaPaises();
                break;
             
            default:
                break;        
        }
        system("CLS");
    }while(opcaoMenu!=QTDE_ITENS_MENU_PRINCIPAL);
    return 0;
}

//==============================================================================
// Objetivo   : Gerenciar os dados dos pilotos
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void controlePilotos()
{
     char opcaoMenu;
     char *itensMenu[]={ "Cadastrar piloto",
                         "Alterar dados piloto",
                         "Excluir Piloto",
                         "Pesquisa Piloto",
                         "Apresenta cadastrados",
                         "Voltar"
                       };
    do{
        system("CLS");
        gotoxy(32,8);
        printf("CONTROLE DOS PILOTOS");
        opcaoMenu = menuVertical(QTDE_ITENS_MENU_PILOTOS_FONTE,itensMenu,BRANCO,VERMELHO,10,30,1,1,PRETO,BRANCO,2,1);
        switch(opcaoMenu)
        {
            case 1:
                cadastraPiloto();
                break;
            case 2:
                alteraDadosPiloto();
                break;
            case 3:
               excluiPiloto();
                break;
            case 4:
                pesquisaPilotoPorNome();
                break;
            case 5:
                apresentaTodosPilotos();              

        }
        system("CLS");
    }while(opcaoMenu!=QTDE_ITENS_MENU_PILOTOS_FONTE);
}
//==============================================================================
// Objetivo   : Gerenciar um controle dos dados dos circuitos
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void controleCircuitos()
{
     char opcaoMenu;
     char *itensMenu[]={ "Cadastrar um circuito",
                         "Alterar dados de um circuito",
                         "Apresentar os circuitos",
                         "Voltar"
                       };
     do{
         gotoxy(34,8);
         printf("CONTROLE DOS CIRCUITOS\n");
         opcaoMenu = menuVertical(QTDE_ITENS_MENU_CIRCUITOS,itensMenu,BRANCO,VERMELHO,10,30,1,1,PRETO,BRANCO,2,1);
         switch(opcaoMenu)
         {
             case 1:
              cadastraCircuito();
              break;
             
             case 2:
              alteraDadosCircuito();  
              break;
             
             case 3:
              apresentaTodosCircuitos();
              break;
         }
         system("CLS");
  }while(opcaoMenu!=QTDE_ITENS_MENU_CIRCUITOS);
}
//==============================================================================
// Objetivo   : Gerenciar o controle dos dados das voltas
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void controleVoltas()
{
     char opcaoMenu;
     char *itensMenu[]={ "Cadastrar Melhor Volta",
                         "Alterar dados Melhor Volta",
                         "Excluir Melhor Volta",
                         "Apresenta Melhores Voltas",
                         "Voltar"
                       };
    do{
        
        gotoxy(32,8);
        printf("CONTROLE DAS VOLTAS");
        opcaoMenu = menuVertical(QTDE_ITENS_MENU_VOLTAS,itensMenu,BRANCO,VERMELHO,10,30,1,1,PRETO,BRANCO,2,1);
        switch(opcaoMenu)
        {
            case 1:
                cadastraMelhorVolta();
                break;
            case 2:
                alteraDadosMelhorVolta();
                break;
            case 3:
               excluiMelhorVolta();
                break;
            case 4:
                apresentaMelhoresVoltas();
        }
       system("CLS");
    }while(opcaoMenu!=QTDE_ITENS_MENU_VOLTAS);
}
//==============================================================================
// Objetivo   : Gerenciar a consulta e pesquisa do controle dos dados dos pilotos
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void consultasPesquisas()
{
     char opcaoMenu;
     char *itensMenu[]={ "Pesquisa Piloto por circuito e data",
                         "Pesquisa circuito por nome ou codigo",
                         "Lista pilotos de uma equipe em um periodo",
                         "Pesquisa pilotos, equipes e circuitos por tempo de volta",
                         "Voltar"
                       };
                         
     do{
         system("CLS");
         gotoxy(37,8);
         printf("RELATORIOS");
         opcaoMenu = menuVertical(QTDE_ITENS_MENU_RELATORIOS,itensMenu,BRANCO,VERMELHO,10,15,1,1,PRETO,BRANCO,2,1);
         switch(opcaoMenu)
         {
              case 1:
                pesquisaPilotoPorCircuitoData();
                break;
              
              case 2:
                pesquisaCircuitoPorNomeOuCod();
                break;
            
              case 3:
               listaPilotosEquipePorPeriodo();
                break;
            
              case 4:
                apresentaTudoPorTempo();
                break;            
         }
     }while(opcaoMenu!=QTDE_ITENS_MENU_RELATORIOS);
}

//==============================================================================
// Objetivo   : Cadastrar um piloto
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void cadastraPiloto()
{
    struct Piloto piloto;
    FILE *arquivo;
    int codRepetido,existePais;
    
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
       leValidaString("Pais=","Nome=invalido!",piloto.paisOrigem,TAM_NOME_PAIS,11,15);
       existePais=verificaPais(piloto.paisOrigem,ARQ_PAISES);
       if(existePais==0)
       {
            apresentaMsg("Pais nao cadastrado no arquivo paises");
            fclose(arquivo); 
            return;
       }
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
//====================================================================================================
// Objetivo   : Cadastrar um circuito
// Parâmetros : Nenhum
// Retorno    : Nenhum
//====================================================================================================
void cadastraCircuito()
{
     struct Circuito circuito;
     FILE *arq;
     int existePais;
     
     system("CLS");
     desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
     arq = abreArquivo(ARQ_CIRCUITOS,"ab");
     if(arq!=NULL)
     {
       leValidaString("Nome do circuito: ", "Nome=invalido", circuito.nome, TAM_NOME_CIRCUITO,11,11);
       fseek(arq, 0, SEEK_END);
       circuito.codigo = (ftell(arq)/sizeof(circuito))+1;
       leValidaString("Pais=","Nome=invalido!",circuito.pais,TAM_NOME_PAIS,11,12);
       existePais=verificaPais(circuito.pais,ARQ_PAISES);
       if(existePais==0)
       {
            apresentaMsg("Pais nao cadastrado no arquivo paises");
            fclose(arq);
            return;
       }
       circuito.tamanhoKm = leValidaReal("Tamanho do circuito(KM)=", "Tamanho do circuito(KM)= invalido",MIN_CIRCUITO, MAX_CIRCUITO,11,13);
       circuito.codPilotoMelhorVolta=0;
       circuito.melhorVolta.minutos=0;
       circuito.melhorVolta.segundos=0;
       circuito.melhorVolta.milisegundos=0;
       limpaJanela(11,11,19,69,PRETO);
       gotoxy(20,15);
       if(fwrite(&circuito,sizeof(circuito),1,arq)==1)
       {
            apresentaMsg("Cirucito cadastrado com sucesso");
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
     int verificaCodigoPiloto,dataValida,verificaCodCircuito,verificaVoltaCircuito,posicaoArq,flag=0;
    
     system("CLS");
     arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"ab");
     if(arquivo!=NULL)
     {
        posicaoArq=apresentaTodosPilotos();
        arquivo2=abreArquivo(ARQ_PILOTOS,"rb");
        if(arquivo2!=NULL)
        {
            fseek(arquivo2,0,SEEK_END);
            if(posicaoArq!=0)
            {
                fseek(arquivo2,(posicaoArq-1)*sizeof(piloto),SEEK_SET);
                if(fread(&piloto,sizeof(piloto),1,arquivo2)==1)
                {
                    voltaRapida.codPiloto=piloto.codigoId;
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
                    fseek(arquivo,0,SEEK_END);
                    if(posicaoArq!=0)
                    {
                        fseek(arquivo3,(posicaoArq-1)*sizeof(circuito),SEEK_SET);
                        if(fread(&circuito,sizeof(circuito),1,arquivo3)==1)
                        {
                           voltaRapida.codCircuito=circuito.codigo;
                        }
                    }
                    fclose(arquivo3);
                    verificaVoltaCircuito=verificaSeTemVolta(voltaRapida.codPiloto,voltaRapida.codCircuito);
                    if(verificaVoltaCircuito==2)
                    {
                       apresentaMsg("Esse piloto ja tem uma volta nesse circuito!");
                    }
                    else
                    {
                        desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                        leValidaString ("Nome Equipe=","Nome Equipe=invalido!",voltaRapida.nomeEquipe,TAM_NOME_EQUIPE,11,13);
                        do{
                            gotoxy(11,14);
                            printf("Data=");
                            voltaRapida.data.dia=leInteiro("",16,14);
                            voltaRapida.data.mes=leInteiro("/",19,14);
                            voltaRapida.data.ano=leInteiro("/",22,14);
                            dataValida=validaData(voltaRapida.data.dia,voltaRapida.data.mes,voltaRapida.data.ano);
                            if(dataValida==0)
                            {
                                gotoxy(11,14);
                                printf("Data=invalida       ");
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
                            apresentaMsg("Melhor volta cadastrada com sucesso!");
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
    
    if(itensMenu != NULL)
    {
        if(cont==0)
        {
           apresentaMsg("Nao ha cadastros!");
           opcaoMenu=0;
        }
        else
        {
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
// Objetivo   : Apresentar os dados de todos os circuitos
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
int apresentaTodosCircuitos()
{
    FILE *arquivo;
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
            arquivo=abreArquivo(ARQ_PILOTOS,"rb");
            if(arquivo!=NULL)
            {
                while(!feof(arquivo))
                {
                    if(fread(&piloto,sizeof(Piloto),1,arquivo)==1)
                    {
                        if(piloto.codigoId==circuitos[aux].codPilotoMelhorVolta)
                        {
                            strcpy(str,piloto.nome);
                            break;
                        }
                    }
                }
                fclose(arquivo);
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
    if(arquivo!=NULL)
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
// Objetivo   : Alterar dados de um piloto
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void alteraDadosPiloto()
{
     struct Piloto piloto;
     int posicaoArq,posicaoMaxima,opcaoAltera;
     int codRepetido,existePais;
     FILE *arquivo;
     char opcao,*itensMenu2[]={" Nome"," Pais"," Sexo"," Idade"," Salvar e Sair"},strAux[TAM_NOME_PAIS];
    
     do{
         system("CLS");
         gotoxy(68,21);
         printf("ESC=Voltar");
         posicaoArq=apresentaTodosPilotos();
         arquivo=abreArquivo(ARQ_PILOTOS,"r+b");
         if(arquivo!=NULL)
         {
            fseek(arquivo,0,SEEK_END);
            posicaoMaxima=ftell(arquivo)/sizeof(piloto);
            if(posicaoArq!=0)
            {
                fseek(arquivo,(posicaoArq-1)*sizeof(piloto),SEEK_SET);
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
                                   system("CLS");
                                   desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                   leValidaString("Pais=","Nome=invalido!",strAux,TAM_NOME_PAIS,11,12);
                                   existePais = verificaPais(strAux,ARQ_PAISES);
                                   if(existePais==0)
                                   {
                                        apresentaMsg("Pais nao cadastrado no arquivo paises!");
                                   }
                                   else
                                   {
                                        strcpy(piloto.paisOrigem,strAux);
                                        gotoxy(11,12);
                                        printf("Pais=%s",piloto.paisOrigem);
                                   }
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
           fclose(arquivo); 
        }
        system("CLS");
    }while(posicaoArq!=0);  
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
    
     do{
         flag=0;
         system("CLS");
         gotoxy(68,21);
         printf("ESC=Voltar");
         posicaoArq=apresentaMelhoresVoltas();
         arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"r+b");
         if(arquivo!=NULL)
         {
            fseek(arquivo,0,SEEK_END);
            posicaoMaxima=ftell(arquivo)/sizeof(MelhorVolta);
            if(posicaoArq!=0)
            {
               fseek(arquivo,(posicaoArq-1)*sizeof(MelhorVolta),SEEK_SET);
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
                                    dataValida=validaData(melhorVolta.data.dia,melhorVolta.data.mes,melhorVolta.data.ano);
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
//==============================================================================================
// Objetivo   : Alterar os dados de um circuito
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================================
void alteraDadosCircuito()
{
     struct Circuito circuito;
     int posicaoArq,posicaoMaxima,opcaoAltera;
     int codRepetido,existePais;
     FILE *arquivo;
     char opcao,*itensMenu2[]={"Nome","Pais","Tamanho","Salvar e Sair"},strAux[TAM_NOME_PAIS];
    
     do{
          system("CLS");
          gotoxy(68,21);
          printf("ESC=Voltar");
          posicaoArq = apresentaTodosCircuitos();
          arquivo=abreArquivo(ARQ_CIRCUITOS,"r+b");
          if(arquivo!=NULL)
          {
             fseek(arquivo,0,SEEK_END);
             posicaoMaxima=ftell(arquivo)/sizeof(circuito);
             if(posicaoArq!=0)
             {
                fseek(arquivo,(posicaoArq-1)*sizeof(circuito),SEEK_SET);
                if(fread(&circuito,sizeof(circuito),1,arquivo)==1)
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
                                     
                                   system("CLS");
                                   desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                   leValidaString("Pais=","Nome=invalido!",strAux,TAM_NOME_PAIS,11,12);
                                   existePais=verificaPais(strAux,ARQ_PAISES);
                                   if(existePais==0)
                                   {
                                        system("CLS");
                                        desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                        gotoxy(11,12);
                                        printf("Pais nao cadastrado no arquivo %s!",ARQ_PAISES);
                                        getch();
                                    }
                                    else
                                    {
                                        strcpy(circuito.pais,strAux);
                                        gotoxy(11,12);
                                        printf("Pais=%s",circuito.pais);
                                    }
                                    break;
                                
                                case 3:
                                     
                                    system("CLS");
                                    desenhaMoldura(10,10,20,70,PRETO,BRANCO,2,1);
                                    circuito.tamanhoKm=leValidaReal("Tamanho em KM a ser atualizado: ","Tamanho invalido!", MIN_CIRCUITO, MAX_CIRCUITO,11,12);
                            }
                       }while(opcaoAltera!=QTDE_ITENS_MENU_CIRCUITOS);
                       if(fseek(arquivo,(posicaoArq-1)*sizeof(circuito),SEEK_SET)==0)
                       {
                           if(fwrite(&circuito,sizeof(circuito),1,arquivo)==1)
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
             fclose(arquivo); 
         }
         system("CLS");
    }while(posicaoArq!=0);  
}
//==============================================================================
// Objetivo   : Excluir um piloto do arquivo
// Parâmetros : Nenhum
// Retorno    : Nenhum
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
            fseek(arquivo,0,SEEK_END);
            posicaoMaxima=ftell(arquivo)/sizeof(Piloto);
            if(posicaoArq!=0)
            {
                fseek(arquivo,(posicaoArq-1)*sizeof(Piloto),SEEK_SET);
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
                      arquivoTemp=abreArquivo(ARQ_PILOTOS_TEMP,"wb");
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
                                       apresentaMsg("Exclusao realizada com sucesso"); 
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
                          apresentaMsg("Esse piloto nao pode ser excluido pois ja tem registro de um volta");
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
         printf("ESC= VOLTAR");
         posicaoArq=apresentaMelhoresVoltas();
         arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
         if(arquivo!=NULL)
         {
            fseek(arquivo,0,SEEK_END);
            posicaoMaxima=ftell(arquivo)/sizeof(MelhorVolta);
            if(posicaoArq!=0)
            {
                fseek(arquivo,(posicaoArq-1)*sizeof(MelhorVolta),SEEK_SET);
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
//===========================================================================================================================
// Objetivo   : Apresentar os dados de um piloto
// Parâmetros : Dados de uma estrutura
// Retorno    : Nenhum
//===========================================================================================================================
void apresentaUmPiloto(struct Piloto piloto)
{
      char *sexoExtenso;   
    
      piloto.sexo=='M' ? (sexoExtenso="Masculino" ): (sexoExtenso="Feminino");
      printf("%-7d%-15.15s%-6d%-11.11s%-15.15s\n",piloto.codigoId,piloto.nome,piloto.idade,sexoExtenso,piloto.paisOrigem);
}
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
// Objetivo   : Apresentar os dados de uma melhor volta
// Parâmetros : Dados da estrutura melhor volta
// Retorno    : Nenhum
//==============================================================================
void apresentaUmaMelhorVolta(struct MelhorVolta melhorVolta)
{
     FILE *arquivo;
     FILE *arquivo2;
     struct Piloto piloto;
     struct Circuito circuito;
    
    
     arquivo=abreArquivo(ARQ_PILOTOS,"rb");
     arquivo2=abreArquivo(ARQ_CIRCUITOS,"rb");
     if(arquivo!=NULL && arquivo2!=NULL)
     {
        while(!feof(arquivo))
        {
              if(fread(&piloto,sizeof(Piloto),1,arquivo)==1)
              {
                 if(piloto.codigoId==melhorVolta.codPiloto)
                 {
                    break;
                 }
              }
        }
        while(!feof(arquivo2))
        {
               if(fread(&circuito,sizeof(Circuito),1,arquivo2)==1)
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
       fclose(arquivo);
       fclose(arquivo2);
     }
}
//==============================================================================                                   
//  Objetivo : Obter os dados do arquivo e coloca na memoria            
//  Parâmetros: endereço do contador,tamanho dos dados e endereço da stream do arquivo                    
//  Retorno   : endereço do vetor                                          
//============================================================================== 
void* obtemDados(int *cont,int tamanhoDados,char *nomeArq)
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
//==============================================================================
// Objetivo   : Pesquisar um piloto pelo nome ou id
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void pesquisaPilotoPorNome()
{
     FILE *arquivo;
     struct Piloto piloto,*pilotos;
     int qtdePilotos,cont=0,verifica=0,codigoPesquisa,opcao,flag,cont2=0;
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
        fseek(arquivo,0,SEEK_END);
    	qtdePilotos=ftell(arquivo)/sizeof(Piloto);
    	pilotos=(Piloto*)malloc(qtdePilotos*sizeof(Piloto));
    	if(pilotos != NULL)
        {
        	rewind(arquivo);
        	while(!feof(arquivo))
            {
    	        if(fread(&pilotos[cont],sizeof(Piloto),1,arquivo) == 1)
                {
                    cont++;
                }
            }
            fclose(arquivo);
            ordenaValores(pilotos,qtdePilotos);
            for(cont=0;cont<qtdePilotos;cont++)
            {
                flag=0;
                if(opcao==1)
                {             
                    strcpy(nomeAux,pilotos[cont].nome);
                    passaParaMaiusculo(nomeAux);
                    strcpy(nomeAux2,nomePesquisa);
                    passaParaMaiusculo(nomeAux2);
                    if(strstr(nomeAux,nomeAux2))
                    {
                        pilotos[cont].sexo=='M' ? (sexoExtenso="Masculino" ): (sexoExtenso="Feminino");
                        verifica=1;
                        flag=1;
                    }                         
                }
                else
                {
                    if(opcao==2)
                    {
                        if(pilotos[cont].codigoId==codigoPesquisa)
                        {
                            verifica=1;
                             flag=1;
                        } 
                    }     
                }
                if(flag==1)
                {
                   sprintf(dados,"%-7d%-15.15s%-6d%-11.11s%-15.15s",pilotos[cont].codigoId,pilotos[cont].nome,pilotos[cont].idade,
                            sexoExtenso,pilotos[cont].paisOrigem);
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
        else
        {
            apresentaMsg("Erro ao alocar memoria pilotos");
        }
    }
}
//==============================================================================
// Objetivo   : Listar os paises cadastrados
// Parâmetros : Nenhum
// Retorno    : Nenhum
//==============================================================================
void listaPaises()
{
     FILE *arquivo;
     char str[TAM_STR];
     int cont=0;
    
     system("CLS");
     arquivo=abreArquivo(ARQ_PAISES,"rb");
     gotoxy(35,3);
     printf("PAISES CADASTRADOS");
     if(arquivo!=NULL)
     { 
        while(!feof(arquivo))
        {
             if(fgets(str,sizeof(str),arquivo)!=NULL)
             {
                gotoxy(25,5+cont); 
                printf("%s",str);
                cont++;
             }
        }
        fclose(arquivo);
     }
     desenhaMoldura(2, 23,5+cont,66,PRETO,BRANCO,2,1);
     getch();
     system("CLS");
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
//======================================================================================================================================
// Objetivo   : Ler e validar uma string.
// Parâmetros : Endereço da string titulo,endereço da msg de Erro string e endereço da string,além da quantidade máxima de caracteres.
// Retorno    : Nenhum
//======================================================================================================================================
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
// Parâmetros : Endereços da string
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
// Objetivo   : atualizar o tempo de um circuito
// Parâmetros : endereço do vetor de estruturas da melhor volta daquela circuito
// Retorno    : nenhum
//==============================================================================
void atualizaTempoCircuito(struct MelhorVolta menorTempo)
{
     FILE *arquivo;
     struct Circuito circuito;
    
     arquivo=abreArquivo(ARQ_CIRCUITOS,"r+b");
     if(arquivo!=NULL)
     {
        fseek(arquivo,(menorTempo.codCircuito-1)*sizeof(Circuito),SEEK_SET);
        if(fread(&circuito,sizeof(Circuito),1,arquivo)==1)
        {
            circuito.codPilotoMelhorVolta=menorTempo.codPiloto;
            circuito.melhorVolta=menorTempo.tempo;
        }
        if(fseek(arquivo,(menorTempo.codCircuito-1)*sizeof(Circuito),SEEK_SET)==0)
        {
           if(fwrite(&circuito,sizeof(Circuito),1,arquivo)!=1)
           {
                apresentaMsg("Erro ao atualizado tempo do circuito");
           }
        }
        fclose(arquivo); 
     }
}
//==============================================================================                                  
//  Objetivo :  Apresentar mensagem de erro          
//  Parâmetros: Msg                    
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
// Objetivo   : Verificar o menor tempo dentro do arquivo voltas
// Parâmetros : Codigo do circuito
// Retorno    : Menor tempo de um cirucito
//==============================================================================
struct MelhorVolta verificaMenorTempo(int codCircuito)
{
       
       FILE *arquivo;
       int alvo,cont1=0,cont2=0;
       struct MelhorVolta *auxiliar,menorTempo,auxCont;
    
    
       arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
       if(arquivo!=NULL)
       {
          while(!feof(arquivo))
          {
                if(fread(&auxCont,sizeof(MelhorVolta),1,arquivo) == 1)
                {
                   if(auxCont.codCircuito==codCircuito)
                   {
                      cont2++;
                   }
                }
          }
          auxiliar=(MelhorVolta*)malloc(cont2*sizeof(MelhorVolta));      
          if(auxiliar!=NULL)
          {
             rewind(arquivo);
             while(!feof(arquivo))
             {
                   if(fread(&auxCont,sizeof(MelhorVolta),1,arquivo) == 1)
                   {
                      if(auxCont.codCircuito==codCircuito)
                      {
                         auxiliar[cont1]=auxCont;
                         cont1++;
                      }
                   }
             }
          }
          else
          {
             apresentaMsg("Erro ao alocar memoria");
             cont1=0; 
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
       }else
       {
          menorTempo=ordenaCrescente(auxiliar,cont2);
       }
       if(auxiliar!=NULL)
       {
          free(auxiliar);
       }
       return menorTempo; 
}
//=================================================================================
// Objetivo   : Ordenar vetor de estruturas em ordem crescente
// Parâmetros : Endereço do vetor de estruturas e quantidade de registros
// Retorno    : Primeira estrutura do vetor
//=================================================================================
struct MelhorVolta ordenaCrescente(struct MelhorVolta *auxiliar,int qtdeRegistros)
{
       int alvo,cont1,flag;
       struct MelhorVolta auxOrdena;
       for(alvo=0;alvo<qtdeRegistros-1;alvo++)
       {
           for(cont1=alvo+1;cont1<qtdeRegistros;cont1++)
           {
               flag=0;
               if(auxiliar[alvo].tempo.minutos>auxiliar[cont1].tempo.minutos)
               {
                  flag=1;
               }
               else
               {
                  if(auxiliar[alvo].tempo.minutos==auxiliar[cont1].tempo.minutos && auxiliar[alvo].tempo.segundos>auxiliar[cont1].tempo.segundos)
                  {
                     flag=1;
                  }
                  else
                  { 
                    if(auxiliar[alvo].tempo.minutos==auxiliar[cont1].tempo.minutos &&  
                        auxiliar[alvo].tempo.segundos==auxiliar[cont1].tempo.segundos && 
                        auxiliar[alvo].tempo.milisegundos>auxiliar[cont1].tempo.milisegundos)
                    {
                        flag=1;
                    }
               }          
            }
            if(flag==1)
            {
               auxOrdena=auxiliar[alvo];
               auxiliar[alvo]=auxiliar[cont1];
               auxiliar[cont1]=auxOrdena; 
            }
        }
    }
    return auxiliar[0];
}
//==============================================================================
// Objetivo   : Verificar se um piloto tem registro de alguma volta em um circuito
// Parâmetros : Codigo de id do piloto
// Retorno    : 1-se tiver ou 2-se tiver no circuito informado ou 0-se não tiver
//==============================================================================
int verificaSeTemVolta(int codigoPiloto,int codigoCircuito)
{
    FILE *arquivo;
    struct MelhorVolta melhorVolta;
    int existe=0;
    
    arquivo=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
    if(arquivo != NULL)
    {
       while(!feof(arquivo))
       {
             if(fread(&melhorVolta,sizeof(melhorVolta),1,arquivo)==1)
             {
                if(melhorVolta.codPiloto==codigoPiloto)
                {
                   existe = 1;
                  
                   if(melhorVolta.codCircuito==codigoCircuito)
                   {
                      existe=2;
                   }
                   break;
                }    
             }
       }
       fclose(arquivo);
    }
    return existe;
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
      return arquivo; 
}
//====================================================================================================
// Objetivo   : Ler e validar um inteiro
// Parâmetros : Referência aos titulo, msg de erro, valores min e max, coluna e linha 
// Retorno    : Numero inteiro valido
//====================================================================================================
int leValidaInteiro(char *titulo,char *msgErro,int valorMinimo,int valorMaximo,int coluna,int linha)
{
    
    int nroInteiro,flag;
    do{
        nroInteiro=leInteiro(titulo,coluna,linha);
        flag = validaInteiro(nroInteiro,valorMinimo,valorMaximo);
        if(flag==0)
        {
            gotoxy(coluna,linha);
            printf("%s.(Min %d - Max %d)         ",msgErro,valorMinimo,valorMaximo);
            getch();
            gotoxy(coluna,linha);
			limpaJanela(linha,coluna,linha,strlen(msgErro)+coluna+30,PRETO);
        }
    }while(flag==0);
    return nroInteiro;
}
//==============================================================================
// Objetivo   : Ler um numero inteiro
// Parâmetros : Endereço da string titulo, coluna e linha
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
        if(ret==0)
        {
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
    
    int flag;
    if(nroInteiro<valorMinimo || nroInteiro>valorMaximo)
    {
        flag=0;
    }
    else
    {
        flag=1;
    } 
    return flag;
}
/********************************************************
 Nome       : validaData
 Objetivo   : Efetua a validação de uma data a partir das 
              informações do dia, mes e ano
 Parâmetros : dia, mes e ano   
 Retorno    : 1 - data valida ou 0 - data invalida  
********************************************************/
int validaData(int dia, int mes, int ano)
{
    int retorno=1;
    
    if(ano<2014 || mes<1 || mes >12 || dia<1 || dia >31)
       return 0;
          
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

        if(moldura)
           	limpaJanela(linha-2,coluna-1,linha+n,coluna+tamMaiorTexto+2,corFundoAtual);
        else
           	limpaJanela(linha,coluna,linha+n,coluna+tamMaiorTexto,corFundoAtual);
   
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
// Parâmetros : Numero rea, valor minimo e valor maximo
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
//=======================================================================================================
// Objetivo   : Ler e validar um numero real
// Parâmetros : Endereço da string titulo,endereço da string msg erro, valor minimo e valor maximo
// Retorno    : Numero real valido
//=======================================================================================================   
float leValidaReal(char *titulo, char *erro, float valorMinimo,float valorMaximo,int coluna,int linha)
{
    int nroReal,flag;
    do{
        nroReal=leReal(titulo,coluna,linha);
        flag=validaReal(nroReal,valorMinimo,valorMaximo);
        if(flag==0)
        {
            gotoxy(coluna,linha);
            printf("%s.(Min %.1f - Max %.1f)",erro,valorMinimo,valorMaximo);
            getch();
            gotoxy(coluna,linha);
			limpaJanela(linha,coluna,linha,strlen(erro)+coluna+25,PRETO);
        }
    }while(flag==0);
    return nroReal;
    
}
//========================================================================================
// Objetivo   : Ler e validar uma opcao
// Parâmetros : Endereços das strings: titulo,msgErro e string com as opcaoes de validação
// Retorno    : Caracter valido
//========================================================================================
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
//  Objetivo : Passa um nome para maiusculo.           
//  Parâmetros: Endereço da string nome                    
//  Retorno   : Nenhum                                          
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
// Objetivo   : Ordenar  a estrutura em ordem alfabetica por nome
// Parâmetros : Endereço da struct e qtde de elementos.
// Retorno    : Nenhum
//==============================================================================
void ordenaValores(struct Piloto *pilotos,int qtdeElementos)
{
    int alvo,cont;
    struct Piloto auxOrdena;
    for(alvo=0;alvo<qtdeElementos-1;alvo++)
    {
        for(cont=alvo+1;cont<qtdeElementos;cont++)
        {
            if(strcmpi(pilotos[alvo].nome,pilotos[cont].nome)==1)
            {
                auxOrdena=pilotos[alvo];
                pilotos[alvo]=pilotos[cont];
                pilotos[cont]=auxOrdena;
            }
        }
    }
}
//==============================================================================                                     
//  Objetivo :  Retorna a cor de fundo e de texto              
//  Parâmetros: corFundo - cor de fundo, corTexto - cor do texto                        
//  Retorno   : Nenhum                                          
//============================================================================== 
void retornaCor(int corFundo,int corTexto)
{
     textbackground(corFundo);
     textcolor(corTexto);
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
     FILE *arqPiloto;
     struct Circuito circuito;
     struct MelhorVolta volta;
     struct Piloto piloto;
     struct Data data;
     int nro,opcao,dataValida,cont=0,cont2=0,opcaoMenu,flag=0;
     char **itensMenu=NULL,**itensMenu2=NULL,dados[TAM_MSG];

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
            dataValida=validaData(data.dia,data.mes,data.ano);
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
    arqVoltas=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
    arqPiloto=abreArquivo(ARQ_PILOTOS,"rb");
    if(arqVoltas!=NULL && arqPiloto!=NULL)
    {
        while(!feof(arqVoltas))
        {
            if(fread(&volta,sizeof(MelhorVolta),1,arqVoltas)==1)
            {
                if(opcao=='S')
                {
                    if(nro==volta.codCircuito && data.ano==volta.data.ano && data.mes==volta.data.mes && data.dia==volta.data.dia)
                    {
                        if(fread(&piloto,sizeof(Piloto),1,arqPiloto)==1)
                        { 
                           sprintf(dados,"%-15.15s%-10.10s%02d:%02d.%-05.03d\n",piloto.nome,volta.nomeEquipe,
                               volta.tempo.minutos,volta.tempo.segundos,volta.tempo.milisegundos);
                               flag=1;
                        }
                    }
                }
                else
                {
                    if(nro==volta.codCircuito)
                    {
                        if(fread(&piloto,sizeof(Piloto),1,arqPiloto)==1)
                        { 
                             sprintf(dados,"%-15.15s%-10.10s%02d:%02d.%-05.03d\n",piloto.nome,volta.nomeEquipe,
                                     volta.tempo.minutos,volta.tempo.segundos,volta.tempo.milisegundos);
                                     flag=1;
                        }
                    }
                }
                itensMenu2=(char**)realloc(itensMenu2,sizeof(char*)*(cont2+1));
                if(itensMenu2 != NULL)
                {
                       itensMenu2[cont2] = (char*) malloc(sizeof(char)*sizeof(dados));
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
            }
            
        }
        fclose(arqVoltas);
        fclose(arqPiloto);
        if(itensMenu2 != NULL)
        {
            if(flag==0)
            {
               apresentaMsg("Nenhum piloto encontrado!");
               opcaoMenu=0;
            }
            else
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
        }
    }
}

//=========================================================================================
// Objetivo   : Pesquisar as informações de um circuito atraves de parte do nome ou codigo
// Parâmetros : Nenhum
// Retorno    : Nenhum
//=========================================================================================
void pesquisaCircuitoPorNomeOuCod()
{
     FILE *arquivo;
     FILE *arquivo2;
     char str[TAM_NOME_PILOTO];
     struct Piloto piloto;
     struct Circuito circuito,*circuitos;
     int verifica=0,cont=0,codigoPesquisa,qtdeCircuitos,opcao,flag,cont2=0,opcaoMenu;
     char nomePesquisa[TAM_NOME_CIRCUITO],dados[TAM_MSG];
     char nomeAux[TAM_NOME_CIRCUITO],nomeAux2[TAM_NOME_CIRCUITO];
     char *itensMenu[]={"Pesquisa por nome","Pesquisa por Codigo"};
     char **itensMenu2=NULL;
    
     system("CLS");
     arquivo=abreArquivo(ARQ_CIRCUITOS,"rb");
     if(arquivo!=NULL)
     {
        opcao = menuVertical(2,itensMenu,BRANCO,VERMELHO,13,30,1,1,PRETO,BRANCO,2,1);
        system("CLS");
        if(opcao==1)
        {
            leValidaString("Nome=","nome invalido!",nomePesquisa,TAM_NOME_CIRCUITO,11,12);
        }
        else
        {
            if(opcao==2)
            {
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
        fseek(arquivo,0,SEEK_END);
    	qtdeCircuitos=ftell(arquivo)/sizeof(Circuito);
    	circuitos=(Circuito*)malloc(qtdeCircuitos*sizeof(Circuito));
    	if(circuitos!=NULL)
        {
            rewind(arquivo);
            while(!feof(arquivo))
            {
    	        if(fread(&circuitos[cont],sizeof(Circuito),1,arquivo) == 1)
                {
                    cont++;
                }
            }
            fclose(arquivo);
            system("CLS");
            for(cont=0;cont<qtdeCircuitos;cont++)
            {
                flag=0;
                if(opcao==1)
                {
                    strcpy(nomeAux,circuitos[cont].nome);
                    passaParaMaiusculo(nomeAux);
                    strcpy(nomeAux2,nomePesquisa);
                    passaParaMaiusculo(nomeAux2);
                    if(strstr(nomeAux,nomeAux2))
                    {
                        verifica=1;
                        flag=1;
                    }                         
                }
                else
                {
                    if(opcao==2)
                    {
                        if(circuitos[cont].codigo==codigoPesquisa)
                        {
                            verifica=1;
                            flag=1;
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
}


//===============================================================================
// Objetivo   : Listar todos os pilotos de uma equipe em um periodo      arrumar
// Parâmetros : Nenhum
// Retorno    : Nenhum
//===============================================================================
void listaPilotosEquipePorPeriodo()
{
     FILE *arquivoVoltas;
     FILE *arquivoPilotos;
     FILE *arquivoCircuitos;
     struct MelhorVolta volta;
     struct Piloto piloto,*pilotos;
     struct Circuito circuito;
     char **itensMenu2=NULL;
     int qtdePilotos,cont=0,cont2=0,dataValida,invalido,flag=0,flag2,flag3,opcaoMenu;
     char nomePesquisa[TAM_NOME_EQUIPE],dados[TAM_MSG],str[TAM_NOME_CIRCUITO],msg[TAM_MSG];
     struct Data data1,data2;
     float auxData,auxData1,auxData2;
    
     system("CLS");
     arquivoVoltas=abreArquivo(ARQ_MELHORES_VOLTAS,"rb");
     arquivoPilotos=abreArquivo(ARQ_PILOTOS,"rb");
     arquivoCircuitos=abreArquivo(ARQ_CIRCUITOS,"rb");
     if(arquivoVoltas!=NULL && arquivoPilotos!=NULL && arquivoCircuitos!=NULL)
     {
        fseek(arquivoPilotos,0,SEEK_END);
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
           ordenaValores(pilotos,qtdePilotos);
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
                dataValida=validaData(data1.dia,data1.mes,data1.ano);
                if(dataValida==0)
                {
                    gotoxy(11,12);
                    printf("Data=invalida       ");
                    getch();
                    limpaJanela(12,11,12,50,PRETO);
                }
            }while(dataValida==0);
            auxData1=(float)(data1.dia/365)+(data1.mes/12)+data1.ano;
            do{
                gotoxy(28,12);
                printf("Ate:");
                data2.dia=leInteiro("",33,12);
                data2.mes=leInteiro("/",35,12);
                data2.ano=leInteiro("/",38,12);
                dataValida=validaData(data2.dia,data2.mes,data2.ano);
                if(dataValida==0)
                {
                    gotoxy(28,12);
                    printf("Data=invalida       ");
                    getch();
                    limpaJanela(12,28,12,50,PRETO);
                }
            }while(dataValida==0);
            auxData2=(float)(data2.dia/365)+(data2.mes/12)+data2.ano;
            system("CLS");

            flag3=0;
            for(cont=0;cont<qtdePilotos;cont++)
            { 
                rewind(arquivoVoltas); 
                while(!feof(arquivoVoltas))
                {
                    flag2=0;
                    if(fread(&volta,sizeof(MelhorVolta),1,arquivoVoltas) == 1)
                    {
                        invalido=0;                         
                        if((stricmp(nomePesquisa,volta.nomeEquipe)==0) && volta.codPiloto==pilotos[cont].codigoId)
                        {
                            flag=1;
                            flag2=1;
                            auxData=(float)(volta.data.dia/365)+(volta.data.mes/12)+volta.data.ano;
                            if(auxData<auxData1 || auxData>auxData2)
                            {
                                invalido=1;
                            }
                        }
                        if(invalido==0 && flag2==1)
                        {
                           flag3=1;
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
                                   }
                                   else
                                   {
                                       apresentaMsg("Erro ao alocar memoria para uma string!");
                                   }
                                   cont2++;   
                            } 
                        }
                    }
                }
            }
            if(itensMenu2!=NULL)
            {
                 if(cont2-1==0)
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
            
           if(flag==0)
           {
                apresentaMsg("Essa equipe nao existe!");
           }
           else
           {
                if(flag3==0)
                {
                    sprintf(msg,"nenhum piloto correu por essa equipe entre %02d/%02d/%4d e %02d/%02d/%4d",data1.dia,data1.mes,data1.ano,
                           data2.dia,data2.mes,data2.ano);
                    apresentaMsg(msg);
                }
            } 
            free(pilotos);
            pilotos=NULL;
            fclose(arquivoVoltas);
            fclose(arquivoCircuitos);
            fclose(arquivoPilotos);
       }
    }
}

//==============================================================================
//Objetivo: Apresentar dados a partir de um tempo informado pelo usuario
//Parâmetros: Nenhum
//Retorno: Nenhum
//============================================================================== 
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
         opcaoMenu = menuVertical(cont2,itensMenu2,BRANCO,AZUL,10,10,1,1,PRETO,BRANCO,2,2);
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
