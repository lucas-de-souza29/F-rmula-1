int validaDataRestrita(int dia, int mes, int ano);
void* obtemDados(int *cont,int tamanhoDados,char *nomeArq);
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, 
                     int colFinal,int corFundo);
void leValidaString (char *titulo, char *msgErro, char *str, int max,int coluna,int linha);
void tiraTerminador(char *str);
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal,
          int corFundoAtual, int corLetraAtual,int tipo,int fechamento);
void criaArquivoSeNaoExistir(char *nome);
void apresentaMsg( char *msg);
struct MelhorVolta ordenaCrescente(struct MelhorVolta *auxiliar,int qtdeRegistros);
int verificaExistenciaArq(char *nomeArquivo);
FILE * abreArquivo (char *nome, char *modo);
int leValidaInteiro(char *titulo,char *msgErro,int valorMinimo,int valorMaximo,int coluna,int linha);
int leInteiro(char *titulo,int coluna,int linha);
int validaInteiro(int nroInteiro,int valorMinimo,int valorMaximo);
int validaData(int dia, int mes, int ano,int diaAtual,int mesAtual,int anoAtual);
int menuVertical(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini,
                int moldura,int corFundoAtual, int corLetraAtual,int tipo,int fechamento);
float leReal(char *titulo,int coluna,int linha);
float validaReal(float nroReal,float valorMinimo,float valorMaximo);
float leValidaReal(char *titulo, char *erro, float valorMinimo,float valorMaximo,int coluna,int linha);
char leValidaOpcao(char *titulo,char *msgErro,char *str,int coluna,int linha);
void passaParaMaiusculo(char *nome);
int ordenaValores(const void *p1, const void*p2);
void retornaCor(int corFundo,int corTexto);
void obtemDataHoraAtual(int *dia, int * mes, int *ano, int *hora,int *minutos, int *segundos);
