
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
	
    uint64_t a,restoC,restoD,restoE; 
	uint64_t pot = g % P; //será usado para a multiplicação em modulo caso a divisão do b por 2 tenha resto 1

	uint64_t metadeB = b / 2; //divindo a chave em dois blocos
	uint64_t restoB = b % 2; //pegando o resto da divisão
	
	if (metadeB / 2 >= 1){ // dividindo em mais dois blocos
		restoC = metadeB % 2; // resto da divisão
		metadeB = metadeB / 2; 
	} else { restoC = 9; }
	
	if (metadeB / 2 >= 1){  //dividindo em mais dois blocos
    	restoD = metadeB % 2; // resto da divisão
		metadeB = metadeB / 2; 
	} else { restoD = 9;}
	
	if (metadeB / 2 >= 1){ //dividindo em mais dois blocos
		restoE = metadeB % 2; // resto da divisão
		metadeB = metadeB / 2; 
	} else { restoE = 9;}

	// resto da divisão por 2 é 0 ou 1 então só tem divisao se for o resultado é maior ou igual a 1 
	// caso contrario o resto vai receber o valor 9 para sinalizar q não teve divisão		
			
    a = g % P; // fazendo o modulo de g¹
	
	//fazendo a multiplicaçao por modulo no for pelo  ultimo bloco de divisao da chave
	for (uint64_t i = 1; i < metadeB;i++){ 
		a = (a * pot) % P;
	}
	
	//verificando se o bloco foi divido 
	if (restoE != 9){
		//fazendo a  multiplicacao modular dos blocos  a1 · a2 mod m = (a1 mod m · a2 mod m) mod m = um numero B
		a = (a * a) % P;	
		//caso existe um resto fazer a multiplicação de g¹ com o resultado
		if (restoE == 1) { 
			a = (a * pot) % P;
		}
	}
	//verificando se o bloco foi divido 
	if (restoD != 9){		
		//multiplicando o outro bloco de divisão modular   a1 · a2 mod m = (a1 mod m · a2 mod m) mod m = um numero B
		a = (a * a) % P;	
		//caso existe um resto fazer a multiplicação de g¹ com o resultado
		if (restoD == 1) { 
			a = (a * pot) % P;
		}	
	}
	//verificando se o bloco foi divido 
	if (restoC != 9){		
		//multiplicando o outro bloco de divisão pegando o B da anterior  B · B mod m = (B mod m · B mod m) mod m = um numero C
		a = (a * a) % P;
		//caso existe um resto fazer a multiplicação de g¹ com o resultado 
		if (restoC ==1) { 
    		a = (a * pot) % P;
		}
	}
			
	//multiplicando o outro bloco de divisão pegando o B da anterior  C · C mod m = (C mod m · C mod m) mod m = um numero D
	a = (a * a) % P;	
	//caso existe um resto fazer a multiplicação de g¹ com o resultado 
	if (restoB == 1) { 
		a = (a * pot) % P;
	}	


	return a;
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
    a =  187;//rand(); // chave gerada pelo função rand 
    x = powmod(G, a, P); // Valor de A 
	printf("Alice %"SCNu64"\n", x);
	
    // Chave privada de Bob
    b = 95;//rand(); // chave gerada pelo função rand 
    y = powmod(G, b, P); // Valor de B
	printf("Bob %"SCNu64"\n", y);	
 
    // Valor secreto de Alive e Bob
    ka = powmod(y, a, P); // Segredo de Alice
	printf("O segredo de Alice é: %"SCNu64"\n", ka);

	kb = powmod(x, b, P); // segredo de Bob
    printf("O segredo de Bob : %"SCNu64"\n", kb);
     
    return 0;
}