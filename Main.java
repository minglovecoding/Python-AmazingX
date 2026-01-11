import java.util.*;
public class Main{
    public static void main(String args[]){
        ArrayList<Integer>a=new ArrayList<Integer>();
        a.add(1);
        a.add(2);
        a.add(3);
        a.add(4);
        a.add(5);
        System.out.println(a.toString());
        int target=5;
        int left=0,right=a.size()-1;
        while(left<=right){
            int mid=(left+right)/2;
            if(a.get(mid)==target){
                System.out.println("target's index is "+mid);
                return;
            }
            else if(a.get(mid)>target){
                right=mid-1;
            }
            else{
                left=mid+1;
            }
        }
    }
}