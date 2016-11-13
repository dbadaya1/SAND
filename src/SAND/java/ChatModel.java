package SAND.java;

import javax.swing.*;
import java.util.ArrayList;

/**
 * Created by ALPHA-BETA on 14-10-16.
 */
public class ChatModel extends AbstractListModel<ChatModel.Chat> {

    int remoteId;
    ChatModel(int remoteId) {
        this.remoteId = remoteId;
    }
    static class Chat {
        char type;
        final String message;
        final String time;

        Chat(char type,String message,String time) {
            this.type = type;
            this.message = message;
            this.time = time;

        }
        public String toString() {
            return message;
        }
    }

    private ArrayList<Chat> chat = new ArrayList<>();

    @Override
    public int getSize() {
        return chat.size();
    }

    @Override
    public Chat getElementAt(int index) {
        return chat.get(index);
    }


    void sendMessage(String message) {
        chat.add(new Chat('a',message,"Time"));
        fireContentsChanged(this,chat.size(),chat.size() + 1);
        try {
            Chats.wf.write(message + ";" + Chats.getIpAddress(remoteId));
        }
        catch(Exception e) {
                        e.printStackTrace();

        }
    }

    void receiveMessage(String message) {
        chat.add(new Chat('a',message,"Time"));
        fireContentsChanged(this,chat.size(),chat.size() + 1);

    }


}
