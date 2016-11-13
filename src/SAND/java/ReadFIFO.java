package SAND.java;


public class ReadFIFO {


 static {
     System.loadLibrary("ReadFIFO");
 }

 private native void initializeReadFIFO(String fileName);
  private native String readFIFO();
 private native void closeReadFIFO();


ReadFIFO(String fileName) throws Exception{
    initializeReadFIFO(fileName);
    
}

public void close() throws Exception{
    closeReadFIFO();
}

public String read() throws Exception{
    return readFIFO();
}

    
}