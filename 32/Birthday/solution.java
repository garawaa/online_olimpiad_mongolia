import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;


public class A {

    static final int[] MONTHS = new int[]{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[][] dates = new int[n][2];
        for (int i = 0; i < n; i++) {
            dates[i][0] = in.nextInt();
            dates[i][1] = in.nextInt() - 1;
        }
        int results = 0;
        int resDay = 0;
        int resMonth = 0;
        for (int month = 0; month < MONTHS.length; month++) {
            for (int day = 1; day <= MONTHS[month]; day++) {
                if (check(dates, day, month)) {
                    resDay = day;
                    resMonth = month;
                    results++;
                }
            }
        }
        if (results != 1) throw new RuntimeException(results + " correct solutions");
        PrintWriter out = new PrintWriter(System.out);
        out.println(resDay + " " + (resMonth + 1));
        out.close();
    }

    private static boolean check(int[][] dates, int day, int month) {
        if (!checkFirstPhrase(dates, day, month)) {
            return false;
        }
        if (!checkSecondPhrase(dates, day, month)) {
            return false;
        }
        if (!checkThirdPhrase(dates, day, month)) {
            return false;
        }
        return true;
    }

    private static boolean checkThirdPhrase(int[][] dates, int day, int month) {
        int v = 0;
        for (int m = 0; m < MONTHS.length; m++) {
            if (checkFirstPhrase(dates, day, m) && checkSecondPhrase(dates, day, m)) {
                if (m != month) return false;
                v++;
            }
        }
        return v == 1;
    }

    private static boolean checkSecondPhrase(int[][] dates, int day, int month) {
        int[] countInMonth = new int[MONTHS.length];
        for (int[] date : dates) {
            countInMonth[date[1]]++;
        }
        if (countInMonth[month] < 2) return false;
        int v = 0;
        for (int[] date : dates) {
            if (date[1] == month) {
                if (checkFirstPhrase(dates, date[0], month)) {
                    if (date[0] != day) return false;
                    v++;
                }
            }
        }
        return v == 1;
    }


    private static boolean checkFirstPhrase(int[][] dates, int day, int month) {
        int[] countInMonth = new int[MONTHS.length];
        boolean[] possible = new boolean[MONTHS.length];
        int possibleCount = 0;
        for (int[] date : dates) {
            countInMonth[date[1]]++;
            if (date[0] == day) {
                possible[date[1]] = true;
                possibleCount++;
            }
        }
        if (possibleCount < 2) return false;
        for (int m = 0; m < MONTHS.length; m++) {
            if (possible[m] && countInMonth[m] == 1)
                return false;
        }
        return true;
    }
}
