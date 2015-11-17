// main.c

/*==========================================*/
/* 	DESCRIÇÃO

- Passagens de parâmetro de entrada pela linha de comando.



*/
/*==========================================*/

/*==========================================*/
//	INCLUDES
#include	"jvm.h"
#include	<stdio.h>
/*==========================================*/


int	main(int, char **);	// função principal do programa

/*==========================================*/
// função main()
// - Trata os dados de entrada.
int	main(int argc, char* argv[]){
	FILE *	input;
	
	switch(argc){
		case	1:
			puts("Uso: ./jvm arquivo.class [args...]\n");
			return	0;
		default:
			input = fopen(argv[1],"r");
			if(!input){
				printf("Erro ao abrir o arquivo %s.\n", argv[1]);
				return 0;
			}
			else{
				jvmStart(input, argc-2, argv+2);
				fclose(input);
			}
	}
}// fim da função main()
/*==========================================*/
