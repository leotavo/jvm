// jvm.c

/*==========================================*/
// 	DESCRIÇÃO

// Implementação dos métodos da JVM


/*==========================================*/
//	INCLUDES
#include	"jvm.h"
#include	"verifier.h"
#include	<stdlib.h>
#include	<string.h>
#include	<stdbool.h>

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
	jvm->heap = (HEAP_AREA *) malloc(sizeof(HEAP_AREA));
	
	CLASS_DATA	* main_class_data;
	
	
/*	puts("DEBUG:\tCLASS LOADING");*/
	classLoading(class_filename, &main_class_data, NULL, jvm);
	classLinking(main_class_data, jvm);
	classInitialization(main_class_data, jvm);
	
	// INTERPRETADOR
	
	classUnloading(main_class_data, jvm);
	jvmExit(jvm);
}// fim da função jvmStart
/*==========================================*/

// função classLoading
void	classLoading(char * class_filename, CLASS_DATA ** cd, CLASS_DATA * classloader, JVM * jvm){
	
/*	
The loading process consists of three basic activities. To load a type, the Java virtual machine must:

- given the type's fully qualified name (char * class_filename), produce a stream of binary data (ClassFile ** cf) that represents the type - OK
- parse the stream of binary data into internal data structures in the method area - OK
- create an instance of class java.lang.Class that represents the type - OK
*/
/*	puts("DEBUG:\tCRIANDO CLASSFILE");*/
	FILE	* class_binary_file;
	ClassFile	* cf;
	
	class_binary_file = fopen(class_filename, "r");
	if(!class_binary_file){
		puts("ClassNotFoundException");
		exit(EXIT_FAILURE);
	}
	else{
		cf = loadClassFile(class_binary_file);
	}
/*	puts("DEBUG:\tCRIANDO CLASS_DATA");*/
	(*cd) = (CLASS_DATA *) malloc(sizeof(CLASS_DATA));
	
	(*cd)->prox = jvm->method_area;
	jvm->method_area = (*cd);
	(*cd)->class_variables = NULL;
	(*cd)->instance_class = NULL;
	
	if(!classloader){
		(*cd)->classloader_reference = (*cd);
	}
	else{
		(*cd)->classloader_reference = classloader;
	}
	(*cd)->classfile = cf;
	(*cd)->runtime_constant_pool = cf->constant_pool;
	(*cd)->field_data = cf->fields;
	(*cd)->method_data = cf->methods;
	
}// fim da função classLoading

/*==========================================*/
// função classLinking
void	classLinking(CLASS_DATA * cd, JVM * jvm){
	classLinkingVerification(cd, jvm);
	classLinkingPreparation(cd, jvm);
}// fim da função classLinking

/*==========================================*/
// função classLinkingVerification
void	classLinkingVerification(CLASS_DATA * cd, JVM * jvm){
/*	A IMPLEMENTAR
Verification: ensuring the correctness of the imported type
https://www.artima.com/insidejvm/ed2/security3.html
Structural Checks on The Classfile
- magic number = 0xCAFEBABE = OK (ClassLoading)
- major/minor version supported = <= java 1.2 = OK (ClassLoading)
- tipo e tamanho dos componentes do classfile (bytes truncados ou extras) = OK (ClassLoading)
Semantic Checks on the Type Data
- verificar se um componente do classfile está bem formado. (exemplo: descritor de um método); = OK (verifyClassfile)
- verificações de classe:
-- toda classe, exceto Object, tem q ter uma superclasse  = OK (verifyClassfile) = TESTAR
-- classe final não é herdada; = OK (verifyFinal) = TESTAR
-- método final não é sobrecarregado = OK (verifyFinal) = TESTAR
- entradas válidas da Constant Pool (índices referem-se ao tipo correto) = OK (verifyConstantPool)
- verificação de regras da linguagem java que deveriam ter sido vistas em tempo de compilação ????
Bytecode Verifier: FALTANDO
- nao importa o caminho de execução, ao chegar num certo bytecode, a operand_stack tem o mesmo numero de itens e mesmo tipo;
- variavel local nao pode ser acessada antes de conter um valor apropriado.
- atribuição de valores apropriados à fields de classe
- metodos da classe sao sempre invocados com o correto numero e tipo de argumentos.
- verifica que cada opcode é valido, que tem operandos válidos
- cada opcode tem operandos válidos na pilha e o no vetor de variaveis locais
*/
	verifyClassfile(cd->classfile);
	verifySuperFinal(cd->classfile, jvm);
	verifyOverrideMethodFinal(cd->classfile, jvm);
}// fim da função classLinkingVerification

/*==========================================*/
// função classLinkingPreparation
void	classLinkingPreparation(CLASS_DATA * cd, JVM * jvm){
/*
Preparation: allocating memory for class variables and initializing the memory to default values
*/
/*	puts("DEBUG:\tCRIANDO OBJECT");*/
/*	OBJECT	* obj = (OBJECT *) malloc(sizeof(OBJECT));*/
/*	obj->prox = (jvm->heap)->objects;*/
/*	(jvm->heap)->objects = obj;*/
/*	obj->class_data_reference = cd;*/
/*	obj->instance_variables = NULL;*/
/*	cd->instance_class = obj;*/
		
		
	if(!(cd->classfile)->fields_count){
		cd->class_variables = NULL;
	}
	else{
/*		puts("DEBUG:\tCRIANDO VARIABLES");*/
		for(u2 i = 0; i < (cd->classfile)->fields_count; i++){
			VARIABLE	* var = (VARIABLE *) malloc(sizeof(VARIABLE));
			var->field_reference = cd->field_data + i;
			
			VALUE	* value = (VALUE *) malloc(sizeof(VALUE));
			u2	descriptor_index = (cd->field_data + i)->descriptor_index;
			value->type = (cd->runtime_constant_pool + descriptor_index - 1)->u.Utf8.bytes[0];
/*			printf("DEBUG:\tvalue->type = %c\n", value->type);*/
			switch(value->type){
				case	BOOLEAN:
					value->u.Boolean.boolean = 0;
					break;
				case	BYTE:
					value->u.Byte.byte = 0;
					break;
				case	CHAR:
					value->u.Char.char_ = 0;
					break;
				case	DOUBLE:
					value->u.Double.high_bytes = 0;
					value->u.Double.low_bytes = 0;
					break;
				case	FLOAT:
					value->u.Float.float_ = 0;
					break;
				case	INT:
					value->u.Integer.integer = 0;
					break;
				case	LONG:
					value->u.Long.high_bytes = 0;
					value->u.Long.low_bytes = 0;
					break;
				case	REF_INST:
					value->u.InstanceReference.reference = NULL;
					break;
				case	SHORT:
					value->u.Short.short_ = 0;
					break;
				case	REF_ARRAY:
					value->u.ArrayReference.reference = NULL;
					break;
				default:
					puts("VerifyError");
					exit(EXIT_FAILURE);
			}
			u2	access_flags = (cd->field_data + i)->access_flags;
			if(!(access_flags & ACC_FINAL)){
				if((access_flags & ACC_STATIC) || ((cd->classfile)->access_flags & ACC_INTERFACE)){		
/*					puts("DEBUG:\tCLASS_VARIABLE");*/
					var->prox = cd->class_variables;
					cd->class_variables = var;
				}
			}
/*			else{*/
/*/*				puts("DEBUG:\tINSTANCE_VARIABLE");*/
/*				var->prox = obj->instance_variables;*/
/*				obj->instance_variables = var;*/
/*			}*/
		}
	}
}// fim da função classLinkingPreparation
/*==========================================*/
// função classLinkingResolution
void	classLinkingResolution(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR = EM TEMPO DE EXECUÇÃO
Verification of Symbolic References
ao executar bytecodes e carregar classfiles
Resolution: transforming symbolic references from the type into direct references.
*/
}// fim da função classLinkingResolution

/*==========================================*/
// função getClassName
char	*	getClassName(CLASS_DATA * cd){
 	cp_info	* cp_aux = (cd->classfile)->constant_pool + (cd->classfile)->this_class - 1;
 	char	* class_name = cp_aux->u.Utf8.bytes;
 	class_name[cp_aux->u.Utf8.length] = '\0';
 	return	class_name;
 }
/*==========================================*/
// função classInitialization
void	classInitialization(CLASS_DATA * cd, JVM * jvm){
/*	A IMPLEMENTAR
Initialization of a class consists of two steps:

Initializing the class's direct superclass (if any), if the direct superclass hasn't already been initialized
Executing the class's class initialization method, if it has one
*/
	
	if((cd->classfile)->super_class){
		cp_info	* cp_aux = (cd->classfile)->constant_pool + (cd->classfile)->super_class - 1;
		cp_aux = (cd->classfile)->constant_pool + cp_aux->u.Class.name_index - 1;
		char	* super_class_name = cp_aux->u.Utf8.bytes;
		super_class_name[cp_aux->u.Utf8.length] = '\0';
		
		if(strcmp(super_class_name, "java/lang/Object")){
			CLASS_DATA	* cd_super;
			if(!(cd_super = getSuperClass(cd->classfile, jvm))){
				classLoading(super_class_name, &cd_super, cd, jvm);
				classLinking(cd_super, jvm);
				classInitialization(cd_super, jvm);
			}
		}
		execute("<clinit>", cd, jvm);			
	}	
}// fim da função classInitialization

/*==========================================*/
// função getMethod
method_info	* getMethod(char * method_name, CLASS_DATA * cd){
	char *	name;
	cp_info	* cp_aux;
	method_info	* method_aux;
	for(u2	i = 0; i < (cd->classfile)->methods_count; i++){
		method_aux = cd->method_data + i;
		cp_aux = method_aux->name_index + (cd->classfile)->constant_pool - 1;
		name = cp_aux->u.Utf8.bytes;
		name[cp_aux->u.Utf8.length] = '\0';
		if(!strcmp(method_name, name)){
			return (cd->method_data + i);
		}
	}
	return	NULL;
	
	
}// fim da função getMethod

/*==========================================*/
// função getCodeAttribute
attribute_info	* getCodeAttribute(method_info * method, CLASS_DATA * cd){
	cp_info	* cp_aux;
	char	* attribute_name;
	for(u2	i = 0; i < method->attributes_count; i++){
		cp_aux = (cd->classfile)->constant_pool + (method->attributes + i)->attribute_name_index - 1;
		attribute_name = cp_aux->u.Utf8.bytes;
		attribute_name[cp_aux->u.Utf8.length] = '\0';
		if(!strcmp("Code", attribute_name)){
			return	(method->attributes + i);
		}
	}
	return	NULL;
}// fim da função getMethod

/*==========================================*/
// função execute
void	executeMethod(char * method_name, CLASS_DATA * cd, JVM * jvm){
	method_info	* method = getMethod(method_name, cd);
	if(method){
		attribute_info	* code_attr = getCodeAttribute(method, cd);
		if(code_attr){
		
		}
	}
	
}// fim da função execute

/*==========================================*/
// função classUnloading
void	classUnloading(CLASS_DATA * cd, JVM * jvm){
/*	A IMPLEMENTAR
https://docs.oracle.com/javase/specs/jvms/se6/html/Concepts.doc.html#19175
*/
	free(cd);
}// fim da função classUnloading
/*==========================================*/
// função jvmExit
void	jvmExit(JVM * jvm){
/*	A IMPLEMENTAR
	
*/
	free(jvm);
}// fim da funçao jvmExit
/*==========================================*/


