#include "functii.h"

int main(int argc, const char* argv[])
{
    int M, N, T, K, i, j;
    FILE *matrice_initiala;
    lista_gen* head=NULL;
    stiva_gen* top=NULL;
    matrice_initiala=fopen(argv[1],"rt");
    nod *root=NULL;
    root=(nod*)malloc(sizeof(nod));
    root->left=root->right=NULL;
    root->coordonate=NULL;

    if(matrice_initiala==NULL)
    {
        printf("Fisierul nu poate fi deschis.\n");
        exit(1);    
      }
    fscanf(matrice_initiala, "%d", &T);
    fscanf(matrice_initiala, "%d", &N);
    fscanf(matrice_initiala, "%d", &M);
    fscanf(matrice_initiala, "%d", &K);
    fgetc(matrice_initiala);
   
    char ** matrice;
    matrice=(char**)malloc(N*sizeof(char*));
    for(i=0; i<N; i++)
    {
        matrice[i]=(char*)malloc(M*sizeof(char));
    }

   
    for(i=0; i<N; i++)
    {
           
        for(j=0; j<M; j++)
        {
          fscanf(matrice_initiala, "%c", &matrice[i][j]);
        }
      fgetc(matrice_initiala);
    }

    if(T==1)
        {
            FILE * generatii;
            generatii=fopen(argv[2], "wt");
            if(generatii==NULL)
            {
                printf("Fisierul nu poate fi deschis.\n");
                exit(1);  
            }
            implementare_reguli(matrice, generatii, K, M, N);
            
            fclose(generatii);
        }
    if(T==2)
    {
        FILE * fisier_stiva;
        fisier_stiva=fopen(argv[2], "wt");
        if(fisier_stiva==NULL)
        {
            printf("Fisierul nu poate fi deschis.\n");
            exit(1);
        }
        creare_stiva(matrice, fisier_stiva, K, M, N);
        fclose(fisier_stiva);
    }
    char**matrice_noua=(char**)malloc(N*sizeof(char*));
    for(i=0; i<N; i++)
    {
        matrice_noua[i]=(char*)malloc(M*sizeof(char));
    }

    if(T==3)
    {
        FILE * fisier3;
        fisier3=fopen(argv[2], "wt");
        if(fisier3==NULL)
        {
            printf("Fisierul nu poate fi deschis.\n");
            exit(1);
        }
        celula(matrice, fisier3, K, M, N, 0, &root);
        for(i=0; i<N; i++)
        {
            for(j=0; j<M; j++)
            {
                matrice_noua[i][j]='+';
            }
        }
        
        preordine(fisier3, root, N, M, matrice_noua);
        fclose(fisier3);
    }


    int M1, N1, T1, K1;
    FILE *fisier_bonus;
    fisier_bonus=fopen("fisier_bonus.txt", "rt");
    if(fisier_bonus==NULL)
    {
        printf("Fisierul pentru operatia inversa nu poate fi deschis.\n");
        exit(1);
    }
    fscanf(fisier_bonus, "%d", &T1);
    printf("T1: %d\n", T1);
    fscanf(fisier_bonus, "%d", &N1);
    printf("N1: %d\n", N1);
    fscanf(fisier_bonus, "%d", &M1);
    printf("M1: %d\n", M1);
    fscanf(fisier_bonus, "%d", &K1);
    printf("K1: %d\n", K1);
    fgetc(fisier_bonus);


if(T1==5)
{

        char *linie;

    for (i = 0; i <K1; i++)
    {
        stiva_gen *copie = (stiva_gen*)malloc(sizeof(stiva_gen));
        if(copie == NULL)
        {
            printf("Eroare la alocarea memoriei pentru stiva generatii.\n");
            exit(1);
        }
        copie->adaug_lista = NULL;
            copie->next=top;;
            top=copie;
        lista_gen *aux=NULL;
        int capacitate = 100;
        linie = (char*)malloc(capacitate * sizeof(char));
        int loc = 0;
        int c=0;
        const char *sir;
            while(c!= '\n' && c != EOF)
            {
                c = fgetc(fisier_bonus);
                if (c == '\n' || c == EOF) 
                {
                    break; // Terminare linie
                }
                if (loc + 1 >= capacitate) 
                {
                    capacitate = 2*capacitate;
                    char *temp= (char*)realloc(linie, capacitate * sizeof(char));
                    if (temp == NULL) 
                    {
                        free(linie);
                        printf("Eroare la reallocare memorie.\n");
                        exit(1);
                    }
                    linie = temp; // Actualizare pointer
                }
                linie[loc++] = c;
            }
           linie[loc] = '\0'; // Terminare sir
           sir= strtok(linie, " ");
           if(sir == NULL)
           {
               printf("Eroare: linia este goala.\n");
               free(linie);
               exit(1);
           }  
           copie->k = atoi(sir);
            sir = strtok(NULL, " ");
              if (sir == NULL) 
              {
                printf("Eroare: numarul de coloane lipseste.\n");
                free(linie);
                exit(1);
              }
           while (sir != NULL)
        {
            lista_gen *adauga_next= (lista_gen*)malloc(sizeof(lista_gen));
            adauga_next->l = atoi(sir);
            sir = strtok(NULL, " "); 
            if (sir == NULL) 
            {
                printf("Eroare: numarul de linii lipseste.\n");
                free(adauga_next);
                free(linie);
                exit(1);
            } 
            adauga_next->c = atoi(sir);
        //    sir = strtok(NULL, " ");
            adauga_next->next = NULL;
             sir = strtok(NULL, " ");

            if (copie->adaug_lista == NULL)
            {
                copie->adaug_lista = adauga_next;
                aux= adauga_next;
            }
            else
            {
                aux->next = adauga_next;
                aux=adauga_next;
            }
       } 
   free(linie);
   

    }

    char ** matrice_ultima_gen;
    matrice_ultima_gen=(char**)malloc(N1*sizeof(char*));
    for(i=0; i<N1; i++)
    {
        matrice_ultima_gen[i]=(char*)malloc(M1*sizeof(char));
    }
   
    for(i=0; i<N1; i++)
    {   
           
        for(j=0; j<M1; j++)
        {
          fscanf(fisier_bonus, "%c", &matrice_ultima_gen[i][j]);
        }
      fgetc(fisier_bonus);
    }
    FILE *fisier_bonus1;
    fisier_bonus1=fopen("fisier_bonus1.txt", "wt");
    if(fisier_bonus1==NULL)
    {
        printf("Fisierul pentru operatia inversa nu poate fi deschis.\n");
        exit(1);
    }
    mers_invers(matrice_ultima_gen, fisier_bonus1, K1, top, N1, M1);
    for(i=0; i<N; i++)
    {
        free(matrice_ultima_gen[i]);
    }
    free(matrice_ultima_gen);
    fclose(fisier_bonus1);

}fclose(fisier_bonus);



    // Graph *g;
    // int *solutie;
    // int *gasit;
    // solutie=(int*)malloc(N*M*sizeof(int));
    // gasit=(int*)malloc(N*M*sizeof(int));
    // solutie[0]=0;
    // gasit[0]=0;
    // g=(Graph*)malloc(sizeof(Graph));
    // g->V=N*M;
    // g->E=0;
    // g->a=(int**)malloc(g->V*sizeof(int*));
    // for(i=0; i<g->V; i++)
    // {
    //     g->a[i]=(int*)malloc(g->V*sizeof(int));
    // }
    // for(i=0; i<g->V; i++)
    // {
    //     for(j=0; j<g->V; j++)
    //     {
    //         g->a[i][j]=0;
    //     }
    // }
    // if(T==4)

    // {
    //     int pozitie=0;
    //     FILE * fisier_graf;
    //     fisier_graf=fopen(argv[2], "wt");
    //     if(fisier_graf==NULL)
    //     {
    //         printf("Fisierul nu poate fi deschis.\n");
    //         exit(1);
    //     }
    //     DFS(g);
    //     lant_hamiltonian(g, solutie, pozitie, gasit);
    //     fclose(fisier_graf);
    // }

    for(i=0; i<N; i++)
    {
     free(matrice_noua[i]);
    }
    free(matrice_noua);
    // free(solutie);
    // free(gasit);
    sterge_lista(&head);
    sterge_stiva(&top);
    sterge_arbore(root);

    for(i=0; i<N; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
    
    fclose(matrice_initiala);
    sterge_stiva(&top);
    return 0;
}
