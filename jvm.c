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
	
	ClassFile	* main_classfile;
	main_classfile = newClassFile();
	
	classLoading(main_class_binary_file, main_classfile, jvm);
	classLinking(main_classfile, jvm);
	classInitialization(main_classfile, jvm);
	classUnloading(main_classfile, jvm);
	jvmExit(jvm);

}// fim da função jvmStart
/*==========================================*/
// função classLoading
void	classLoading(FILE * bf, ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19175
*/
}// fim da função classLoading
/*==========================================*/
// função classLinking
void	classLinking(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#22574
*/
	classLinkingVerification(cf, jvm);
	classLinkingPreparation(cf, jvm);
	classLinkingResolution(cf, jvm);
}// fim da função classLinking
/*==========================================*/
// função classLinkingVerification
void	classLinkingVerification(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
https://www.artima.com/insidejvm/ed2/security3.html
Structural Checks on The Classfile
- magic number = 0xCAFEBABE
- major/minor version supported = <= java 1.2
- tipo e tamanho dos componentes do classfile (bytes truncados ou extras)
Semantic Checks on the Type Data
- verificar se um componente do classfile está bem formado. (exemplo: descritor de um método);
- verificações de classe:
-- toda classe, exceto Object, tem q ter uma superclasse;
-- classe final não é subclasse; método final não é sobrecarregado
- entradas válidas da Constant Pool (índices referem-se ao tipo correto)
- verificação de regras da linguagem java que deveriam ter sido vistas em tempo de compilação.
*/
}// fim da função classLinkingVerication
/*==========================================*/
// função classLinkingPreparation
void	classLinkingPreparation(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR

*/
}// fim da função classLinkingPreparation
/*==========================================*/
// função classLinkingResolution
void	classLinkingResolution(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR

*/
}// fim da função classLinkingResolution
/*==========================================*/
// função classInitialization
void	classInitialization(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19075
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#24237

*/
}// fim da função classInitialization
/*==========================================*/
// função classUnloading
void	classUnloading(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19175
*/
	free(cf);
}// fim da função classUnloading
/*==========================================*/
// função jvmExit
void	jvmExit(JVM * jvm){
/*	A IMPLEMENTAR
	
*/
	free(jvm);
}// fim da funçao jvmExit
/*==========================================*/


