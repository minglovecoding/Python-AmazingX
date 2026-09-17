//6
//4 3 0 5 1 2

//0 0 0 3 1 2
//1≤n≤100，0≤a≤10
import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner in=new Scanner(System.in);
        int n=in.nextInt();
        int[] a=new int[101];
        for(int i=0;i<n;i++){
            a[i]=in.nextInt();
        }
        for(int i=0;i<n;i++){
            int j=i-1;
            int cnt=0;
            while(j>=0){
                if(a[j]<a[i]) cnt++;
                j--;
            }
            System.out.print(cnt+" ");
        }
        System.out.println();
    }
}
//for循环遍历每一头鱼index
//while循环往左遍历每头鱼可爱值是否小于本身