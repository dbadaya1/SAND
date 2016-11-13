package SAND.java;
import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.*;
import java.io.*;
/**
 * Created by ALPHA-BETA on 12-10-16.
 */
public class SearchGUI extends BasePanel {
    private JTextField txtIpFrom,txtIpTo;
    private JButton btnSearch;
    private JTable tblSearchResults;
    JScrollPane scrollPane;

    SearchGUI() {
        super();
        initialize();
 

                 Thread t = new Thread(new Runnable() {
            public void run() {
                try {
                    ReadFIFO rf = new ReadFIFO("/tmp/c");

                    while(true) {
                        String a  = rf.read();
                        String[] data = a.split(";");

                           System.out.println(data[0] + data[1]);
                        if(data.length == 2)
                            Chats.getChat(data[1]).receiveMessage(data[0]);
                        Thread.sleep(1000);

                    }
                }
                catch(Exception e) {
                    e.printStackTrace();
                }

            }
        });
        //t.start();
    }

    void initialize() {
        txtIpFrom = new JTextField(10);
        txtIpTo = new JTextField(10);
        btnSearch = new JButton("Search");

        tblSearchResults = new JTable();
        //tblSearchResults.setBounds(100,40,200,300);
        scrollPane = new JScrollPane(tblSearchResults);

        tblSearchResults.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent evt) {
                int row = tblSearchResults.rowAtPoint(evt.getPoint());
                if (row >= 0) {
                    parent.openPanel(new SelectActionGUI(row));
                }
            }
        });


        add(txtIpFrom);
        add(txtIpTo);
        add(btnSearch);
        add(scrollPane);

        btnSearch.addActionListener(e -> {
            String from  = txtIpFrom.getText().toString();
            String to = txtIpTo.getText().toString();

    String command = "/home/ubuntu/SAND/src/SAND/c/ping.out " + ipRange(from,to);

        //in windows
        //String command = "ping -n 3 " + domainName;

        String output = executeCommand(command);
        output = output.substring(0,output.length()-1);
        String[] result = output.split(" ");
        tblSearchResults.setModel(new PingResultsModal(result));
                Chats.initialize(tblSearchResults.getRowCount());

       for(int i = 0;i<tblSearchResults.getRowCount();i++) {
            Chats.setIpAddress(i,tblSearchResults.getValueAt(i,0).toString());
        }
        
        });



    }

private static String ipRange(String start,String end) {
    
    String[] startParts = start.split("(?<=\\.)(?!.*\\.)");
    String[] endParts = end.split("(?<=\\.)(?!.*\\.)");

    int first = Integer.parseInt(startParts[1]);
    int last = Integer.parseInt(endParts[1]);

StringBuilder sb = new StringBuilder();
    for (int i = first; i <= last; i++) {
        sb.append(startParts[0] + i + " ");
    }
    return sb.toString();
}
    private static String executeCommand(String command) {

        StringBuffer output = new StringBuffer();

        Process p;
        try {
            p = Runtime.getRuntime().exec(command);
            p.waitFor();
            BufferedReader reader =
                            new BufferedReader(new InputStreamReader(p.getInputStream()));

                        String line = "";
            while ((line = reader.readLine())!= null) {
                output.append(line + "\n");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return output.toString();

    }




}