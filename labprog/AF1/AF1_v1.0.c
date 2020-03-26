#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXSTR 1024

//Carregar ficherio .txt para verificar palindromos

//definição da estrutura de dados que irá conter os palindromos
typedef struct SPalin {
    
    char *palindromo;           //conterá a palavra que é polindromo
    struct SPalin *seguinte;

} LPalin;

//função para adicionar palavra a lista
LPalin *Adicionar (LPalin *lista, char *word) {

    LPalin *bloco;

    bloco = (LPalin*)malloc(sizeof(LPalin));
    bloco->palindromo = (char*)malloc(strlen(word)+1);
    
    if (bloco != NULL && bloco->palindromo != NULL)  {
            strcpy(bloco->palindromo, word);            //copia o que está num endereço para outro, até encontrar o \0 
            bloco->seguinte = lista;
            return bloco;
    }

    printf("Bloco não alocado!");
    return lista;
}

//função para remover "lixo" que poderá estar na palavra
void RemoveSimbolos (char *word) {

    int i, j;

    for(i=0; word[i]!='\0'; i++) 
        while (!(isalpha(word[i]) || word[i]=='\0')) {
            for(j=i; word[j] != '\0'; j++) 
                word[j]=word[j+1];
            word[j]='\0';
        }
}

//função que tornar em minusculas todos caracteres
void Minusculas (char *word) {

    int i;

    for (i=0; word[i] != '\0'; i++)
        word[i] = tolower(word[i]);
}

//funçao verifica se as palavras são palindromos
bool Verifica (char *word) {

    int i, len;

    RemoveSimbolos(word);
    Minusculas (word);

    len=strlen(word);

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
        printf("Palindromo -> %s\n", tmp->palindromo);
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

void LerFicheiro (FILE *f, LPalin *lista) {


}

//função principal
int main (int argc, char **argv) {

    char *token, string[MAXSTR];
    LPalin *lista=NULL;             
    FILE *f;
   
    //setlocale(LC_ALL,"Portuguese_Portugal.1252");
    //printf("agora já posso usar ç e então\n");
    f=fopen(argv[1], "rt");         //abertura do ficheiro texto presente como argumento 1 da linha de comando
    
    if (f==NULL || argc!=2) {
        perror("Erro ao abrir ficheiro, ou número de argumentos inválido!");            //mensagem de erro em caso de não cumprir com condição
        return 1;
    }

    while (!feof(f))
        if (fgets(string,MAXSTR,f)!=NULL) {
            printf("%s\n",string);
            token = strtok(string,"\n");
            while (token != NULL) {
                if (Verifica(token)) 
                    lista = Adicionar(lista, token);
            token = strtok(NULL,"\n");
            }
        }

    MostraLista(lista);
    Libertar(lista);
    fclose(f);

    return 0;
}
