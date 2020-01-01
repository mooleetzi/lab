package cn.cdut.a6pan.ui.main;


import android.content.ClipboardManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.paging.PagedListAdapter;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import cn.cdut.a6pan.Bean.File;
import cn.cdut.a6pan.R;
import cn.refactor.lib.colordialog.PromptDialog;

public class MyPagedListAdapter extends PagedListAdapter<File,MyPagedListAdapter.MyViewHolder> {

    private final static String TAG="File_Adpater";
    private FileChooseListener listener;
    private FileViewModel fileViewModel;


    public void setFileViewModel(FileViewModel fileViewModel) {
        this.fileViewModel = fileViewModel;
    }

    public MyPagedListAdapter(@NonNull DiffUtil.ItemCallback<File> diffCallback) {
        super(diffCallback);
    }

    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, final int position) {
        final View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.file_list_item,parent,false);
        MyViewHolder holder = new MyViewHolder(view);
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Integer pos= (Integer) v.getTag();
                File file=getCurrentList().get(pos);
                if (file.getDirectory()){//文件夹
                    Log.d(TAG,file.getPath()+", "+fileViewModel.getPath().getValue());
                    fileViewModel.putPrePath(file.getPath(),fileViewModel.getPath().getValue());
                    fileViewModel.getPath().setValue(file.getPath());
                }
                else {
                    openPreview(view,file);
                }

            }
        });
        holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                Integer pos= (Integer) view.getTag();
                if (listener!=null)
                    listener.onLongClick(getItem(pos));
                return true;//不再触发单击事件
            }
        });
        return holder;
    }

    public void openPreview(View v,File fp){
        new PromptDialog(v.getContext())
                .setDialogType(PromptDialog.DIALOG_TYPE_INFO)
                .setAnimationEnable(true)
                .setTitleText(v.getResources().getString(R.string.file_preview))
                .setContentText("             等待6盘官方支持")
                .setPositiveListener("确定", new PromptDialog.OnPositiveListener() {
                    @Override
                    public void onClick(PromptDialog dialog) {
                        dialog.dismiss();
                    }
                }).show();
    }


    public void setListener(FileChooseListener listener){
        this.listener=listener;
    }


    @Override
    public void onBindViewHolder(@NonNull final MyViewHolder holder, final int position) {
        holder.fileTime = holder.itemView.findViewById(R.id.fileTime);
        holder.fileName = holder.itemView.findViewById(R.id.fileName);
        holder.fileSize=holder.itemView.findViewById(R.id.fileSize);
        File file= getItem(position);
        holder.fileSize.setText(File.getSize(file));
        holder.fileTime.setText(File.getTime(file));
        holder.fileIcon = holder.itemView.findViewById(R.id.fileIcon);
        holder.fileIcon.setImageDrawable(File.getIcon(file,holder.itemView));
        holder.checkBox = holder.itemView.findViewById(R.id.fileCheck);
        if (file!=null)
            holder.checkBox.setChecked(file.getChecked());
        holder.checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                listener.onCheckChanged(b, position);
            }
        });
        holder.itemView.setTag(position);

        holder.fileName.setText(file.getName());
    }

    class MyViewHolder extends RecyclerView.ViewHolder {
        public TextView fileName;
        public TextView fileTime;
        public ImageView fileIcon;
        public CheckBox checkBox;
        public TextView fileSize;
        public View itemView;
        public MyViewHolder(@NonNull View itemView) {
            super(itemView);
            this.itemView=itemView;
        }
    }
    interface FileChooseListener{
        void onCheckChanged(Boolean b,Integer i);
        void onLongClick(File file);
    }
}