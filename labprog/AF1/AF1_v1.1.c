#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>
#include <wchar.h>      //wide strings
#include <wctype.h>
#include "palindromo.h"

//Carregar ficherio .txt para verificar palindromos

//função para adicionar palavra a lista
LPalin *Adicionar (LPalin *lista, wchar_t *word) {

    LPalin *bloco;

    bloco = (LPalin*)malloc(sizeof(LPalin));
    bloco->palindromo = (wchar_t*)malloc(wcslen(word)+10);
    
    if (bloco != NULL && bloco->palindromo != NULL)  {
            wcscpy(bloco->palindromo, word);            //copia o que está num endereço para outro, até encontrar o \0 
            bloco->seguinte = lista;
            return bloco;
    }

    printf("Bloco não alocado!");
    return lista;
}

//função para remover "lixo" que poderá estar na palavra
void RemoveSimbolos (wchar_t *word) {

    int i, j;

    for(i=0; word[i]!='\0'; i++) 
        while (!(iswspace(word[i]) || iswalpha(word[i]) || word[i]=='\0')) {
            for(j=i; word[j] != '\0'; j++) 
                word[j]=word[j+1];
            word[j]='\0';
        }
}

//função que tornar em minusculas todos caracteres
void Minusculas (wchar_t *word) {

    int i;

    for (i=0; word[i] != '\0'; i++)
        word[i] = towlower(word[i]);
}

//funçao verifica se as palavras são palindromos
bool VerificaPalavra (wchar_t *word) {

    int i, len;

    RemoveSimbolos(word);
    Minusculas (word);

    len=wcslen(word);

    if (len>=3 && len<=10) {
        for (i=0; i < len/2; i++) 
            if (word[i] != word[len-1-i])
                return false;
        return true;
    }
    return false;
}

//função que faz o print dos palindromos encontrados
void MostraLista(LPalin *lista) {

    LPalin *tmp;
    int count=0;
    
    tmp=lista;
    while (tmp != NULL)   {
        count++;
        wprintf(L"Palindromo -> %ls\n", tmp->palindromo);
        tmp = tmp->seguinte;
    }
    printf("\nTotal de Palindromos encontrados: %d", count);
}

//função para libertar blocos de memória alocados
void Libertar (LPalin *lista) {

    LPalin *aux;

    while (lista != NULL) {
        aux=lista->seguinte;
        free (lista->palindromo);                   
        free(lista);
        lista=aux;
    }
}

//Função que lê do ficheiro
LPalin *LerFicheiro (FILE *f, LPalin *lista, int opcao) {

    wchar_t string[MAXSTR];                        //* *string[6] array of 6 strings*/ 

    if (opcao == 1)       //fscanf lê sequÊncia de caracteres conforme padrão, neste caso caracteres até proximo whitespace
        while (!feof(f)) {
            fwscanf(f,L"%ls",string);
            if (VerificaPalavra(string)) 
                lista = Adicionar(lista, string);
        }

    if (opcao == 2) 
        while (!(feof(f))) {
            fwscanf(f,L"%[^\n]\n",string);
            //fgets(string,MAXSTR,f);
            wprintf(L"%ls\n\n",string);
            //perror("wprintf");
        }
        
      return lista;
}