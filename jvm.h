

// jvm.h

/*==========================================*/
// 	DESCRIÇÃO

// Define os tipos e métodos utilizados pela JVM.

/*==========================================*/
#ifndef		JVM_H
#define		JVM_H
/*==========================================*/
//	INCLUDES
#include	"classreader.h"
#include	<stdio.h>
#include	<stdbool.h>
/*==========================================*/
//	TIPOS

typedef	u1	OPCODE;
typedef char	TYPE;
typedef	int8_t	s1;
typedef int16_t	s2;
typedef	int32_t	s4;
typedef	int64_t	s8;

// Descritores de Fields
#define		BYTE		'B'
#define		CHAR		'C'
#define		DOUBLE		'D'
#define		FLOAT		'F'
#define		INT		'I'
#define		LONG		'J'
#define		REF_INST	'L'
#define		SHORT		'S'
#define		BOOLEAN		'Z'
#define		REF_ARRAY	'['


// OBJECT
typedef	struct object	obj;
typedef	struct array	ar;


// VALUE
typedef	struct value{
	TYPE	type;
	union{
		struct{// BYTE
			s1	byte;
		}Byte;
		
		struct{// SHORT
			s2	short_;
		}Short;
		
		struct{// INTEGER
			s4	integer;
		}Integer;
		
		struct{// LONG
			u4	high_bytes;
			u4	low_bytes;
		}Long;
		
		struct{// FLOAT
			u4	float_;
		}Float;
		
		struct{// DOUBLE
			u4	high_bytes;
			u4	low_bytes;
		}Double;
		
		struct{// CHAR
			u2	char_;
		}Char;
		
		struct{// boolean
			u1	boolean;
		}Boolean;
		
		struct{// INSTANCE REFERENCE
			struct object	* reference;
		}InstanceReference;
		
		struct{// ARRAY REFERENCE
			struct array	* reference;
		}ArrayReference;
		
		struct{// RETURN ADDRESS
			OPCODE	* return_address;
		}ReturnAddress;
	}u;
}VALUE;

typedef	struct operand{
	u4	value;
	TYPE	type;
	struct operand 	* prox;
}OPERAND;

// FRAME
typedef	struct frame{
	u4		* local_variables;
	OPERAND		* operand_stack;
	cp_info		* current_constant_pool;
	VALUE		* return_value;
	struct frame	* prox;
}FRAME;



// THREAD
typedef	struct thread{
	OPCODE		* program_counter;	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6648
	FRAME		* jvm_stack;// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6654
	struct thread	* prox;
}THREAD;



// HEAP_AREA
typedef	struct heap_area{	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#15730
	struct object	* objects;
	VALUE		* arrays;
}HEAP_AREA;

// FIELD_DATA
typedef	struct	field_data{
	cp_info	* field_name; // CONSTANT_Utf8
	cp_info	* field_descriptor; // CONSTANT_Utf8
	TYPE	field_type;
	u2	modifiers;	// access_flags	
	field_info	* info;
	struct variable	* var;
}FIELD_DATA;

// VARIABLE
typedef	struct variable{
	FIELD_DATA	* field_reference;
	VALUE		value;	
	struct variable	* prox;
}VARIABLE;



// METHOD_DATA
typedef	struct	method_data{
	cp_info	* method_name; // CONSTANT_Utf8
	cp_info	* method_descriptor; // CONSTANT_Utf8
	u2	modifiers;	// access_flags	
	struct class_data	* class_data;
	
	// se o método não é abstrato.
	u4	code_length;
	u1	* bytecodes; // instruções da jvm
	u2	stack_size; // tamanho da pilha de operandos
	u2	locals_size; // tamanho do vetor de variaveis locais
	u2	exception_table_length;
	exception_table_type	* exception_table;
	method_info	* info; 
}METHOD_DATA;

// CLASS_DATA
typedef	struct class_data{
	cp_info			* class_name; // CONSTANT_Utf8
	ClassFile		* classfile;
	u2			modifiers;
	struct class_data	* classloader_reference;
	cp_info			* runtime_constant_pool;
	FIELD_DATA		* field_data;
	METHOD_DATA		* method_data;
	VARIABLE		* class_variables;
	struct object		* instance_class;
	struct class_data	* prox;
}CLASS_DATA;

typedef	struct object{
	CLASS_DATA	* class_data_reference;
	VARIABLE	* instance_variables;
	struct object	* prox;
}OBJECT;

typedef	struct array{
	CLASS_DATA	* class_data_reference;
	u4		array_length;
	VALUE		* entry;
}ARRAY;

// JVM
typedef	struct jvm{
	THREAD		* threads;
	HEAP_AREA	* heap;
	CLASS_DATA	* method_area;	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6656
}JVM;
/*==========================================*/


void	jvmStart(char *, int, char **);
void	classLoading(char *, CLASS_DATA **, CLASS_DATA *, JVM *);
void	classLinking(CLASS_DATA *, JVM *);
void	classLinkingVerification(CLASS_DATA *, JVM *);
void	classLinkingPreparation(CLASS_DATA *, JVM *);
void	classLinkingResolution(ClassFile *, JVM *);
void	classInitialization(CLASS_DATA *, JVM *, THREAD *);
void	executeMethod(char *, CLASS_DATA *, JVM *, THREAD *, void *);
void	classUnloading(CLASS_DATA *, JVM *);
attribute_info	* getCodeAttribute(METHOD_DATA *, CLASS_DATA *);
char	*	getClassName(CLASS_DATA *);
CLASS_DATA	* getSuperClass(ClassFile *, JVM *);
CLASS_DATA	* getClass(cp_info *, JVM *);
void	jvmExit(JVM *);
void	PrintConstantUtf8(cp_info *, FILE *);
VARIABLE	* getClassVariable(cp_info *, CLASS_DATA *);
METHOD_DATA	* getMethod(char *, CLASS_DATA *);
bool		isSuperClass(CLASS_DATA *, CLASS_DATA *);

void	pushOperand(u4, FRAME *);
u4	popOperand(FRAME *);








#endif

