#include "functii.h"

void sterge_stiva(stiva_gen **top)
{
    while ((*top) != NULL)
    {
        stiva_gen *temp;
        temp = (*top);
        (*top) = (*top)->next;
        sterge_lista(&(temp->adaug_lista));
        free(temp);
    }
}

void adauga_la_inceput(lista_gen **head, int linii, int coloane)
{
    lista_gen *celula_noua = (lista_gen *)malloc(sizeof(lista_gen));
    celula_noua->l = linii;
    celula_noua->c = coloane;
    celula_noua->next = *head;
    *head = celula_noua;
}

void adauga_la_sfarsit(lista_gen **head, int linii, int coloane)
{
    lista_gen *aux = *head;
    lista_gen *celula_noua = (lista_gen *)malloc(sizeof(lista_gen));
    celula_noua->l = linii;
    celula_noua->c = coloane;
    if (*head == NULL)
    {
        free(celula_noua);
        adauga_la_inceput(head, linii, coloane);
    }
    else
    {
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = celula_noua;
        celula_noua->next = NULL;
    }
}

void push(stiva_gen **top, int nr_generatie, lista_gen *generatie)
{
    stiva_gen *gen_noua = (stiva_gen *)malloc(sizeof(stiva_gen));
    gen_noua->k = nr_generatie;
    gen_noua->adaug_lista = generatie;
    gen_noua->next = *top;
    *top = gen_noua;
}

lista_gen *copie_lista(lista_gen *head)
{

    if (head == NULL)
    {
        return NULL;
    }
    lista_gen *cop = (lista_gen *)malloc(sizeof(lista_gen));
    cop->l = head->l;
    cop->c = head->c;
    cop->next = copie_lista(head->next);
    return cop;
}

void sterge_lista(lista_gen **head)
{
    lista_gen *copie;
    while (*head != NULL)
    {
        copie = (*head)->next;
        free(*head);
        *head = copie;
    }
}

void sterge_arbore(nod *root)
{
    if (root == NULL)
        return;
    sterge_arbore(root->left);
    sterge_arbore(root->right);
    sterge_lista(&(root->coordonate));
    free(root);
}

void preordine(FILE *fisier3, nod *root, int N, int M, char **matrice_noua)   ////afisare task 3
{
    printf("Preordine: ");
    if (root == NULL)
    {
        return;
    }

    char **matrice_locala = copie_matrice(matrice_noua, N, M);
    int i,j;
    lista_gen *lista = root->coordonate;
    lista_gen *q = NULL;
    if( root->left!=NULL)
    {
        q = root->left->coordonate;
    }
    

    while (lista != NULL)
    {
        if(matrice_locala[lista->l][lista->c] == 'X')
        {
            matrice_locala[lista->l][lista->c] = '+';
        }
        else
        {
            matrice_locala[lista->l][lista->c] = 'X';
        }
        lista = lista->next;
    }

    char **copie_matr= (char **)malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
    {
        copie_matr[i] = (char *)malloc(M * sizeof(char));
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            copie_matr[i][j] = matrice_noua[i][j];
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            fprintf(fisier3, "%c", matrice_locala[i][j]);
        }
        fprintf(fisier3, "\n");
    }
    fprintf(fisier3, "\n");

    printf("Matrice copie:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%c", copie_matr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
        while (q != NULL)
    {
        printf("(%d, %d) ", q->l, q->c);
        q = q->next;
    }
    printf("\n");

    preordine(fisier3, root->left, N, M, matrice_locala);

    preordine(fisier3, root->right, N, M, matrice_locala);

    for (i = 0; i < N; i++)
    {
        free(matrice_locala[i]);
    }
    free(matrice_locala);

    for (i = 0; i < N; i++)
    {
        free(copie_matr[i]);
    }
    free(copie_matr);
}
char **copie_matrice(char **matrice, int N, int M)
{
    int i, j;
    char **copie_matr;
    copie_matr = (char **)malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
    {
        copie_matr[i] = (char *)malloc(M * sizeof(char));
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            copie_matr[i][j] = matrice[i][j];
        }
    }
    return copie_matr;
}

int **nr_vecini_vii(char **matrice, FILE *generatii, int K, int M, int N)
{
    int i, j;
    //vie este o matrice care retine daca celula este vie sau moarta (1 pentru vie, 0 pentru moarta)
    //suma_vecini_vii este o matrice care retine numarul de vecini vii pentru fiecare celula
    int **suma_vecini_vii, **vie;

    suma_vecini_vii = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++)
    {
        suma_vecini_vii[i] = (int *)malloc(M * sizeof(int));
    }
    vie = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++)
    {
        vie[i] = (int *)malloc(M * sizeof(int));
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            vie[i][j] = 0;                       // initializez matricea vie cu 0
            if (matrice[i][j] == 'X')                
            {
                vie[i][j] = 1;                  // daca celula este vie, devine 1
            }
        }
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            suma_vecini_vii[i][j] = 0;
            if (i == 0 && j == 0) // elementul din stanga sus
            {
                suma_vecini_vii[i][j] = vie[i][j + 1] + vie[i + 1][j] + vie[i + 1][j + 1];
            }
            if (i == 0 && j == M - 1) // elementul din dreapta sus
            {
                suma_vecini_vii[i][j] = vie[i][j - 1] + vie[i + 1][j - 1] + vie[i + 1][j];
            }
            if (i == 0 && j != 0 && j != M - 1) // elementele din mijloc, sus
            {
                suma_vecini_vii[i][j] = vie[i][j - 1] + vie[i][j + 1] + vie[i + 1][j - 1] + vie[i + 1][j] + vie[i + 1][j + 1];
            }
            if (i == N - 1 && j == 0) // elementul din stanga jos
            {
                suma_vecini_vii[i][j] = vie[i - 1][j] + vie[i - 1][j + 1] + vie[i][j + 1];
            }
            if (i == N - 1 && j == M - 1) // elementul din dreapta jos
            {
                suma_vecini_vii[i][j] = vie[i - 1][j - 1] + vie[i - 1][j] + vie[i][j - 1];
            }
            if (i == N - 1 && j != 0 && j != M - 1) // elementele din mijloc, jos
            {
                suma_vecini_vii[i][j] = vie[i][j - 1] + vie[i][j + 1] + vie[i - 1][j - 1] + vie[i - 1][j] + vie[i - 1][j + 1];
            }
            if (j == 0 && i != 0 && i != N - 1) // elememtele din mijloc margine stanga
            {
                suma_vecini_vii[i][j] = vie[i - 1][j] + vie[i + 1][j] + vie[i - 1][j + 1] + vie[i][j + 1] + vie[i + 1][j + 1];
            }
            if (j == M - 1 && i != 0 && i != N - 1) // elementele din mijloc margine dreapta
            {
                suma_vecini_vii[i][j] = vie[i - 1][j] + vie[i + 1][j] + vie[i - 1][j - 1] + vie[i][j - 1] + vie[i + 1][j - 1];
            }
            if (i != 0 && i != N - 1 && j != 0 && j != M - 1) // elementele din mijlocul matricei
            {
                suma_vecini_vii[i][j] = vie[i - 1][j - 1] + vie[i - 1][j] + vie[i - 1][j + 1] + vie[i][j - 1] + vie[i][j + 1] + vie[i + 1][j - 1] + vie[i + 1][j] + vie[i + 1][j + 1];
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        free(vie[i]);
    }
    free(vie);
    return suma_vecini_vii;
}

void implementare_reguli(char **matrice, FILE *generatii, int K, int M, int N)   /// functia pt task 1
{
    int i, j, nr_executari = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            fprintf(generatii, "%c", matrice[i][j]);           // afisez prima generatie in fisier
        }
        fprintf(generatii, "\n");
    }
    fprintf(generatii, "\n");
    while (nr_executari < K)
    {
        int **suma_vecini_vii = NULL;
        suma_vecini_vii = nr_vecini_vii(matrice, generatii, K, M, N);  // apelez functia care returneaza numarul de vecini vii pentru fiecare celula
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                if (matrice[i][j] == 'X' && (suma_vecini_vii[i][j] < 2 || suma_vecini_vii[i][j] > 3))
                {
                    matrice[i][j] = '+';
                }
                if (matrice[i][j] == '+' && suma_vecini_vii[i][j] == 3)
                {
                    matrice[i][j] = 'X';
                }
            }
        }
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                fprintf(generatii, "%c", matrice[i][j]);
            }
            fprintf(generatii, "\n");
        }
        fprintf(generatii, "\n");
        nr_executari++;
        for (i = 0; i < N; i++)
        {
            free(suma_vecini_vii[i]);
        }
        free(suma_vecini_vii);
    }
}
void creare_stiva(char **matrice, FILE *fisier_stiva, int K, int M, int N) /// functia pt task 2
{
    int i, j, nr_executari = 0; // nr_schimbari = 0;
    int **suma_vecini_vii = NULL;
    lista_gen *head = NULL;
    stiva_gen *top = NULL;
    while (nr_executari < K)
    {
        suma_vecini_vii = nr_vecini_vii(matrice, fisier_stiva, K, M, N);    // apelez functia care returneaza numarul de vecini vii pentru fiecare celula
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                if (matrice[i][j] == 'X' && (suma_vecini_vii[i][j] < 2 || suma_vecini_vii[i][j] > 3))
                {
                    matrice[i][j] = '+';                             // daca celula este vie si are mai putin de 2 sau mai mult de 3 vecini vii, devine moarta
                    adauga_la_sfarsit(&head, i, j);                  // adaug in lista celulele care s-au schimbat
                }
                else if (matrice[i][j] == '+' && suma_vecini_vii[i][j] == 3)
                {
                    matrice[i][j] = 'X';                             // daca celula este moarta si are 3 vecini vii, devine vie
                    adauga_la_sfarsit(&head, i, j);                   // adaug in lista celulele care s-au schimbat
                }
            }
        }

        nr_executari++;                     // creste numarul de executari
        push(&top, nr_executari, head);     // adaug in stiva generatia curenta si lista celulelor care s-au schimbat
        sterge_lista(&head);               // sterg lista pentru a putea adauga celulele care s-au schimbat in generatia urmatoare
        for (i = 0; i < N; i++)
        {
            free(suma_vecini_vii[i]);
        }
        free(suma_vecini_vii);
    }
    for (i = 0; i < K; i++)
    {
        stiva_gen *copie = top;
        for (j = 0; j < K - i - 1; j++)
        {
            copie = copie->next;
        }
        fprintf(fisier_stiva, "%d", copie->k);         // afisez numarul generatiei in fisier
        while (copie->adaug_lista != NULL)
        {
            fprintf(fisier_stiva, " %d %d", copie->adaug_lista->l, copie->adaug_lista->c);  // afisez coordonatele celulelor care s-au schimbat in generatia curenta
            copie->adaug_lista = copie->adaug_lista->next;     // trec la urmatoarea celula din lista
        }
        fprintf(fisier_stiva, "\n");
    }

    sterge_stiva(&top);
}

// void alt_mod(char **matrice, FILE * fisier_stiva, int K, int M, int N)  ///alta varianta pt task2
// {
//   int i, j, nr_executari=0, nr_schimbari=0, contor;
//   int **suma_vecini_vii=NULL;
//   lista_gen*head=NULL;
//   lista_gen* copie_head=NULL;
//   stiva_gen*top=NULL;
//   int **vecini_vii;
//     vecini_vii = (int **)malloc(sizeof(int *));


//   while(nr_executari<K)
//   {
//   if(nr_executari==0)
//   {
//     suma_vecini_vii=nr_vecini_vii(matrice, fisier_stiva, K, M, N);
//         for(i=0; i<N; i++)
//     {
//         for(j=0; j<M; j++)
//         {
//             if(matrice[i][j]=='X' && (suma_vecini_vii[i][j]<2 || suma_vecini_vii[i][j]>3))
//             {
//                     matrice[i][j]='+';
//                     adauga_la_sfarsit(&head, i, j);
//                     nr_schimbari++;
//                     vecini_vii[0]=vecini_vii[0]-1;
//             }
//             if(matrice[i][j]=='+' && suma_vecini_vii[i][j]==3)
//             {
//                 matrice[i][j]='X';
//                 adauga_la_sfarsit(&head, i, j);
//                 nr_schimbari++;
//                 vecini_vii[0]=vecini_vii[0]+1;
//             }
//         }
//     }
//     }

//     copie_head=copie_lista(head);

// if(nr_executari!=0)
//   {
//     contor=0;
//         for(i=0; i<N; i++)
//     {
//         for(j=0; j<M; j++)
//         {
//                 head=head->next;
//                 while(copie_head!=NULL)
//                 {
//                     if((copie_head->l==i && copie_head->c==j+1) || (copie_head->l==i+1 && copie_head->c==j) || (copie_head->l==i+1 && copie_head->c==j+1) || (copie_head->l==i && copie_head->c==j-1) || (copie_head->l==i+1 && copie_head->c==j-1) || (copie_head->l==i-1 && copie_head->c==j) || (copie_head->l==i-1 && copie_head->c==j+1) || (copie_head->l==i-1 && copie_head->c==j-1))
//                     {
//                         contor++;
//                     }

//                     copie_head=copie_head->next;
//                 }
//                 if(contor==3 && vecini_vii[i][j]==3)
//                 {
//                     adauga_la_sfarsit(&head, i, j);
//                 }
//         }
//     }
//     }

//     nr_executari++;
//     push(&top, nr_executari, copie_head);
//     copie_head=copie_lista(head);
//     sterge_lista(&head);
//     sterge_lista(&copie_head);
//     for(i=0; i<N; i++)
//   {
//     free(suma_vecini_vii[i]);
//   }
//   free(suma_vecini_vii);
//    }
//    for (i = 0; i < K; i++)
//     {
//         stiva_gen *copie = top;
//         for (j = 0; j < K - i - 1; j++)
//         {
//             copie = copie->next;
//         }
//         fprintf(fisier_stiva, "%d", copie->k);
//         lista_gen *aux = copie->adaug_lista;
//         while (aux != NULL)
//         {
//             fprintf(fisier_stiva, " %d %d", aux->l, aux->c);
//             aux = aux->next;
//         }
//         fprintf(fisier_stiva, "\n");
//     }
//    for(i = 0; i < N; i++)
//   {
//     free(vecini_vii[i]);
//   }
//   free(vecini_vii);
//   sterge_stiva(&top);
  
// }


// stiva_gen *stiva_inversata(stiva_gen *top)
// {

//     stiva_gen *inversat = NULL;
//     while (top != NULL)
//     {
//         stiva_gen *temp = top;
//         top = top->next;
//         temp->next = inversat;    // Inversez stiva pentru a porni de la ultima generatie
//         inversat = temp;
//     }
//     return inversat;
// }

void mers_invers(char **matrice_initiala, FILE * fisier_bonus, int K1,  stiva_gen *top, int N1, int M1)
{
 int i, j;
 //stiva_gen *inversata= stiva_inversata(top); // Inversam stiva pentru a prelua generatiile in ordine inversa
 while(K1>0 && top!=NULL)
 {
    fprintf(fisier_bonus, "%d", K1);
    lista_gen *lista = top->adaug_lista; // Preluam lista generata de la generatia curenta
    while (lista != NULL)
    {
        if(matrice_initiala[lista->l][lista->c] == 'X')
        {
            matrice_initiala[lista->l][lista->c] = '+';
        }
        else
        {
            matrice_initiala[lista->l][lista->c] = 'X';
        }
        fprintf(fisier_bonus, " %d %d", lista->l, lista->c);          
        lista = lista->next;
    }
    fprintf(fisier_bonus, "\n");
    K1--;
    sterge_lista(&(top->adaug_lista)); // Eliberam lista generata
       top=top->next;
 }

 fprintf(fisier_bonus, "\n");
   for(i=0; i<N1; i++)
    {
        for (j = 0; j < M1; j++)
        {
            fprintf(fisier_bonus, "%c", matrice_initiala[i][j]);         // afisez matricea initiala in fisier
        }
        fprintf(fisier_bonus, "\n");
    }
    fprintf(fisier_bonus, "\n");

}


void celula(char **matrice, FILE *fisier3, int K, int M, int N, int executari, nod **root)   ///functie task 3
{
    if (K == executari)
    {
        return;
    }
    int i, j;
    int **suma_vecini_vii1, **suma_vecini_vii2;
    char **matrice_initiala, **matrice_copie, **matrice_stanga, **matrice_dreapta;
    matrice_initiala = copie_matrice(matrice, N, M);
    matrice_stanga = copie_matrice(matrice, N, M);
    matrice_dreapta = copie_matrice(matrice, N, M);

    if(*root == NULL)
    {
        *root = (nod *)malloc(sizeof(nod));
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->coordonate = NULL;
    }
    if (executari == 0)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                if (matrice_initiala[i][j] == 'X')
                {
                    adauga_la_inceput(&(*root)->coordonate, i, j);  // adaug in lista coordonatele celulelor vii (starea initiala)
                }
            }
        }
     }
  
    (*root)->left = (nod *)malloc(sizeof(nod));  //creez nodul stang al arborelui
    (*root)->left->left = NULL;
    (*root)->left->right = NULL;
    (*root)->left->coordonate = NULL;           //initializare coordonate

    (*root)->right = (nod *)malloc(sizeof(nod));    //creez nodul drept
    (*root)->right->left = NULL;
    (*root)->right->right = NULL;
    (*root)->right->coordonate = NULL;          //initializare coordonate

    suma_vecini_vii1 = nr_vecini_vii(matrice_initiala, fisier3, K, M, N);

   // Se modifica celulele:


    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (matrice_initiala[i][j] == '+' && suma_vecini_vii1[i][j] == 2)  //regula pentru partea stanga
            {
                printf("(%d, %d) ", i, j);
                adauga_la_sfarsit(&(*root)->left->coordonate, i, j);  // adaug in lista coordonatele celulelor care s-au schimbat
            }
        }
    }

   lista_gen *list1= (*root)->left->coordonate;  // lista cu coordonatele celulelor care s-au schimbat in partea stanga
    while (list1 != NULL)
    {
        if (matrice_stanga[list1->l][list1->c] == '+')
        {
            matrice_stanga[list1->l][list1->c] = 'X';   // daca celula este moarta si are 2 vecini vii, devine vie
        }
        list1 = list1->next;
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (matrice_initiala[i][j] == 'X' && (suma_vecini_vii1[i][j] < 2 || suma_vecini_vii1[i][j] > 3))
            {
                adauga_la_sfarsit(&(*root)->right->coordonate, i, j);   
            }
            else if (matrice_initiala[i][j] == '+' && suma_vecini_vii1[i][j] == 3)
            {
                adauga_la_sfarsit(&(*root)->right->coordonate, i, j);
            }
        }
    }


lista_gen *list2= (*root)->right->coordonate;            // lista cu coordonatele celulelor care s-au schimbat in partea dreapta
    while (list2 != NULL)
    {
        if (matrice_dreapta[list2->l][list2->c] == 'X')
        {
            matrice_dreapta[list2->l][list2->c] = '+';   // daca celula este vie si are mai putin de 2 sau mai mult de 3 vecini vii, devine moarta
        }
        else if(matrice_dreapta[list2->l][list2->c] == '+')
        {
            matrice_dreapta[list2->l][list2->c] = 'X';  // daca celula este moarta si are 3 vecini vii, devine vie
        }
        list2 = list2->next;
    }

    celula(matrice_stanga, fisier3, K, M, N, executari + 1, &(*root)->left);   //apelez recursiv pentru partea stanga a arborelui

for(i=0; i<N; i++)
    {
       free(matrice_stanga[i]);
    }
    free(matrice_stanga);

    celula(matrice_dreapta, fisier3, K, M, N, executari + 1, &(*root)->right); //apelez recursiv pentru partea dreapta a arborelui

    //eliberez memoria
 for (i = 0; i < N; i++)
    {
        free(matrice_dreapta[i]);     
    }
    free(matrice_dreapta);

    for (i = 0; i < N; i++)
    {
        free(suma_vecini_vii1[i]);
    }
    free(suma_vecini_vii1);

    for (i = 0; i < N; i++)
    {
        free(matrice_initiala[i]);
    }
    free(matrice_initiala);
}

// void DFS_scan(Graph *g, int visited[], int i)
// {
//     int j;
//     visited[i] = 1;
//     printf("Nodul %d->", i);
//     for (j = 0; j < g->V; j++)
//         if (g->a[i][j] == 1 && visited[j] == 0)
//             DFS_scan(g, visited, j);
// }
// int DFS(Graph *g)
// {
//     int i, comp_conexe = 0, visited[g->V];
//     for (i = 0; i < g->V; i++)
//         visited[i] = 0;
//     for (i = 0; i < g->V; i++)
//         if (visited[i] == 0)
//         {
//             DFS_scan(g, visited, i);
//             comp_conexe++;
//             printf("\n");
//         }
//     return comp_conexe;
// }

// int DFS_scan_cycle(Graph *g, int visited[], int prev, int i)
// {
//     int j;
//     visited[i] = 1;
//     printf("Nodul %d->", i);
//     for (j = 0; j < g->V; j++)
//         if (g->a[i][j] == 1)
//             if (visited[j] == 0)
//                 if (DFS_scan_cycle(g, visited, i, j) == 0)
//                     return 0;
//                 else if (j != prev)
//                     return 0;
//     return 1;
// }

// void lant_hamiltonian(Graph *g, int *solutie, int pozitie, int *gasit)
// {
//     int i, j;
//     if (pozitie == g->V)
//     {
//         *gasit = 1;
//         return;
//     }
//     for (i = 0; i < g->V; i++)
//     {
//         if (g->a[solutie[pozitie - 1]][i] == 1)
//         {
//             int ok = 1;
//             for (j = 0; j < pozitie; j++)
//             {
//                 if (solutie[j] == i)
//                 {
//                     ok = 0;
//                     break;
//                 }
//             }
//             if (ok)
//             {
//                 solutie[pozitie] = i; 
//                 lant_hamiltonian(g, solutie, pozitie + 1, gasit);
//                 if (*gasit)
//                 {
//                     return;
//                 }
//             }
//         }
//     }
// }
