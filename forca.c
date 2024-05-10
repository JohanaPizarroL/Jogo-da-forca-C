#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

//variáveis globais, são usada na maioria das funções
char palavrasecreta[TAM_PALAVRA];
char chutes[26]; //chutes, podem ser todas as letras co alfabeto
int chutesdados = 0;

void abertura(){
	printf("*****************************\n");
	printf("*       Jogo da Forca       *\n");
	printf("*****************************\n\n");
}

void chuta(){
	char chute;
	printf("Digite uma letra: ");
	scanf(" %c", &chute);//espaco pra q ignore o enter e nao contar char
	chutes[chutesdados] = chute; 
	chutesdados++; 
}

int jachutou(char letra){
	int achou = 0;
	for(int j = 0; j < chutesdados; j++){
		if(chutes[j] == letra){
			achou = 1; //se for encontrado
			break;
		}
	}
	return achou;
}

void desenhaforca(){ 
	//printf("Voce ja deu %d chutes\n", chutesdados);
	int erros = chutes_errados();

	printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

	for(int i = 0; i < strlen(palavrasecreta); i++){
		if(jachutou(palavrasecreta[i])){
			printf("%c ", palavrasecreta[i]);
		}
		else{
			printf("_ ");
		}
	}
	printf("\n");
}

//adicionar palavra ao arquivo de texto (escrever no fim do arquivo)
void adiciona_palavra(){
	char resposta;
	printf("Voce deseja adicionar uma nova palavra (S/N)?: ");
	scanf(" %c", &resposta);
	if(resposta == 'S'){
		char nova_palavra[TAM_PALAVRA];
		printf("Digite a nova palavra: ");
		scanf("%s", nova_palavra);
		
		FILE* f = fopen("palavras.txt", "r+");
		if(f == NULL){
			printf("Erro ao abrir o arquivo!");
			exit(1);
		}
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0 , SEEK_SET);//volta a primeira posicao do arq
		fprintf(f, "%d", qtd);

		//reposicionar o cursor no fim do arquivo
		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", nova_palavra); //escrevendo a nova palavra no fim do arquivo
		fclose(f);
		printf("Palavra adicionada com sucesso!\n");
	}

}

void escolhe_palavra(){
	//sprintf(palavrasecreta, "MELANCIA");
	FILE *f;
	f = fopen("palavras.txt", "r"); //abrindo o arquivo para leitura
	if(f == 0){
		printf("Desculpe, o arquivo de texto não está disponivel");
		exit(1);
	}
	int qtd_palvras;
	fscanf(f, "%d", &qtd_palvras); //lendo a primeira linha do arq

	srand(time(0));
	int randomzin = rand() % qtd_palvras; //na qtd de palavras do arq

	for(int i = 0; i <= randomzin; i++){
		fscanf(f, "%s", palavrasecreta);
	}
	fclose(f); //fechando arquivo
}

// verifica se ganhou
int acertou(){
	for(int i = 0; i < strlen(palavrasecreta); i++){
		if(!jachutou(palavrasecreta[i])){ // se nao chutou
			return 0; //acaba o programa
		}
	}
	return 1; //todas as letras dessa palavra ja foram chutadas = ganhou
}


//verifica a quantidade de erros
int chutes_errados(){
	int erros = 0;
	for(int i = 0; i < chutesdados; i++){
		int existe = 0; //se a letra existe ou não
		for(int j = 0; j < strlen(palavrasecreta); j++){
			if(chutes[i] == palavrasecreta[j]){
				existe = 1;
				break;
			}
		}
		if(!existe) // se existe = 0
			erros++; //nao achou a palavra entao errou mais uma vez
	}
	return erros; // se erro for maior que 5, retorna 1 ou 0


}

int enforcou(){ 
	return chutes_errados() >= 5;
}


int main(){
	escolhe_palavra();
	abertura();

	do {
		desenhaforca();//palavrasecreta, chutes, chutesdados sao agora globais
		chuta();

	} while(!acertou() && !enforcou()); //enquando nao acertar e nao for enforcado
// acertou e enforcou estao com () parametro vaazio pq o parametro delas e uma var global
	if(acertou()){
		printf("Parabéns, você ganhou!!!\n\n");
		printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

	}else{
		printf("\nPoxa, você foi enforcado!\nA palavra secreta era %s\n\n", palavrasecreta);
		printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
	}
	adiciona_palavra();
	printf("Até o próximo jogo!!!\n\n");

	return 0;
}

