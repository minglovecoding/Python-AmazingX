import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Main{
    public static Scoreboard{
        private String team1;
        private String team2;
        private int score1;
        private int score2;
        private boolean turn;

        public Scoreboard(String name1,String name2){
            team1=name1;
            team2=name2;
            score1=0;
            score2=0;
            turn=true;
        }
        
        public void recordPlay(int score){
            if(score==0){
                turn=!turn;
            }else{
                if(turn){
                    score1+=score;
                }else{
                    score2+=score;
                }
            }
        }

        public String getScore(){
            if(turn){
                return score1+"-"+score2+"-"+team1;
            }
            else{
                return score1+"-"+score2+"-"+team2;
            }
        }
    }

    public static void main(String[] args) throws FileNotFoundException{
        File file = new File("data.txt");
        Scanner sc= new Scanner(file);
        int sum=0;
        while (sc.hasNextInt()){
            sum+=sc.nextInt();      
        }
        System.out.println(sum);
        sc.close();
    }
}
