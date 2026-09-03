public class Main{
	public static void main(String[] args){
			  int x = 23;
    		strange(x); //实际参数
    		System.out.println("2. x = " + x);
	}
	public static void strange(int x){//形式参数
	  		x = x + 1;
   		System.out.println("1. x = " + x);
}
}
//The value of x in main did not change. 