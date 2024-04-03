import java.util.*;

public class Maze {
    Random random = new Random();
    int size;
    int[][] maze;
    Cel[] cur;
    public final static int PATH = 0, WALL = 1;

    public int[][] getMaze() {
        return maze;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void driver() {
        maze = new int[2 * size + 1][2 * size + 1];
        cur = new Cel[size];
        for (int i = 0; i < size; i++)          // 첫 행 초기화
            cur[i] = new Cel(0, i);
        for (int i = 2; i <= 2 * size; i++)     // 칸은 PATH로 초기화
            for (int j = 2; j <= 2 * size; j++)
                maze[i][j] = PATH;
        // 미로 생성 시작
        for (int i = 0; i < size; i++) {
            makeSet();
            makeRightWalls();
            makeDown();
            if (i == size - 1)
                end();
            printMaze(i);
            if (i != size - 1)
                genNextRow();
        }
        for (int i = 0; i <= 2 * size; i++)     // 끝 벽 감싸기
            maze[i][0] = maze[0][i] = maze[i][2 * size] = maze[2 * size][i] = WALL;
        for (int i = 2; i <= 2 * size; i += 2)  // 필수로 벽인 부분
            for (int j = 2; j <= 2 * size; j += 2)
                maze[i][j] = WALL;
        maze[1][2*size] = PATH;    // 탈출구 표시
    }

    private void makeSet() {
        for (Cel cell : cur) {
            if (cell.set == null) { // 집합이 없으면 생성
                cell.set = new ArrayList<>();
                cell.set.add(cell);
            }
        }
    }

    private void makeRightWalls() {
        for (int i = 1; i < cur.length; i++) {
            if (cur[i - 1].set.contains(cur[i]))
                continue;                   // 같은 집합이면 건너뛰기
            if (random.nextBoolean()) {
                cur[i - 1].right = false;   // 랜덤 결과로 벽을 허물고 집합을 합치기
                merge(i);
            }
        }
    }

    private void merge(int i) {
        ArrayList<Cel> currentList = cur[i - 1].set;
        ArrayList<Cel> nextList = cur[i].set;
        for (Cel j : nextList) {
            currentList.add(j);     // 앞 셀에 j 셀을 더하기
            j.set = currentList;    // j 셀의 집합을 앞 셀로 변경
        }
    }

    private void makeDown() {
        for (Cel cel : cur) {
            for (Cel x : cel.set) // 초기화
                x.down = true;
            do {                  // 랜덤으로 down을 결정
                cel.set.get(random.nextInt(cel.set.size())).down = false;
            } while (random.nextBoolean());
        }
    }

    private void end() {
        for (int i = 1; i < cur.length; i++) {
            if (!cur[i - 1].set.contains(cur[i])) {
                cur[i - 1].right = false;  // set에 없으면 벽 허물고 합치기
                merge(i);
            }
        }
    }

    private void genNextRow() {
        for (Cel cel : cur) {   // 셀을 초기화
            cel.right = true;
            cel.x++;
            if (cel.down) {
                cel.set.remove(cel);
                cel.set = null;
            }
        }
    }

    private void printMaze(int rowPos) {
        rowPos = 2 * rowPos + 1;
        for (int i = 0; i < cur.length; i++) {
            if (cur[i].right)
                maze[rowPos][2 * i + 2] = WALL;
            if (cur[i].down)
                maze[rowPos + 1][2 * i + 1] = WALL;
        }
    }
}