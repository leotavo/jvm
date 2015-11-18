// jvm.c

/*==========================================*/
// 	DESCRIÇÃO

// Implementação dos métodos da JVM


/*==========================================*/
//	INCLUDES
#include	"jvm.h"
#include	<stdlib.h>

/*==========================================*/
//	MÉTODOS

/*==========================================*/
// função jvmStart
void	jvmStart(FILE * main_class_binary_file, int num_args, char * args[]){
/*
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#16491
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19042
*/	
	JVM	* jvm;
	jvm = (JVM *) malloc(sizeof(JVM));
	
	ClassFile	* main_cf;
	
	classLoading(main_class, &main_cf);
	classLinking(&main_cf);

}// fim da função jvmStart

/*==========================================*/
// função classLoading
void	classLoading(FILE * class_binary_file, ClassFile ** cf){
/*
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19175
*/

}// fim da função classLoading

/*==========================================*/

// função classLinking
void	classLinking(ClassFile ** cf){
/*
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#22574
*/
	classLinkingVerification(cf);
	classLinkingPreparation(cf);
	classLinkingResolution(cf);
}// fim da função classLinking

/*==========================================*/
// função classLinkingVerification
void	classLinkingVerification(ClassFile ** cf){
/*

*/
}// fim da função classLinkingVerication

/*==========================================*/
// função classLinkingPreparation
void	classLinkingPreparation(ClassFile ** cf){
/*

*/
}// fim da função classLinkingPreparation

/*==========================================*/
// função classLinkingResolution
void	classLinkingResolution(ClassFile ** cf){
/*

*/
}// fim da função classLinkingResolution

/*==========================================*/
// função classInitialization
void	classInitialization(ClassFile ** cf){
/*
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19075
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#24237
*/
}// fim da função classInitialization

/*==========================================*/
// função jvmExit
void	jvmExit(){

}// fim da funçao jvmExit



