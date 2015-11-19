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
void	jvmStart(char * class_filename, int num_args, char * args[]){
/*
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#16491
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19042
*/	
	JVM	* jvm;
	jvm = (JVM *) malloc(sizeof(JVM));
	jvm->method_area = NULL;
	jvm->threads = NULL;
	jvm->heap = (HEAP_AREA *) malloc(sizeof(HEAP_AREA);
	
	ClassFile	* main_classfile;
		
	classLoading(class_filename, &main_classfile, NULL, jvm);
	
	classLinking(main_classfile, jvm);
	classInitialization(main_classfile, jvm);
	
	// INTERPRETADOR
	
	classUnloading(main_classfile, jvm);
	jvmExit(jvm);

}// fim da função jvmStart
/*==========================================*/
// função classLoading
void	classLoading(char * class_filename, ClassFile ** cf, CLASS_DATA * classloader, JVM * jvm){
	
/*	A IMPLEMENTAR
Loading: finding and importing the binary data for a type
The loading process consists of three basic activities. To load a type, the Java virtual machine must:

given the type's fully qualified name, produce a stream of binary data that represents the type - OK
parse the stream of binary data into internal data structures in the method area - OK
create an instance of class java.lang.Class that represents the type - OK
*/
	// CRIANDO O CLASSFILE.
	FILE	* class_binary_file;
	class_binary_file = fopen(class_filename, "r");
	if(!class_binary_file){
		// LANÇA EXCEÇÃO ARQUIVO.CLASS
		exit(EXIT_FAILURE);
	}
	else{
		cf = loadClassFile(class_binary_file);
	}
	
	// CRIANDO O CLASS_DATA
	CLASS_DATA	* cd = (CLASS_DATA *) malloc(sizeof(CLASS_DATA));
	cd->prox = jvm->method_area;
	jvm->method_area = cd;
	cd->class_variables = NULL;
	cd->instance_class = NULL;
	
	if(!classloader){
		cd->classloader_reference = cd;
	}
	else{
		cd->classloader_reference = classloader;
	}
	cd->classfile = cf;
	cd->runtime_constant_pool = cf->constant_pool;
	cd->field_data = cd->fields;
	cd->method_data = cd->methods;
	
	// CRIANDO OBJECT
		OBJECT	* obj = (OBJECT *) malloc(sizeof(OBJECT));
		obj->prox = (jvm->heap)->objects;
		(jvm->heap)->objects = obj;
		obj->class_data_reference = cd;
		obj->instance_variables = NULL;
		cd->instance_class = obj;
		
		
	if(!(cd->classfile)->fields_count){
		cd->class_variables = NULL;
	}
	else{
		
		
		// CRIANDO CLASS_VARIABLES E INSTANCE_VARIABLES
		for(u2 i = 0; i < (cd->classfile)->fields_count; i++){
			VARIABLE	* var = (VARIABLE *) malloc(sizeof(VARIABLE));
			var->field_reference = cd->field_data + i;
			VALUE	* value = (VALUE *) malloc(sizeof(VALUE));
			// acessar descriptor_index do field para definir o tipo de value
			// verificar atributo ConstantValue do field para inicializar
		 if((cd->field_data + i)->access_flags | ACC_STATIC){ // CLASS_VARIABLES
			var->prox = cd->class_variables;
			cd->class_variables = var;
		 }
		 else{ // INSTANCE_VARIABLES
		 	var->prox = obj->instance_variables;
			obj->instance_variables = var;
		}
		}		
	}
	
	
}// fim da função classLoading
/*==========================================*/
// função classLinking
void	classLinking(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
Linking: performing verification, preparation, and (optionally) resolution
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#22574
*/
	classLinkingVerification(cf, jvm);
	classLinkingPreparation(cf, jvm);
/*	classLinkingResolution(cf, jvm);*/  // EM TEMPO DE EXECUÇÃO
}// fim da função classLinking
/*==========================================*/
// função classLinkingVerification
void	classLinkingVerification(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
Verification: ensuring the correctness of the imported type
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
Bytecode Verifier:
- nao importa o caminho de execução, ao chegar num certo bytecode, a operand_stack tem o mesmo numero de itens e mesmo tipo;
- variavel local nao pode ser acessada antes de conter um valor apropriado.
- atribuição de valores apropriados à fields de classe
- metodos da classe sao sempre invocados com o correto numero e tipo de argumentos.
- verifica que cada opcode é valido, que tem operandos válidos
- cada opcode tem operandos válidos na pilha e o no vetor de variaveis locais


*/
}// fim da função classLinkingVerication
/*==========================================*/
// função classLinkingPreparation
void	classLinkingPreparation(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
Preparation: allocating memory for class variables and initializing the memory to default values
*/
}// fim da função classLinkingPreparation
/*==========================================*/
// função classLinkingResolution
void	classLinkingResolution(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
Verification of Symbolic References
ao executar bytecodes e carregar classfiles
Resolution: transforming symbolic references from the type into direct references.
*/
}// fim da função classLinkingResolution
/*==========================================*/
// função classInitialization
void	classInitialization(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19075
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#24237
Initialization: invoking Java code that initializes class variables to their proper starting values.
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19175
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


