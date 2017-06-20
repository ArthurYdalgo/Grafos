#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define TAM_VET 10000
#define Path_MAX 1000
#include "ArtGrafos.h"
///LISTA

l_est* CriarLista()
{
    int i;
    l_est* Li = (l_est*) malloc (sizeof (l_est));
    Li->Vert = (Vrtc**) malloc ( (TAM_VET) * sizeof (Vrtc));
    for (i = 0; i < TAM_VET ; i++)
    {
        Li->Vert[i] = NULL;
    }
    if (!Li)
        return NULL;
    Li->maxElem = TAM_VET;
    Li->qtdElem = 0;
    return Li;
}

int Dest_Lista (l_est *Li)
{
    if (!Li)
        return 0;
    free (Li);
    return 1;
}

int InserirFim (l_est *Li, Vrtc *Dados)
{
    if (!Li)
        return -1;
    if (Li->qtdElem == Li->maxElem)
        return 0;
    Li->Vert[Li->qtdElem] = Dados;
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

int InserirPos (l_est *Li, Vrtc *Dados, int Pos)
{
    int i;
    if (!Li)
        return -1;
    if (Pos > Li->maxElem || Pos < 0)
        return -2;
    if (Li->qtdElem >= Li->maxElem)
        return 0;
    for (i = Li->qtdElem; i >= Pos; i--)
        Li->Vert[i + 1] = Li->Vert[i];
    Li->Vert[Pos] = Dados;
    Li->qtdElem++;
    return 1;
}

int RemoverPos (l_est *Li, int Pos)
{
    int i;
    for (i = Li->qtdElem; i > Pos; i--)
        Li->Vert[i + 1] = Li->Vert[i];
    Li->qtdElem--;
    return 1;
}

int RemoveDado (l_est *Li, Vrtc *Dados)
{
    int i = BuscarDado (Li, Dados);
    if (i >= 0)
    {
        RemoverPos (Li, i);
        return 1;
    }
    else
    {
        return -1;
    }
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
    int i;
    Vrtc *v = (Vrtc*) malloc (sizeof (Vrtc));
    v->Inf.check = 0;
    v->Inf.fl = 0;
    v->Inf.id = Li->qtdElem;
    v->Inf.it = 0;
    v->Inf.nome = NULL;
    v->Inf.str = NULL;
    v->Path = (Vrtc**) malloc (Path_MAX * sizeof (Vrtc));
    v->Inf.pathsO = 0;
    v->Inf.pathsI = 0;
    for (i = 0; i < Path_MAX ; i++)
    {
        v->Path[i] = NULL;
    }
    return v;
}

int CriarVertice (l_est *Li)
{
    int esc;
    char *nome = (char*) malloc (100 * sizeof (char));
    system ("cls");
    Vrtc *v = AlocaVert (Li);
    if (v)
    {
        printf ("De um nome ao seu vertice: ");
        scanf ("%s", nome);
        v->Inf.nome = (char*) malloc (100 * sizeof (char));
        strcpy (v->Inf.nome, nome);
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
    int idE, num, i, id, esc;
    if (Li->qtdElem == 0)
    {
        printf ("Nao ha vertices\n");
        system ("pause");
    }
    else
    {
        MostraVertc (Li);
        printf ("Escolha um vertice: ");
        scanf ("%d", &idE);
        printf ("Quantas conexoes deseja fazer?: ");
        scanf ("%d", &num);
        if (num > 0)
        {
            printf ("Insira o ID dos vertices desejados\n");
            for (i = 0; i < num ; i++)
            {
                printf ("%da conexao com: ", i + 1);
                scanf ("%d", &id);
                ConectaVertc (idE, id, Li);
                printf ("Deseja que seja de mão dupla? (0 ou 1): ");
                scanf ("%d", &esc);
                if (esc == 1)
                    ConectaVertc (id, idE, Li);
            }
        }
    }
}

int SelecionaVertc (l_est *Li, Vrtc *Vs)
{
    int num, id, esc, i;
    printf ("Vertices disponiveis\n\n");
    MostraVertc (Li);
    printf ("Quantas conexoes deseja fazer?: ");
    scanf ("%d", &num);
    if (num > 0)
    {
        printf ("Insira o ID dos vertices desejados\n");
        for (i = 0; i < num ; i++)
        {
            printf ("%da conexao com: ", i + 1);
            scanf ("%d", &id);
            ConectaVertc (Vs->Inf.id, id, Li);
            printf ("Deseja que seja de mão dupla? (0 ou 1): ");
            scanf ("%d", &esc);
            if (esc == 1)
                ConectaVertc (id, Vs->Inf.id, Li);
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
            Li->Vert[idS]->Path[S->Inf.pathsI] = D;
        }
        else
        {
            printf ("N sei pq\n");
            return -1;
        }
        if (Li->Vert[idS]->Path[S->Inf.pathsI] == D)
        {
            Li->Vert[idS]->Inf.pathsO++;
            Li->Vert[idD]->Inf.pathsI++;
            return 1;
        }
        else
        {
            return -2;
        }
    }
    else
        return -1;
}

void MostraVertc (l_est *Li)
{
    if (Li)
    {
        if (Li->qtdElem > 0)
        {
            int i;
            for (i = 0; i < Li->qtdElem ; i++)
            {
                printf ("/--------------/\n\n");
                printf ("Id do vertice: %d\n", Li->Vert[i]->Inf.id);
                if (Li->Vert[i]->Inf.nome)
                    printf ("Nome: %s\n", Li->Vert[i]->Inf.nome);
                else
                    printf ("Vertice sem nome\n");
                /*if (Li->Vert[i]->Inf.str)
                    printf ("Texto: %s\n", Li->Vert[i]->Inf.str);
                else
                    printf ("Vertice sem texto\n");*/
                //printf ("Inteiro: %d\n", Li->Vert[i]->Inf.it);
                printf ("Numero de PathOuts: %d\n", Li->Vert[i]->Inf.pathsO);
                printf ("Numero de PathIns: %d\n", Li->Vert[i]->Inf.pathsI);
                //printf ("Float: %.3f\n\n", Li->Vert[i]->Inf.fl);
                printf ("/--------------/\n");
            }
        }
    }
}
