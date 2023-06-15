#include <stdio.h>
#include <string.h>
#include "forca.h"

//variáveis globais
char palavra[20];
char chutes[26];
int chutesdados = 0;



void abertura(){
	printf("*****************************\n");
	printf("*       Jogo da Forca       *\n");
	printf("*****************************\n\n");
}

int jachutou(char letra){
//funcao com retorno
	int achou = 0;

	for(int j = 0; j < chutesdados; j++){
		if(chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
}

void chuta(){
	char chutou;
	scanf(" %c", &chutou);//espaco pra q ignore o enter e nao contar char

	chutes[(chutesdados)] = chutou; 
	(chutesdados)++; 

}

void desenhaforca(){

	for(int i = 0; i < strlen(palavra); i++){
	int achou = jachutou(palavra[i] );
		if(achou){
			printf("%c ", palavra[i]);
		}
		else{
			printf("_ ");
		}

	}
	printf("\n");
}

void palavrasecreta(){
	sprintf(palavra, "MELANCIA");
//mostra a palavra secreta
}

int acertou(){


	for(int i = 0; i < chutesdados; i++){
		if(!jachutou(palavra[i])){
			return 0; //nao ganhou
		}
	}
	return 1; //acertou todas as letras da palavra secreta

}

int enforcou(){

	int erros = 0;

	for(int i = 0; i < chutesdados; i++){

		int existe = 0;

		for(int j = 0; j < strlen(palavra); j++){
			if(chutes[i] == palavra[j]){
				existe = 1;
				break;
			}

		}

		if(!existe)
			erros++;

	}

	return erros >= 5; //num max de erros

}


int main(){

	abertura();
	palavrasecreta();


	do {

		desenhaforca();
		chuta();
		//tentativas passada como referencia (ponteiro)

	} while(!acertou() && !enforcou());  //enquando nao acertar e nao enforcar

	return 0;
}