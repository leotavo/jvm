// info.h

/*======================================================*/
/* 	DESCRIÇÃO

- Definição dos tipos e estruturas que contém informações sobre constantes, atributos, fields e métodos.
*/
/*======================================================*/

#ifndef	INFO_H
#define	INFO_H

#include	<inttypes.h>
typedef	uint8_t		u1;	// 1 byte
typedef	uint16_t	u2;	// 2 bytes
typedef	uint32_t	u4;	// 4 bytes
/*======================================================*/
//	INFO

// cp_info. itens do pool de constantes.
typedef struct cp_info{
	u1	tag;
	union{
		struct{
			u2	name_index;
		}Class;
		
		struct{
			u2	class_index;
			u2	name_and_type_index;
		}Ref;
		
		struct{
			u2	name_index;
			u2	descriptor_index;
		}NameAndType;
		
		struct{
			u2	length;	
			u1*	bytes;
		}Utf8;
				
		struct{
			u2	string_index;
		}String;
		
		struct{
			u4	bytes;
		}Integer_Float;
				
		struct{
			u4 	high_bytes;
			u4 	low_bytes;
		}Long_Double;
	}u;
}cp_info;

// definição de tipos para attribute_info
typedef struct exception_table_type{
	u2	start_pc;
	u2	end_pc;
	u2	handler_pc;
	u2	catch_type; 
}exception_table_type;

typedef struct classes_type{
	u2	inner_class_info_index;
	u2	outer_class_info_index;
	u2	inner_name_index;
	u2	inner_class_access_flags;
}classes_type;

typedef struct line_number_table_type{
	u2	start_pc;
	u2	line_number; 
}line_number_table_type;

typedef struct local_variable_table_type{	
	u2	start_pc;
	u2	length;
	u2	name_index;
	u2	descriptor_index;
	u2	index;
}local_variable_table_type;

// attribute_info
typedef struct attribute_info{
	u2	attribute_name_index;		// aponta para um índice na constant_pool contendo uma Constant_Utf8 com nome do atributo
	u4	attribute_length;
	union{
		struct{
			u2	constantvalue_index;
		}ConstantValue;
		
		struct{
			u2		max_stack;
			u2 		max_locals;
			u4		code_length;
			u1*		code;
			u2		exception_table_length;
			exception_table_type *	exception_table;
			u2		attributes_count;
			struct attribute_info*	attributes;
		}Code;
		
		struct{
		
		}Deprecated;
		
		struct{
			u2		number_of_exceptions;
			u2*		exception_index_table;
		}Exceptions;
				
		struct{
			u2		number_of_classes;
			classes_type *	classes;
		}InnerClasses;
		
		struct{
			u2		line_number_table_length;
			line_number_table_type *	line_number_table;
		}LineNumberTable;
				
		struct{
			u2		local_variable_table_length;
			local_variable_table_type *	local_variable_table;
		}LocalVariableTable;
		
		struct{
		
		}Synthetic;
		
		struct{
			u2		sourcefile_index;
		}SourceFile;
	}u;
}attribute_info;

typedef	struct field_info{
	u2		access_flags;			/* máscara de bits que especifica permissões de acesso
							e propriedades do field */
	u2		name_index;			// índice para o constant_pool contendo o nome do field
	u2		descriptor_index;		// índice para o constant_pool contendo um descritor de field válido
	u2		attributes_count;		// número de atributos do field
	attribute_info*	attributes;			// array contendo informações sobre os atributos do field
}field_info;

typedef struct method_info{
	u2		access_flags;			/* máscara de bits que especifica permissões de acesso
							e propriedades do método */
	u2		name_index;			/* índice para o constant_pool contendo o nome simples
							do método, ou nome especial <init> */
	u2		descriptor_index;		// índice para o constant_pool contendo um descritor de método válido
	u2		attributes_count;		// número de atributos do metodo
	attribute_info*	attributes;
}method_info;


#endif
