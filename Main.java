public class Main {
    public static void change(int[] arr) {
    arr[0] = 8;
    arr = new int[] {1, 2};
}

    public static void main(String[] args) {
        int[] counts = new int[1];
boolean[] flags = new boolean[1];
String[] names = new String[1];
System.out.println(counts[0] + " " + flags[0] + " " + (names[0] == null));
}
}