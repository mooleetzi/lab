package adapter;

public class RepairShop implements Repair {
    private ArmAdpter armAdpter=new ArmAdpter();
    private OutLookAdapter outLookAdapter=new OutLookAdapter();
    @Override
    public void repair(Object r) {
        if (r instanceof Arm)
            armAdpter.repair((Arm) r);
        else if (r instanceof OutLook)
            outLookAdapter.repair((OutLook)r);
    }
}
