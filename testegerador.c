
#include<stdio.h>
#include<math.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
 
//funcao para retornar o valor de g^c mod p
uint64_t powmod(uint64_t g, uint64_t b, uint64_t P)
{
	// a ideia é usar a aritmética modular então a1 · a2 mod m = (a1 mod m · a2 mod m) mod m. entao fazer a divisão
	// do numero b que é a chave privada em blocos e depois multiplicando esses blocos usando a formula de multiplicação de modulos.
	
  /*  uint64_t a,b2,bAux; 
	int posicao,ini = 1;
	
	uint64_t pot = 1 ; 
    b2 = 2*b;
	bAux = b;
	for (int i = ini ;i <= b2; i = 2*i){
		if (i == 1){  
			pot = pot * ( g % P);
			printf("primeiro modulo %"SCNu64"\n", pot);	
		}else
		if (i < bAux){	
			pot = (pot*pot) % P;
			posicao = i;
			printf("n modulos %"SCNu64"\n", pot);	
		} else {
			bAux = (b - posicao);
			b2 = 2*bAux;
			ini = 1 ;
		} 	
	}*/
	uint64_t r = 1;
		g = g%P;
	while (b > 0){
		if (b & 1){
			 r = (r*g)%P;
		}
		printf("b antes %"SCNu64"\n", b);
		b = b>>1;
		printf("b depois %"SCNu64"\n", b);
		g = (g*g) %P;
	}
	return r;
} 
 

int main()
{
    uint64_t P = 0, G, x, a, y, b, ka, kb; 
    printf("Entre com um primo \n");
	scanf("%"SCNu64, &P) ;
	printf("primo %"SCNu64"\n", P);
	//teste do Primo até 32 bits
	while ((P <= 0) || (P > 4294967295)){
		printf("Entre com um primo maior que 0 e menor que 32 bits(4294967295). \n");
		scanf("%"SCNu64, &P) ;
	}

 
    printf("Entre com o gerador \n");
	scanf("%"SCNu64, &G) ;
	//teste do gerador até 32 bits
	while ((G <= 0) || (G > 4294967295)){
		printf("Entre com um Gerador maior que 0 e menor que 32 bits(4294967295). \n");
		scanf("%"SCNu64, &G) ;
	}


    // chave privada de Alice 
    a =  151;//rand(); // chave gerada pelo função rand 
    x = powmod(G, a, P); // Valor de A 
	printf("Alice %"SCNu64"\n", x);
	
    // Chave privada de Bob
    b = 151;//rand(); // chave gerada pelo função rand 
    y = powmod(G, b, P); // Valor de B
	printf("Bob %"SCNu64"\n", y);	
 
    // Valor secreto de Alive e Bob
    ka = powmod(y, a, P); // Segredo de Alice
	printf("O segredo de Alice é: %"SCNu64"\n", ka);

	kb = powmod(x, b, P); // segredo de Bob
    printf("O segredo de Bob : %"SCNu64"\n", kb);
     
    return 0;
}