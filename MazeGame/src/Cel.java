import java.util.*;

public class Cel {
    public boolean right, down;
    public ArrayList<Cel> set;
    public int x, y;

    Cel(int a, int b) {
        x = a;
        y = b;
        right = true;
        down = true;
        set = null;
    }
}