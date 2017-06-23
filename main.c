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
    MEN_CAM,
    MOSTRA_C,
    MOSTRA_A,
    EXPORTA,
    IMPORTA,
    APAGA,
    SAIR
};

int main()
{
    int esc = 1;
    int check, idI, idF;
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
        printf ("[%d] - Menor caminho de um vertice a outro\n", MEN_CAM);
        printf ("[%d] - Mostrar conexoes de um vertice\n", MOSTRA_C);
        printf ("[%d] - Mostrar arranjos\n", MOSTRA_A);
        printf ("[%d] - Exportar grafo\n", EXPORTA);
        printf ("[%d] - Importar grafo\n", IMPORTA);
        printf ("[%d] - Apagar grafo\n", APAGA);
        printf ("[%d] - Sair\n", SAIR);
        printf ("Escolha: ");
        scanf ("%d", &esc);
        switch (esc)
        {
        ///OK
        case CRIAR:
            CriarVertice (Li);
            break;
        ///OK
        case DELETAR:
            DeletarVertice (Li);
            break;
        ///OK
        case CONECTAR:
            NovaConexao (Li);
            break;
        ///OK
        case MOSTRA_V:

            MostraVertcs (Li);
            system ("pause");
            break;
        ///OK
        case DESC_V:
            DesconectaVert (Li);
            break;
        ///OK
        case MEN_CAM:
            MostraVertcs (Li);
            printf ("\nSelecione o ID de saida: ");
            scanf("%d",&idI);
            printf ("Selecione o ID de chegada: ");
            scanf("%d",&idF);
            check = MenorCaminho (Li, idI, idF);
            if(check==0)
            {
                printf("Os dois vertices nao estao ligados\n");
            }else if(check<0&&check!=-2)
            {
                printf("Nao tenho ideia do que aconteceu...\n");
            }else if(check==-2){
                printf("Nao ha vertices\n");
            }else{
                printf("Menor caminho: %d\n",check);
            }
            system("pause");
            break;
        ///OK
        case MOSTRA_C:
            MostraConexao (Li);
            system ("pause");
            break;
        ///OK
        case MOSTRA_A:
            MostraArranjos (Li);
            break;
        ///OK
        case EXPORTA:
            ExportaGrafo (Li);
            break;
        ///OK
        case IMPORTA:
            ImportaGrafo (Li);
            break;
        ///OK
        case APAGA:
            RemoveTodos(Li);
            break;
        case SAIR:
            Dest_Lista (Li);
            break;
        }
    }
    return 0;
}
