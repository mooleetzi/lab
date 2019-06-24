public class FormatDirector {
    private Format fm;
    private FormatBuilder fb;

    public void setFb(FormatBuilder fb) {
        this.fb = fb;
        fb.setFormat(fm);
    }
    public Format getResult(){
        return fb.getResult();
    }
}
