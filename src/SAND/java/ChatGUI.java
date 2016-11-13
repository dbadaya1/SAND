package SAND.java;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by ALPHA-BETA on 14-10-16.
 */
public class ChatGUI extends BasePanel {
    private JList<ChatModel.Chat> lstChat;
    private JTextField messageTxt;
    private JButton sendBtn;
    private int remoteId;
    ChatGUI(int remoteId) {
        super();
        this.remoteId = remoteId;
        messageTxt = new JTextField(20);
        sendBtn = new JButton("Send");
        lstChat = new JList<>(Chats.getChat(remoteId));
        add(lstChat);
        add(messageTxt);
        add(sendBtn);

        sendBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Chats.getChat(remoteId).sendMessage(messageTxt.getText());
            }
        });
   

        

           // WriteFIFO wf  = new WriteFIFO();
         //   wf.write("Hello");
          // rf.close();


    }













}
