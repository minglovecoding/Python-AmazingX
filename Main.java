import java.util.*;
public class Main{  
    public static void main(String[] args){
    int count = 0;
for (int i = 1; i <= 4; i++) {
    for (int j = i; j <= 4; j++) {
        count++;
    }
    System.out.print(count+" ");
}
System.out.println(count);
    }
}
