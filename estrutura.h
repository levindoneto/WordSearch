        // Structs usadas no programa
typedef char TipoInfo[25];

struct s_TipoPtNo{
       int linha;
       struct s_TipoPtNo* prox;
       };
typedef struct s_TipoPtNo TipoPtNo;

struct TNodoA{
TipoInfo info;
int FB;
struct TNodoA *esq;
struct TNodoA *dir;
struct TNodoA *listaLSE;
};
typedef struct TNodoA TNodoA;

typedef struct TNodoA pNodoA;


        //Funções para a AVL
int Altura (pNodoA * a);
int Calcula_FB(pNodoA * a);
void Desenha(pNodoA * a , int nivel);
int is_avl(pNodoA * a);
//Rotacoes usadas
pNodoA * rotacao_direita(pNodoA * pt);
pNodoA * rotacao_esquerda(pNodoA * pt);
pNodoA * rotacao_dupla_direita (pNodoA * pt);
pNodoA * rotacao_dupla_esquerda (pNodoA * pt);
pNodoA * Caso1 (pNodoA * a , int *ok);
pNodoA * Caso2 (pNodoA * a , int *ok);
//Indexação de palavras
pNodoA * InsereAVL (pNodoA * a, TipoInfo x, int *ok, int linha);
pNodoA * consultar(pNodoA *raiz, TipoInfo word);                      // Funcao para consultar os nods da AVL
void imprimeAVL(pNodoA *raiz,FILE *saida);


        //Funções Lista LSE
TipoPtNo* cria_lista(void);
TipoPtNo* insere_ord (TipoPtNo* l, int linha);
void imprime(TipoPtNo* l,FILE *saida);
TipoPtNo* destroi(TipoPtNo* ptLista);
//void le_dados (TipoInfoNo *dados);
