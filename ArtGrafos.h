#ifndef ARTGRAFOS_H_INCLUDED
#define ARTGRAFOS_H_INCLUDED

///GRAFO E LISTA

typedef struct info
{
   int check;
   char *str;
   char *nome;
   int id;
   float fl;
   int it;
   int pathsO;
   int pathsI;
} info;

typedef struct Vrtc
{
   info Inf;
   struct Vrtc **Path;
} Vrtc;

typedef struct l_est{
    Vrtc **Vert;
    int qtdElem;
    int maxElem;
} l_est;

///GRAFO E LISTA CABEÇALHO

Vrtc *AlocaVert();
int CriarVertice(l_est *Li);
int ConectaVertc(int idS,int idD,l_est *Li);
int SelecionaVertc(l_est *Li,Vrtc *Vs);
void MostraVertc(l_est *Li);
void NovaConexao();

l_est*  CriarLista ();
l_est*  CriarLista_C ();
int     Dest_Lista (l_est *Li);
int     InserirFim (l_est *Li, Vrtc *Dados);
int     InserirInicio (l_est *Li, Vrtc *Dados);
int     InserirPos (l_est *Li, Vrtc *Dados, int pos);
int     RemoveDado(l_est *Li, Vrtc *Dados);
int     RemoverPos (l_est *Li, int pos);
Vrtc *    BuscarPos (l_est *Li, int pos);
int     BuscarDado (l_est *Li, Vrtc *Dados);


#endif // ARTGRAFOS_H_INCLUDED
