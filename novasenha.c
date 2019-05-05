#include<math.h>
#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<string.h>
// estrutura para guardar os usuarios com a funcao da senha
typedef struct estructUsuario{
	char nome[20];
	char senha[20];
} estructUsuario;

//funcao para pegar o nome de usuario da entrada de nome e senha
char fNomeUsuario(char *nomeSenha,int *j,char *usuario){
int caracter;
char entradaValida = 'N';
	for ( int i =0;i<21;i++){	
		    caracter = nomeSenha[i];
			if (caracter == 32) {
				entradaValida = 'S';
				*j = i;  // ao achar o espaço, guarda a posicao dele para pegar a senha
				break;
			} else {
			usuario[i] = nomeSenha[i];}
		}
	
	if (entradaValida != 'S'){
		printf("Entre com usuário ate 20 caracteres\n");
	}
	return entradaValida;
}
//funcao para pegar a senha
char fSenhaUsuario(char *nomeSenha,int j, char *senhaDigitada,int senha){ 
	// criado um parametro senha pois essa funcao sera usada tanto para a funcao da senha q contem apenas numeros e a senha digita que pode ter qualquer caracter
	//passando 0 ele vai verificar somente numeros.
    int num64[20];
	int codigoNumero;
	int tamanho;
	j = j+1; // a posicao do espaco foi passado como parametro para seguir na proxima posicao
    char entradaValida = 'S';
	for (int i=0;i<21;i++){
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
		tamanho = strlen(senhaDigitada);//verificar se é um inteiro de 64 bits
		if (tamanho > 20){
			printf("entre com um numero menor que 64 bits (18446744073709551615)\n");
			entradaValida = 'N';
		} else 
		if (tamanho == 20){
			for (int t = 0 ; t < 20 ; t++){
				num64[t] = senhaDigitada[t];
					
			}
			if (num64[0] > 1 || num64[1] > 8 || num64[2] > 4 || num64[3] > 4 || num64[4] > 6 || num64[5] > 7 || num64[6] > 4 || num64[7] > 4 || num64[8] > 0 || num64[9] > 7 || num64[10] > 3 || num64[11] > 7 || num64[12] > 0 || num64[13] > 9 ||num64[14] > 5 || num64[15] > 5 || num64[16] > 1|| num64[17] > 6 || num64[18] > 1 || num64[19] > 5) {
				printf("entre com um numero menor que 64 bits (18446744073709551615)\n");
				entradaValida = 'N';
			}else
			entradaValida = 'S';
		} else	
			entradaValida = 'S';
	}

	return entradaValida;
}
//funcao para testar o login digitado 
int testeLogin(char *usuario,char *senhaDigitada, estructUsuario *vUsuario,int nUsuarios){
int nCaracterLogin;
int nCaracterUsuario;
int nCaracterSenha;
int nCaracterSenhaL;
char achou = 'S';
char achouSenha = 'S';
int posVetorUsuario;
int codigoUsuario, codigoLogin,codigoSenhaU,codigoSenhaL;	
int n;
uint64_t senhaCript = 5381;	
char senhaCriptStr[20];	
int resposta;

	nCaracterUsuario = strlen(usuario);
	for (int i = 0; i < nUsuarios; i++){
		nCaracterLogin = strlen(vUsuario[i].nome);
		if (nCaracterUsuario == nCaracterLogin){
			achou = 'S';
			for (int j = 0 ; j < nCaracterLogin; j++){
				codigoUsuario = usuario[j];
				codigoLogin = vUsuario[i].nome[j];
				if (codigoUsuario != codigoLogin){
					
					achou = 'N';
					break;
				} 	
			} 
			if ( achou == 'S') {
				posVetorUsuario = i;
				break;
			}	
		}	else achou = 'N';
		
	} //primeiro verifica o usuario entre o usuario digitado	
	
	if ( achou == 'S') {
		
		nCaracterSenha = strlen(senhaDigitada);
		nCaracterSenhaL = strlen(vUsuario[posVetorUsuario].senha);

		for (int i=0;i<nCaracterSenha;i++){  // calculo da funcao da senha seguindo a formula Hi = 33 . Hi-1 + ci         onde H0 = 5381
			n = senhaDigitada[i];
			senhaCript = 33*senhaCript+n;
 
	    }
		
		memset(senhaCriptStr,(int)0,sizeof(char)*20);
		sprintf(senhaCriptStr,"%"SCNu64,senhaCript);
		nCaracterSenha = strlen(senhaCriptStr);
		for (int k = 0; k < nCaracterSenha;k++){   //faz a verificacao da senha com o resultado da formula com o cadastro no vetor de estrutura
			if (nCaracterSenha == nCaracterSenhaL){
				achouSenha = 'S';
				for (int m = 0;m < nCaracterSenhaL;m++){
					codigoSenhaU = senhaCriptStr[m];
					codigoSenhaL = vUsuario[posVetorUsuario].senha[m];
					if (codigoSenhaU != codigoSenhaL){
						achouSenha = 'N';
						break;
					}	
				}			
				
			}	else achouSenha = 'N';
		}
		
	}

	if ((achou == 'S') && (achouSenha == 'S'))    //resposta = 0 - login aceito, resposta = 1 - usuario nao encontrado , resposta = 2 - senha incorreta
		resposta = 0 ;
	else
	if ( (achou == 'N'))
		resposta = 1;
	else
	if ((achou == 'S') && (achouSenha == 'N'))
		resposta = 2;
	return resposta;
}
	
int main()
{


	char p ;
	char usuario[20];
	char senhaDigitada[20] ;
	char nomeSenha[42];
	char entradaValida = 'N';

    int n,i,j=0;
	int	nCaracterUsuario,nUsuarios,nLogin;
	uint64_t senhaCript = 5381;	
	uint64_t intsenha;
	estructUsuario *vUsuario;

	int resposta;
    //primeira entrada de n linhas contendo usuario e funcao da senha
	printf("Entre com o numero de usuarios cadastrados\n");
	scanf("%d",&nUsuarios);
	vUsuario = (estructUsuario*)malloc(nUsuarios*sizeof(estructUsuario));
	
	for (int nCadastros = 0;nCadastros < nUsuarios;nCadastros++){
		while (entradaValida != 'S'){
			memset(nomeSenha,(int)0,sizeof(char)*42);
			printf("Entre com o usuário e senha (usuario senha)\n");
			scanf(" %[^\n]s",nomeSenha);
			entradaValida = fNomeUsuario(nomeSenha,&j,usuario);
			if (entradaValida == 'S'){
				entradaValida = fSenhaUsuario(nomeSenha,j,senhaDigitada,0);
			}	
		}
		usuario[j] = '\0';


		strcpy(vUsuario[nCadastros].nome,usuario);
		strcpy(vUsuario[nCadastros].senha,senhaDigitada);
		if (nCadastros < nUsuarios)
			entradaValida = 'N';
	}
	
    //segunda entrada com m linhas contendo usuario e a senha 
	printf("Entre com o numero de logins\n");
	scanf("%d",&nLogin);	   
	entradaValida = 'N';	   
		   
	for (int nCadastros = 0;nCadastros < nLogin;nCadastros++){
		while (entradaValida != 'S'){
			memset(nomeSenha,(int)0,sizeof(char)*42);
			printf("Entre com o usuário e senha (usuario senha)\n");
			scanf(" %[^\n]s",nomeSenha);
			entradaValida = fNomeUsuario(nomeSenha,&j,usuario);
			if (entradaValida == 'S'){
				entradaValida = fSenhaUsuario(nomeSenha,j,senhaDigitada,1);
			}	
		}

		usuario[j] = '\0';

		resposta = testeLogin(usuario,senhaDigitada, vUsuario,nUsuarios);
        if (resposta == 0) printf("login aceito\n");
		else if (resposta == 1) printf("Usuario não encontrado\n");
		else if (resposta == 2) printf("senha Incorreta\n");
	
		
		if (nCadastros < nLogin)
			entradaValida = 'N';
	}
	

   	
return 0;
}