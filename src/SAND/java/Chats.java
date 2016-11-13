package SAND.java;

abstract class Chats {
    private static ChatModel[] chats;
    public static WriteFIFO wf;
    private static String[] ipAddresses;

    
    static ChatModel getChat(int remoteid) {
        return chats[remoteid];
    }

  static ChatModel getChat(String ip) {
        for(int i = 0;i<ipAddresses.length;i++) {
            if(ipAddresses[i].equals(ip)) {
                System.out.println("resturing" + Integer.toString(i));
                return chats[i];
            }
        }
        return null;
    }


    static void initialize(int size) {
        chats = new ChatModel[size];
        ipAddresses = new String[size];
        for(int i = 0;i<size;i++) {
            chats[i] = new ChatModel(i);

        }
        try {
        wf = new WriteFIFO("/tmp/java");
    }
        catch(Exception e) {
            e.printStackTrace();
        }
    

    }

    static void setIpAddress(int remoteId,String ipAddress) {
        ipAddresses[remoteId] = ipAddress;
    }

static String getIpAddress(int remoteId) {
        return ipAddresses[remoteId];
    }

}


