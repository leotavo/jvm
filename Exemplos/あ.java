// java > 1.5

import java.util.Scanner;
        
public class あ{

    public static void main(String[] args) {
    	int array[][] = new int [3][2];
    	Thread x[] = new Thread[10];
    	String y[][] = new String[2][5];
        Scanner entrada = new Scanner(System.in);
        int idade;
        
        System.out.println("Digite sua idade: ");
        idade = entrada.nextInt();
        
        System.out.println("Sua idade é " + idade);
        switch (idade){
    		case 1 : idade = 2;
    		case 2 : idade =3;
    		default : idade = 4;
	}      
    }
    
    public int simpleSwitch(int intOne) {
    switch (intOne) {
        case 0:
            return 3;
        case 1:
            return 2;
        case 4:
            return 1;
        default:
            return -1;
    }
}
    

}
