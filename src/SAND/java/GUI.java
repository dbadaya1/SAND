package SAND.java;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by ALPHA-BETA on 12-10-16.
 */
public class GUI extends JFrame {
    private BasePanel pnlCurrent;
    private JButton btnBack;
    public JTextField temp;


    GUI() {
        super();
        initialize();

        btnBack.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openBackPanel(pnlCurrent.getBackPanel());
            }
        });
    }


    void initialize() {
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setLayout(new BorderLayout());
        btnBack = new JButton("Back");
        add(btnBack,BorderLayout.BEFORE_FIRST_LINE);

        temp = new JTextField();
        add(temp,BorderLayout.AFTER_LAST_LINE);

        openPanel(new SearchGUI());

    }

    void openPanel(BasePanel newPanel) {
        if(pnlCurrent != null) {
            pnlCurrent.setVisible(false);
        }
        this.add(newPanel, BorderLayout.CENTER);
        newPanel.setBackPanel(pnlCurrent);
        pnlCurrent = newPanel;
        pnlCurrent.setParent();
        pnlCurrent.setVisible(true);


    }

    void openBackPanel(BasePanel backPnl) {
        if(pnlCurrent != null) {
            pnlCurrent.setVisible(false);
        }
        pnlCurrent = backPnl;
        pnlCurrent.setVisible(true);

    }


}
