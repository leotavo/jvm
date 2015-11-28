package Exemplos;

public class ExemploInterfaceamento {

	public static void main(String[] args) {
		ModeloTV001 tv1 = new ModeloTV001(21);
		ModeloSDX tv2 = new ModeloSDX (42);
		
		tv1.ligar();
		tv2.ligar();
		
		System.out.print("TV1 - modelo " + tv1.MODELO + " esta ");
		System.out.println(tv1.isLigada() ? "ligada" : "desligada");
		System.out.print("TV2 - modelo " + tv2.MODELO + " esta ");
		System.out.println(tv1.isLigada() ? "ligada" : "desligada");
		
		// ambas as TVs estao ligadas e vamos desliga-las
		System.out.println("Desligando modelo " + tv1.MODELO);
		tv1.desligar();
		System.out.println("Desligando modelo " + tv2.MODELO);
		tv2.desligar();
	}
}
