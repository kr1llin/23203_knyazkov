package nsu.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class MenuComponents {
    private JButton startBtn, downloadBtn;
    private JLabel status;
    private JProgressBar progress;

    public MenuComponents(ActionListener actionListener){
        startBtn = new JButton("Start Server");
        startBtn.setFont(new Font("Arial", Font.BOLD, 50));
        startBtn.addActionListener(actionListener);

        downloadBtn = new JButton("Init torrent");
        downloadBtn.setFont(new Font("Arial", Font.BOLD, 50));
        downloadBtn.addActionListener(actionListener);

        status = new JLabel("Server port: undefined");
        status.setFont(new Font("Arial", Font.BOLD, 40));
        status.setHorizontalAlignment(JLabel.CENTER);

        progress = new JProgressBar(0, 100);
        progress.setValue(0);
        progress.setFont(new Font("Arial", Font.BOLD, 40));
        progress.setStringPainted(true);
    }

    public void updateStatus(String text){
        status.setText(text);
    }

    public JButton getStartBtn() {
        return startBtn;
    }

    public JButton getDownloadBtn() {
        return downloadBtn;
    }

    public JLabel getLabel() {
        return status;
    }

    public JProgressBar getProgress() {
        return progress;
    }
}
