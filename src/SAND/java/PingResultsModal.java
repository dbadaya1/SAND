package SAND.java;
import javax.swing.table.AbstractTableModel;

public class PingResultsModal  extends AbstractTableModel {

    private String[] columnNames = {"IP"};
   private String[][] data;


PingResultsModal(String[] data) {
            this.data = new String[data.length][1];

    for(int i = 0;i<data.length;i++) {
       // this.data[i] = new String[1];
        this.data[i][0] = data[i];
}
}
    public int getColumnCount() {
        return columnNames.length;
    }

    public int getRowCount() {
        return data.length;
    }

    public String getColumnName(int col) {
        return columnNames[col];
    }

    public String getValueAt(int row, int col) {
        return data[row][col];
    }

    public Class getColumnClass(int c) {
        return getValueAt(0, c).getClass();
    }



}
