import java.io.*; //引入java里的BufferedReader类

public class Buffer{
    public static void main(String[] args)throws IOException{
        char c;
        System.out.println("输入字符, 按下 'e' 键退出。");
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        do{
            c=(char)br.read();
            System.out.print(c);
        }while(c!='e');
    }
}

