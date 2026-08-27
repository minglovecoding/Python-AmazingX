public class Receipt{
    public static void main(String[] args){
        int x=2.5;
        int subtotal=38+40+30;
        double tax=subtotal*0.08;
        double tip=subtotal*0.15;
        double total=subtotal+tax+tip;
        System.out.println("Total:"+total);
    }
}