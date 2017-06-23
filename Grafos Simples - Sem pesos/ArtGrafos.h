#ifndef ARTGRAFOS_H_INCLUDED
#define ARTGRAFOS_H_INCLUDED

typedef struct l_est l_est;
typedef struct Vrtc Vrtc;

/// ******************
/// ******************

      ///GRAFO

/// ******************
/// ******************

///Estrutura vértice
typedef struct Vrtc
{
    int id;
    int check;
    char *str;
    l_est *pathsIn, *pathsOut;
} Vrtc;

///Criação e alocação
Vrtc *AlocaVert();
int  CriarVertice (l_est *Li);

///Menor caminho
int  MenorCaminho (l_est *Li, int idI, int idF);
int  MenorCaminhoRec (l_est *Li, Vrtc *V,int idF,int qnt);

///Utilitarias
int  ConfereSobras (l_est *Li, Vrtc *V);
int  ConexaoRepetida (int idO, int idI, l_est *Li);
void ReIdVertices (l_est *Li);
void MostraVertcs (l_est *Li);
void ZeraChecks(l_est *Li);

///Mostragem
void MostraConexao (l_est *Li);
void MostraArranjos (l_est *Li);
void ImprimiVrtc (Vrtc *V);

///Novas conexoes
void NovaConexao(l_est *Li);
int  ConectaVertc (int idS, int idD, l_est *Li);

///Desconectar
void DesconectaVert (l_est *Li);
void DeletarVertice (l_est *Li);

///Importar e exportar
void ExportaGrafo (l_est *Li);
void ImportaGrafo (l_est *Li);

/// ******************
/// ******************

       ///Lista

/// ******************
/// ******************

///Estrutura Lista
typedef struct l_est
{
    Vrtc **Vert;
    int qtdElem, maxElem;
} l_est;

///Criação e destruição
l_est*  CriarLista ();
int     Dest_Lista (l_est *Li);

///Inserção
int     InserirFim (l_est *Li, Vrtc *V);

///Remoção
int     RemoverPos (l_est *Li, int pos);
int     RemoveTodos (l_est *Li);

///Busca
Vrtc *  BuscarPos (l_est *Li, int pos);
int     BuscarDado (l_est *Li, Vrtc *Dados);

#endif // ARTGRAFOS_H_INCLUDED
