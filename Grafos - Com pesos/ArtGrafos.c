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
        free (Li->Vert);
        Li->maxElem = 10;
        Li->qtdElem = 0;
        Li->Vert = (Vrtc**) malloc (10 * sizeof (Vrtc));
        return 1;
    }
    else
    {
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


///LISTA DE LIGAÇÕES


///*******************************************************************
///*******************************************************************
///*******************************************************************
///*******************************************************************

///CRIAÇÃO E DESTRUIÇÃO
l_lig* CriarListaL()
{
    l_lig* Li = (l_lig*) malloc (sizeof (l_lig));
    Li->lig = (lig*) malloc (10 * sizeof (lig));
    Li->qtdElem = 0;
    if (!Li)
        return NULL;
    Li->maxElem = 10;
    return Li;
}

int Dest_ListaL (l_lig *Li)
{
    if (!Li)
        return 0;
    free (Li);
    return 1;
}

///INSERÇÃO
int InserirFimL (l_lig *Li, lig L)
{
    if (!Li)
        return -1;
    if (Li->qtdElem == Li->maxElem)
        return 0;
    if (Li->qtdElem == Li->maxElem - 3)
    {
        Li->lig = (lig*) realloc (Li->lig, ( (Li->qtdElem) * 2) * sizeof (lig));
        Li->maxElem *= 2;
    }
    Li->lig[Li->qtdElem] = L;
    Li->qtdElem++;
    return 1;
}

///REMOÇÃO
int RemoverPosL (l_lig *Li, int Pos)
{
    int i;
    for (i = Pos; i < Li->qtdElem - 1; i++)
        Li->lig[i] = Li->lig[i + 1];
    Li->qtdElem--;
    return 1;
}

///BUSCA
lig BuscarPosL (l_lig *Li, int Pos)
{
    return Li->lig[Pos];
}

int BuscarDadoL (l_lig *Li, Vrtc* V)
{
    int i;
    for (i = 0; i < Li->qtdElem; i++)
        if (Li->lig[i].Vprox == V)
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
    v->peso = 0;
    v->pathsIn = CriarListaL();
    v->pathsOut = CriarListaL();
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
    int idE, i, j, nIn, nOut, idAux, peso;
    Vrtc *V, *vAux;
    lig lAux, lAux2;
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
                lAux = BuscarPosL (V->pathsOut, i);
                ImprimeLig (lAux);
                printf ("/--------------/\n");
            }
            printf ("\n\tConexoes de chegando\n");
            for (i = 0; i < V->pathsIn->qtdElem ; i++)
            {
                lAux = BuscarPosL (V->pathsIn, i);
                ImprimeLig (lAux);
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
                printf ("Peso da ligacao: ");
                scanf ("%d", &peso);
                vAux = BuscarPos (Li, idAux);
                for (j = 0; j < vAux->pathsIn->qtdElem ; j++)
                {
                    lAux2 = BuscarPosL (vAux->pathsIn, j);
                    if (lAux2.Vprox == V && lAux2.peso == peso)
                    {
                        RemoverPosL (vAux->pathsIn, j);
                        break;
                    }
                }
                for (j = 0; j < V->pathsOut->qtdElem ; j++)
                {
                    lAux2 = BuscarPosL (V->pathsOut, j);
                    if (lAux2.Vprox == vAux && lAux2.peso == peso)
                    {
                        RemoverPosL (V->pathsOut, j);
                        break;
                    }
                }
            }
            for (i = 0; i < nIn ; i++)
            {
                printf ("ID do vertice saida: ");
                scanf ("%d", &idAux);
                printf ("Peso da ligacao: ");
                scanf ("%d", &peso);
                vAux = BuscarPos (Li, idAux);
                for (j = 0; j < vAux->pathsOut->qtdElem ; j++)
                {
                    lAux2 = BuscarPosL (vAux->pathsOut, j);
                    if (lAux2.Vprox == V && lAux2.peso == peso)
                    {
                        RemoverPosL (vAux->pathsOut, j);
                        break;
                    }
                }
                for (j = 0; j < V->pathsIn->qtdElem ; j++)
                {
                    lAux2 = BuscarPosL (V->pathsIn, j);
                    if (lAux2.Vprox == vAux && lAux2.peso == peso)
                    {
                        RemoverPosL (V->pathsIn, j);
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

void DesconectaVertP (l_est *Li, int peso)
{
}

///MOSTRAGEM
void MostraConexao (l_est *Li)
{
    int idE, i;
    Vrtc *V;
    lig lAux;
    MostraVertcs (Li);
    printf ("\n");
    printf ("Escolha o vertice: ");
    scanf ("%d", &idE);
    V = BuscarPos (Li, idE);
    printf ("O vertice [%d] - \"%s\" esta conectado com\n", idE, V->str);
    printf ("/--------------/\n");
    for (i = 0; i < V->pathsOut->qtdElem ; i++)
    {
        lAux = BuscarPosL (V->pathsOut, i);
        ImprimiVrtc (lAux.Vprox);
        printf ("/--------------/\n");
    }
    system ("pause");
}

void MostraArranjos (l_est *Li)
{
    int i, j, cont = 1;
    Vrtc *vAux;
    lig lAux;
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
                    lAux = BuscarPosL (vAux->pathsOut, j);
                    printf ("[%d]:%s -[%d]-> [%d]:%s\n", vAux->id, vAux->str, lAux.peso, lAux.Vprox->id, lAux.Vprox->str);
                }
            }
            cont++;
        }
    }
    else
    {
        printf ("Nao ha vertices\n");
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

void ImprimeLig (lig Lig)
{
    if (Lig.Vprox)
    {
        printf ("/--------------/\n");
        printf ("Id do vertice: %d\n", Lig.Vprox->id);
        printf ("Nome: %s\n", Lig.Vprox->str);
        printf ("Peso da ligação: %d\n", Lig.peso);
    }
}

///NOVAS CONEXOES
void NovaConexao (l_est *Li)
{
    int idE, id, esc, peso;
    if (Li->qtdElem == 0)
    {
        printf ("Nao ha vertices\n");
        system ("pause");
    }
    else
    {
        MostraArranjos (Li);
        printf ("Escolha o vertice de saida: ");
        scanf ("%d", &idE);
        if (idE < Li->qtdElem && idE >= 0)
        {
            printf ("Escolha o vertice destino: ");
            scanf ("%d", &id);
            printf ("Peso da ligação: ");
            scanf ("%d", &peso);
            if (id < Li->qtdElem && id >= 0)
            {
                if (!ConexaoRepetida (peso, idE, id, Li))
                    ConectaVertc (peso, idE, id, Li);
                printf ("Deseja que seja de mão dupla? (0 ou 1): ");
                scanf ("%d", &esc);
                if (esc == 1)
                    if (!ConexaoRepetida (peso, id, idE, Li))
                        ConectaVertc (peso, id, idE, Li);
            }
        }
    }
}

int ConectaVertc (int peso, int idS, int idD, l_est *Li)
{
    if (Li)
    {
        Vrtc *vS, *vD;
        lig lS, lD;
        vS = BuscarPos (Li, idS);
        vD = BuscarPos (Li, idD);
        lS.Vprox = vS;
        lS.peso = peso;
        lD.Vprox = vD;
        lD.peso = peso;
        if (vD && vS)
        {
            InserirFimL (vS->pathsOut, lD);
            InserirFimL (vD->pathsIn, lS);
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
    Vrtc *vAux;
    lig lAux;
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
            lAux = BuscarPosL (vAux->pathsOut, j);
            fprintf (fOut, "%d %d> %d\n", vAux->id, lAux.peso, lAux.Vprox->id);
        }
    }
    fprintf (fOut, "-1 -1> -1");
    fclose (fOut);
}

void ImportaGrafo (l_est *Li)
{
    char str[100], tag[100];
    int id, idO, idI, peso;
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
                fscanf (fIn, "%d %d> %d", &idO, &peso, &idI);
                if (idO != -1 && peso != -1 && idI != -1)
                {
                    if (!ConexaoRepetida (peso, idO, idI, Li))
                        ConectaVertc (peso, idO, idI, Li);
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        printf ("Arquivo n existe\n");
        system ("pause");
    }
    ReIdVertices (Li);
    fclose (fIn);
}

///UTILITARIOS
int ConexaoRepetida (int peso, int idO, int idI, l_est *Li)
{
    int i;
    lig lAux;
    Vrtc *V = BuscarPos (Li, idO);
    for (i = 0; i < V->pathsOut->qtdElem ; i++)
    {
        lAux = BuscarPosL (V->pathsOut, i);
        if (lAux.Vprox->id == idI)
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
    lig lAux;
    for (i = 0; i < Li->qtdElem ; i++)
        if (i != V->id)
        {
            vAux = BuscarPos (Li, i);
            for (j = 0; j < vAux->pathsOut->qtdElem ; j++)
            {
                lAux = BuscarPosL (vAux->pathsOut, j);
                if (lAux.Vprox == V)
                {
                    RemoverPosL (vAux->pathsOut, j);
                    break;
                }
            }
            for (j = 0; j < vAux->pathsIn->qtdElem ; j++)
            {
                lAux = BuscarPosL (vAux->pathsIn, j);
                if (lAux.Vprox == V)
                {
                    RemoverPosL (vAux->pathsIn, j);
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
    lig lAux;
    if (Li->qtdElem > 0)
    {
        Vrtc *V = BuscarPos (Li, idI);
        if (V)
        {
            for (i = 0; i < V->pathsOut->qtdElem; i++)
            {
                lAux = BuscarPosL (V->pathsOut, i);
                temp = MenorCaminhoRec (Li, lAux.Vprox, idI, idF, lAux.peso);
                if (temp > qnt && qnt == 0)
                {
                    qnt = temp;
                }
                else if (qnt > 0 && temp < qnt)
                {
                    qnt = temp;
                }
                ZeraChecks (Li);
            }
        }
        else
            return -1;
    }
    else
        return -2;
    return qnt;
}

int MenorCaminhoRec (l_est *Li, Vrtc *V, int idI, int idF, int qnt)
{
    int i = 0;
    int temp = 0;
    lig lAux;
    if (V)
    {
        if (V->id == idF)
        {
            return qnt;
        }
        else
        {
            if (!V->check)
            {
                for (i = 0; i < V->pathsOut->qtdElem ; i++)
                {
                    lAux = BuscarPosL (V->pathsOut, i);
                    qnt += lAux.peso;
                    if (lAux.Vprox->id != idI)
                    {
                        V->check = 1;
                        temp = MenorCaminhoRec (Li, lAux.Vprox, idI, idF, qnt);
                        ZeraChecks (Li);
                    }
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
