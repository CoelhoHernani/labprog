#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>
#include <wchar.h>      //wide strings
#include "palindromo.h"

//função principal
int main (int argc, char **argv) {

    LPalin *lista=NULL;     
    int opcao, n=0;        
    FILE *f;
    wchar_t c;
    
    setlocale(LC_ALL,"pt_PT.UTF-8");
    setlocale(LC_CTYPE,"");

    f=fopen(argv[1], "r");     //abertura do ficheiro texto presente como argumento 1 da linha de comando
    fwide(f,1);                 //stream orientation set to wide chars

    if (f==NULL || argc!=2) {
        wprintf(L"Erro ao abrir ficheiro, ou número de argumentos inválido!");    //mensagem de erro em caso de não cumprir com condição
        return 1;
    }
    
    //Para efeitos de analise, verificação dos caracteres 
    do
    {
         c = fgetwc (f);
         n++;
        putwc(c,stdout);
        //printf("[c:%d s:%d]",c, sizeof(c));
    } while (c != WEOF);
    printf("\ncs:%d c:%d fs:%ld\n",sizeof(c), n, ftell(f));    

    do  {
        wprintf(L"Escolha o modo de verificação de palindromos que pretende fazer:\n1 - Palavras\n2 - Frases\n3 - Ambos\n");
        scanf("%d", &opcao);
    } while(opcao >3 || opcao <1);

    switch (opcao) {
        case 1:
            lista = LerFicheiro(f, lista, opcao);
            MostraLista(lista);
            Libertar(lista);
            break;
        case 2:
            lista = LerFicheiro(f, lista, opcao);
            printf("aaa");
            break;
        case 3:
            printf("vv");
            break;
    }
    
    fclose(f);

    return 0;
}