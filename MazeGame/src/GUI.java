import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class GUI extends JFrame {
    JLayeredPane contentPane = new JLayeredPane();
    JPanel mazePane = new JPanel(); // 미로 판
    JLabel timeLabel = new JLabel("0:00"); // 타이머 Label
    Timer th = new Timer(timeLabel); // 타이머 객체
    Maze mazeGame;                   // 미로 게임 객체
    int[][] maze;                    // 미로 배열
    Player player = new Player(Color.red, this); // player 객체
    JComboBox<String> level = new JComboBox<>(new String[]{"easy", "normal", "hard", "expert"});
    final int[] levelIndex = {10, 20, 30, 40}; // level 별 판 크기
    boolean success = false;         // 게임 성공 여부

    GUI() {
        setTitle("미로 게임");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // menu 패널 설정
        JPanel menuPane = new JPanel();
        menuPane.add(level);            // 난이도 선택 추가

        JButton generateButton = new JButton("Game Start");
        generateButton.addActionListener(new ButtonActionListener());
        menuPane.add(generateButton);   // 미로 생성 버튼 추가
        menuPane.add(timeLabel);        // 타이머 표시 Label 추가

        // ContentPane 설정, 이벤트 리스너 추가
        setContentPane(contentPane);
        contentPane.addKeyListener(new GameKeyListener());
        contentPane.setLayout(new BorderLayout());

        // 메뉴 패널과 미로 게임 패널 추가
        contentPane.add(menuPane, BorderLayout.NORTH, 0);
        contentPane.add(mazePane, BorderLayout.CENTER, 0);

        setSize(900, 1000);
        setVisible(true);

        contentPane.setFocusable(true);
        contentPane.requestFocus();
    }


    // 미로 탈출 여부 확인
    public boolean isSuccess() {
        if (success) return true;
        success = player.getRow() == 1 && player.getCol() == maze.length - 1;
        return success;
    }

    public JPanel getMazePane() { return mazePane; }

    // 버튼 클릭 이벤트 리스너
    class ButtonActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            // 초기화
            success = false;
            mazePane.removeAll();
            repaint();

            // 새 게임 생성
            mazeGame = new Maze();
            int size = levelIndex[level.getSelectedIndex()];
            mazeGame.setSize(size);
            mazeGame.driver();

            // 생성한 미로 데이터 받기, layout 설정
            maze = mazeGame.getMaze();
            int n = maze.length;
            mazePane.setLayout(new GridLayout(n,n));

            // 미로판 그리기
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (maze[row][col] == Maze.WALL) {
                        mazePane.add(new RectPan(Color.BLACK));
                    } else {
                        mazePane.add(new JPanel());
                    }
                }
            }

            // player 설정 및 그리기
            player.SetSize(300/size, 300/size, maze.length);
            player.paintPlayer();

            revalidate();

            contentPane.setFocusable(true);
            contentPane.requestFocus();

            // timer 생성 및 시작
            if (th.isAlive()) { // 이전 타이머가 있을 경우 중단
                th.interrupt();
            }
            th = new Timer(timeLabel);
            th.start();
        }
    }

    // 키 이벤트 리스너 (방향키와 WASD키 사용)
    class GameKeyListener extends KeyAdapter {
        public void keyPressed(KeyEvent e) {
            if (success) return;
            int keyCode = e.getKeyCode();
            switch (keyCode) {
                case KeyEvent.VK_UP:
                case KeyEvent.VK_W:
                    if (maze[player.getRow()-1][player.getCol()] == Maze.WALL)
                        return;
                    player.movePoint(-1, 0);
                    break;
                case KeyEvent.VK_DOWN:
                case KeyEvent.VK_S:
                    if (maze[player.getRow()+1][player.getCol()] == Maze.WALL)
                        return;
                    player.movePoint(1, 0);
                    break;
                case KeyEvent.VK_LEFT:
                case KeyEvent.VK_A:
                    if (maze[player.getRow()][player.getCol()-1] == Maze.WALL)
                        return;
                    player.movePoint(0, -1);
                    break;
                case KeyEvent.VK_RIGHT:
                case KeyEvent.VK_D:
                    if (maze[player.getRow()][player.getCol()+1] == Maze.WALL)
                        return;
                    player.movePoint(0, 1);
                    break;
            }
            if (isSuccess()) {
                th.interrupt(); // 타이머 중지

                // 미로 판에 성공 메시지 출력
                mazePane.setLayout(new BorderLayout());
                mazePane.add(new GUI.SuccessMassagePane());

                revalidate();
            }
        }
    }

    // 미로의 각 칸을 만드는 클래스
    class RectPan extends JPanel {
        int width = 100, height = 100;
        Color color;

        RectPan(Color c) {
            color = c;
        }
        @Override  // component를 그려야 하는 때마다 호출됨
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            if (success) return; // 게임 성공 시에는 그리지 않음
            g.drawRect(0, 0, width, height);
            g.setColor(color);
            g.fillRect(0, 0, width, height);
        }
    }

    class SuccessMassagePane extends JPanel {
        int rectWidth = 300;
        int rectHeight = 60;
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            if (!success) return; // 게임이 성공 했을 때만 그림

            // 성공 메시지 배경 사각형 그리기
            int x = (getWidth() - rectWidth) / 2;
            int y = (getHeight() - rectHeight) / 2;

            g.setColor(Color.LIGHT_GRAY);
            g.fillRect(x, y, rectWidth, rectHeight);

            // 성공 메시지 label 그리기
            String labelText = "success!!!  " + timeLabel.getText();
            FontMetrics fontMetrics = g.getFontMetrics();
            int stringWidth = fontMetrics.stringWidth(labelText);
            int stringHeight = fontMetrics.getHeight();

            int tx = (getWidth() - stringWidth) / 2;
            int ty = (getHeight() - stringHeight) / 2 + fontMetrics.getAscent();

            g.setColor(Color.BLACK);
            g.setFont(new Font("Arial", Font.BOLD, 16));
            g.drawString(labelText, tx, ty);
        }
    }
}