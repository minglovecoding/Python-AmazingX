import java.util.*;
public class Main {
    
    public static void main(String[] args) {
    Student[][] a = new Student[2][3];
System.out.println(a[0][0].getName());
    }
}
public class Student {
    private String name;
    private int score;

    public Student(String name, int score) {
        this.name = name;
        this.score = score;
    }

    public String getName() { return name; }
    public int getScore() { return score; }

    public void setScore(int newScore) {
        score = newScore;
    }

    public String getLetterGrade() {
        if (score >= 90) return "A";
        else if (score >= 80) return "B";
        else if (score >= 70) return "C";
        else if (score >= 60) return "D";
        else return "F";
    }

    public String getSummary() {
        return name + " (" + score + ")";
    }
}