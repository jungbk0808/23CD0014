import javax.swing.*;

public class Timer extends Thread {
    JLabel timeLabel;
    int s, m;
    public Timer(JLabel timeLabel) {
        this.timeLabel = timeLabel;
    }
    public void run() {
        s = 0;
        m = 0;
        while (true) {
            if (s >= 60) {
                s -= 60;
                m++;
            }
            if (s < 10) {
                timeLabel.setText(m+":0"+s);
            }
            else {
                timeLabel.setText(m+":"+s);
            }
            s++;
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                return;
            }
        }
    }
}
