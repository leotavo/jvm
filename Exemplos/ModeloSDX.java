/************************************************
 * Codigo retirado do site TI Expert
 * Visite-nos em WWW.TIEXPERT.NET
 *
 * @Author: Denys W. Xavier
 *************************************************/

package Exemplos;

public class ModeloSDX extends TV implements ControleRemoto {
	public final String MODELO = "TV-SDX";

	public ModeloSDX(int tamanho) {
		super(tamanho);
	}

	public void desligar() {
		System.out.println("Tchau!");
		super.setLigada(false);
	}

	public void ligar() {
		super.setLigada(true);
	}

	public void aumentarVolume(int taxa) {
	}

	public void diminuirVolume(int taxa) {
	}

	public void mudarCanal(int canal) {
	}

}
