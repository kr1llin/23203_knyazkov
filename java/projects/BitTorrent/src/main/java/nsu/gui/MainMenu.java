package nsu.gui;

import nsu.logic.Engine;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.List;

public class MainMenu extends JFrame implements ActionListener {
    private final MenuComponents menuComponents = new MenuComponents(this);
    private final Engine engine;
    private final List<String> peers;
    private boolean isMetaInit = false;

    public MainMenu(List<String> peers) {
        super("BitTorrent Client");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(900, 900);
        setLocationRelativeTo(null);
        this.peers = peers;

        engine = new Engine();
        initUI();
    }

    private void startProgressUpdater() {
        Timer timer = new Timer(200, e -> updateProgress());
        timer.start();
    }

    private void updateProgress() {
        if (engine.getDataProgress() >= 0 && engine.getDataProgress() <= 100) {
            menuComponents.getProgress().setValue(engine.getDataProgress());
            menuComponents.updateStatus(String.format("Active connections: %d", engine.getActiveConnections().size()));
        }
    }


    private void initUI() {

        JPanel mainPanel = new JPanel(new BorderLayout(10, 10));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        JPanel controlPanel = new JPanel(new GridLayout(2, 1, 10, 10));

        JButton startServerBtn = menuComponents.getStartBtn();
        JButton downloadBtn = menuComponents.getDownloadBtn();

        startServerBtn.setToolTipText("Start listening for incoming connections");
        downloadBtn.setToolTipText("Start downloading file from peers");

        controlPanel.add(startServerBtn);
        controlPanel.add(downloadBtn);

        JPanel statusPanel = new JPanel(new GridLayout(2, 1, 10, 10));
        statusPanel.add(menuComponents.getProgress());
        statusPanel.add(menuComponents.getLabel());

        mainPanel.add(controlPanel, BorderLayout.SOUTH);
        mainPanel.add(statusPanel, BorderLayout.CENTER);

        add(mainPanel);
        setVisible(true);
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == menuComponents.getStartBtn()) {
            handleServerStart();
        } else if (e.getSource() == menuComponents.getDownloadBtn()) {
            handleMetaInit();
        }
    }

    // accept peer connections
    // ADD ADDRESS VALIDATION
    private void handleServerStart() {
        String hostnameStr = (String) JOptionPane.showInputDialog(
                this, "Enter server ip:",
                "Server Setup",
                JOptionPane.PLAIN_MESSAGE, null, null, "127.0.0.1"
        );

        String portStr = (String) JOptionPane.showInputDialog(
                this, "Enter server port:",
                "Server Setup",
                JOptionPane.PLAIN_MESSAGE, null, null, "1337"
        );

        if (portStr == null || portStr.trim().isEmpty()) return;

        try {
            int port = Integer.parseInt(portStr);
            menuComponents.getStartBtn().setEnabled(false);
            engine.startServer(hostnameStr, port);
            menuComponents.updateStatus("Server is running on socket: " + hostnameStr + ":" + port);
        } catch (NumberFormatException ex) {
            showError("Invalid port number!");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // init meta -> start download
    private void handleMetaInit() {

        try {
            if (!isMetaInit) {
                // COMMENTED OUT WHILE DEBUGGING
//                JFileChooser fileChooser = new JFileChooser();
//                if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
//                    File torrentFile = fileChooser.getSelectedFile();
//                    engine.initTorrentMeta(torrentFile.getAbsolutePath());
                engine.initTorrentMeta("/home/krillin/code/nsu/23203_knyazkov/java/projects/BitTorrent/src/main/resources/torrents/Kiki's Delivery Service [BD-rip 1920x1080 x264 FLAC].mkv.torrent");
//                    menuComponents.updateStatus("Initialized meta for torrent: " + torrentFile.getName());
                    isMetaInit = true;
                    menuComponents.getDownloadBtn().setText("Start Downloading");
//                }
            }
            else {
                handleDownloadStart();
            }
        } catch (IOException e) {

        }
    }

    private void handleDownloadStart() {
        try {
            engine.startClient(peers);
            startProgressUpdater();
        } catch (IOException e) {

        }
    }

    private void showError(String message) {
        JOptionPane.showMessageDialog(
                this, message, "Error",
                JOptionPane.ERROR_MESSAGE
        );
    }
}