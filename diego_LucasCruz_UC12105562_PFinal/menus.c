#include <stdio.h>
#include "defines.h"
#include "structs.h"
#include "menus.h"
#include "funcoesGenericas.h"
#include "pilotos.h"
#include "circuitos.h"
#include "melhoresVoltas.h"

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
        
        gotoxy(34,8);
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
                         "Pesquisa Circuito por nome ou codigo",
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
