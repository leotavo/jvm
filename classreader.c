
// classreader.c

/*======================================================*/
/* 	DESCRIÇÃO

- Implementação dos métodos do classloader da JVM.
*/
/*======================================================*/
//	INCLUDES

#include	"classreader.h"
#include	<stdlib.h>
#include	<inttypes.h>
#include	<string.h>

/*======================================================*/
//	MÉTODOS AUXILIARES
// retorna 1 byte lido da stream fileInput
u1		u1Read(FILE * fi){
	u1	toReturn = getc(fi);
	if(toReturn == EOF){
		puts("ClassFormatError");
		exit(EXIT_FAILURE);
	}
	return	toReturn;
}

// retorna 2 bytes lidos da stream fileInput
u2		u2Read(FILE * fi){
	u2	toReturn = getc(fi);
	if(toReturn == EOF){
		puts("ClassFormatError");
		exit(EXIT_FAILURE);
	}
	u1	toReturn2 = getc(fi);
	if(toReturn2 == EOF){
		puts("ClassFormatError");
		exit(EXIT_FAILURE);
	}
	toReturn = (toReturn << 8) | toReturn2;
	return	toReturn;
}

// retorna 4 bytes lidos da stream fileInput
u4		u4Read(FILE * fi){
	u4	toReturn = getc(fi);
	if(toReturn == EOF){
		puts("ClassFormatError");
		exit(EXIT_FAILURE);
	}
	u1	toReturn2 = getc(fi);
	if(toReturn2 == EOF){
		puts("ClassFormatError");
		exit(EXIT_FAILURE);
	}
	toReturn = (toReturn << 8) | toReturn2;
	
	toReturn2 = getc(fi);
	if(toReturn2 == EOF){
		puts("ClassFormatError");
		exit(EXIT_FAILURE);
	}
	toReturn =  (toReturn << 8) | toReturn2;
	
	toReturn2 = getc(fi);
	if(toReturn2 == EOF){
		puts("ClassFormatError");
		exit(EXIT_FAILURE);
	}
	toReturn =  (toReturn << 8) | toReturn2;
	return	toReturn;
}

// retorna o tipo de atributo.
ATTRIBUTE_TYPE	getAttributeType(attribute_info * attr, ClassFile * cf){
	u2		name_index = attr->attribute_name_index;
	cp_info *	cp = cf->constant_pool + name_index - 1;
	
	// CONSTANT_Utf8
	u2		length = cp->u.Utf8.length;
	u1*		bytes = cp->u.Utf8.bytes;
	
	if(length != 0){		
		switch(bytes[0]){
			case	'C':
				if(length == strlen("Code")){
					if(bytes[1] == 'o' && bytes[2] == 'd' && bytes[3] == 'e'){
						return	CODE;
					}
				}
				else if(length == strlen("ConstantValue")){
					if(bytes[1] == 'o' && bytes[2] == 'n' && bytes[3] == 's' &&
					bytes[4] == 't' && bytes[5] == 'a' && bytes[6] == 'n' &&
					bytes[7] == 't' && bytes[8] == 'V' && bytes[9] == 'a' &&
					bytes[10] == 'l' && bytes[11] == 'u' && bytes[12] == 'e'){
						return	CONSTANT_VALUE;
					}
				}
				break;
			case	'D':
				if(length == strlen("Deprecated"))
					if(bytes[1] == 'e' && bytes[2] == 'p' && bytes[3] == 'r' &&
					bytes[4] == 'e' && bytes[5] == 'c' && bytes[6] == 'a' &&
					bytes[7] == 't' && bytes[8] == 'e' && bytes[9] == 'd'){
						return	DEPRECATED;
					}
				break;
			case	'E':
				if(length == strlen("Exceptions"))
					if(bytes[1] == 'x' && bytes[2] == 'c' && bytes[3] == 'e' &&
					bytes[4] == 'p' && bytes[5] == 't' && bytes[6] == 'i' &&
					bytes[7] == 'o' && bytes[8] == 'n' && bytes[9] == 's'){
						return	EXCEPTIONS;
					}
				break;
			case	'I':
				if(length == strlen("InnerClasses"))
					if(bytes[1] == 'n' && bytes[2] == 'n' && bytes[3] == 'e' &&
					bytes[4] == 'r' && bytes[5] == 'C' && bytes[6] == 'l' &&
					bytes[7] == 'a' && bytes[8] == 's' && bytes[9] == 's' &&
					bytes[10] == 'e' && bytes[11] == 's'){
						return	INNER_CLASSES;
					}
				break;
			case	'L':
				if(length == strlen("LineNumberTable")){
					if(bytes[1] == 'i' && bytes[2] == 'n' && bytes[3] == 'e' &&
					bytes[4] == 'N' && bytes[5] == 'u' && bytes[6] == 'm' &&
					bytes[7] == 'b' && bytes[8] == 'e' && bytes[9] == 'r' &&
					bytes[10] == 'T' && bytes[11] == 'a' && bytes[12] == 'b' &&
					bytes[13] == 'l' && bytes[14] == 'e'){
						return	LINE_NUMBER_TABLE;
					}
				}
				else if(length == strlen("LocalVariableTable"))
					if(bytes[1] == 'o' && bytes[2] == 'c' && bytes[3] == 'a' &&
					bytes[4] == 'l' && bytes[5] == 'V' && bytes[6] == 'a' &&
					bytes[7] == 'r' && bytes[8] == 'i' && bytes[9] == 'a' &&
					bytes[10] == 'b' && bytes[11] == 'l' && bytes[12] == 'e' &&
					bytes[13] == 'T' && bytes[14] == 'a' && bytes[15] == 'b' &&
					bytes[16] == 'l' && bytes[17] == 'e'){
						return	LOCAL_VARIABLE_TABLE;
					}
				break;
			case	'S':
				if(length == strlen("Synthetic")){
					if(bytes[1] == 'y' && bytes[2] == 'n' && bytes[3] == 't' &&
					bytes[4] == 'h' && bytes[5] == 'e' && bytes[6] == 't' &&
					bytes[7] == 'i' && bytes[8] == 'c'){
						return	SYNTHETIC;
					}				
				}
				else if(length == strlen("SourceFile"))
					if(bytes[1] == 'o' && bytes[2] == 'u' && bytes[3] == 'r' &&
					bytes[4] == 'c' && bytes[5] == 'e' && bytes[6] == 'F' &&
					bytes[7] == 'i' && bytes[8] == 'l' && bytes[9] == 'e'){
						return	SOURCE_FILE;
					}
				break;
			default:
				return	UNKNOWN;
		}
	}
	return	UNKNOWN;	
}
/*======================================================*/
// MÉTODOS DE MANIPULAÇÃO DE CLASSFILE.

// Faz a leitura do arquivo .class, e retorna um ponteiro para estrutura ClassFile com os campos preenchidos;
ClassFile *	loadClassFile(FILE * fi){
	ClassFile *	cf = newClassFile(); // alocando espaço para estrutura do tipo ClassFile.
	setMagic(cf, fi);		// le u4 (4 bytes) do arquivo e atualiza o campo magic do ClassFile.
	setVersion(cf, fi);		// le dois u2 (2 bytes) do arquivo e atualiza os campos minor_version e major_version do ClassFile
	setConstantPool(cf, fi);	// le e armazena o pool de constantes.
	setAccessFlags(cf, fi);		// le u2 (2 bytes) do arquivo e atualiza o campo access_flags do ClassFile
	setThisClass(cf, fi);
	setSuperClass(cf, fi);
	setInterfaces(cf, fi);
	setFields(cf, fi);
	setMethods(cf, fi);
	setAttributes(NULL, NULL, NULL, cf, fi);
	if(getc(fi) != EOF){
		puts("ClassFormatError");
	}
	return	cf;
}

// retorna ponteiro para estrutura ClassFile alocada.
ClassFile*	newClassFile(){
	ClassFile *	cf = (ClassFile *) malloc(sizeof(ClassFile));
	return	cf;
}

// le e armazena o valor do campo magic da ClassFile
void		setMagic(ClassFile * cf, FILE * fi){
	cf->magic = u4Read(fi);	
	if(cf->magic != 0xCAFEBABE){
		puts("ClassFormatError");
		free(cf);
		exit(EXIT_FAILURE);
	}
}

// le e armazena os campos minor_version e major_version da ClassFile.
void		setVersion(ClassFile * cf, FILE * fi){
	cf->minor_version = u2Read(fi);
	cf->major_version = u2Read(fi);
	if((cf->major_version > 46) || (cf->major_version < 45) || (cf->major_version == 46 && cf->minor_version != 0)){
		puts("UnsupportedClassVersionError");
		exit(EXIT_FAILURE);
	}
}

// le e armazena o pool de constantes do ClassFile
void		setConstantPool(ClassFile * cf, FILE * fi){
	cf->constant_pool_count = u2Read(fi);
	if(cf->constant_pool_count == 0){
		puts("VerifyError");
		exit(EXIT_FAILURE);
	}
	cf->constant_pool = (cp_info *) malloc((cf->constant_pool_count -1)*sizeof(cp_info));
	
	cp_info * cp;
	for(cp = cf->constant_pool; cp < (cf->constant_pool + cf->constant_pool_count - 1); cp++){
		cp->tag = u1Read(fi);
		
		switch(cp->tag){			
			case	CONSTANT_Class:
				cp->u.Class.name_index = u2Read(fi);
				break;
			case	CONSTANT_Fieldref:
			case	CONSTANT_Methodref:
			case	CONSTANT_InterfaceMethodref:
				cp->u.Ref.class_index = u2Read(fi);
				cp->u.Ref.name_and_type_index = u2Read(fi);
				break;			
			case	CONSTANT_String:
				cp->u.String.string_index = u2Read(fi);
				break;
			case	CONSTANT_Integer:
			case	CONSTANT_Float:
				cp->u.Integer_Float.bytes = u4Read(fi);
				break;
			case	CONSTANT_Long:
			case	CONSTANT_Double:
				cp->u.Long_Double.high_bytes = u4Read(fi);
				cp->u.Long_Double.low_bytes = u4Read(fi);
				cp++;	// Long e Double ocupam dois índices da constant_pool
				break;
			case	CONSTANT_NameAndType:
				cp->u.NameAndType.name_index = u2Read(fi);
				cp->u.NameAndType.descriptor_index = u2Read(fi);
				break;
			case	CONSTANT_Utf8:
				cp->u.Utf8.length = u2Read(fi);
				cp->u.Utf8.bytes = (u1 *) malloc((cp->u.Utf8.length) * sizeof(u1));
				for(u2 i = 0; i < cp->u.Utf8.length; i++){
					cp->u.Utf8.bytes[i] = u1Read(fi);
				}
				break;
			default:
				puts("VerifyError");
				exit(EXIT_FAILURE);
		}	
	}
}

// le e armazena o campo access_flags do ClassFile
void		setAccessFlags(ClassFile * cf, FILE * fi){
	cf->access_flags = u2Read(fi);
}

// le e armazena o campo this_class do ClassFile
void		setThisClass(ClassFile * cf, FILE * fi){
	cf->this_class = u2Read(fi);
}

// le e armazena o campo super_class do ClassFile
void		setSuperClass(ClassFile * cf, FILE * fi){
	cf->super_class = u2Read(fi);
}

// le e armazena as interfaces do ClassFile
void		setInterfaces(ClassFile * cf, FILE * fi){
	cf->interfaces_count = u2Read(fi);
	
	cf->interfaces = (u2 *) malloc((cf->interfaces_count)*sizeof(u2));
	for(u2 * in = cf->interfaces; in < (cf->interfaces + cf->interfaces_count); in++){
		*in = u2Read(fi);
	}
}

// le e armazena os fields do ClassFile
void		setFields(ClassFile * cf, FILE * fi){
	cf->fields_count = u2Read(fi);
	
	cf->fields = (field_info *) malloc((cf->fields_count)*sizeof(field_info));
	for(field_info * fd_in = cf->fields; fd_in < (cf->fields + cf->fields_count); fd_in++){
		fd_in->access_flags = u2Read(fi);
		fd_in->name_index = u2Read(fi);
		fd_in->descriptor_index = u2Read(fi);
		setAttributes(fd_in, NULL, NULL, cf, fi);
	}
}

// le e armazena os métodos do ClassFile
void		setMethods(ClassFile * cf, FILE * fi){
	cf->methods_count = u2Read(fi);
	cf->methods = (method_info *) malloc((cf->methods_count)*sizeof(method_info));
	for(method_info * mt_in = cf->methods; mt_in < (cf->methods + cf->methods_count); mt_in++){
		mt_in->access_flags = u2Read(fi);
		mt_in->name_index = u2Read(fi);
		mt_in->descriptor_index = u2Read(fi);
		setAttributes(NULL, mt_in, NULL, cf, fi);
	}
}

// le e armazena os atributos do ClassFile
void		setAttributes(field_info * fd_in, method_info * mt_in, attribute_info * attr_in, ClassFile * cf,FILE * fi){
	attribute_info *	attributes;
	u2			attributes_count;
	if(fd_in != NULL){
		fd_in->attributes_count = u2Read(fi);
		fd_in->attributes = (attribute_info *) malloc(fd_in->attributes_count * sizeof(attribute_info));
		
		attributes_count = fd_in->attributes_count;
		attributes = fd_in->attributes;
	}	
	else if(mt_in != NULL){
		mt_in->attributes_count = u2Read(fi);
		mt_in->attributes = (attribute_info *) malloc(mt_in->attributes_count * sizeof(attribute_info));
		
		attributes_count = mt_in->attributes_count;
		attributes = mt_in->attributes;		
	}
	else if(attr_in != NULL){
		attr_in->u.Code.attributes_count = u2Read(fi);
		attr_in->u.Code.attributes = (attribute_info *) malloc(attr_in->u.Code.attributes_count * sizeof(attribute_info));
		
		attributes_count = attr_in->u.Code.attributes_count;
		attributes = attr_in->u.Code.attributes;
	}
	else if(cf != NULL){
		cf->attributes_count = u2Read(fi);
		cf->attributes = (attribute_info *) malloc(cf->attributes_count * sizeof(attribute_info));
		
		attributes_count = cf->attributes_count;
		attributes = cf->attributes;
	}	
	else{
		puts("Erro ao setar atributos");
		exit(EXIT_FAILURE);
	}
	
	for(attribute_info * attr = attributes; attr < (attributes + attributes_count); attr++){
		attr->attribute_name_index = u2Read(fi);
		attr->attribute_length = u4Read(fi);
		
		switch(getAttributeType(attr, cf)){
			case	CONSTANT_VALUE:
				attr->u.ConstantValue.constantvalue_index = u2Read(fi);
				break;
			case	CODE:
				attr->u.Code.max_stack = u2Read(fi);
				attr->u.Code.max_locals = u2Read(fi);
				attr->u.Code.code_length = u4Read(fi);
				attr->u.Code.code = (u1 *) malloc(attr->u.Code.code_length * sizeof(u1));
				for(u1 * cd = attr->u.Code.code; cd < (attr->u.Code.code + attr->u.Code.code_length); cd++)
					*cd = u1Read(fi);
				
				attr->u.Code.exception_table_length = u2Read(fi);				
				attr->u.Code.exception_table =
				(exception_table_type *) malloc(attr->u.Code.exception_table_length * sizeof(exception_table_type));
				
				for(exception_table_type * ex_tb = attr->u.Code.exception_table; 
				ex_tb < (attr->u.Code.exception_table + attr->u.Code.exception_table_length); ex_tb++){
					ex_tb->start_pc = u2Read(fi);
					ex_tb->end_pc = u2Read(fi);
					ex_tb->handler_pc = u2Read(fi);	
					ex_tb->catch_type = u2Read(fi);					
				}
				setAttributes(NULL, NULL, attr, cf, fi);
				break;
			case	DEPRECATED:
				break;
			case	EXCEPTIONS:
				attr->u.Exceptions.number_of_exceptions = u2Read(fi);
				attr->u.Exceptions.exception_index_table = (u2 *) malloc(attr->u.Exceptions.number_of_exceptions * sizeof(u2));
				for(u2 * ex_in_tb = attr->u.Exceptions.exception_index_table; 
				ex_in_tb < (attr->u.Exceptions.exception_index_table + attr->u.Exceptions.number_of_exceptions); ex_in_tb++)
					* ex_in_tb = u2Read(fi);					
				break;
			case	INNER_CLASSES:
				attr->u.InnerClasses.number_of_classes = u2Read(fi);
				attr->u.InnerClasses.classes =
				(classes_type *) malloc(attr->u.InnerClasses.number_of_classes * sizeof(classes_type));
				for(classes_type * cl = attr->u.InnerClasses.classes; 
				cl < (attr->u.InnerClasses.classes + attr->u.InnerClasses.number_of_classes); cl++){
					cl->inner_class_info_index = u2Read(fi);
					cl->outer_class_info_index = u2Read(fi);
					cl->inner_name_index = u2Read(fi);
					cl->inner_class_access_flags = u2Read(fi);					
				}
				break;
			case	LINE_NUMBER_TABLE:
				attr->u.LineNumberTable.line_number_table_length = u2Read(fi);
				attr->u.LineNumberTable.line_number_table = (line_number_table_type *)
				malloc(attr->u.LineNumberTable.line_number_table_length * sizeof(line_number_table_type));
				
				for(line_number_table_type * ln_tb = attr->u.LineNumberTable.line_number_table; 
				ln_tb < (attr->u.LineNumberTable.line_number_table + attr->u.LineNumberTable.line_number_table_length); ln_tb++){
					ln_tb->start_pc = u2Read(fi);
					ln_tb->line_number = u2Read(fi);
				}
				break;
			case	LOCAL_VARIABLE_TABLE:
				attr->u.LocalVariableTable.local_variable_table_length = u2Read(fi);
				attr->u.LocalVariableTable.local_variable_table = (local_variable_table_type *)
				malloc(attr->u.LocalVariableTable.local_variable_table_length * sizeof(local_variable_table_type));
				
				for(local_variable_table_type * lv_tb = attr->u.LocalVariableTable.local_variable_table; 
				lv_tb < (attr->u.LocalVariableTable.local_variable_table +
				attr->u.LocalVariableTable.local_variable_table_length); lv_tb++){
					lv_tb->start_pc = u2Read(fi);
					lv_tb->length = u2Read(fi);
					lv_tb->name_index = u2Read(fi);
					lv_tb->descriptor_index = u2Read(fi);
					lv_tb->index = u2Read(fi);
				}
				break;
			case	SYNTHETIC:
				break;
			case	SOURCE_FILE:
				attr->u.SourceFile.sourcefile_index = u2Read(fi);
				break;
			case	UNKNOWN:
				// IGNORANDO ATRIBUTOS DESCONHECIDOS
				break;							
		}
	}
}



// libera memória alocada da estrutura ClassFile
void		freeClassFile(ClassFile * cf){

	// Constant_Pool
	for(cp_info * cp = cf->constant_pool; cp < (cf->constant_pool + cf->constant_pool_count - 1); cp++){
		switch(cp->tag){
			case	CONSTANT_Utf8:
				free(cp->u.Utf8.bytes);
				break;
		}
	}
	free(cf->constant_pool);
	
	// Interfaces
	free(cf->interfaces);
	
	// Fields
	for(field_info * fd_in = cf->fields; fd_in < (cf->fields + cf->fields_count); fd_in++){
		// CORRIGIR ESTE TRECHO
/*		for(attribute_info * attr = fd_in->attributes; attr < (fd_in->attributes + fd_in->attributes_count); attr++){*/
/*			free(attr->info);*/
/*		}*/
		free(fd_in->attributes);	
	}
	free(cf->fields);
	
	// Methods
	for(method_info * mt_in = cf->methods; mt_in < (cf->methods + cf->methods_count); mt_in++){
		// CORRIGIR ESTE TRECHO
/*		for(attribute_info * attr = mt_in->attributes; attr < (mt_in->attributes + mt_in->attributes_count); attr++){*/
/*			free(attr->info);*/
/*		}*/
		free(mt_in->attributes);	
	}
	free(cf->methods);
	
	// Attributes
	// CORRIGIR ESTE TRECHO
/*	for(attribute_info * attr = cf->attributes; attr < (cf->attributes + cf->attributes_count); attr++){*/
/*		free(attr->info);*/
/*	}	*/
	
	free(cf);
}
/*======================================================*/
