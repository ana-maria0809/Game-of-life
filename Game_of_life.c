#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void implementare_reguli(char **matrice, FILE * generatii, int K, int M, int N)
{
  int i, j, nr_executari=0;
  int **suma_vecini_vii, **vie;
 
  suma_vecini_vii=(int**)malloc(N*sizeof(int*));
  for(i=0; i<N; i++)
  {    
      suma_vecini_vii[i]=(int*)malloc(M*sizeof(int));
  }
  vie=(int**)malloc(N*sizeof(int*));
  for(i=0; i<N; i++)
  {
      vie[i]=(int*)malloc(M*sizeof(int));
  }
  for(i=0; i<N; i++)
  {
      for(j=0; j<M; j++)
      {
          fprintf(generatii, "%c", matrice[i][j]);
      }
      fprintf(generatii, "\n");
  }
  fprintf(generatii, "\n");

  while(nr_executari<K)
  {
  for(i=0; i<N; i++)
  {
    for(j=0; j<M; j++)
    { 
        vie[i][j]=0;
        if(matrice[i][j]=='X')
        {
            vie[i][j]=1;
        }
    }
  }

  for(i=0; i<N; i++)
  {
    for(j=0; j<M; j++)
    {
        suma_vecini_vii[i][j]=0;
        if(i==0 && j==0)    // elementul din stanga sus
        {
            suma_vecini_vii[i][j]=vie[i][j+1]+vie[i+1][j]+vie[i+1][j+1];
        }
        if(i==0 && j==M-1)  //elementul din dreapta sus
        {
            suma_vecini_vii[i][j]=vie[i][j-1]+vie[i+1][j-1]+vie[i+1][j];
        }
        if(i==0 && j!=0 && j!=M-1)   // elementele din mijloc, sus
        {
            suma_vecini_vii[i][j]=vie[i][j-1]+vie[i][j+1]+vie[i+1][j-1]+vie[i+1][j]+vie[i+1][j+1];
        }
        if(i==N-1 && j==0)     // elementul din stanga jos
        {
            suma_vecini_vii[i][j]=vie[i-1][j]+vie[i-1][j+1]+vie[i][j+1];
        }
        if(i==N-1 && j==M-1)   // elementul din dreapta jos
        {
            suma_vecini_vii[i][j]=vie[i-1][j-1]+vie[i-1][j]+vie[i][j-1];
        }
        if(i==N-1 && j!=0 && j!=M-1)  //elementele din mijloc, jos
        {
            suma_vecini_vii[i][j]=vie[i][j-1]+vie[i][j+1]+vie[i-1][j-1]+vie[i-1][j]+vie[i-1][j+1];
        }
        if(j==0 && i!=0 && i!=N-1)   // elememtele din mijloc margine stanga
        {
            suma_vecini_vii[i][j]=vie[i-1][j]+vie[i+1][j]+vie[i-1][j+1]+vie[i][j+1]+vie[i+1][j+1];
        }
        if(j==M-1 && i!=0 && i!=N-1)  // elementele din mijloc margine dreapta
        {
            suma_vecini_vii[i][j]=vie[i-1][j]+vie[i+1][j]+vie[i-1][j-1]+vie[i][j-1]+vie[i+1][j-1];
        }
        if(i!=0 && i!=N-1 && j!=0 && j!=M-1) // elementele din mijlocul matricei
        {
            suma_vecini_vii[i][j]=vie[i-1][j-1]+vie[i-1][j]+vie[i-1][j+1]+vie[i][j-1]+vie[i][j+1]+vie[i+1][j-1]+vie[i+1][j]+vie[i+1][j+1];
        }
    }
    
    }
        for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            if(matrice[i][j]=='X' && (suma_vecini_vii[i][j]<2 || suma_vecini_vii[i][j]>3))
            {
                    matrice[i][j]='+';
            }
            if(matrice[i][j]=='+' && suma_vecini_vii[i][j]==3)
            {
                matrice[i][j]='X';
            }
        }
    }
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            fprintf(generatii, "%c", matrice[i][j]);
        }
        fprintf(generatii, "\n");
    }
        fprintf(generatii, "\n");
    nr_executari++;
    }
  for(i=0; i<N; i++)
  {
    free(suma_vecini_vii[i]);
  }
  free(suma_vecini_vii);
  for(i=0; i<N; i++)
  {
    free(vie[i]);
  }
  free(vie);
}

int main(int argc, const char* argv[])
{
    int M, N, T, K, i, j;
    FILE *matrice_initiala;
    matrice_initiala=fopen(argv[1],"rt");
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
    FILE * generatii;
    generatii=fopen(argv[2], "wt");
    if(generatii==NULL)
  {
    printf("Fisierul nu poate fi deschis.\n");
    exit(1);
  }
    implementare_reguli(matrice, generatii, K, M, N);
    for(i=0; i<N; i++)
    {
     free(matrice[i]);
    }
    free(matrice);
   fclose(matrice_initiala);
    fclose(generatii);
    return 0;
}
