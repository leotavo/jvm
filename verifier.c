// verifier.c


#include	"verifier.h"
#include	"jvm.h"
#include	<stdlib.h>
#include	<string.h>



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
// função verifyConstantPool
void	verifyConstantPool(ClassFile * cf){	
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
				if(cp->tag != CONSTANT_Fieldref){
					cp_info	* cp_aux;
					cp_aux = cf->constant_pool + cp->u.Ref.name_and_type_index - 1;
					cp_aux = cf->constant_pool + cp_aux->u.NameAndType.descriptor_index - 1;
					if(cp_aux->tag != CONSTANT_Utf8){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					if((cp_aux->u.Utf8).length < 3){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					if(((cp_aux->u.Utf8).bytes)[0] != '('){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
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
}// fim da função verifyConstantPool

/*==========================================*/
// função verifyAccessFlags
void	verifyAccessFlags(ClassFile * cf){
	u2	access_flags;
	
	// Testando flags de classes
	access_flags = cf->access_flags;
	if(access_flags & 0xF9CE){
		puts("VerifyError");
		exit(EXIT_FAILURE);	
	}
	
	// Testando flags de fields
	for(u2 i = 0; i < cf->fields_count; i++){
		access_flags = (cf->fields + i)->access_flags;
		if(access_flags & 0xFF20){
			puts("VerifyError");
			exit(EXIT_FAILURE);
		}
	}
	
	// Testando flags de métodos
	for(u2 i = 0; i < cf->methods_count; i++){
		access_flags = (cf->methods + i)->access_flags;
		if(access_flags & 0xF2C0){
			puts("VerifyError");
			exit(EXIT_FAILURE);
		}
	}
}// fim da função verifyAccessFlag

/*==========================================*/
// função verifyBytecode
void	verifyBytecode(attribute_info * attr, ClassFile * cf){
// verifica atributo CODE
// 4.8 Constraints on Java Virtual Machine Code


} // fim da funcao verifyBytecode

/*==========================================*/
// função verifyClassfile
void	verifyClassfile(ClassFile * cf){

	// checa inconsistências na Constant Pool
	verifyConstantPool(cf);
	
	// checa flags inválidas
	verifyAccessFlags(cf);
	
	cp_info	* cp_aux;
	
	// checa this_class
	cp_aux = cf->constant_pool + cf->this_class - 1;
	if(cp_aux->tag != CONSTANT_Class){
		puts("VerifyError");
		exit(EXIT_FAILURE);
	}
	
	// checa super_class
	if(cf->super_class){
		cp_aux = cf->constant_pool + cf->super_class - 1;
		if(cp_aux->tag != CONSTANT_Class){
			puts("VerifyError");
			exit(EXIT_FAILURE);
		}
	}
	else{
		// Toda classe, exceto Object, deve ter uma superclasse FALTA TESTAR ISSO
		cp_aux = cf->constant_pool + cf->this_class - 1;
		cp_aux = cf->constant_pool + cp_aux->u.Class.name_index - 1;
		char	* string = cp_aux->u.Utf8.bytes;
		string[cp_aux->u.Utf8.length] = '\0';
		if(strcmp(string, "java/lang/Object")){
			puts("VerifyError");
			exit(EXIT_FAILURE);		
		}
	}
	
	// checa interfaces
	for(u2 i = 0; i < cf->interfaces_count; i++){
		cp_aux = cf->constant_pool + (*(cf->interfaces + i)) - 1;
		if(cp_aux->tag != CONSTANT_Class){
			puts("VerifyError");
			exit(EXIT_FAILURE);
		}
	}
	
	// checa fields
	for(u2 i = 0; i < cf->fields_count; i++){
		u2	name_index = (cf->fields + i)->name_index;
		cp_aux = cf->constant_pool + name_index - 1;
		if(cp_aux->tag != CONSTANT_Utf8){
			puts("VerifyError: field name_index");
			exit(EXIT_FAILURE);		
		}
		u2	descriptor_index = (cf->fields + i)->descriptor_index;
		cp_aux = cf->constant_pool + descriptor_index - 1;
		if(cp_aux->tag != CONSTANT_Utf8){
			puts("VerifyError: field descriptor_index");
			exit(EXIT_FAILURE);		
		}
		// checa atributos de fields
		u2	attributes_count = (cf->fields + i)->attributes_count;
		for(u2	j = 0; j < attributes_count; j++){
			cp_aux = cf->constant_pool + ((cf->fields + i)->attributes + j)->attribute_name_index - 1;
			if(cp_aux->tag != CONSTANT_Utf8){
				puts("VerifyError: field attribute_name_index");
				exit(EXIT_FAILURE);
			}
			switch(getAttributeType(((cf->fields + i)->attributes + j), cf)){
				case	CODE:
				case	EXCEPTIONS:
				case	INNER_CLASSES:
				case	LINE_NUMBER_TABLE:
				case	LOCAL_VARIABLE_TABLE:
				case	SOURCE_FILE:
					puts("VerifyError");
					exit(EXIT_FAILURE);
					break;
				case	DEPRECATED:
				case	SYNTHETIC:
					if(((cf->fields + i)->attributes + j)->attribute_length){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					break;
			}
		}		
	}
	
	// checa métodos
	for(u2 i = 0; i < cf->methods_count; i++){
		u2	name_index = (cf->methods + i)->name_index;
		cp_aux = cf->constant_pool + name_index;
		if(cp_aux->tag != CONSTANT_Utf8){
			puts("VerifyError");
			exit(EXIT_FAILURE);		
		}
		
		u2	descriptor_index = (cf->methods + i)->descriptor_index;
		cp_aux = cf->constant_pool + descriptor_index;
		if(cp_aux->tag != CONSTANT_Utf8){
			puts("VerifyError");
			exit(EXIT_FAILURE);		
		}
		
		// checa atributos de métodos
		u2	attributes_count = (cf->methods + i)->attributes_count;
		for(u2	j = 0; j <  attributes_count; j++){
			cp_aux = cf->constant_pool + ((cf->methods + i)->attributes + j)->attribute_name_index - 1;
			if(cp_aux->tag != CONSTANT_Utf8){
				puts("VerifyError");
				exit(EXIT_FAILURE);
			}
			switch(getAttributeType(((cf->methods + i)->attributes + j), cf)){
				case	CODE:
					verifyBytecode(((cf->methods + i)->attributes + j), cf);
					// checa atributos do atributo Code
					u2	code_attributes_count = ((cf->methods + i)->attributes + j)->u.Code.attributes_count;
					for(u2	k = 0; k < code_attributes_count; k++){
						attribute_info	* attr = ((cf->methods + i)->attributes + j)->u.Code.attributes + k;
						cp_aux = cf->constant_pool + attr->attribute_name_index - 1;
						if(cp_aux->tag != CONSTANT_Utf8){
							puts("VerifyError");
							exit(EXIT_FAILURE);
						}
						switch(getAttributeType(attr, cf)){
							case	CODE:
							case	DEPRECATED:
							case	EXCEPTIONS:
							case	INNER_CLASSES:
							case	SOURCE_FILE:
							case	SYNTHETIC:
								puts("VerifyError");
								exit(EXIT_FAILURE);
								break;
							case	LINE_NUMBER_TABLE:
								break;
							case	LOCAL_VARIABLE_TABLE:
								for(u2	l = 0; l < attr->u.LocalVariableTable.local_variable_table_length; l++){
									cp_aux = cf->constant_pool 
									+ (attr->u.LocalVariableTable.local_variable_table)->name_index;
									if(cp_aux->tag != CONSTANT_Utf8){
										puts("VerifyError");
										exit(EXIT_FAILURE);
									}
									cp_aux = cf->constant_pool 
										+ (attr->u.LocalVariableTable.local_variable_table)->descriptor_index;
									if(cp_aux->tag != CONSTANT_Utf8){
										puts("VerifyError");
										exit(EXIT_FAILURE);
									}
									if(!isFieldDescriptor(cp_aux, 0)){
										puts("VerifyError");
										exit(EXIT_FAILURE);
									}									
								}
								break;
						}
					}
					break;
				case	EXCEPTIONS:
					;
					u2	number_of_exceptions = ((cf->methods + i)->attributes + j)->u.Exceptions.number_of_exceptions;
					for(u2	k = 0; k < number_of_exceptions; k++){
						u2	exception_index =
						*(((cf->methods + i)->attributes + j)->u.Exceptions.exception_index_table + k);
						if(!exception_index){
							puts("VerifyError");
							exit(EXIT_FAILURE);
						}
						cp_aux = cf->constant_pool + exception_index - 1;
						if(cp_aux->tag != CONSTANT_Class){
							puts("VerifyError");
							exit(EXIT_FAILURE);
						}						
					}
					break;
				case	INNER_CLASSES:
				case	LINE_NUMBER_TABLE:
				case	LOCAL_VARIABLE_TABLE:
				case	SOURCE_FILE:
					puts("VerifyError");
					exit(EXIT_FAILURE);
					break;
				case	DEPRECATED:
				case	SYNTHETIC:
					if(((cf->methods + i)->attributes + j)->attribute_length){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					break;
			}
		}
	}
	
	// checa atributos de classe
	for(u2 i = 0; i < cf->attributes_count; i++){
		cp_aux = cf->constant_pool + (cf->attributes + i)->attribute_name_index - 1;
		if(cp_aux->tag != CONSTANT_Utf8){
			puts("VerifyError");
			exit(EXIT_FAILURE);
		}
		switch(getAttributeType(cf->attributes + i, cf)){
			case	CODE:
			case	EXCEPTIONS:
			case	LINE_NUMBER_TABLE:
			case	LOCAL_VARIABLE_TABLE:
				puts("VerifyError");
				exit(EXIT_FAILURE);
				break;
			case	INNER_CLASSES:
				;
				u2	number_of_classes = (cf->attributes + i)->u.InnerClasses.number_of_classes;
				for(u2 j = 0; j < number_of_classes; j++){
					classes_type	* class = ((cf->attributes + i)->u.InnerClasses.classes + j);
					if(!(class->inner_class_info_index) || !(class->outer_class_info_index) || !(class->inner_name_index)){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					cp_aux = cf->constant_pool + class->inner_class_info_index - 1;
					if(cp_aux->tag != CONSTANT_Class){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					cp_aux = cf->constant_pool + class->outer_class_info_index - 1;
					if(cp_aux->tag != CONSTANT_Class){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					cp_aux = cf->constant_pool + class->inner_name_index - 1;
					if(cp_aux->tag != CONSTANT_Utf8){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
					u2	access_flags = class->inner_class_access_flags;
					if(access_flags & 0xF9E0){
						puts("VerifyError");
						exit(EXIT_FAILURE);	
					}
				}
				break;
			case	SOURCE_FILE:
				if((cf->attributes + i)->attribute_length != 2){
					puts("VerifyError");
					exit(EXIT_FAILURE);				
				}
				cp_aux = cf->constant_pool + (cf->attributes + i)->u.SourceFile.sourcefile_index - 1;
				if(cp_aux->tag != CONSTANT_Utf8){
					puts("VerifyError");
					exit(EXIT_FAILURE);
				}
				break;
			case	DEPRECATED:
			case	SYNTHETIC:
				if((cf->attributes + i)->attribute_length){
					puts("VerifyError");
					exit(EXIT_FAILURE);				
				}
				break;
		}
	}
} // fim da funcao verifyClassfile


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
			ClassFile	* cf_super = NULL;
			while(cd){
				cf_super = cd->classfile;
				cp_aux = cf_super->constant_pool + cf_super->this_class - 1;
				cp_aux = cf_super->constant_pool + cp_aux->u.Class.name_index - 1;
				char	* class_name = cp_aux->u.Utf8.bytes;
				class_name[cp_aux->u.Utf8.length] = '\0';
				if(!strcmp(super_name, class_name)){
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
// função verifyFinal
void	verifySuperFinal(ClassFile * cf, JVM * jvm){

	// verifica se a classe atual foi herdada uma classe final
	CLASS_DATA	* cd_super;
	if(cd_super = getSuperClass(cf, jvm)){	
		if((cd_super->classfile)->access_flags & ACC_FINAL){
			puts("VerifyError");
			exit(EXIT_FAILURE);
		}
	}
}

/*==========================================*/
// função verifyOverrideMethodFinal
void	verifyOverrideMethodFinal(ClassFile * cf, JVM * jvm){
	// verifica se método final é sobrecarregado
	cp_info	* cp_aux = NULL;
	for(u2	i = 0; i < cf->methods_count; i++){
		cp_aux = (cf->methods + i)->name_index + cf->constant_pool - 1;
		char	* method_name = cp_aux->u.Utf8.bytes;
		method_name[cp_aux->u.Utf8.length] = '\0';
		CLASS_DATA	* cd_super = cd_super = getSuperClass(cf, jvm);
		while(cd_super){
			for(u2	i = 0; i < (cd_super->classfile)->methods_count; i++){
				cp_aux = ((cd_super->classfile)->methods + i)->name_index + (cd_super->classfile)->constant_pool - 1;
				char	* super_method_name = cp_aux->u.Utf8.bytes;
				super_method_name[cp_aux->u.Utf8.length] = '\0';
				if(!strcmp(method_name, super_method_name)){			
					if(((cd_super->classfile)->methods + i)->access_flags == ACC_FINAL){
						puts("VerifyError");
						exit(EXIT_FAILURE);
					}
				}
			}
			cd_super = getSuperClass(cd_super->classfile, jvm);
		}				
	}
}
