package cn.cdut.a6pan.ui.main;

import android.content.Context;
import android.os.Build;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.RequiresApi;

import java.util.List;

import cn.cdut.a6pan.Bean.File;
import cn.cdut.a6pan.R;


public class MyFileListDialogAdapter extends BaseAdapter {
    private final static String TAG = "FILE_LIST_DIALOG_ADAPTER";
    private LayoutInflater mInflater;
    private List<File> list;
    private View temp=null;
    public MyFileListDialogAdapter(Context ctx, List<File> list) {
        mInflater = LayoutInflater.from(ctx);
        this.list = list;
    }

    public MyFileListDialogAdapter(Context ctx) {
        mInflater = LayoutInflater.from(ctx);
    }

    @Override
    public int getCount() {
        if (list == null)
            return 0;
        return list.size();
    }

    @Override
    public Object getItem(int i) {
        if (list == null)
            return null;
        return list.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    @Override
    public View getView(final int i, View view, ViewGroup viewGroup) {
        MyFileListDialogAdapter.ViewHolder holder = null;
        View view1 = mInflater.inflate(R.layout.file_list_dialog_item, null);
        if (temp==null)
            temp=view1;
        if (view==null);
        holder = new MyFileListDialogAdapter.ViewHolder();
        holder.fileName = view1.findViewById(R.id.fileDialogName);
        File file= (File) getItem(i);
        holder.fileIcon=view1.findViewById(R.id.fileDialogIcon);
        holder.fileIcon.setImageDrawable(view1.getResources().getDrawable(R.drawable.ic_folder));
        view1.setTag(holder);

        holder.fileName.setText(list.get(i).getName());

        return view1;
    }

    public final class ViewHolder {
        public TextView fileName;
        public ImageView fileIcon;
    }
}
