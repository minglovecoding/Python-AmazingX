import java.util.*;
public class Main{
    public static double baseCharge(int minutes){
        if(minutes<=30){
            return minutes*2.0;
        }
        if(minutes<=90){
            return 60+(minutes-30)*1.0;
        }
        return 120+(minutes-90)*0.5;
    }  
    public static void main(String[] args){
        int[] values = {2, 4, 6};
        for (int i=0;i<values.length;i++) {
            values[i] += 10;
        }
        System.out.println(values[1]);
        return;
}
}
//text="abc abc abc";
//git push ssh://git@ssh.github.com:443/minglovecoding/Python-AmazingX.git HEAD