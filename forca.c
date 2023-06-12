#include <stdio.h>
#include <string.h>

void abertura();
int jachutou(char letra, char chutes[26], int tentativas);
void chuta(char chutes[26], int* tentativas);
void desenhaforca(char palavra[20], char chutes[26], int tentativas);
void palavrasecreta(char palavra[20]);


void abertura(){

	printf("*****************************\n");
	printf("*       Jogo da Forca       *\n");
	printf("*****************************\n\n");
}

int jachutou(char letra, char chutes[26], int tentativas){
//funcao com retorno
	int achou = 0;

	for(int j = 0; j < tentativas; j++){
		if(chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
}

void chuta(char chutes[26], int* tentativas){ //* pq estamos passando o endereço
	// lembrar de usar (*) em tentativas para acessar o conteúdo e não a mem
	char chutou;
	scanf(" %c", &chutou);//espaco pra q ignore o enter e nao contar char

	//chutes[tentativas] = chutou; //aqui temos o endereço da var tentativas
	//mas queremos o conteúdo, entao usamos com *
	chutes[(*tentativas)] = chutou; //() para resolver primeiro,
	//guardamos o chute que o usuário fez no vetor de chutes...na mem
	(*tentativas)++; 

}

void desenhaforca(char palavra[20], char chutes[26], int tentativas){

	for(int i = 0; i < strlen(palavra); i++){

	int achou = jachutou(palavra[i], chutes, tentativas);

	if(achou){
		printf("%c ", palavra[i]);

	}else{
	printf("_ ");
	}

	}
	printf("\n");
}

void palavrasecreta(char palavra[20]){
	sprintf(palavra, "MELANCIA");
//mostra a palavra secreta
}

int main(){

	char palavra[20];

	int acertou = 0; //bool
	int enforcou = 0;

	char chutes[26];
	int tentativas = 0;

	palavrasecreta(palavra);

	abertura();

	do {
		desenhaforca(palavra, chutes, tentativas);
		
		chuta(chutes, &tentativas);
		//tentativas passada como referencia (ponteiro)


	} while(!acertou && !enforcou);  //enquando nao acertar e nao enforcar

	return 0;
}