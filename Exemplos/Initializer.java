// On CD-ROM in file classlife/ex1/Example1a.java
class Example1a {

    // "= 3 * (int) (Math.random() * 5.0)" is the class variable
    // initializer
    static int size = 3 * (int) (Math.random() * 5.0);
}


// On CD-ROM in file classlife/ex1/Example1b.java
class Example1b {

    static int size;

    // This is the static initializer
    static {

        size = 3 * (int) (Math.random() * 5.0);
    }
}
