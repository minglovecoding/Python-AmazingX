import java.util.*;
public class Main{
    public static void main(String args[]){
        int[][] mat={{1,2,3},{4,5,6},{7,8,9}};
        for(int i=0;i<mat.length;i++){
            for(int j=0;j<mat[0].length;j++){
                System.out.print(mat[i][j]+" ");
            }
            System.out.println();
        }
    }
}