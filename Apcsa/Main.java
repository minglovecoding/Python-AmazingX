public class Main {
    public static void main(String[] args) {
        // Math.random(): [0.0, 1.0)
        double r = Math.random();
        System.out.println("r in [0,1): " + r);

        // 0..n-1
        int n = 6;
        int a = (int)(Math.random() * n);
        System.out.println("int in [0," + (n-1) + "]: " + a);

        // [lo, hi]  (闭区间，含两端)
        int lo = 10, hi = 20;
        int b = lo + (int)(Math.random() * (hi - lo + 1));
        System.out.println("int in [" + lo + "," + hi + "]: " + b);

        // [lo, hi)  (左闭右开，不含 hi)
        int c = lo + (int)(Math.random() * (hi - lo));
        System.out.println("int in [" + lo + "," + hi + "): " + c);
    }
}