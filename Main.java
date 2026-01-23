class A{
    public A(){System.out.print("1");}
    public A(int n){System.out.print("2");}
}
class B extends A{
    public B(){
        super(2);
        System.out.print("3");
    }
}
public class Main{
    public static void main(String[] args){
        new B();
    }
}