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
	switch(argc){
		case	1:
			puts("Uso: ./jvm arquivo.class [args...]\n");
			return	0;
		default:
			jvmStart(argv[1], argc-2, argv+2);
}// fim da função main()
/*==========================================*/
