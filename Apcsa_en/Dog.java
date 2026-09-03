import java.io.*;

public class Dog{ //class
    private String name;
    private int age;
    public Dog(String name1){ //initialize
        //this(name,0);
        this.name=name1;
        System.out.println("小狗的名字是 : " + this.name); 
    }

    public Dog(String name1,int age){ //initialize
    }

    public void setAge(int age1){
        this.age=age1;
    }
    public int getAge(){
        return age;
    }
    public static void main(String[] args){
        Dog dog1 = new Dog( "xiaohei" ); //object
        dog1.setAge(10);
        System.out.println("Age is: "+dog1.getAge());
        dog1.setAge(12);
        int age=dog1.getAge();
        System.out.println("Age is: "+age);
    }
}
//Dog
//初始化xiaohei的Dog

//修改xiaohei名字为xiaohuang
//打印xiaohuang的age
//设置年龄为11
//打印xiaohuang的age