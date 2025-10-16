public class Main {
    public static void main(String[] args) {
        Animal a1 = new Animal();
        Animal a2 = new Dog();          // 多态：父类引用指向子类对象

        a1.speak();                     // 调用 Animal.speak()
        a2.speak();                     // 调用 Dog.speak()（重写生效）
    }
}

class Animal {
    public void speak() {
        System.out.println("Animal: ...");
    }
}

class Dog extends Animal {               // extend：Dog 继承 Animal
    @Override                            // override：重写 speak()
    public void speak() {
        System.out.println("Dog: Woof!");
    }
}
