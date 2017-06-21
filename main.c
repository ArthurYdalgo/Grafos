#include <stdio.h>
#include <stdlib.h>

#include "ArtGrafos.h"

enum
{
    CRIAR = 1,
    DELETAR,
    CONECTAR,
    MOSTRA_V,
    DESC_V,
    MOSTRA_C,
    MOSTRA_A,
    SAIR
};

int main()
{
    int esc = 1;
    l_est *Li = CriarLista();
    while (esc != SAIR)
    {
        system ("cls");
        printf ("=== MENU ===\n");
        printf ("[%d] - Criar vertice\n", CRIAR);
        printf ("[%d] - Deletar vertice\n", DELETAR);
        printf ("[%d] - Conectar vertices\n", CONECTAR);
        printf ("[%d] - Mostrar vertices\n", MOSTRA_V);
        printf ("[%d] - Desconectar vertices\n", DESC_V);
        printf ("[%d] - Mostrar conexoes de um vertice\n", MOSTRA_C);
        printf ("[%d] - Mostrar arranjos\n", MOSTRA_A);
        printf ("[%d] - Sair\n", SAIR);
        printf ("Escolha: ");
        scanf ("%d", &esc);
        switch (esc)
        {
        ///OK
        case CRIAR:
            CriarVertice (Li);
            break;
        case DELETAR:
        ///OK
            DeletarVertice (Li);
            break;
        case CONECTAR:
        ///OK
            NovaConexao (Li);
            break;
        case MOSTRA_V:
        ///OK
            MostraVertcs (Li);
            system("pause");
            break;
        /// A IMPLEMENTAR
        case DESC_V:
            DesconectaVert(Li);
            break;
        ///OK
        case MOSTRA_C:
            MostraConexao (Li);
            system("pause");
            break;
        /// A IMPLEMENTAR
        case MOSTRA_A:
            MostraArranjos (Li);
            break;
        case SAIR:
            break;
        }
    }
    return 0;
}
