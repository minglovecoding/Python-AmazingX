import java.util.*;
public class Main{  
    public static boolean haveSameContents(int[] arr1,int[] arr2){
        if(arr1.length!=arr2.length) return false;
        for(int k=0;k<arr1.length;k++){
            if(arr1[k]!=arr2[k]) return false;
        }
        return true;
    } 
    
    public static void printInreverseOrder(ArrayList<String>names){

    } 
    public static void main(String[] args){
        int t=0;
        for(int v=1;v<20;v=v*3){
            t=t+v;
            System.out.print(t+" ");
        }
        System.out.println(t);
    }
}

// 0 1 2
// 1 1 2


// 1 0 2
// 1 1 2