import java.util.*;
public class Main{
    public static void selectionSort(int arr[]) {
    for (int i = 0; i < arr.length - 1; i++) {
        // find smallest from i to end of array
        int min_idx = i;
        for (int j = i + 1; j < arr.length; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // swap minimum with element at index i
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

    public static void main(String[] args){
        int[] a={4,5,2,1,3};
        selectionSort(a);
        System.out.println(Arrays.toString(a));
    }
}

//构造一个names的动态数组
//add Ricky Sean
//把names所有元素打印
//打印size大小
//各自单独取出自己的名字

//{4,5,2,1,3}
//{1,2,3,4,5}
