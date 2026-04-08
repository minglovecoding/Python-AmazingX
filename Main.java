import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Main{
    public static void main(String[] args) throws FileNotFoundException{
        File file = new File("data.txt");
        Scanner sc= new Scanner(file);
        int sum=0;
        while (sc.hasNextInt()){
            sum+=sc.nextInt();      
        }
        System.out.println(sum);
        sc.close();
    }
}