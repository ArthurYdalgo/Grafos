#ifndef ARTGRAFOS_H_INCLUDED
#define ARTGRAFOS_H_INCLUDED

typedef struct l_est l_est;
typedef struct Vrtc Vrtc;

///GRAFO

typedef struct Vrtc{
  int id;
  char *str;
  l_est *pathsIn, *pathsOut;
} Vrtc;

Vrtc *AlocaVert();
int CriarVertice(l_est *Li);
int ConectaVertc(int idS,int idD,l_est *Li);
void MostraVertcs(l_est *Li);
void NovaConexao();
void DeletarVertice(l_est *Li);
void ReIdVertices(l_est *Li);
void MostraConexao(l_est *Li);
void MostraArranjos(l_est *Li);
int MostrarArranjoRec(Vrtc*V);
void ImprimiVrtc(Vrtc *V);
void DesconectaVert(l_est *Li);
void ExportaGrafo(l_est *Li);
void ImportaGrafo(l_est *Li);

///Lista

typedef struct l_est {
  Vrtc **Vert;
  int qtdElem, maxElem;
} l_est;

l_est*  CriarLista ();
int ConfereSobras(l_est *Li,Vrtc *V);
l_est*  CriarLista_C ();
int     Dest_Lista (l_est *Li);
int     InserirFim (l_est *Li, Vrtc *V);
int     InserirInicio (l_est *Li, Vrtc *Dados);
int     InserirPos (l_est *Li, Vrtc *Dados, int pos);
int     RemoverPos (l_est *Li, int pos);
Vrtc *    BuscarPos (l_est *Li, int pos);
int     BuscarDado (l_est *Li, Vrtc *Dados);

#endif // ARTGRAFOS_H_INCLUDED
