class Example1c {

    static int width;
    static int height = (int) (Math.random() * 2.0);

    // This is the static initializer
    static {

        width = 3 * (int) (Math.random() * 5.0);
    }
}
