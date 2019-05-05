#include<math.h>
#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<string.h>
// estrutura para guardar os usuarios com a sua chave verificadora
typedef struct estructUsuario{
	char nome[20];
	uint32_t senha;
} estructUsuario;

//funcao para pegar o nome de usuario da entrada de nome e chave verificadora
char fNomeUsuario(char *nomeSenha,int *j,char *usuario){
int caracter;
char entradaValida = 'N';
	for ( int i =0;i<21;i++){	
		    caracter = nomeSenha[i];
			if (caracter == 32) {
				entradaValida = 'S';
				*j = i;  // ao achar o espaço, guarda a posicao dele para pegar a chave verificadora
				break;
			} else {
			usuario[i] = nomeSenha[i];}
		}
	
	if (entradaValida != 'S'){
		printf("Entre com usuário ate 20 caracteres\n");
	}
	return entradaValida;
}
//funcao para pegar a chave
char fSenhaUsuario(char *nomeSenha,int j, char *senhaDigitada,int senha){ 
	// criado um parametro senha pois essa funcao sera usada tanto para a funcao da senha q contem apenas numeros e a senha digita que pode ter qualquer caracter
	//passando 0 ele vai verificar somente numeros.
    int num32[10];
	int codigoNumero;
	int tamanho;
	j = j+1; // a posicao do espaco foi passado como parametro para seguir na proxima posicao
    char entradaValida = 'S';
	for (int i=0;i<11;i++){
		codigoNumero = nomeSenha[j] ;                      //se codigo numero = 0 so pode entrar numero para representar a funcao da senha
		if( ((codigoNumero < 48) || (codigoNumero > 57)) &&(codigoNumero != 0) && (senha == 0) ) {
			printf("Entrada inválida, senha somente em numeros\n");
			entradaValida = 'N';
			break;
		} else {	
			senhaDigitada[i] = nomeSenha[j];
			j++;
		}
	}
	if (entradaValida == 'S') {	
		tamanho = strlen(senhaDigitada);//verificar se é um inteiro de 32 bits
		if (tamanho > 10){
			printf("entre com um numero menor que 32 bits (4294967295)\n");
			entradaValida = 'N';
		} else 
		if (tamanho == 20){
			for (int t = 0 ; t < 20 ; t++){
				num32[t] = senhaDigitada[t];
					
			}
			if (num32[0] > 4 || num32[1] > 2 || num32[2] > 9 || num32[3] > 4 || num32[4] > 9 || num32[5] > 6 || num32[6] > 7 || num32[7] > 2 || num32[8] > 9 || num32[9] > 5)  {
				printf("entre com um numero menor que 32 bits (4294967295)\n");
				entradaValida = 'N';
			}else
			entradaValida = 'S';
		} else	
			entradaValida = 'S';
	}

	return entradaValida;
}

//funcao para retornar o valor de g^c mod p
uint32_t powmod(uint32_t g, uint32_t b, uint32_t P)
{
	uint32_t r = 1;
		g = g%P;
	while (b > 0){
		if (b & 1){
			 r = (r*g)%P;
		}
		b = b>>1;
		g = (g*g) %P;
	}
	return r;

} 

	
int main()
{

	char usuario[20];
	char senhaDigitada[10] ;
	char nomeSenha[32];
	char entradaValida = 'N';
	int achou ;
    int i,j=0;
	int	nUsuarios,nLogin;
	
	int moduloN;
	int docOriginal;
	estructUsuario *vUsuario;
	uint32_t docAssinado;
	uint32_t senhaChave;
	uint32_t verificaDoc;
	//guardar o modulo N e o doc original
	while (entradaValida != 'S'){
			memset(nomeSenha,(int)0,sizeof(char)*32);
			printf("Entre com o modulo N e o documento original\n");
			scanf(" %[^\n]s",nomeSenha);
			entradaValida = fNomeUsuario(nomeSenha,&j,usuario); //guarda o nome de usuario
			if (entradaValida == 'S'){
				entradaValida = fSenhaUsuario(nomeSenha,j,senhaDigitada,0); //guarda a chave
			}	
	}
	moduloN = atoi(usuario);
	docOriginal = atoi(senhaDigitada);

	printf("Entre com o numero de usuarios cadastrados\n");
	scanf("%d",&nUsuarios);
	vUsuario = (estructUsuario*)malloc(nUsuarios*sizeof(estructUsuario));
	entradaValida = 'N';
	//primeira entrada de n linhas contendo usuario e a chave
	for (int nCadastros = 0;nCadastros < nUsuarios;nCadastros++){
		while (entradaValida != 'S'){
			memset(nomeSenha,(int)0,sizeof(char)*32);
			printf("Entre com o usuário e chave (usuario chave)\n");
			scanf(" %[^\n]s",nomeSenha);
			entradaValida = fNomeUsuario(nomeSenha,&j,usuario);
			if (entradaValida == 'S'){
				entradaValida = fSenhaUsuario(nomeSenha,j,senhaDigitada,0);
			}	
		}
		usuario[j] = '\0';

		senhaChave =atoi(senhaDigitada);
		
		strcpy(vUsuario[nCadastros].nome,usuario);
		vUsuario[nCadastros].senha = senhaChave;

		if (nCadastros < nUsuarios)
			entradaValida = 'N';
	}
	
    //segunda entrada com m linhas o numero de documentos
	printf("Entre com o numero de documentos\n");
	scanf("%d",&nLogin);	   
	entradaValida = 'N';	  
		   
	for (int nCadastros = 0;nCadastros < nLogin;nCadastros++){

			printf("Entre com o documento assinado\n");
			scanf("%"SCNu32, &docAssinado) ;
			achou = 0;
			for (int k = 0;k < nUsuarios;k++){	

				verificaDoc = powmod(docAssinado, vUsuario[k].senha, moduloN);
				if (verificaDoc == docOriginal){
					achou = 1;
					printf("assinado pelo usuario %s\n", vUsuario[k].nome);
					break;
				}
			}
			if (achou == 0){
				printf("Assinante nao encontrado\n");
			}
	
	}
	 

   	
return 0;
}