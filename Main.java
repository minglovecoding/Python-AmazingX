import java.util.*;
public class Main{
    public static void main(String[] args){
        int[] num=new int[5];
        int sum=0;
        Scanner in=new Scanner(System.in);
        for(int i=0;i<num.length;i++){
            num[i]=in.nextInt();
            int sum+=num[i];
        }

        int res=num[0];
        for(int i=1;i<num.length;i++){
            if(num[i]>res){
                res=num[i];
            }
        }
        //average
        double avg=(sum*1.0)/num.length;
        System.out.println(res);
        System.out.println(avg);
    }
}

//声明一个数组num num里有5个数
//5个数是要从键盘输入的
//输出这5个数里最大的值