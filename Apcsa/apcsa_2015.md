1️⃣

```java
public class DiverseArray
{
    /** Returns the sum of the entries in the one-dimensional array arr. */
    public static int arraySum(int[] arr)
    {
        int sum = 0;
        for (int i = 0; i < arr.length; i++)
        {
            sum += arr[i];
        }
        return sum;
    }

    /**
     * Returns a one-dimensional array in which the entry at index k is the sum
     * of the entries of row k of the two-dimensional array arr2D.
     */
    public static int[] rowSums(int[][] arr2D)
    {
        int[] sums = new int[arr2D.length];

        for (int r = 0; r < arr2D.length; r++)
        {
            sums[r] = arraySum(arr2D[r]);
        }

        return sums;
    }

    /**
     * Returns true if all rows in arr2D have different row sums;
     * false otherwise.
     */
    public static boolean isDiverse(int[][] arr2D)
    {
        int[] sums = rowSums(arr2D);

        for (int i = 0; i < sums.length; i++)
        {
            for (int j = i + 1; j < sums.length; j++)
            {
                if (sums[i] == sums[j])
                {
                    return false;
                }
            }
        }

        return true;
    }
}
```

2️⃣

```java
public class HiddenWord
{
    private String word;

    public HiddenWord(String w)
    {
        word = w;
    }

    public String getHint(String guess)
    {
        String hint = "";

        for (int i = 0; i < guess.length(); i++)
        {
            String letter = guess.substring(i, i + 1);

            if (letter.equals(word.substring(i, i + 1)))
            {
                hint += letter;
            }
            else if (word.indexOf(letter) >= 0)
            {
                hint += "+";
            }
            else
            {
                hint += "*";
            }
        }
        return hint;
    }
}
```

3️⃣

```java
// a)
public int getValueAt(int row, int col)
{
    for (SparseArrayEntry e : entries)
    {
        if (e.getRow() == row && e.getCol() == col)
        {
            return e.getValue();
        }
    }
    return 0;
}
// b)
public void removeColumn(int col)
{
    for (int i = entries.size() - 1; i >= 0; i--)
    {
        SparseArrayEntry e = entries.get(i);

        if (e.getCol() == col)
        {
            entries.remove(i);
        }
        else if (e.getCol() > col)
        {
            // 创建新对象（因为不能修改原对象）
            SparseArrayEntry newEntry =
                new SparseArrayEntry(e.getRow(), e.getCol() - 1, e.getValue());

            entries.remove(i);
            entries.add(newEntry);
        }
    }

    numCols--;
}
```

***

```java
public class Scoreboard
{
    private String team1;
    private String team2;
    private int score1;
    private int score2;
    private boolean team1Active;

    public Scoreboard(String name1, String name2)
    {
        team1 = name1;
        team2 = name2;
        score1 = 0;
        score2 = 0;
        team1Active = true;
    }

    public void recordPlay(int points)
    {
        if (points == 0)
        {
            team1Active = !team1Active;
        }
        else
        {
            if (team1Active)
            {
                score1 += points;
            }
            else
            {
                score2 += points;
            }
        }
    }

    public String getScore()
    {
        if (team1Active)
        {
            return score1 + "-" + score2 + "-" + team1;
        }
        else
        {
            return score1 + "-" + score2 + "-" + team2;
        }
    }
}
```

