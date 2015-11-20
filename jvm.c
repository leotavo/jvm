// jvm.c

/*==========================================*/
// 	DESCRIÇÃO

// Implementação dos métodos da JVM


/*==========================================*/
//	INCLUDES
#include	"jvm.h"
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
	
	ClassFile	* main_classfile;
	
	
/*	puts("DEBUG:\tCLASS LOADING");*/
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
	
/*	
The loading process consists of three basic activities. To load a type, the Java virtual machine must:

- given the type's fully qualified name (char * class_filename), produce a stream of binary data (ClassFile ** cf) that represents the type - OK
- parse the stream of binary data into internal data structures in the method area - OK
- create an instance of class java.lang.Class that represents the type - OK
*/
/*	puts("DEBUG:\tCRIANDO CLASSFILE");*/
	FILE	* class_binary_file;
	
	class_binary_file = fopen(class_filename, "r");
	if(!class_binary_file){
		puts("ClassNotFoundException");
		exit(EXIT_FAILURE);
	}
	else{
		*cf = loadClassFile(class_binary_file);
	}
/*	puts("DEBUG:\tCRIANDO CLASS_DATA");*/
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
	cd->classfile = *cf;
	cd->runtime_constant_pool = (*cf)->constant_pool;
	cd->field_data = (*cf)->fields;
	cd->method_data =(*cf)->methods;
	
/*	puts("DEBUG:\tCRIANDO OBJECT");*/
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
			if((cd->field_data + i)->access_flags & ACC_STATIC){
/*				puts("DEBUG:\tCLASS_VARIABLE");*/
				var->prox = cd->class_variables;
				cd->class_variables = var;
			}
			else{
/*				puts("DEBUG:\tINSTANCE_VARIABLE");*/
				var->prox = obj->instance_variables;
				obj->instance_variables = var;
			}
		}
	}
}// fim da função classLoading

/*==========================================*/
// função classLinking
void	classLinking(ClassFile * cf, JVM * jvm){

	classLinkingVerification(cf, jvm);
	classLinkingPreparation(cf, jvm);
}// fim da função classLinking

/*==========================================*/
// função isFieldDescriptor
bool	isFieldDescriptor(cp_info * cp, u2 index){
	u2	length = cp->u.Utf8.length;
	u1	* bytes = cp->u.Utf8.bytes + index;
	if(index == length){
		return	true;
	}
	switch(*bytes){
		case	BOOLEAN:
		case	BYTE:
		case	CHAR:
		case	DOUBLE:
		case	FLOAT:
		case	INT:
		case	LONG:
		case	SHORT:
			return	isFieldDescriptor(cp, ++index);
			break;
		case	REF_INST:
			;
			char	* string = (char *) bytes;
			string[cp->u.Utf8.length - index] = '\0';
			
			if((length - index) < 3 || !strchr(string, ';')){
				return	false;
			}
			return	isFieldDescriptor(cp, strchr(string, ';') - string + 2);
			break;
		default:
			return	false;
	}	
}
// fim da função isFieldDescriptor

/*==========================================*/
// função isMethodDescriptor
bool	isMethodDescriptor(cp_info * cp, u2 index){
	u2	length = cp->u.Utf8.length;
	u1	* bytes = cp->u.Utf8.bytes + index;
	
	if(index >= (length - 1)){
		return false;
	}
	
	bool	returnDescriptor = false;
	if((*bytes) == ')'){
		returnDescriptor = true;
		index++;
		bytes++;
		if(((*bytes) == '[')){
			index++;
			bytes++;
		}
		if(index == length){
			return false;
		}	
	}
	switch(*bytes){
		case	BOOLEAN:
		case	BYTE:
		case	CHAR:
		case	DOUBLE:
		case	FLOAT:
		case	INT:
		case	LONG:
		case	SHORT:
			if(!returnDescriptor){
				return	isMethodDescriptor(cp, ++index);
			}
			if(index == (length-1)){
				return	true;
			}
			return	false;
			break;
		case	REF_INST:
			;
			char	* string = (char *) bytes;
			string[cp->u.Utf8.length - index + 1] = '\0';
			
			if((length - index) < 3 || !strchr(string, ';')){
				return	false;
			}
			if(!returnDescriptor){
				return	isMethodDescriptor(cp, strchr(string, ';') - string + 2);
			}
			index += strlen(string);
			if(index == (length)){
				return	true;
			}
			return	false;
			break;
		case	'V':
			if(!returnDescriptor){
				return	false;
			}
			if(index == (length-1)){
				return	true;
			}
			return	false;
			break;
		default:
			return	false;
	}	
}	
// fim da função isFieldDescriptor
/*==========================================*/
// função classLinkingVerification
void	classLinkingVerification(ClassFile * cf, JVM * jvm){
/*	A IMPLEMENTAR
Verification: ensuring the correctness of the imported type
https://www.artima.com/insidejvm/ed2/security3.html
Structural Checks on The Classfile
- magic number = 0xCAFEBABE = OK (ClassLoading)
- major/minor version supported = <= java 1.2 = OK (ClassLoading)
- tipo e tamanho dos componentes do classfile (bytes truncados ou extras) = OK (ClassLoading)
Semantic Checks on the Type Data
- verificar se um componente do classfile está bem formado. (exemplo: descritor de um método);
- verificações de classe:
-- toda classe, exceto Object, tem q ter uma superclasse;
-- classe final não é subclasse; método final não é sobrecarregado
- entradas válidas da Constant Pool (índices referem-se ao tipo correto) = OK
- verificação de regras da linguagem java que deveriam ter sido vistas em tempo de compilação.
Bytecode Verifier:
- nao importa o caminho de execução, ao chegar num certo bytecode, a operand_stack tem o mesmo numero de itens e mesmo tipo;
- variavel local nao pode ser acessada antes de conter um valor apropriado.
- atribuição de valores apropriados à fields de classe
- metodos da classe sao sempre invocados com o correto numero e tipo de argumentos.
- verifica que cada opcode é valido, que tem operandos válidos
- cada opcode tem operandos válidos na pilha e o no vetor de variaveis locais
*/	
	// Verify Constant Pool
	cp_info	* cp;
	for(u2	i = 0; i < (cf->constant_pool_count - 1); i++){
		cp = cf->constant_pool + i;
		switch(cp->tag){			
			case	CONSTANT_Class:
				if((cf->constant_pool + cp->u.Class.name_index - 1)->tag != CONSTANT_Utf8){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				break;
			case	CONSTANT_Fieldref:
			case	CONSTANT_Methodref:
			case	CONSTANT_InterfaceMethodref:
				if((cf->constant_pool + cp->u.Ref.class_index - 1)->tag != CONSTANT_Class){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				if((cf->constant_pool + cp->u.Ref.name_and_type_index - 1)->tag != CONSTANT_NameAndType){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				break;			
			case	CONSTANT_String:
				if((cf->constant_pool + cp->u.String.string_index - 1)->tag != CONSTANT_Utf8){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				break;
			case	CONSTANT_Integer:
			case	CONSTANT_Float:
			case	CONSTANT_Long:
			case	CONSTANT_Double:
				break;
			case	CONSTANT_NameAndType:
				if((cf->constant_pool + cp->u.NameAndType.name_index - 1)->tag != CONSTANT_Utf8){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				cp_info	* cp_aux;
				if((cp_aux = cf->constant_pool + cp->u.NameAndType.descriptor_index - 1)->tag != CONSTANT_Utf8){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				if(cp_aux->u.Utf8.length == 0){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				u2	length = cp_aux->u.Utf8.length;
				u1	* bytes = cp_aux->u.Utf8.bytes;
				
				char	* string = (char *) cp_aux->u.Utf8.bytes;
				string[cp_aux->u.Utf8.length] = '\0';
				switch(*bytes){
					case	BOOLEAN:
					case	BYTE:
					case	CHAR:
					case	DOUBLE:
					case	FLOAT:
					case	INT:
					case	LONG:
					case	SHORT:
						if(length != 1){
							puts("VerifyError");
							exit(EXIT_FAILURE);
						}
						break;
					case	REF_INST:
							if(length < 3 || bytes[length-1] != ';'){
								puts("VerifyError");
								exit(EXIT_FAILURE);
							}
						break;
					case	REF_ARRAY:
							if(length < 2){
								puts("VerifyError");
								exit(EXIT_FAILURE);
							}
							u2	index = 0;
							while((*bytes) == REF_ARRAY){
								index++;
								bytes++;
							}
							if(!isFieldDescriptor(cp_aux,index)){
								puts("VerifyError");
								exit(EXIT_FAILURE);	
							}
						break;
					case	'(':
						if(length < 3){
							puts("VerifyError");
							exit(EXIT_FAILURE);
						}
						if(!isMethodDescriptor(cp_aux,1)){
							puts("VerifyError");
							exit(EXIT_FAILURE);	
						}
						break;
					default:
						puts("VerifyError");
						exit(EXIT_FAILURE);
						break;
				}
			case	CONSTANT_Utf8:
				break;	
		}
	}
}// fim da função classLinkingVerification


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


