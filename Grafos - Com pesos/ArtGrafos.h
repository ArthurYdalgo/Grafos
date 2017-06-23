#ifndef ARTGRAFOS_H_INCLUDED
#define ARTGRAFOS_H_INCLUDED

typedef struct l_est l_est;
typedef struct Vrtc Vrtc;
typedef struct l_lig l_lig;
typedef struct lig lig;

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
    int peso;
    char *str;
    l_lig *pathsIn, *pathsOut;
} Vrtc;

///Estrutura ligação
typedef struct lig
{
    int peso;
    Vrtc *Vprox;
} lig;

///Criação e alocação
Vrtc *AlocaVert();
int  CriarVertice (l_est *Li);

///Menor caminho
int  MenorCaminho (l_est *Li, int idI, int idF);
int  MenorCaminhoRec (l_est *Li, Vrtc *V,int idI,int idF,int qnt);

///Utilitarias
int  ConfereSobras (l_est *Li, Vrtc *V);
int  ConexaoRepetida (int peso,int idO, int idI, l_est *Li);
void ReIdVertices (l_est *Li);
void MostraVertcs (l_est *Li);
void ZeraChecks(l_est *Li);

///Mostragem
void MostraConexao (l_est *Li);
void MostraArranjos (l_est *Li);
void ImprimiVrtc (Vrtc *V);
void ImprimeLig(lig Lig);

///Novas conexoes
void NovaConexao(l_est *Li);
int  ConectaVertc (int peso,int idS, int idD, l_est *Li);

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

///Estrutura Lista de vertices
typedef struct l_est
{
    Vrtc **Vert;
    int qtdElem, maxElem;
} l_est;


///Estrutura lista de ligações
typedef struct l_lig
{
    lig *lig;
    int qtdElem, maxElem;
} l_lig;


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
