import java.util.*;

public class Scannerr{
    public static void main(String[] args){
        Scanner A= new Scanner(System.in);
        int n=A.nextInt();
        double x=A.nextDouble();
        A.nextLine(); //读上一行的换行符
        String s=A.next();
        //System.out.println(n);
        //System.out.println(x);
        System.out.println(s);
        System.out.printf("n=%d, x=%.3f, s=%s\n", n, x, s);
        A.close();
    }
}

//输出100 10.123 hello