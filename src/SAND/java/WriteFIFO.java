package SAND.java;


public class WriteFIFO {


 static {
     System.loadLibrary("WriteFIFO");
 }

 private native void initializeWriteFIFO(String fileName);
 private native void writeFIFO(String message);
 private native void closeWriteFIFO();


WriteFIFO(String fileName) throws Exception{
    initializeWriteFIFO(fileName);
    
}

public void close() throws Exception{
    closeWriteFIFO();
}

public void write(String message) throws Exception{
    writeFIFO(message);
}

    
}