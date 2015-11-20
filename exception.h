//	exception.h

/*==========================================*/
// 	DESCRIÇÃO

// Define exceções da jvm


/*==========================================*/

#ifndef	EXCEPTION_H
#define	EXCEPTION_H

char	*	exceptions[] = 	{
				"ClassNotFoundException",
				"ClassFormatError",
				"UnsupportedClassVersionError",
				"ClassCircularityError",
				"NoClassDefFoundError",
				"VerifyError"
				};

// Thrown when an application tries to load in a class through its string name
// but no definition for the class with the specified name could be found.
#define		ClassNotFoundException		0

//LinkageError
// The binary data that purports to specify a requested compiled class or interface is malformed.
#define		ClassFormatError		1	

// A class or interface could not be loaded because it is represented using an unsupported version of the class file format.
#define		UnsupportedClassVersionError	2

// A class or interface could not be loaded because it would be its own superclass or superinterface
#define		ClassCircularityError		3

// No definition for a requested class or interface could be found by the relevant class loader.
#define		NoClassDefFoundError		4

//  "verifier" detects that a class file, though well formed, contains some sort of internal inconsistency or security problem.
#define		VerifyError			5

#endif

