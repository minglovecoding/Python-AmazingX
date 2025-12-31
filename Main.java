import java.util.*;

public class Main{
    public static void printArray(double[] array) {
    for (int i = 0; i < array.length; i++) {
        System.out.print(array[i] + " ");
    }
    System.out.print("\n");
    }
    public static double[] reverse(double[] array){
        double[] result=new double[array.length];
        for(int i=0,j=array.length-1;i<array.length;i++,j--){
            result[i]=array[j];
        }
        return result;
    }
    public static void main(String[] agrs){
        double[] li={1.0,2.0,3.0};
        printArray(li);
        printArray(reverse(li));
    }
  }