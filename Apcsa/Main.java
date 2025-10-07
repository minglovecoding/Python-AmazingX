public class RunoobTest {
    public static void main(String[] args) {
        int a = 10, b = 20;
        swap(a, b); // 调用swap方法
        int[] r = swap(a, b);
        a = r[0];
        b = r[1];
        System.out.println("a = " + a + ", b = " + b); // 输出a和b的值
    }
    
    static int[] swap(int x, int y){
        return new int[]{y, x};
    }
}