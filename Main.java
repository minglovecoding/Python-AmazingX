public class Main {
    public static void main(String[] args) {
}
}
interface Shape {
    double getArea();
}
class Square implements Shape {
    private double side;
    public Square(double side) { this.side = side; }
    double getArea() { return side * side; }
}