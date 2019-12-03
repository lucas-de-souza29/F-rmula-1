#include <stdio.h>
#include <conio.c>
#include "defines.h"
#include "structs.h"
#include "funcoesGenericas.h"
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
   
// Instruções

   criaArquivoSeNaoExistir(ARQ_PILOTOS);
   criaArquivoSeNaoExistir(ARQ_CIRCUITOS);  
   criaArquivoSeNaoExistir(ARQ_MELHORES_VOLTAS);
   
   limpaJanela(1,1,25,80,PRETO); 
   desenhaMoldura(5,5,10,70,PRETO,BRANCO,2,1);

   gotoxy(15,6);
   fprintf(stdout,"Bem-vindo ao Sistema de Controle de Provas da Formula 1");
   obtemDataHoraAtual(&dia,&mes,&ano,&horas,&minutos, &segundos) ; 
                        
   gotoxy(18,8);
   fprintf(stdout," Data : %02d/%02d/%02d  Hora : %02d:%02d:%02d",dia,mes,ano,horas,minutos,segundos);   
   getch();
   system("CLS");

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
