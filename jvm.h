

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


typedef	u1	INSTRUCTION;

// FRAME
typedef	struct frame{
	/* data */
}FRAME;

// THREAD
typedef	struct thread{
	INSTRUCTION	* program_counter;	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6648
	FRAME		* jvm_stack;		// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6654
}THREAD;

// CLASS_INSTANCE
typedef	struct class_instance{
	/* data */
}CLASS_INSTANCE;

// HEAP_AREA
typedef	struct heap_area{	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#15730
	CLASS_INSTANCE	* objects;
	ARRAYS		* arrays;
}HEAP_AREA;

// CLASS_DATA
typedef	struct class_data{
	ClassFile	* cf;
	
}CLASS_DATA;

// JVM
typedef	struct jvm{
	THREADS		* threads;
	HEAP_AREA	* heap;
	CLASS_DATA	* method_area;	// https://docs.oracle.com/javase/specs/jvms/se6/html/Overview.doc.html#6656
}JVM;
/*==========================================*/


<<<<<<< HEAD
void	jvmStart(FILE *, int, char **);
void	classLoading(FILE *, ClassFile **);
void	classLinking(ClassFile **);
void	classLinkingVerification(ClassFile **);
void	classLinkingPreparation(ClassFile **);
void	classLinkingResolution(ClassFile **);
void	classInitialization(ClassFile **);
void	jvmExit();
=======

void	jvmStart(FILE *, int, char **);
void	jvmLoading(FILE *);
>>>>>>> 97f251dd3f4937832a6d3f4d1f34f33cd7f3d939









#endif

