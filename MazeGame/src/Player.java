import javax.swing.*;
import java.awt.*;

// player의 좌표와 이동을 나타내는 클래스
class Player extends JPanel {
    int width, height;
    int row, col, length;
    Color color;
    JPanel mazePane;
    GUI gui;

    Player(Color c, GUI gui) {
        color = c;
        this.gui = gui;
        mazePane = gui.getMazePane();
    }

    public int getRow() { return row; }
    public int getCol() { return col; }

    public void SetSize(int w, int h, int mazeLength) {
        width = w;
        height = h;
        length = mazeLength;
        row = length - 2;
        col = 1;
    }

    // player 이동
    public void movePoint(int row, int col) {
        removePlayer();
        this.row += row;
        this.col += col;
        paintPlayer();
        revalidate();
    }

    // 현재 player 지우기
    private void removePlayer() {
        mazePane.remove(row * length + col);
        mazePane.add(new JPanel(), row * length + col);
    }

    // 현재 player 그리기
    public void paintPlayer() {
        mazePane.remove(row * length + col);
        mazePane.add(this, row * length + col);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (gui.isSuccess()) return; // 게임 성공 시에는 그리지 않음
        int x = (getWidth() - width) / 2;
        int y = (getHeight() - height) / 2;
        g.drawOval(x, y, width, height);
        g.setColor(color);
        g.fillOval(x, y, width, height);
    }
}
