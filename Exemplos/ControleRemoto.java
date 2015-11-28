/************************************************
 * Codigo retirado do site TI Expert
 * Visite-nos em WWW.TIEXPERT.NET
 *
 * @Author: Denys W. Xavier
 *************************************************/

package Exemplos;

public interface ControleRemoto {
	/*
	 * Perceba que apenas a assinatura dos metodos estao aqui.
	 * E cada metodo termina com um ponto-e-virgula (;)
	 */
	void mudarCanal(int canal);

	void aumentarVolume(int taxa);

	void diminuirVolume(int taxa);

	void ligar();

	void desligar();
}
