#define MAXSTR 1024

//definição da estrutura de dados que irá conter os palindromos
typedef struct SPalin {
    
    wchar_t *palindromo;           //conterá a palavra que é polindromo
    struct SPalin *seguinte;

} LPalin;

//função para adicionar palavra a lista
LPalin *Adicionar (LPalin *lista, wchar_t *word);

//função para remover "lixo" que poderá estar na palavra
void RemoveSimbolos (wchar_t *word);

//função que tornar em minusculas todos caracteres
void Minusculas (wchar_t *word);

//funçao verifica se as palavras são palindromos
bool Verifica (wchar_t *word);

//função que faz o print dos palindromos encontrados
void MostraLista(LPalin *lista);

//função para libertar blocos de memória alocados
void Libertar (LPalin *lista);

//Função que lê do ficheiro
LPalin *LerFicheiro (FILE *f, LPalin *lista, int opcao);