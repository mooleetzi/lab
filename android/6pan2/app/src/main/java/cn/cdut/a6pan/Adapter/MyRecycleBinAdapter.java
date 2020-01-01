package cn.cdut.a6pan.ui.main;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.paging.PagedListAdapter;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.RecyclerView;

import cn.cdut.a6pan.Bean.File;
import cn.cdut.a6pan.R;
import cn.refactor.lib.colordialog.PromptDialog;

public class MyRecycleBinAdapter extends PagedListAdapter<File, MyRecycleBinAdapter.MyViewHolder> {


    private final static String TAG="File_Adpater";
    private FileChooseListener listener;
    private FileViewModel fileViewModel;


    public void setFileViewModel(FileViewModel fileViewModel) {
        this.fileViewModel = fileViewModel;
    }

    public MyRecycleBinAdapter(@NonNull DiffUtil.ItemCallback<File> diffCallback) {
        super(diffCallback);
    }

    @NonNull
    @Override
    public MyRecycleBinAdapter.MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, final int position) {
        final View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.file_recycle_bin_list_item,parent,false);
        MyViewHolder holder = new MyViewHolder(view);
        return holder;
    }


    public void setListener(FileChooseListener listener){
        this.listener=listener;
    }


    @Override
    public void onBindViewHolder(@NonNull MyRecycleBinAdapter.MyViewHolder holder, final int position) {
        holder.fileTime = holder.itemView.findViewById(R.id.fileTime);
        holder.fileName = holder.itemView.findViewById(R.id.fileName);
        holder.fileSize=holder.itemView.findViewById(R.id.fileSize);
        holder.fileDelete=holder.itemView.findViewById(R.id.fileDelete);
        File file= getItem(position);
        holder.fileRecycle=holder.itemView.findViewById(R.id.fileRecycle);
        holder.fileRecycle.setTag(position);
        holder.fileDelete.setTag(position);
        holder.fileRecycle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (listener!=null)
                    listener.recycle(getCurrentList().get((Integer) view.getTag()));
            }
        });
        holder.fileDelete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (listener!=null)
                    listener.delete(getCurrentList().get((Integer) view.getTag()));
            }
        });
        holder.fileSize.setText(File.getSize(file));
        holder.fileTime.setText(File.getTime(file));
        holder.fileIcon = holder.itemView.findViewById(R.id.fileIcon);
        holder.itemView.setTag(position);
        holder.fileName.setText(file.getName());
    }

    class MyViewHolder extends RecyclerView.ViewHolder {
        public TextView fileName;
        public TextView fileTime;
        public ImageView fileIcon;
        public ImageView fileRecycle;
        public ImageView fileDelete;
        public TextView fileSize;
        public View itemView;
        public MyViewHolder(@NonNull View itemView) {
            super(itemView);
            this.itemView=itemView;
        }
    }
    public interface FileChooseListener{
        void recycle(File file);
        void delete(File file);
    }
}
