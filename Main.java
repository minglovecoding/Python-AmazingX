import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        double x = in.nextDouble();
        String s = in.next();   // 遇空白就停
        in.nextLine();          // 若后面要整行，先吃掉残余换行
        String line = in.nextLine();
        System.out.printf("n=%d, x=%.2f, s=%s, line=%s\n", n, x, s, line);
        in.close();
    }
}