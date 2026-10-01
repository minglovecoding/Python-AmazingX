public class Main{    
    //BinarySearch
    public static void mystery1(int n) {
    if (n <= 0) {
        System.out.print("X ");
    } else {
        System.out.print(n + " ");
        mystery1(n - 2);
        System.out.print(n + " ");
    }
}
    public static void mystery2(String s) {
    if (s.length() <= 1) {
        System.out.print(s);
    } else {
        mystery2(s.substring(1));
        System.out.print(s.charAt(0));
    }
}
    public static void main(String[] args){
        mystery2("APCSA");
    }
}
