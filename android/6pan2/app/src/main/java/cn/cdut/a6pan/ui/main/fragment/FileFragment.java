package cn.cdut.a6pan.ui.main;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.databinding.DataBindingUtil;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import android.Manifest;
import android.app.DownloadManager;
import android.content.ContentValues;
import android.content.Context;
import android.content.pm.PackageManager;
import android.database.ContentObserver;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.paging.PagedList;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.room.Room;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.PopupMenu;
import android.widget.Toast;

import com.google.gson.Gson;
import com.hb.dialog.myDialog.MyAlertInputDialog;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;

import cn.cdut.a6pan.Bean.File;
import cn.cdut.a6pan.Bean.Result;
import cn.cdut.a6pan.Bean.ResultFileSingle;
import cn.cdut.a6pan.Bean.ResultSendMessage;
import cn.cdut.a6pan.DAO.FileDao;
import cn.cdut.a6pan.DataBase.FileDataBase;
import cn.cdut.a6pan.Dialog.BackUpStopDialog;
import cn.cdut.a6pan.Dialog.MyBottemChooseDialog;
import cn.cdut.a6pan.Dialog.MyBottemDialog;
import cn.cdut.a6pan.Dialog.MyBottemFileChooseDialog;
import cn.cdut.a6pan.R;
import cn.cdut.a6pan.Utils.Code;
import cn.cdut.a6pan.Utils.DataBaseHelper;
import cn.cdut.a6pan.Utils.HttpHelper;
import cn.cdut.a6pan.databinding.FileFragmentBinding;
import cn.refactor.lib.colordialog.PromptDialog;

public class FileFragment extends Fragment implements SwipeRefreshLayout.OnRefreshListener, MyPagedListAdapter.FileChooseListener,MyBottemFileChooseDialog.OnCenterItemClickListener,MyBottemDialog.OnCenterItemClickListener,MyBottemChooseDialog.OnCenterItemClickListener {

    private FileViewModel mViewModel;

    private FileFragmentBinding binding;

    private MyPagedListAdapter adapter;

    private MyBottemChooseDialog myBottemChooseDialog;
    private MyBottemDialog myBottemDialog;
    private MyBottemFileChooseDialog myBottemFileChooseDialog;
    private BackUpStopDialog backUpStopDialog;
    private FileDao fileDao;
    private FileDataBase fileDataBase;
    private int preFileOp=0;

    private LiveData<List<File>> download;


    private Handler handler=new Handler(){
        @Override
        public void handleMessage(@NonNull Message msg) {
            Gson gson=new Gson();
            switch (msg.what){
                case Code.FILE_DELETE_SUCCESS:{
                    String response= (String) msg.obj;
                    final ResultSendMessage res = gson.fromJson(response, ResultSendMessage.class);
                    if (res.getSuccess()){
                        binding.swipeLayout.setRefreshing(true);
                        onRefresh();
                        Toast.makeText(getActivity(), getResources().getString(R.string.delete_success), Toast.LENGTH_SHORT).show();
                    }
                    else {
                        Toast.makeText(getActivity(), getResources().getString(R.string.delete_failed), Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.FILE_DELETE_FAILED:{
                    Toast.makeText(getActivity(), getResources().getString(R.string.delete_failed), Toast.LENGTH_SHORT).show();
                    break;
                }
                case Code.FOLDER_CREATE_SUCCESS:{
                    String resp= (String) msg.obj;
                    Log.d(TAG,resp);
                    ResultFileSingle res=gson.fromJson(resp,ResultFileSingle.class);
                    if (res.getSuccess()){
                        binding.swipeLayout.setRefreshing(true);
                        onRefresh();
                        Toast.makeText(getActivity(),getString(R.string.folder_create_success),Toast.LENGTH_SHORT).show();
                    }
                    else {
                        Toast.makeText(getActivity(),res.getMessage(),Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.FOLDER_CREATE_FAILED:{
                    String resp= (String) msg.obj;
                    Log.d(TAG,resp);
                    Toast.makeText(getActivity(),getString(R.string.folder_create_failed),Toast.LENGTH_SHORT).show();
                    break;
                }
                case Code.FILE_MOVE_SUCCESS:{
                    String resp= (String) msg.obj;
                    Result res=gson.fromJson(resp,Result.class);
                    if (res.getSuccess()){
                        binding.swipeLayout.setRefreshing(true);
                        onRefresh();
                        Toast.makeText(getActivity(),getString(R.string.file_move_success),Toast.LENGTH_SHORT).show();
                    }
                    else {
                        Toast.makeText(getActivity(),res.getMessage(),Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.FILE_MOVE_FAILED:{
                    Toast.makeText(getActivity(),getString(R.string.file_move_failed),Toast.LENGTH_SHORT).show();
                    break;
                }
                case Code.FILE_COPY_SUCCESS:{
                    String resp= (String) msg.obj;
                    Result res=gson.fromJson(resp,Result.class);
                    if (res.getSuccess()){
                        binding.swipeLayout.setRefreshing(true);
                        onRefresh();
                        Toast.makeText(getActivity(),getString(R.string.file_copy_success),Toast.LENGTH_SHORT).show();
                    }
                    else {
                        Toast.makeText(getActivity(),res.getMessage(),Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.FILE_COPY_FAILED:{
                    Toast.makeText(getActivity(),getString(R.string.file_copy_failed),Toast.LENGTH_SHORT).show();
                    break;
                }
                case Code.FILE_DOWNLOAD_ADDR_SUCCESS:{
                    ResultFileSingle res;
                    String resp= (String) msg.obj;
                    res=gson.fromJson(resp,ResultFileSingle.class);
                    if (res.getSuccess()){
                        Toast.makeText(getActivity(),getString(R.string.file_download_addr_success),Toast.LENGTH_SHORT).show();
                        downloadByURL(res.getResult().getDownloadAddress(),res.getResult());
                    }
                    else {
                        Toast.makeText(getActivity(),res.getMessage(),Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.FILE_DOWNLOAD_ADDR_FAILED:{
                    Toast.makeText(getActivity(),getString(R.string.file_download_addr_failed),Toast.LENGTH_SHORT).show();
                    break;
                }
                case Code.FILE_RENAME_SUCCESS:{
                    String resp= (String) msg.obj;
                    Result res=gson.fromJson(resp,Result.class);
                    if (res.getSuccess()){
                        binding.swipeLayout.setRefreshing(true);
                        onRefresh();
                        Toast.makeText(getActivity(),getString(R.string.file_rename_success),Toast.LENGTH_SHORT).show();
                    }
                    else {
                        Toast.makeText(getActivity(),res.getMessage(),Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.FILE_RENAME_FAILED:{
                    Toast.makeText(getActivity(),getString(R.string.file_rename_failed),Toast.LENGTH_SHORT).show();
                    break;
                }
            }
        }
    };

    private final static String TAG = "File_Frag";

    private HashSet<Integer> set;

    public static FileFragment newInstance() {
        return new FileFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        fileDataBase= FileDataBase.getDataBase(getContext());
        fileDao=fileDataBase.getFileDao();
        download=fileDao.getAllFiles();
        download.observe(this, new Observer<List<File>>() {
            @Override
            public void onChanged(List<File> list) {
                if (list==null||list.isEmpty())
                    return;
                Log.d(TAG,list.get(0).getName()+", length: "+list.size());
            }
        });
        backUpStopDialog=new BackUpStopDialog(getContext(),getActivity(),R.layout.dialog_recycle,new int[]{R.id.clearRecycle,R.id.recycleCancel});
        myBottemDialog = new MyBottemDialog(getContext(), R.layout.dialog_bottem, new int[]{R.id.file_download, R.id.file_delete, R.id.file_opration_more});
        myBottemChooseDialog = new MyBottemChooseDialog(getContext(), R.layout.dialog_bottem_choose, new int[]{R.id.fileMove, R.id.file_copy, R.id.file_cancel});
        myBottemDialog.setOnCenterItemClickListener(this);
        myBottemFileChooseDialog = new MyBottemFileChooseDialog(getContext(), R.layout.dialog_bottem_file_choose, new int[]{R.id.fileChooseCancel,R.id.fileChooseConfirm1});
        myBottemFileChooseDialog.setOnCenterItemClickListener(this);
        myBottemChooseDialog.setOnCenterItemClickListener(this);
        mViewModel=ViewModelProviders.of(getActivity()).get(FileViewModel.class);
        mViewModel.setCtx(getContext());
        mViewModel.getIsCloseDialog().observe(getActivity(), new Observer<Boolean>() {
            @Override
            public void onChanged(Boolean aBoolean) {
                if (aBoolean&&adapter!=null) {
                    if (adapter.getCurrentList()!=null) {
                        for (File file : adapter.getCurrentList())
                            file.setChecked(false);
                    }
                    myBottemDialog.dismiss();
                }
            }
        });
        binding = DataBindingUtil.inflate(inflater, R.layout.file_fragment, container, false);
        LinearLayoutManager manager = new LinearLayoutManager(getContext());
        binding.recyclerList.setLayoutManager(manager);
        adapter = new MyPagedListAdapter(new DiffUtil.ItemCallback<File>() {
            @Override
            public boolean areItemsTheSame(@NonNull File oldItem, @NonNull File newItem) {
                return oldItem.getIdentity().equals(newItem.getIdentity());
            }

            @Override
            public boolean areContentsTheSame(@NonNull File oldItem, @NonNull File newItem) {
                return oldItem.getIdentity().equals(newItem.getIdentity());
            }
        });
        adapter.setFileViewModel(mViewModel);
        binding.recyclerList.setAdapter(adapter);
        binding.swipeLayout.setOnRefreshListener(this);
        adapter.setListener(this);

        binding.swipeLayout.setRefreshing(true);
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                binding.swipeLayout.setRefreshing(true);
                loadData();
            }
        }, 1000);

        binding.back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String path=mViewModel.getPath().getValue();
                String pre=mViewModel.getPrePath(path);
                Log.d(TAG,"change.... "+path+" "+pre);
                if (pre!=null)
                    mViewModel.getPath().setValue(pre);
            }
        });

        binding.sort.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                PopupMenu popupMenu=new PopupMenu(getActivity(),view);
                popupMenu.inflate(R.menu.sort_menu);
                popupMenu.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                    @Override
                    public boolean onMenuItemClick(MenuItem menuItem) {
                        switch (menuItem.getItemId()){
                            case R.id.name_asc:{
                                mViewModel.setOrderBy(2);
                                break;
                            }
                            case R.id.name_desc:{
                                mViewModel.setOrderBy(1);
                                break;
                            }
                            case R.id.date_asc:{
                                mViewModel.setOrderBy(3);
                                break;
                            }
                            case R.id.date_desc:{
                                mViewModel.setOrderBy(4);
                                break;
                            }
                        }
                        return false;
                    }
                });
                popupMenu.show();
            }
        });
        binding.newFolder.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final MyAlertInputDialog myAlertInputDialog = new MyAlertInputDialog(getContext()).builder()
                        .setTitle("请输入文件夹名")
                        .setEditText("...");
                myAlertInputDialog.setPositiveButton("添加", new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        String newpath=myAlertInputDialog.getResult();
                        HashMap<String,String>params=new HashMap<>();
                        params.put("path",mViewModel.getPath().getValue());
                        params.put("name",newpath);
                        HttpHelper.postWithJson(getString(R.string.folder_create_api),new HashMap(),params,handler,Code.FOLDER_CREATE_SUCCESS,Code.FOLDER_CREATE_FAILED);
                        myAlertInputDialog.dismiss();
                    }
                }).setNegativeButton("取消", new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        myAlertInputDialog.dismiss();
                    }
                });
                myAlertInputDialog.getPositiveButton().setBackgroundColor(getResources().getColor(R.color.colorPrimary));
                myAlertInputDialog.show();
            }
        });
        binding.uploadFile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openWarning("文件上传");
//                Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
//                intent.setType("*/*");//设置类型，这里是任意类型
//                intent.addCategory(Intent.CATEGORY_OPENABLE);
//                startActivityForResult(Intent.createChooser(intent, "Select a File to Upload"), 1);
            }
        });
        binding.backupStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                backUpStopDialog.show();
            }
        });
        return binding.getRoot();
    }



    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(getActivity()).get(FileViewModel.class);
        mViewModel.getPath().observe(this, new Observer<String>() {
            @Override
            public void onChanged(String s) {
                binding.swipeLayout.setRefreshing(true);
                Log.d(TAG,"cur :"+s);
                adapter.submitList(null);
                if (s.equals("/")){
                    binding.back.setVisibility(View.GONE);

                    new Handler().postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            binding.recyclerList.setPadding(0,0,0,dp2px(getContext(),190));
                            binding.backupStop.setVisibility(View.VISIBLE);
                        }
                    }, 500);
                }
                else {

                    binding.back.setVisibility(View.VISIBLE);

                    new Handler().postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            binding.recyclerList.setPadding(0,0,0,dp2px(getContext(),130));
                            binding.backupStop.setVisibility(View.GONE);
                        }
                    }, 100);
                }
                mViewModel.getRefreshLiveData().observe(getActivity(), new Observer<PagedList<File>>() {
                    @Override
                    public void onChanged(@Nullable PagedList<File> listBeans) {
                        binding.swipeLayout.setRefreshing(false);
                        adapter.submitList(listBeans);
                        mViewModel.getChecked().setValue(new HashSet<Integer>());
                    }
                });
            }
        });
        mViewModel.getChecked().observe(getActivity(), new Observer<HashSet<Integer>>() {
            @Override
            public void onChanged(HashSet<Integer> integers) {
                if (integers.isEmpty())
                    mViewModel.getIsCloseDialog().setValue(true);
            }
        });

    }


    private void loadData() {
        mViewModel.getLiveData().observe(this, new Observer<PagedList<File>>() {
            @Override
            public void onChanged(@Nullable PagedList<File> resultsBeans) {
                binding.swipeLayout.setRefreshing(false);
                adapter.submitList(resultsBeans);
                mViewModel.getChecked().setValue(new HashSet<Integer>());
            }
        });
    }


    @Override
    public void onRefresh() {
        adapter.submitList(null);
        mViewModel.getRefreshLiveData().observe(this, new Observer<PagedList<File>>() {
            @Override
            public void onChanged(@Nullable PagedList<File> listBeans) {
                binding.swipeLayout.setRefreshing(false);
                adapter.submitList(listBeans);
                mViewModel.getChecked().setValue(new HashSet<Integer>());
            }
        });
    }

    @Override
    public void onCheckChanged(Boolean b, Integer i) {
        HashSet<Integer> set=mViewModel.getChecked().getValue();
        HashSet<Integer> nset=new HashSet();
        adapter.getCurrentList().get(i).setChecked(b);
        nset.addAll(set);
        if (b)
            nset.add(i);
        else
            nset.remove(i);
        if (b)
            myBottemDialog.show();
        mViewModel.getChecked().setValue(nset);
    }

    @Override
    public void onLongClick(final File file) {//长按重命名
        final MyAlertInputDialog myAlertInputDialog = new MyAlertInputDialog(getContext()).builder()
                .setTitle("请输入新的文件名")
                .setEditText("...");
        myAlertInputDialog.setPositiveButton("确定", new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String newpath=myAlertInputDialog.getResult();
                HashMap<String,String>params=new HashMap<>();
                params.put("path",file.getPath());
                params.put("name",newpath);
                HttpHelper.postWithJson(getString(R.string.file_rename_api),new HashMap(),params,handler,Code.FILE_RENAME_SUCCESS,Code.FILE_RENAME_FAILED);
                myAlertInputDialog.dismiss();
            }
        }).setNegativeButton("取消", new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                myAlertInputDialog.dismiss();
            }
        });
        myAlertInputDialog.getPositiveButton().setBackgroundColor(getResources().getColor(R.color.colorPrimary));
        myAlertInputDialog.show();
    }


    public void deleteFile(){
        Log.e(TAG, "deleting file...");
        final HashMap params=new HashMap<String,Object>();
        List<HashMap> list=new ArrayList<>();
        Iterator iterator=mViewModel.getChecked().getValue().iterator();
        while (iterator.hasNext()){
            HashMap cur=new HashMap();
            cur.put("path",adapter.getCurrentList().get((Integer) iterator.next()).getPath());
            list.add(cur);
        }

        params.put("source",list);
        HashMap<String, String> header = new HashMap<>();
        HttpHelper.postWithJson(getString(R.string.file_delete_api),header,params,handler, Code.FILE_DELETE_SUCCESS,Code.FILE_DELETE_FAILED);
    }


    public void moveFile(){
        List<HashMap> source=new ArrayList<>();
        Iterator iterator=mViewModel.getChecked().getValue().iterator();
        while (iterator.hasNext()){
            HashMap<String,String> cur=new HashMap<>();
            cur.put("path",adapter.getCurrentList().get((Integer) iterator.next()).getPath());
            source.add(cur);
        }
        HashMap<String,Object> params=new HashMap<>();
        HashMap<String,String>des=new HashMap<>();
        params.put("source",source);
        des.put("path",myBottemFileChooseDialog.getPath());
        params.put("destination",des);
        HttpHelper.postWithJson(getString(R.string.file_move_api),new HashMap(),params,handler,Code.FILE_MOVE_SUCCESS,Code.FILE_MOVE_FAILED);
    }

    public void copyFile() {
        List<HashMap> source=new ArrayList<>();
        Iterator iterator=mViewModel.getChecked().getValue().iterator();
        while (iterator.hasNext()){
            HashMap<String,String> cur=new HashMap<>();
            cur.put("path",adapter.getCurrentList().get((Integer) iterator.next()).getPath());
            source.add(cur);
        }
        HashMap<String,Object> params=new HashMap<>();
        HashMap<String,String>des=new HashMap<>();
        params.put("source",source);
        des.put("path",myBottemFileChooseDialog.getPath());
        params.put("destination",des);
        HttpHelper.postWithJson(getString(R.string.file_copy_api),new HashMap(),params,handler,Code.FILE_COPY_SUCCESS,Code.FILE_COPY_FAILED);
    }

    public void download(List<File> list){
        myBottemDialog.dismiss();
        for (File file:list)
            dowoloadSingle(file);
        if (list.isEmpty()){
            Toast.makeText(getContext(),"仅支持下载文件",Toast.LENGTH_SHORT).show();
        }
    }

    public void dowoloadSingle(File file){
        HashMap<String,String>params=new HashMap<>();
        params.put("path",file.getPath());
        HttpHelper.postWithJson(getString(R.string.file_download_api),new HashMap(),params,handler,Code.FILE_DOWNLOAD_ADDR_SUCCESS,Code.FILE_DOWNLOAD_ADDR_FAILED);
    }

    public void downloadByURL(final String downloadAddress,File file) {
        requestPermission();
        try {
            DownloadManager.Request request=new DownloadManager.Request(Uri.parse(downloadAddress));
            request.setDestinationInExternalPublicDir(getString(R.string.download_folder),file.getName());
            request.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
            DownloadManager downloadManager= (DownloadManager) getContext().getSystemService(Context.DOWNLOAD_SERVICE);
            request.setTitle(file.getName()+"下载中...");
            file.setId(downloadManager.enqueue(request));
            Log.d(TAG,"下载id: "+file.getId().toString());
            new InsertAsyncTask(fileDao).execute(file);
        }
        catch (SecurityException e){
            Toast.makeText(getContext(),e.getMessage(),Toast.LENGTH_SHORT).show();
        }
        catch (NullPointerException e){//null 代表无sd卡
            Toast.makeText(getContext(),e.getMessage(),Toast.LENGTH_SHORT).show();
        }

    }

    private void requestPermission(){
        if (ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.WRITE_EXTERNAL_STORAGE)!= PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(getActivity(),new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,Manifest.permission.READ_PHONE_STATE},0);
        }
    }

    public void openWarning(String title){
        new PromptDialog(getContext())
                .setDialogType(PromptDialog.DIALOG_TYPE_WARNING)
                .setAnimationEnable(true)
                .setTitleText(title)
                .setContentText("             该功能暂不可用")
                .setPositiveListener("确定", new PromptDialog.OnPositiveListener() {
                    @Override
                    public void onClick(PromptDialog dialog) {
                        dialog.dismiss();
                    }
                }).show();
    }

    @Override
    public void OnCenterItemClick(MyBottemChooseDialog dialog, View view) {
        preFileOp=view.getId();
        switch (view.getId()) {
            case R.id.file_cancel: {
                myBottemChooseDialog.dismiss();
                break;
            }
            case R.id.fileMove: {
                myBottemFileChooseDialog.show();
//                openWarning(getString(R.string.file_move));
                Log.e(TAG, "moving");
                break;
            }
            case R.id.file_copy: {
                myBottemFileChooseDialog.show();
                break;
            }
            case R.id.fileChooseCancel: {
                myBottemFileChooseDialog.dismiss();
                break;
            }

        }
    }



    @Override
    public void OnCenterItemClick(MyBottemDialog dialog, View view) {
        switch (view.getId()){
            case R.id.file_delete:{
                deleteFile();
                myBottemDialog.dismiss();
                break;
            }
            case R.id.file_download:{
                List<File>list=new ArrayList<>();
                HashSet<Integer> set=mViewModel.getChecked().getValue();
                for (Integer i:set)
                    if (!adapter.getCurrentList().get(i).getDirectory()){
                        list.add(adapter.getCurrentList().get(i));
                    }
                download(list);
                break;
            }
            case R.id.file_opration_more:{
                myBottemChooseDialog.show();
                break;
            }
        }
    }
    @Override
    public void OnCenterItemClick(MyBottemFileChooseDialog dialog, View view) {

        switch (view.getId()){
            case R.id.fileChooseCancel:{
                Log.d(TAG,"取消");
                dialog.dismiss();
                break;
            }
            case R.id.fileChooseConfirm1:{
                Log.d(TAG,"确定");
                if (preFileOp==R.id.fileMove)
                    moveFile();
                else  if (preFileOp==R.id.file_copy)
                    copyFile();
                dialog.dismiss();
                break;
            }
        }
    }



    @Override
    public void clickItem(View view, int position, File file) {
        Log.d(TAG,"click file"+file.getParent());
    }




    public int dp2px(Context context, float dpVal) {//dp转px
        if (context!=null)
            return (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP,
                dpVal, context.getResources().getDisplayMetrics());
        return 0;
    }

    static class InsertAsyncTask extends AsyncTask<File,Void,Void>{
        private FileDao fileDao;

        public InsertAsyncTask(FileDao fileDao){
            this.fileDao=fileDao;
        }

        @Override
        protected Void doInBackground(File... files) {
            fileDao.insert(files);
            Log.d(TAG,"insert id: "+files[0].getId().toString());
            return null;
        }
    }

    static class QueryAsyncTask extends AsyncTask<File,Void,Void>{


        private FileDao fileDao;

        public QueryAsyncTask(FileDao fileDao){
            this.fileDao=fileDao;
        }
        @Override
        protected Void doInBackground(File... files) {

            return null;
        }
    }
    @Override
    public void onStop() {
        super.onStop();
        mViewModel.getChecked().setValue(new HashSet<Integer>());
    }
}
