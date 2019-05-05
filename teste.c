#include<math.h>
#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<string.h>
 int main()
{

char p ;
//char c[]="teste";
	char *usuario;
	char nomeSenha[20];
	char entradaValida = 'N';
	int caracter;
int n,i,nCaracterUsuario,nUsuarios;
uint64_t senhaCript = 5381;	
	
	while (entradaValida != 'S'){
		printf("Entre com o numero de usuarios cadastrados\n");
		scanf("%d",&nUsuarios);

		printf("Entre com o usuário e senha (usuario senha)");
		scanf(" %[^\n]s",nomeSenha);
		printf("%s",nomeSenha);
		nCaracterUsuario = strlen(nomeSenha);
		
		printf("numero de caract %d\n",nCaracterUsuario);
	    
		for ( int i =0;i<21;i++){	
		    caracter = nomeSenha[i];
			if (caracter == 8) {
				entradaValida = 'S';
				
			}	
		}
	}
	entradaValida = 'S';
	usuario = "teste";
	nCaracterUsuario = strlen(usuario);
	printf("%d\n",nCaracterUsuario);
	
	for (i=0;i<nCaracterUsuario;i++){
		n = usuario[i];
		senhaCript = 33*senhaCript+n;
		
	   printf("%d\n",n); 
	}
	printf("primo %"SCNu64"\n", senhaCript);
	
return 0;
}