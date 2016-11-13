package SAND.java;

public class Main {

    static GUI gui;

    static {
        //System.loadLibrary("Test");
    }

    private static native void a();

    public static void main(String[] args) {

        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                gui = new GUI();
            }
        });

    
     //   a();

    }

 
}
