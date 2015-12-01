	// opcode.h

/*======================================================*/
/* 	DESCRIÇÃO

- Definições das instruções (opcodes) da JVM
*/
/*======================================================*/


/*======================================================*/
	//	OPCODES

// Não faz nada.
#define		nop		0x00
	
	
//	Load and Store Instructions

// Tconst 
// Carregam constantes na pilha de operandos.
#define		aconst_null	0x01
#define		iconst_m1	0x02
#define		iconst_0	0x03
#define		iconst_1	0x04
#define		iconst_2	0x05
#define		iconst_3	0x06
#define		iconst_4	0x07
#define		iconst_5	0x08
#define		lconst_0	0x09
#define		lconst_1	0x0A
#define		fconst_0	0x0B
#define		fconst_1	0x0C
#define		fconst_2	0x0D
#define		dconst_0	0x0E
#define		dconst_1	0x0F

// Tipush
// carregam inteiros com sinal de 8 ou 16 bits na pilha
#define		bipush		0x10
#define		sipush		0x11


// ldc*
// carregam constantes single (int, float, literal string) ou double word (long, double) na pilha
// tem como argumento um indice de 8 ou 16 bits da constant pool
#define		ldc		0x12
#define		ldc_w		0x13
#define		ldc2_w		0x14

// Tload
// carregam valores do vetor de variaveis locais na pilha, ou de arrays referenciados no vetor.
// têm como argumento indices para o vetor, ou índices implícitos.
#define		iload		0x15
#define		lload		0x16
#define		fload		0x17
#define		dload		0x18
#define		aload		0x19
#define		iload_0		0x1A
#define		iload_1		0x1B
#define		iload_2		0x1C
#define		iload_3		0x1D
#define		lload_0		0x1E
#define		lload_1		0x1F
#define		lload_2		0x20
#define		lload_3		0x21
#define		fload_0		0x22
#define		fload_1		0x23
#define		fload_2		0x24
#define		fload_3		0x25
#define		dload_0		0x26
#define		dload_1		0x27
#define		dload_2		0x28
#define		dload_3		0x29
#define		aload_0		0x2A
#define		aload_1		0x2B
#define		aload_2		0x2C
#define		aload_3		0x2D
#define		iaload		0x2E
#define		laload		0x2F
#define		faload		0x30
#define		daload		0x31
#define		aaload		0x32
#define		baload		0x33
#define		caload		0x34
#define		saload		0x35

// Tstore
// grava valores do topo da pilha no vetor de variaveis locais ou em arrays referenciados no vetor.
#define		istore		0x36
#define		lstore		0x37
#define		fstore		0x38
#define		dstore		0x39
#define		astore		0x3A
#define		istore_0	0x3B
#define		istore_1	0x3C
#define		istore_2	0x3D
#define		istore_3	0x3E
#define		lstore_0	0x3F
#define		lstore_1	0x40
#define		lstore_2	0x41	
#define		lstore_3	0x42
#define		fstore_0	0x43
#define		fstore_1	0x44
#define		fstore_2	0x45
#define		fstore_3	0x46
#define		dstore_0	0x47
#define		dstore_1	0x48
#define		dstore_2	0x49
#define		dstore_3	0x4A
#define		astore_0	0x4B
#define		astore_1	0x4C
#define		astore_2	0x4D
#define		astore_3	0x4E
#define		iastore		0x4F
#define		lastore		0x50
#define		fastore		0x51
#define		dastore		0x52
#define		aastore		0x53
#define		bastore		0x54
#define		castore		0x55
#define		sastore		0x56

//	Operand Stack Management Instructions
// instruções de manipulação da pilha (descarte, duplicação, troca de valores)
#define		pop		0x57
#define		pop2		0x58
#define		dup		0x59
#define		dup_x1		0x5A
#define		dup_x2		0x5B
#define		dup2		0x5C		
#define		dup2_x1		0x5D
#define		dup2_x2		0x5E
#define		swap		0x5F

//	Arithmetic Instructions
// instruções lógico-aritméticas que manipulam operandos na pilha
// Tadd
#define		iadd		0x60
#define		ladd		0x61
#define		fadd		0x62
#define		dadd		0x63
	
// Tsub
#define		isub		0x64
#define		lsub		0x65
#define		fsub		0x66
#define		dsub		0x67

// Tmul
#define		imul		0x68
#define		lmul		0x69
#define		fmul		0x6A
#define		dmul		0x6B

// Tdiv
#define		idiv		0x6C
#define		ldiv_		0x6D	// identificador ldiv ja utilizado em stdlib.h
#define		fdiv		0x6E
#define		ddiv		0x6F

// Trem
#define		irem		0x70
#define		lrem		0x71
#define		frem		0x72
#define		drem		0x73

// Tneg
#define		ineg		0x74
#define		lneg		0x75
#define		fneg		0x76
#define		dneg		0x77

// Tshl
#define		ishl		0x78
#define		lshl		0x79
	
// Tshr
#define		ishr		0x7A
#define		lshr		0x7B

// Tushr
#define		iushr		0x7C
#define		lushr		0x7D

// Tand
#define		iand		0x7E
#define		land		0x7F

// Tor
#define		ior		0x80
#define		lor		0x81

// Txor
#define		ixor		0x82
#define		lxor		0x83

// Tinc
#define		iinc		0x84

//	Type Conversion Instructions
// instruções que convertem valores presentes na pilha entre diferentes tipos.
#define		i2l		0x85
#define		i2f		0x86
#define		i2d		0x87
#define		l2i		0x88
#define		l2f		0x89
#define		l2d		0x8A
#define		f2i		0x8B
#define		f2l		0x8C
#define		f2d		0x8D
#define		d2i		0x8E
#define		d2l		0x8F
#define		d2f		0x90
#define		i2b		0x91
#define		i2c		0x92
#define		i2s		0x93

// 	Comparison instructions
#define		lcmp		0x94
#define		fcmpl		0x95
#define		fcmpg		0x96
#define		dcmpl		0x97
#define		dcmpg		0x98

//	Control Transfer Instructions
// conditional branch
#define		ifeq		0x99
#define		ifne		0x9A
#define		iflt		0x9B
#define		ifge		0x9C
#define		ifgt		0x9D
#define		ifle		0x9E
#define		if_icmpeq	0x9F
#define		if_icmpne	0xA0
#define		if_icmplt	0xA1
#define		if_icmpge	0xA2
#define		if_icmpgt	0xA3
#define		if_icmple	0xA4
#define		if_acmpeq	0xA5
#define		if_acmpne	0xA6

// unconditional branch
#define		goto_		0xA7
#define		jsr		0xA8
#define		ret		0xA9

// compound conditional branch
#define		tableswitch	0xAA
#define		lookupswitch	0xAB

// Treturn			
#define		ireturn		0xAC
#define		lreturn		0xAD
#define		freturn		0xAE
#define		dreturn		0xAF
#define		areturn		0xB0
#define		return_		0xB1

// Access Fields
#define		getstatic	0xB2
#define		putstatic	0xB3
#define		getfield	0xB4
#define		putfield	0xB5

//	Method Invocation and Return Instructions
#define		invokevirtual	0xB6
#define		invokespecial	0xB7
#define		invokestatic	0xB8
#define		invokeinterface	0xB9
#define		invokedynamic	0xBA

//	Object Creation and Manipulation
#define		new		0xBB
#define		newarray	0xBC
#define		anewarray	0xBD
#define		arraylength	0xBE


#define		athrow		0xBF

// check properties
#define		checkcast	0xC0
#define		instanceof	0xC1

// monitor
#define		monitorenter	0xC2
#define		monitorexit	0xC3

#define		wide		0xC4

#define		multianewarray	0xC5

#define		ifnull		0xC6
#define		ifnonnull	0xC7

#define		goto_w		0xC8	
#define		jsr_w		0xC9

#define		breakpoint	0xCA

#define		impdep1		0xFE
#define		impdep2		0xFF


// Array contendo strings com os mnemônicos da JVM, para utilização no Exibidor.
char	*	opcodes[] = {
		// 0 a 9
		"nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst2", "iconst_3", "iconst_4", "iconst_5", "lconst_0",
		// 10 a 19
		"lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", "dconst_1", "bipush", "sipush", "ldc", "ldc_w",
		// 20 a 29
		"ldc2_w", "iload", "lload", "fload","dload", "aload", "iload_0", "iload_1", "iload_2", "iload_3",
		// 30 a 39
		"lload_0", "lload_1", "lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3", "dload_0", "dload_1",
		// 40 a 49
		"dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", "iaload", "laload", "faload", "daload",
		// 50 a 59
		"aaload", "baload", "caload", "saload", "istore", "lstore", "fstore", "dstore", "astore", "istore_0",
		// 60 a 69
		"istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1", "lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2",
		// 70 a 79
		"fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3", "astore_0", "astore_1", "astore_2", "astore_3", "iastore",
		// 80 a 89
		"lastore", "fastore", "dastore", "aastore", "bastore", "castore", "sastore", "pop", "pop2", "dup",
		// 90 a 99	
		"dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2", "swap", "iadd", "ladd", "fadd", "dadd",
		// 100 a 109
		"isub", "lsub", "fsub", "dsub", "imul", "lmul", "fmul", "dmul", "idiv", "ldiv",
		// 110 a 119
		"fdiv", "ddiv", "irem", "lrem", "frem", "drem", "ineg", "lneg", "fneg", "dneg",
		// 120 a 129
		"ishl", "lshl", "ishr", "lshr", "iushr", "lushr", "iand", "land", "ior", "lor",
		// 130 a 139
		"ixor", "lxor", "iinc", "i2l", "i2f", "i2d", "l2i", "l2f", "l2d", "f2i",
		// 140 a 149
		"f2l", "f2d", "d2i", "d2l", "d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl",
		// 150 a 159
		"fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", "iflt", "ifge","ifgt", "ifle", "if_icmpeq",
		// 160 a 169
		"if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", "if_acmpeq", "if_acmpne", "goto", "jsr", "ret",
		// 170 a 179
		"tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn", "dreturn", "areturn", "return", "getstatic", "putstatic",
		// 180 a 189
		"getfield", "putfield", "invokevirtual", "invokespecial", "invokestatic", "invokeinterface", "invokedynamic", "new", "newarray", "anewarray",
		// 190 a 199
		"arraylength", "athrow", "checkcast", "instanceof", "monitorenter", "monitorexit", "wide", "multianewarray", "ifnull", "ifnonnull",
		// 200 a 209
		"goto_w", "jsr_w", "breakpoint", NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
		// 210 a 219 
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		// 220 a 229
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		// 230 a 239
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		// 240 a 249
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		// 250 a 255
		NULL, NULL, NULL, NULL, "impdep1", "impdep2"
};



















