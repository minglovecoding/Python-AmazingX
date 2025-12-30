import java.util.*;
public class Main{
  public static void main(String[] args){
    int[] numbers={1,2,3,4,5,6};
    reverse(numbers);
    System.out.println(Arrays.toString(numbers));
  }
  public static void reverse(int[] x){
    for(int i=0;i<x.length/2;i++){
      int temp=x[i];
      x[i]=x[x.length-1-i];
      x[x.length-1-i]=temp;
    }
  }
}