package cn.cdut.sixpan.Bean;

import java.util.List;

public class FileList {
    protected List<File> list;
    protected File parent;

    public List<File> getList() {
        return list;
    }

    public void setList(List<File> list) {
        this.list = list;
    }

    public File getParent() {
        return parent;
    }

    public void setParent(File parent) {
        this.parent = parent;
    }
}
