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
