/************************************************
* Codigo retirado do site TI Expert
* Visite-nos em WWW.TIEXPERT.NET
*
* @Author: Denys W. Xavier
*************************************************/

package Exemplos;

public class TV {
	private int tamanho;
	private int canal;
	private int volume;
	private boolean ligada;

	public TV(int tamanho) {
		this.tamanho = tamanho;
        this.canal = 0;
        this.volume = 0;
        this.ligada = false;
	}

	public int getTamanho() {
		return tamanho;
	}

	public void setTamanho(int tamanho) {
		this.tamanho = tamanho;
	}

	public int getCanal() {
		return canal;
	}

	public void setCanal(int canal) {
		this.canal = canal;
	}

	public int getVolume() {
		return volume;
	}

	public void setVolume(int volume) {
		this.volume = volume;
	}

	public boolean isLigada() {
		return ligada;
	}

	public void setLigada(boolean ligada) {
		this.ligada = ligada;
	}

}
