#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define TAM_VET 10000
#define Path_MAX 1000
#include "ArtGrafos.h"
///LISTA

l_est* CriarLista()
{
    l_est* Li = (l_est*) malloc (sizeof (l_est));
    Li->Vert = (Vrtc**) malloc (1 * sizeof (Vrtc));
    Li->qtdElem = 0;
    Li->Vert[0] = NULL;
    if (!Li)
        return NULL;
    Li->maxElem = TAM_VET;
    return Li;
}

int Dest_Lista (l_est *Li)
{
    if (!Li)
        return 0;
    free (Li);
    return 1;
}

int InserirFim (l_est *Li, Vrtc *V)
{
    if (!Li)
        return -1;
    if (Li->qtdElem == Li->maxElem)
        return 0;
    Li->Vert = (Vrtc**) realloc (Li->Vert, ( (Li->qtdElem) + 1) * sizeof (Vrtc));
    Li->Vert[Li->qtdElem] = V;
    Li->qtdElem++;
    return 1;
}

int InserirInicio (l_est *Li, Vrtc *Dados)
{
    int i;
    if (Li->qtdElem == Li->maxElem)
        return 0;
    for (i = Li->qtdElem; i >= 0; i--)
        Li->Vert[i + 1] = Li->Vert[i];
    Li->Vert[0] = Dados;
    Li->qtdElem++;
    return 1;
}


int RemoverPos (l_est *Li, int Pos)
{
    int i;
    for (i = Pos; i < Li->qtdElem - 1; i++)
        Li->Vert[i] = Li->Vert[i + 1];
    Li->qtdElem--;
    return 1;
}


Vrtc *BuscarPos (l_est *Li, int Pos)
{
    return Li->Vert[Pos];
}

int BuscarDado (l_est *Li, Vrtc *Dados)
{
    int i;
    for (i = 0; i < Li->qtdElem; i++)
    {
        if (Li->Vert[i] == Dados)
            return i;
    }
    return -1;
}

///GRAFOS

Vrtc * AlocaVert (l_est *Li)
{
    Vrtc *v = (Vrtc*) malloc (sizeof (Vrtc));
    v->check = 0;
    v->id = Li->qtdElem;
    v->pathsIn = CriarLista();
    v->pathsOut = CriarLista();
    return v;
}

int CriarVertice (l_est *Li)
{
    system ("cls");
    Vrtc *v = AlocaVert (Li);
    char *nome = (char*) malloc (sizeof (char));
    if (v)
    {
        printf ("De um nome ao seu vertice: ");
        scanf ("%s", nome);
        v->str = (char*) malloc (strlen (nome) * sizeof (char));
        strcpy (v->str, nome);
        free (nome);
        InserirFim (Li, v);
        return 1;
    }
    else
    {
        return -1;
    }
}
void NovaConexao (l_est *Li)
{
    int idE, id, esc;
    if (Li->qtdElem == 0)
    {
        printf ("Nao ha vertices\n");
        system ("pause");
    }
    else
    {
        MostraVertcs (Li);
        printf ("Escolha o vertice de saida: ");
        scanf ("%d", &idE);
        if (idE < Li->qtdElem && idE >= 0)
        {
            printf ("Escolha o vertice destino: ");
            scanf ("%d", &id);
            if (idE < Li->qtdElem && idE >= 0)
            {
                ConectaVertc (idE, id, Li);
                printf ("Deseja que seja de mão dupla? (0 ou 1): ");
                scanf ("%d", &esc);
                if (esc == 1)
                    ConectaVertc (id, idE, Li);
            }
        }
    }
}

void DesconectaVert(l_est *Li)
{

}

void MostraConexao (l_est *Li)
{
    int idE, i;
    Vrtc *V, *vAux;
    MostraVertcs (Li);
    printf ("");
    printf ("Escolha o vertice: ");
    scanf ("%d", &idE);
    V = BuscarPos (Li, idE);
    printf ("O vertice [%d] - \"%s\" esta conectado com\n", idE, V->str);
    printf ("/--------------/\n");
    for (i = 0; i < V->pathsOut->qtdElem ; i++)
    {
        vAux = BuscarPos (V->pathsOut, i);
        ImprimiVrtc (vAux);
        printf ("/--------------/\n");
    }
    system ("pause");
}

void DeletarVertice (l_est *Li)
{
    int id;
    Vrtc *v;
    if (Li->qtdElem == 0)
    {
        printf ("Nao ha vertices\n");
        system ("pause");
    }
    else
    {
        MostraVertcs (Li);
        printf ("Escolha um vertice: ");
        scanf ("%d", &id);
        if (id >= Li->qtdElem)
        {
            printf ("Vertice invalido.\n");
            system ("pause");
        }
        else
        {
            v = BuscarPos (Li, id);
            ConfereSobras (Li, v);
            RemoverPos (Li, id);
            free (v);
            ReIdVertices (Li);
        }
    }
}

void ReIdVertices (l_est *Li)
{
    int i;
    for (i = 0; i < Li->qtdElem ; i++)
        Li->Vert[i]->id = i;
}

int ConfereSobras (l_est *Li, Vrtc *V)
{
    int i, j;
    Vrtc *vAux;
    Vrtc *vAux2;
    for (i = 0; i < Li->qtdElem ; i++)
    {
        if (i != V->id)
        {
            vAux = BuscarPos (Li, i);
            for (j = 0; j < vAux->pathsOut->qtdElem ; j++)
            {
                vAux2 = BuscarPos (vAux->pathsOut, j);
                if (vAux2 == V)
                {
                    RemoverPos (vAux->pathsOut, j);
                    break;
                }
            }
            for (j = 0; j < vAux->pathsIn->qtdElem ; j++)
            {
                vAux2 = BuscarPos (vAux->pathsIn, j);
                if (vAux2 == V)
                {
                    RemoverPos (vAux->pathsIn, j);
                    break;
                }
            }
        }
    }
    return 1;
}

int ConectaVertc (int idS, int idD, l_est *Li)
{
    if (Li)
    {
        Vrtc *S, *D;
        S = BuscarPos (Li, idS);
        D = BuscarPos (Li, idD);
        if (D && S)
        {
            InserirFim (S->pathsOut, D);
            InserirFim (D->pathsIn, S);
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
        return -1;
}

void MostraVertcs (l_est *Li)
{
    if (Li)
        if (Li->qtdElem > 0)
        {
            int i;
            for (i = 0; i < Li->qtdElem ; i++)
                ImprimiVrtc (Li->Vert[i]);
            printf ("/--------------/\n");
        }
}

void ImprimiVrtc (Vrtc *V)
{
    if (V)
    {
        printf ("/--------------/\n");
        printf ("Id do vertice: %d\n", V->id);
        printf ("Nome: %s\n", V->str);
        printf ("Numero de saidas: %d\n", V->pathsOut->qtdElem);
        printf ("Numero de entradas: %d\n", V->pathsIn->qtdElem);
    }
}

void MostraArranjos (l_est *Li)
{
}
