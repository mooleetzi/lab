package composite;

public class DormLeader extends SmallMonitor {
    private DormLeader[] child=null;

    @Override
    public void rushBlakcBoard() {
        super.rushBlakcBoard();
    }

    @Override
    public DormLeader[] getChild() {
        return child;
    }
}
