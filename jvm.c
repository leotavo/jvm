// jvm.c

/*==========================================*/
// 	DESCRIÇÃO

// Implementação dos métodos da JVM


/*==========================================*/
//	INCLUDES
#include	"jvm.h"
#include	"verifier.h"
#include	"interpreter.h"
#include	<stdlib.h>
#include	<string.h>
#include	<stdbool.h>

/*==========================================*/

//	MÉTODOS

/*==========================================*/

void	PrintConstantUtf8(cp_info * cp, FILE * out){
	char	* string = (char *) cp->u.Utf8.bytes;
	string[cp->u.Utf8.length] = '\0';
	fprintf(out, "%s", string );
}

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
	
	
/*	puts("DEBUG:\tCLASS LOADING\n");*/
	classLoading(class_filename, &main_class_data, NULL, jvm);
/*	puts("DEBUG:\tCLASS LINKING\n");*/
	classLinking(main_class_data, jvm);
	
	// INICIA THREAD PRINCIPAL
	THREAD		* main_thread = (THREAD *) malloc(sizeof(THREAD));
	main_thread->program_counter = NULL;
	main_thread->jvm_stack = NULL;
	main_thread->prox = NULL;
	jvm->threads = main_thread;
	
/*	puts("DEBUG:\tCLASS INITIALIZATION\n");*/
	classInitialization(main_class_data, jvm, main_thread);
	
	if(main_class_data->modifiers & ACC_ABSTRACT){
		puts("ERROR: method 'main' not find.");
		exit(EXIT_FAILURE);
	}
	executeMethod("main", main_class_data, jvm, main_thread, main_class_data);
	
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
		printf("Carregando %s\n", class_filename);
		cf = loadClassFile(class_binary_file);
	}
/*	puts("DEBUG:\tCRIANDO CLASS_DATA");*/
	(*cd) = (CLASS_DATA *) malloc(sizeof(CLASS_DATA));
	cp_info	* cp_aux = cf->constant_pool + cf->this_class - 1;
	(*cd)->class_name = cf->constant_pool + cp_aux->u.Class.name_index - 1;
/*	PrintConstantUtf8((*cd)->class_name, stdout);*/
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
	(*cd)->modifiers = ((*cd)->classfile)->access_flags;
	(*cd)->runtime_constant_pool = cf->constant_pool;
	
	// armazena informações dos fields
	(*cd)->field_data = (FIELD_DATA *) malloc(cf->fields_count * sizeof(FIELD_DATA));
	for(u2 i = 0; i < cf->fields_count; i++){
		((*cd)->field_data + i)->field_name = cf->constant_pool + (cf->fields + i)->name_index - 1;
		((*cd)->field_data + i)->field_descriptor = cf->constant_pool + (cf->fields + i)->descriptor_index - 1;
		((*cd)->field_data + i)->modifiers = (cf->fields + i)->access_flags;
		((*cd)->field_data + i)->info = (cf->fields + i);
		if(! isFieldDescriptor(((*cd)->field_data + i)->field_descriptor, 0)){
/*			PrintConstantUtf8(((*cd)->field_data + i)->field_descriptor, stdout);*/
			puts("VerifyError: field descriptor");
			exit(EXIT_FAILURE);
		}
		((*cd)->field_data + i)->field_type = *(((*cd)->field_data + i)->field_name)->u.Utf8.bytes;
	}

	// armazena informações dos métodos
	(*cd)->method_data = (METHOD_DATA *) malloc(cf->methods_count * sizeof(METHOD_DATA));
	for(u2 i = 0; i < cf->methods_count; i++){
		((*cd)->method_data + i)->method_name = cf->constant_pool + (cf->methods + i)->name_index - 1;
		((*cd)->method_data + i)->method_descriptor = cf->constant_pool + (cf->methods + i)->descriptor_index - 1;
		((*cd)->method_data + i)->modifiers = (cf->methods + i)->access_flags;
		((*cd)->method_data + i)->info = (cf->methods + i);
		((*cd)->method_data + i)->class_data = (*cd);
		
		if(*(((*cd)->method_data + i)->method_descriptor)->u.Utf8.bytes != '('){
			puts("VerifyError: method descriptor");
			exit(EXIT_FAILURE);		
		}
		
		if(! isMethodDescriptor(((*cd)->method_data + i)->method_descriptor, 1)){
			puts("VerifyError: method descriptor");
			exit(EXIT_FAILURE);
		}
		
		if(!(((*cd)->method_data + i)->modifiers & ACC_ABSTRACT) && !(((*cd)->method_data + i)->modifiers & ACC_NATIVE)){
			attribute_info	* code_attr = getCodeAttribute((*cd)->method_data + i, *cd);
			if(!code_attr){
				puts("VerifyError: No code attribute");
				exit(EXIT_FAILURE);
			}
			((*cd)->method_data + i)->code_length = code_attr->u.Code.code_length;
			((*cd)->method_data + i)->bytecodes = code_attr->u.Code.code;
			((*cd)->method_data + i)->stack_size = code_attr->u.Code.max_stack;
			((*cd)->method_data + i)->locals_size = code_attr->u.Code.max_locals;
			((*cd)->method_data + i)->exception_table_length = code_attr->u.Code.exception_table_length;
			((*cd)->method_data + i)->exception_table = code_attr->u.Code.exception_table;			
		}
	}	
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
			(cd->field_data + i)->var = var;
			
			u2	descriptor_index = ((cd->field_data + i)->info)->descriptor_index;
			(var->value).type = (cd->runtime_constant_pool + descriptor_index - 1)->u.Utf8.bytes[0];
/*			printf("DEBUG:\t(var->value).type = %c\n", (var->value).type);*/
			switch((var->value).type){
				case	BOOLEAN:
					(var->value).u.Boolean.boolean = 0;
					break;
				case	BYTE:
					(var->value).u.Byte.byte = 0;
					break;
				case	CHAR:
					(var->value).u.Char.char_ = 0;
					break;
				case	DOUBLE:
					(var->value).u.Double.high_bytes = 0;
					(var->value).u.Double.low_bytes = 0;
					break;
				case	FLOAT:
					(var->value).u.Float.float_ = 0;
					break;
				case	INT:
					(var->value).u.Integer.integer = 0;
					break;
				case	LONG:
					(var->value).u.Long.high_bytes = 0;
					(var->value).u.Long.low_bytes = 0;
					break;
				case	REF_INST:
					(var->value).u.InstanceReference.reference = NULL;
					break;
				case	SHORT:
					(var->value).u.Short.short_ = 0;
					break;
				case	REF_ARRAY:
					(var->value).u.ArrayReference.reference = NULL;
					break;
				default:
					puts("VerifyError: Unknown type");
					exit(EXIT_FAILURE);
			}
			u2	access_flags = (cd->field_data + i)->modifiers;
/*			if(!(access_flags & ACC_FINAL)){*/
				if((access_flags & ACC_STATIC) || ((cd->classfile)->access_flags & ACC_INTERFACE)){		
					var->prox = cd->class_variables;
					cd->class_variables = var;
				}
/*			}*/
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
 	cp_info	* cp_aux = cd->class_name;
 	char	* class_name = cp_aux->u.Utf8.bytes;
 	class_name[cp_aux->u.Utf8.length] = '\0';
 	return	class_name;
 }
 
 /*==========================================*/
// função getSuperClass
CLASS_DATA	* getSuperClass(ClassFile * cf, JVM * jvm){
	if(cf->super_class){
		cp_info	* cp_aux = cf->constant_pool + cf->super_class - 1;
		cp_aux = cf->constant_pool + cp_aux->u.Class.name_index - 1;
		char	* super_name = cp_aux->u.Utf8.bytes;
		super_name[cp_aux->u.Utf8.length] = '\0';
		if(strcmp(super_name, "java/lang/Object")){
			CLASS_DATA	* cd = jvm->method_area;
/*			printf("length = %" PRIu16 "\n", (cd->class_name)->u.Utf8.length);*/
			while(cd){
				char	* name = (cd->class_name)->u.Utf8.bytes;
				name[(cd->class_name)->u.Utf8.length] = '\0';
				if(!strcmp(super_name, name)){
					return	cd;
				}
				else{
					cd = cd->prox;
				}	
			}
		}
	}
	return	NULL;
}// fim da função getSuperClass

/*==========================================*/
// funcao getClass
CLASS_DATA	* getClass(cp_info * cp_class_name, JVM * jvm){
	char	* class_name = cp_class_name->u.Utf8.bytes;
	class_name[cp_class_name->u.Utf8.length] = '\0';
	
	CLASS_DATA	* cd = jvm->method_area;
	while(cd){
		char	* cd_class_name = getClassName(cd);
		if(!strcmp(class_name, cd_class_name)){
			return	cd;
		}
		else{
			cd = cd->prox;
		}
	}
	return	NULL;
}

/*==========================================*/
// funcao getClassVariable
VARIABLE	* getClassVariable(cp_info * cp_field_name, CLASS_DATA * field_class){
	VARIABLE	* cv = field_class->class_variables;
	
	while(cv){
		FIELD_DATA	* fr = cv->field_reference;
		
		char	*string1 = cp_field_name->u.Utf8.bytes;
		string1[cp_field_name->u.Utf8.length];
		
		char	*string2 = ((cv->field_reference)->field_name)->u.Utf8.bytes;
		string2[((cv->field_reference)->field_name)->u.Utf8.length];
		if(!strcmp(string1, string2)){
			return	cv;
		}
		else{
			cv = cv->prox;
		}
	}
	return	NULL;

}

/*==========================================*/
// função classInitialization
void	classInitialization(CLASS_DATA * cd, JVM * jvm, THREAD * thread){
/*	A IMPLEMENTAR
Initialization of a class consists of two steps:

Initializing the class's direct superclass (if any), if the direct superclass hasn't already been initialized
Executing the class's class initialization method, if it has one
*/
	
	if((cd->classfile)->super_class){
		cp_info	* cp_aux = (cd->classfile)->constant_pool + (cd->classfile)->super_class - 1;
		cp_aux = (cd->classfile)->constant_pool + cp_aux->u.Class.name_index - 1;
		char	* super_class_name = cp_aux->u.Utf8.bytes;
/*		super_class_name[cp_aux->u.Utf8.length] = '\0';*/
/*		printf("Super class:\t");*/
/*		PrintConstantUtf8(cp_aux, stdout);*/
/*		puts("");*/
/*		if(strcmp(super_class_name, "java/lang/Object")){*/
			CLASS_DATA	* cd_super;
/*			if(!(cd_super = getSuperClass(cd->classfile, jvm))){*/
			if(!(cd_super = getClass(cp_aux, jvm))){
				classLoading(strcat(super_class_name, ".class"), &cd_super, cd, jvm);
			}
			classLinking(cd_super, jvm);
			classInitialization(cd_super, jvm, thread);
/*		}*/
	}
/*	executeMethod("<init>", cd, jvm, thread, cd);*/
	executeMethod("<clinit>", cd, jvm, thread, cd);	
}// fim da função classInitialization

/*==========================================*/
// função getMethod
METHOD_DATA	* getMethod(char * method_name, CLASS_DATA * cd){
	char *	name;
	for(u2	i = 0; i < (cd->classfile)->methods_count; i++){
		name = ((cd->method_data + i)->method_name)->u.Utf8.bytes;
		name[((cd->method_data + i)->method_name)->u.Utf8.length] = '\0';
		if(!strcmp(method_name, name)){
			return	(cd->method_data + i);
		}
	}
	return	NULL;	
}// fim da função getMethod

/*==========================================*/
// função getCodeAttribute
attribute_info	* getCodeAttribute(METHOD_DATA * method, CLASS_DATA * cd){
	cp_info	* cp_aux;
	char	* attribute_name;
	for(u2	i = 0; i < (method->info)->attributes_count; i++){
		cp_aux = (cd->classfile)->constant_pool + ((method->info)->attributes + i)->attribute_name_index - 1;
		attribute_name = cp_aux->u.Utf8.bytes;
		attribute_name[cp_aux->u.Utf8.length] = '\0';
		if(!strcmp("Code", attribute_name)){
			return	((method->info)->attributes + i);
		}
	}
	return	NULL;
}// fim da função getMethod

/*==========================================*/
// função execute
void	executeMethod(char * method_name, CLASS_DATA * cd, JVM * jvm, THREAD * thread, void * this){
	
	METHOD_DATA	* method = getMethod(method_name, cd);
	if(method){
		if(method->modifiers & ACC_ABSTRACT){
			puts("ERROR: executing abstract method.");
			exit(EXIT_FAILURE);
		}
		attribute_info	* code_attr = getCodeAttribute(method, cd);
		if(code_attr){
			// CRIA NOVO FRAME PRO MÉTODO
			FRAME	* frame = (FRAME *) malloc(sizeof(FRAME));
			frame->local_variables = (u4 *) malloc(method->locals_size * sizeof(u4));
			frame->local_variables[0] = (u4) this;
			frame->operand_stack = NULL;
			frame->current_constant_pool = cd->runtime_constant_pool;
			frame->return_value = NULL;
			frame->prox = thread->jvm_stack;
			thread->jvm_stack = frame;
			
			printf("\nmétodo: ");
			PrintConstantUtf8(cd->class_name, stdout);
			printf(".%s\n", method_name);
			// CHAMA O INTERPRETADOR
			interpreter(method, thread, jvm);
			printf("\nEnd\t");
			PrintConstantUtf8(cd->class_name, stdout);
			printf(".%s\n", method_name);
			
		}
		else{
			puts("ERROR: non-abstract method without code attribute.");
			exit(EXIT_FAILURE);			
		}
	}
	else{
		if(strcmp(method_name, "<clinit>")){
			printf("método %s não encontrado.\n", method_name);
			exit(EXIT_FAILURE);	
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

void	pushOperand(u4 word, FRAME * frame){
	OPERAND	* aux = (OPERAND *) malloc(sizeof(OPERAND));
	
	aux->value = word;
	aux->prox = frame->operand_stack;
	frame->operand_stack = aux;
}

u4	popOperand(FRAME * frame){
	if(frame->operand_stack){
		OPERAND	* aux = frame->operand_stack;
		frame->operand_stack = aux->prox;
		u4	word = aux->value;
		free(aux);
		return	word;
	}
	else{
		puts("StackUnderflowError");
		exit(EXIT_FAILURE);
	}
}

bool		isSuperClass(CLASS_DATA * cd1, CLASS_DATA * cd2){}
