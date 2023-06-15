#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
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
	//mostra a palavra secreta
	//função agora sendo implementada com o banco de dados do arquivo palavras.txt

	FILE* f;

	f = fopen("palavras.txt", "r");
	if(f == 0){
		printf("Erro ao abrir banco de dados.\n");
		exit(1);

		//exit 0 = programa sucesso
		//exit >0 = programa com erro
	}


	//queremos escolher apenas uma linha do nosso arquivo
	int num_palavras;
	fscanf(f, "%d", &num_palavras);

	//teriamos que contar o numero de palavras que há dentro do nosso arquivo
	//que seria alg extremamante demorado em casos que haja muitas palavras
	//ou
	//podemos nós humanos, saber quantas palavras há e escrever
	//na primeira linha desse arquivo.txt
	

	//escolher uma linha aleatória
	srand(time(0));
	int randomico = rand() % num_palavras; //resto da divisao

	for(int i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavra);//guardando na var palavra
		//realizando a leitura sequencial das palavras
	}


	fclose(f);
}

int acertou(){

	//para ganhar devemos ter acertado todas
	//se deixamos de chutar alguma letra significa que ainda nao ganhamos o jogo


	for(int i = 0; i < strlen(palavra); i++){
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