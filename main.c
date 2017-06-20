#include <stdio.h>
#include <stdlib.h>

#include "ArtGrafos.h"

enum
{
    CRIAR = 1,
    DELETAR,
    CONECTAR,
    EXIBIR,
    CONECT,
    SAIR
};

int main()
{
    int esc;
    l_est *Li = CriarLista();
    while (esc!=SAIR){
    system("cls");
    printf ("=== MENU ===\n");
    printf ("[1] - Criar vertice\n");
    printf ("[2] - Deletar vertice\n");
    printf ("[3] - Conectar vertices\n");
    printf ("[4] - Desconectar vertices\n");
    printf ("[5] - Mostrar conexoes\n");
    printf ("[6] - Mostrar arranjos\n\n");
    printf ("Escolha: ");
    scanf ("%d", &esc);
    switch (esc)
    {
    case CRIAR:
        CriarVertice (Li);
        break;
    case DELETAR:
        break;
    case CONECTAR:
        NovaConexao(Li);
        break;
    case EXIBIR:
        break;
    case CONECT:
        break;
    case SAIR:

        break;
    }
    }
    return 0;
}
