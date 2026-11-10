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

    public static void main(String[] args) {
        int[] values = {3, 4, 6};
int sum = 0;
for (int x : values) { sum += x; }
double average = sum / values.length;
System.out.println(average);
    //int b=average;
    //System.out.println(b);

    }

}