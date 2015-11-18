

// jvm.h

/*==========================================*/
// 	DESCRIÇÃO

// Define os tipos e métodos utilizados pela JVM.

/*==========================================*/
#ifndef		JVM_H
#define		JVM_H
/*==========================================*/
//	INCLUDES
#include	"classloader.h"
#include	<stdio.h>
/*==========================================*/
//	TIPOS


typedef	u1	OPCODE;
typedef char	TYPE;
typedef	int8_t	s1;
typedef int16_t	s2;
typedef	int32_t	s4;
typedef	int64_t	s8;

#define		BYTE		B
#define		CHAR		C
#define		DOUBLE		D
#define		FLOAT		F
#define		INT			I
#define		LONG		J
#define		REF_INST	L
#define		SHORT		S
#define		BOOLEAN		Z
#define		REF_ARRAY	[



// FRAME
typedef	struct frame{
	u4			* local_variables;
	u4			* operand_stack;
	cp_info		* current_class_constant_pool;
	VALUE		return_value;
}FRAME;

// THREAD
typedef	struct thread{
	OPCODE		* program_counter;	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6648
	FRAME		* jvm_stack;		// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6654
}THREAD;

// OBJECT
typedef	struct object{
	/* data */
}OBJECT;

typedef	struct value{
	TYPE	type;
	union{
		struct{// BYTE
			s1	byte;
		}B;
		
		struct{// SHORT
			s2	short_;
		}S;
		
		struct{// INTEGER
			s4	integer;
		}I;
		
		struct{// LONG
			u4	long_high_bytes;
			u4	long_low_bytes;
		}J;
		
		struct{// FLOAT
			u4	float_;
		}F;
		
		struct{// DOUBLE
			u4	double_high_bytes;
			u4	double_low_bytes;
		}D;
		
		struct{// CHAR
			u2	char_;			
		}C;
		
		struct{// boolean
			u1	boolean;			
		}C;
		
		struct{// REFERENCE
			OBJECT	* reference;
		}L;
		
		struct{// RETURN ADDRESS
			OPCODE	* return_address;
		}
	}u;
}VALUE;

// HEAP_AREA
typedef	struct heap_area{	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#15730
	OBJECT		* objects;
	VALUE		* arrays;
}HEAP_AREA;

// CLASS_DATA
typedef	struct class_data{
	ClassFile	* cf;
	
}CLASS_DATA;

// JVM
typedef	struct jvm{
	THREAD		* threads;
	HEAP_AREA	* heap;
	CLASS_DATA	* method_area;	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6656
}JVM;
/*==========================================*/


void	jvmStart(FILE *, int, char **);
void	classLoading(FILE *, ClassFile *, JVM *);
void	classLinking(ClassFile *, JVM *);
void	classLinkingVerification(ClassFile *, JVM *);
void	classLinkingPreparation(ClassFile *, JVM *);
void	classLinkingResolution(ClassFile *, JVM *);
void	classInitialization(ClassFile *, JVM *);
void	classUnloading(ClassFile *, JVM *);
void	jvmExit(JVM *);









#endif

