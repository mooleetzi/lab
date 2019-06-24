package composite;

import java.util.ArrayList;

public class SmallMonitor extends BigMonitor{
    private SmallMonitor[] child=null;

    @Override
    public void rushBlakcBoard() {
        super.rushBlakcBoard();
    }

    @Override
    public SmallMonitor[] getChild() {
        return child;
    }
}
