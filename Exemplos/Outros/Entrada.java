// java > 1.5

import java.util.Scanner;
        
public class Entrada{

    public static void main(String[] args) {
    	int array[][] = new int [3][2];
    	Thread x[] = new Thread[10];
    	String y[][] = new String[2][5];
        Scanner 尊厳 = new Scanner(System.in);
        int idade;
        
        System.out.println("Digite sua idade: ");
        idade = 尊厳.nextInt();
        
        System.out.println("かつ、尊厳と権利と について平等である" + idade);
        switch (idade){
    		case 1 : idade = 2;
    		case 2 : idade =3;
    		default : idade = 4;
	}      
    }
    
    public int 在尊嚴和權利上一律平等(int intOne) {
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
