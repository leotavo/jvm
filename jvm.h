

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

typedef	u1		OPCODE;
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

// FRAME
typedef	struct frame{
	u4		* local_variables;
	u4		* operand_stack;
	cp_info		* current_class_constant_pool;
	VALUE		return_value;
}FRAME;

// THREAD
typedef	struct thread{
	OPCODE		* program_counter;	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6648
	FRAME		* jvm_stack;		// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6654
}THREAD;



// HEAP_AREA
typedef	struct heap_area{	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#15730
	struct object	* objects;
	VALUE		* arrays;
}HEAP_AREA;

// VARIABLE
typedef	struct variable{
	field_info	* field_reference;
	VALUE		value;	
	struct variable	* prox;
}VARIABLE;

// CLASS_DATA
typedef	struct class_data{
	ClassFile		* classfile;
	struct class_data	* classloader_reference;
	cp_info			* runtime_constant_pool;
	field_info		* field_data;
	method_info		* method_data;
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
void	classLoading(char *, ClassFile **, CLASS_DATA *, JVM *);
void	classLinking(ClassFile *, JVM *);
void	classLinkingVerification(ClassFile *, JVM *);
bool	isFieldDescriptor(cp_info *, u2);
bool	isMethodDescriptor(cp_info *, u2);
void	classLinkingPreparation(ClassFile *, JVM *);
void	classLinkingResolution(ClassFile *, JVM *);
void	classInitialization(ClassFile *, JVM *);
void	classUnloading(ClassFile *, JVM *);
void	jvmExit(JVM *);









#endif

