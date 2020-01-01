package cn.cdut.a6pan.ui.main;

import android.icu.text.SimpleDateFormat;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.sql.Date;
import java.util.List;

import cn.cdut.a6pan.Bean.File;
import cn.cdut.a6pan.R;

public class MyDownloadAdapter extends RecyclerView.Adapter<MyDownloadAdapter.MyViewHolder> {

    private List<File> list;


    public MyDownloadAdapter(List<File> list){
        this.list=list;
    }

    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view= LayoutInflater.from(parent.getContext()).inflate(R.layout.download_file_item,parent,false);
        MyViewHolder holder=new MyViewHolder(view);
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull MyViewHolder holder, int position) {
        File file=list.get(position);
        holder.fileTime = holder.itemView.findViewById(R.id.fileTime);
        holder.fileName = holder.itemView.findViewById(R.id.fileName);
        holder.fileSize=holder.itemView.findViewById(R.id.fileSize);
        holder.fileIcon=holder.itemView.findViewById(R.id.fileIcon);
        holder.progressBar=holder.itemView.findViewById(R.id.progressBar);
        holder.fileSize.setText(getSize(file));
        holder.fileTime.setText(getTime(file));
        holder.fileIcon = holder.itemView.findViewById(R.id.fileIcon);
        holder.itemView.setTag(position);
        holder.fileName.setText(file.getName());
    }

    @Override
    public int getItemCount() {
        if (list==null)
            return 0;
        return list.size();
    }
    class MyViewHolder extends RecyclerView.ViewHolder{
        public View itemView;
        public TextView fileName;
        public TextView fileTime;
        public ImageView fileIcon;
        public ProgressBar progressBar;
        public TextView fileSize;
        public MyViewHolder(View view){
            super(view);
            itemView=view;
        }
    }
    private String getSize(File fp){
        long fileSizeByte=fp.getSize();
        String fileSizeMsg="";
        if (fileSizeByte < 1048576) fileSizeMsg = (fileSizeByte / 1024) + "KB";
        else if (fileSizeByte == 1048576) fileSizeMsg = "1MB";
        else if (fileSizeByte > 1048576 && fileSizeByte < 1073741824) fileSizeMsg = (fileSizeByte / (1024 * 1024)) + "MB";
        else if (fileSizeByte > 1048576 && fileSizeByte == 1073741824) fileSizeMsg = "1GB";
        else if (fileSizeByte > 1073741824 && fileSizeByte < 1099511627776L) fileSizeMsg = (fileSizeByte / (1024 * 1024 * 1024)) + "GB";
        else fileSizeMsg = "文件超过1TB";
        return fileSizeMsg;
    }
    private String getTime(File fp){
        Date date;
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        try {
            date = new Date(fp.getMtime());
        }catch (NullPointerException e){
            date=new Date(fp.getDeleteTime());
        }

        return simpleDateFormat.format(date);
    }
}
