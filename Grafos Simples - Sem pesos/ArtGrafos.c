#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "ArtGrafos.h"

///*******************************************************************
///*******************************************************************
///*******************************************************************
///*******************************************************************


///LISTA


///*******************************************************************
///*******************************************************************
///*******************************************************************
///*******************************************************************

///CRIAÇÃO E DESTRUIÇÃO
l_est* CriarLista()
{
    l_est* Li = (l_est*) malloc (sizeof (l_est));
    Li->Vert = (Vrtc**) malloc (10 * sizeof (Vrtc));
    Li->qtdElem = 0;
    Li->Vert[0] = NULL;
    if (!Li)
        return NULL;
    Li->maxElem = 10;
    return Li;
}

int Dest_Lista (l_est *Li)
{
    if (!Li)
        return 0;
    free (Li);
    return 1;
}

///INSERÇÃO
int InserirFim (l_est *Li, Vrtc *V)
{
    if (!Li)
        return -1;
    if (Li->qtdElem == Li->maxElem)
        return 0;
    if (Li->qtdElem == Li->maxElem - 3)
    {
        Li->Vert = (Vrtc**) realloc (Li->Vert, ( (Li->qtdElem) * 2) * sizeof (Vrtc));
        Li->maxElem *= 2;
    }
    Li->Vert[Li->qtdElem] = V;
    Li->qtdElem++;
    return 1;
}

///REMOÇÃO
int RemoverPos (l_est *Li, int Pos)
{
    int i;
    for (i = Pos; i < Li->qtdElem - 1; i++)
        Li->Vert[i] = Li->Vert[i + 1];
    Li->qtdElem--;
    return 1;
}
int RemoveTodos (l_est *Li)
{
    if (Li)
    {
        int i;
        free (Li->Vert);
        Li->maxElem = 10;
        Li->qtdElem = 0;
        Li->Vert = (Vrtc**) malloc (10 * sizeof (Vrtc));
        return 1;
    }else{
        return -1;
    }
}

///BUSCA
Vrtc *BuscarPos (l_est *Li, int Pos)
{
    return Li->Vert[Pos];
}

int BuscarDado (l_est *Li, Vrtc *Dados)
{
    int i;
    for (i = 0; i < Li->qtdElem; i++)
        if (Li->Vert[i] == Dados)
            return i;
    return -1;
}

///*******************************************************************
///*******************************************************************
///*******************************************************************
///*******************************************************************


///GRAFOS


///*******************************************************************
///*******************************************************************
///*******************************************************************
///*******************************************************************

///CRIAÇÃO E ALOCAÇÃO
Vrtc * AlocaVert ()
{
    Vrtc *v = (Vrtc*) malloc (sizeof (Vrtc));
    v->id = -1;
    v->check = 0;
    v->pathsIn = CriarLista();
    v->pathsOut = CriarLista();
    v->str = NULL;
    return v;
}

int CriarVertice (l_est *Li)
{
    system ("cls");
    Vrtc *v = AlocaVert (Li);
    char nome[100];
    if (v)
    {
        v->id = Li->qtdElem;
        printf ("De um nome ao seu vertice: ");
        scanf ("%s", nome);
        v->str = (char*) malloc ( (strlen (nome) + 1) * sizeof (char));
        strcpy (v->str, nome);
        InserirFim (Li, v);
        return 1;
    }
    else
        return -1;
}

///DESCONECTAR
void DesconectaVert (l_est *Li)
{
    int idE, i, j, nIn, nOut, idAux;
    Vrtc *V, *vAux, *vAux2;
    MostraVertcs (Li);
    printf ("Selecione o vertice: ");
    scanf ("%d", &idE);
    if (idE >= 0 && idE < Li->qtdElem)
    {
        V = BuscarPos (Li, idE);
        if (V->pathsOut->qtdElem == 0 && V->pathsIn->qtdElem == 0)
            printf ("O vertice nao possui conexoes de saida ou entrada\n");
        else
        {
            system ("cls");
            printf ("O vertice \"[%d] - %s\" possui as seguintes conexoes\n\n", V->id, V->str);
            printf ("\tConexoes saindo\n");
            for (i = 0; i < V->pathsOut->qtdElem ; i++)
            {
                vAux = BuscarPos (V->pathsOut, i);
                ImprimiVrtc (vAux);
                printf ("/--------------/\n");
            }
            printf ("\n\tConexoes de chegando\n");
            for (i = 0; i < V->pathsIn->qtdElem ; i++)
            {
                vAux = BuscarPos (V->pathsIn, i);
                ImprimiVrtc (vAux);
                printf ("/--------------/\n");
            }
            printf ("Qnt de saidas a deletar: ");
            scanf ("%d", &nOut);
            printf ("Qnt de entradas a deletar: ");
            scanf ("%d", &nIn);
            for (i = 0; i < nOut ; i++)
            {
                printf ("ID do vertice destino: ");
                scanf ("%d", &idAux);
                vAux = BuscarPos (Li, idAux);
                for (j = 0; j < vAux->pathsIn->qtdElem ; j++)
                {
                    vAux2 = BuscarPos (vAux->pathsIn, j);
                    if (vAux2 == V)
                    {
                        RemoverPos (vAux->pathsIn, j);
                        break;
                    }
                }
                for (j = 0; j < V->pathsOut->qtdElem ; j++)
                {
                    vAux2 = BuscarPos (V->pathsOut, j);
                    if (vAux2 == vAux)
                    {
                        RemoverPos (V->pathsOut, j);
                        break;
                    }
                }
            }
            for (i = 0; i < nIn ; i++)
            {
                printf ("ID do vertice saida: ");
                scanf ("%d", &idAux);
                vAux = BuscarPos (Li, idAux);
                for (j = 0; j < vAux->pathsOut->qtdElem ; j++)
                {
                    vAux2 = BuscarPos (vAux->pathsOut, j);
                    if (vAux2 == V)
                    {
                        RemoverPos (vAux->pathsOut, j);
                        break;
                    }
                }
                for (j = 0; j < V->pathsIn->qtdElem ; j++)
                {
                    vAux2 = BuscarPos (V->pathsIn, j);
                    if (vAux2 == vAux)
                    {
                        RemoverPos (V->pathsIn, j);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        printf ("ID invalido\n");
        system ("pause");
    }
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

///MOSTRAGEM
void MostraConexao (l_est *Li)
{
    int idE, i;
    Vrtc *V, *vAux;
    MostraVertcs (Li);
    printf ("\n");
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

void MostraArranjos (l_est *Li)
{
    int i, j, cont = 1;
    Vrtc *vAux, *vAux2;
    if (Li->qtdElem > 0)
    {
        printf ("Arranjos\n");
        for (i = 0; i < Li->qtdElem ; i++)
        {
            vAux = BuscarPos (Li, i);
            if (vAux->pathsOut->qtdElem == 0)
                printf ("[%d]:%s -> NULL\n", vAux->id, vAux->str);
            else
            {
                for (j = 0; j < vAux->pathsOut->qtdElem ; j++)
                {
                    vAux2 = BuscarPos (vAux->pathsOut, j);
                    printf ("[%d]:%s -> [%d]:%s\n", vAux->id, vAux->str, vAux2->id, vAux2->str);
                }
            }
            cont++;
        }
    }
    else
    {
        printf ("Nao ha vertices");
    }
    system ("pause");
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

///NOVAS CONEXOES
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
            if (id < Li->qtdElem && id >= 0)
            {
                if (!ConexaoRepetida (idE, id, Li))
                    ConectaVertc (idE, id, Li);
                printf ("Deseja que seja de mão dupla? (0 ou 1): ");
                scanf ("%d", &esc);
                if (esc == 1)
                    if (!ConexaoRepetida (id, idE, Li))
                        ConectaVertc (id, idE, Li);
            }
        }
    }
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
            return -1;
    }
    else
        return -1;
}

/// EXPORTAÇÃO E IMPORTAÇÃO

void ExportaGrafo (l_est *Li)
{
    char nome[100];
    int i, j;
    Vrtc *vAux, *vAux2;
    printf ("Insira o nome desejado (sem extensao txt) para arquivo de saida: ");
    scanf ("%s", nome);
    strcat (nome, ".txt");
    FILE *fOut = fopen (nome, "w+");
    fprintf (fOut, "vertices\n");
    for (i = 0; i < Li->qtdElem ; i++)
    {
        vAux = BuscarPos (Li, i);
        fprintf (fOut, "%d %s\n", vAux->id, vAux->str);
        if (i != (Li->qtdElem) - 1)
            fprintf (fOut, "@\n");
    }
    fprintf (fOut, "conexoes\n");
    for (i = 0; i < Li->qtdElem ; i++)
    {
        vAux = BuscarPos (Li, i);
        for (j = 0; j < vAux->pathsOut->qtdElem ; j++)
        {
            vAux2 = BuscarPos (vAux->pathsOut, j);
            fprintf (fOut, "%d > %d\n", vAux->id, vAux2->id);
        }
    }
    fclose (fOut);
}

void ImportaGrafo (l_est *Li)
{
    char str[100], tag[100];
    int id, idO, idI;
    Vrtc *V = AlocaVert();
    printf ("Insira o nome do arquivo (sem extensao) de entrada: ");
    scanf ("%s", str);
    strcat (str, ".txt");
    FILE *fIn = fopen (str, "r");
    fscanf (fIn, "%s", tag);
    if (fIn)
    {
        if (strcmp ("vertices", tag))
        {
            printf ("Arquivo invalido.\n");
            system ("pause");
        }
        else
        {
            while (1)
            {
                V = AlocaVert();
                fscanf (fIn, "%d %s", &id, str);
                V->id = id;
                V->str = (char*) malloc ( (strlen (str) + 1) * sizeof (char));
                strcpy (V->str, str);
                InserirFim (Li, V);
                fscanf (fIn, "%s", tag);
                if (strcmp (tag, "@"))
                    break;
            }
            while (!feof (fIn))
            {
                fscanf (fIn, "%d > %d", &idO, &idI);
                if (!ConexaoRepetida (idO, idI, Li))
                    ConectaVertc (idO, idI, Li);
            }
        }
    }
    else
    {
        printf ("Arquivo n existe\n");
        system ("pause");
    }
    fclose (fIn);
}

///UTILITARIOS
int ConexaoRepetida (int idO, int idI, l_est *Li)
{
    int i;
    Vrtc *vAux;
    Vrtc *V = BuscarPos (Li, idO);
    for (i = 0; i < V->pathsOut->qtdElem ; i++)
    {
        vAux = BuscarPos (V->pathsOut, i);
        if (vAux->id == idI)
            return 1;
    }
    return 0;
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
    return 1;
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

void ZeraChecks (l_est *Li)
{
    int i;
    Vrtc *V;
    for (i = 0; i < Li->qtdElem ; i++)
    {
        V = BuscarPos (Li, i);
        V->check = 0;
    }
}

///MENOR CAMINHO
int MenorCaminho (l_est *Li, int idI, int idF)
{
    int qnt = 0, i, temp;
    if (Li->qtdElem > 0)
    {
        Vrtc *V = BuscarPos (Li, idI);
        if (V)
        {
            for (i = 0; i < V->pathsOut->qtdElem; i++)
            {
                temp = MenorCaminhoRec (Li, BuscarPos (V->pathsOut, i), idF, 0);
                if (temp > qnt && qnt == 0)
                {
                    qnt = temp;
                }
                else if (qnt > 0 && temp < qnt)
                {
                    qnt = temp;
                }
            }
        }
        else
            return -1;
    }
    else
        return -2;
    return qnt;
}

int MenorCaminhoRec (l_est *Li, Vrtc *V, int idF, int qnt)
{
    int i = 0;
    int temp = 0;
    Vrtc *vAux;
    if (V)
    {
        if (V->id == idF)
        {
            qnt++;
            return qnt;
        }
        else
        {
            if (!V->check)
            {
                for (i = 0; i < V->pathsOut->qtdElem ; i++)
                {
                    vAux = BuscarPos (V->pathsOut, i);
                    temp = MenorCaminhoRec (Li, vAux, idF, qnt + 1);
                }
                return temp;
            }
            else
                return 0;
        }
    }
    else
    {
        return 0;
    }
}


