import java.util.*;
public class Main{
    public static void main(String args[]){
        int [][] mat={{1,2,3},{4,5,6},{7,8,9}};
        for(int col=0;col<mat[0].length;col++){
            for(int row=0;row<mat.length;row++){
                System.out.print(mat[row][col]+" ");
            }
            System.out.println();
        }
        System.out.println("Sum is "+sum(mat));
    }
    public static int sum(int[][] a){
        int sum=0;
        for(int[] row:a){
        for(int value:row)
           sum+=value;
   }
   return sum;
}
}
