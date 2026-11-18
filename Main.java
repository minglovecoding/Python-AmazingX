import java.util.*;
public class Main {


    public static void main(String[] args) {
        ArrayList<Integer> a =new ArrayList<Integer>();
        a.add(3);
        a.add(4);
        ArrayList<Integer> b = a;
        b.set(0, 9);
        b = new ArrayList<Integer>();
        b.add(7);
        System.out.println(a + " " + b);


    }
}