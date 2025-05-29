#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct lista_generatii
{
    int l;    /// linia ceululei care s-a modificat
    int c;    /// coloana celulei care s-a modificat
    struct lista_generatii* next;
};
typedef struct lista_generatii lista_gen;

struct stiva_generatii
{
    int k;    ///numarul generatiei
    lista_gen* adaug_lista;
    struct stiva_generatii* next;

};
typedef struct stiva_generatii stiva_gen;

struct nod
{
    lista_gen *coordonate;
    struct nod *left, *right;
};
typedef struct nod nod;

void sterge_stiva(stiva_gen** top);
void adauga_la_inceput(lista_gen** head, int linii, int coloane);
void adauga_la_sfarsit(lista_gen** head, int linii, int coloane);
void push(stiva_gen**top, int nr_generatie, lista_gen* generatie);
lista_gen* copie_lista(lista_gen* head);
void sterge_lista(lista_gen** head);
void sterge_arbore(nod *root);
void preordine(FILE *fisier3, nod *root, int N, int M, char**matrice_noua);
char ** copie_matrice(char** matrice, int N, int M);
int **nr_vecini_vii(char **matrice, FILE * generatii, int K, int M, int N);
void implementare_reguli(char **matrice, FILE * generatii, int K, int M, int N);
void creare_stiva(char **matrice, FILE * fisier_stiva, int K, int M, int N);
void alt_mod(char **matrice, FILE * fisier_stiva, int K, int M, int N);
stiva_gen *stiva_inversata(stiva_gen *top);
void mers_invers(char **matrice_initiala, FILE * fisier_bonus, int K1,  stiva_gen *top, int N1, int M1);
void celula(char **matrice, FILE *fisier3, int K, int M, int N, int executari, nod **root);

struct Graph {
    int V;         // numarul de varfuri
    int E;        // numarul de muchii
    int **a;      // matricea de adiacenta
}; typedef struct Graph Graph;
void DFS_scan(Graph *g, int visited[], int i);
int DFS(Graph *g);
int DFS_scan_cycle(Graph *g, int visited[], int prev, int i);
void lant_hamiltonian(Graph *g, int *solutie, int pozitie, int *gasit);

