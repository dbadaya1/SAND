package SAND.java;

import javax.swing.*;

/**
 * Created by ALPHA-BETA on 06-11-16.
 */
public class BasePanel extends JPanel {
    GUI parent;
    protected BasePanel pnlPrevious;

public void setParent() {
    parent = (GUI)SwingUtilities.getWindowAncestor(this);
}

public BasePanel getBackPanel() {
    return pnlPrevious;
}

public void setBackPanel(BasePanel panel) {
    this.pnlPrevious = panel;
}


}
