class TestVersion{
	public static int soma (int a, int b) {
		return a + b;
	}
	public static void main (String[ ] s)	{
		int i;
		float x = 100.f;
		double y = 1000.;
		int j = 20;
		for (i = 0; i < 10; i++){
			j = soma(j, 10);
		}
		System.out.print (j);
	}
}
