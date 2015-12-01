//	verifier.h

#ifndef		VERIFIER_H
#define		VERIFIER_H


#include	<stdbool.h>
#include	"info.h"
#include	"classreader.h"
#include	"jvm.h"

bool	isFieldDescriptor(cp_info *, u2);
bool	isMethodDescriptor(cp_info *, u2);
void	verifyConstantPool(ClassFile *);
void	verifyAccessFlags(ClassFile *);
void	verifyBytecode(attribute_info *, ClassFile *);
void	verifyClassfile(ClassFile *);
void	verifySuperFinal(ClassFile *, JVM *);
void	verifyOverrideMethodFinal(ClassFile *, JVM *);
#endif
