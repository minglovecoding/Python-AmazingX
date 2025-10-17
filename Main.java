import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        double x1 = in.nextDouble(), y1 = in.nextDouble();
        double x2 = in.nextDouble(), y2 = in.nextDouble();
        double x3 = in.nextDouble(), y3 = in.nextDouble();

        double a = Math.hypot(x1 - x2, y1 - y2);
        double b = Math.hypot(x2 - x3, y2 - y3);
        double c = Math.hypot(x3 - x1, y3 - y1);

        System.out.printf("%.2f\n", a + b + c);
    }
}