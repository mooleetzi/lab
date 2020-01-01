package cn.cdut.a6pan.ui.main;

import androidx.databinding.DataBindingUtil;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.room.Room;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.List;

import cn.cdut.a6pan.Bean.File;
import cn.cdut.a6pan.DAO.FileDao;
import cn.cdut.a6pan.DataBase.FileDataBase;
import cn.cdut.a6pan.R;
import cn.cdut.a6pan.databinding.FragmentDownloadBinding;

public class DownloadFragment extends Fragment {

    private FragmentDownloadBinding binding;

    private FileDao fileDao;
    private FileDataBase fileDataBase;
    private LiveData<List<File>> allFiles;
    private MyDownloadAdapter adapter;
//    private LiveData<List<File>> doneFiles;
//    private LiveData<List<File>>  doingFiles;
//    private MyDownloadAdapter doneAdapter;
//    private MyDownloadAdapter doingAdapter;

    static String TAG="DOWNLOAD_FARG";
    public static DownloadFragment newInstance() {
        return new DownloadFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        fileDataBase= FileDataBase.getDataBase(getContext());
        fileDao=fileDataBase.getFileDao();
        allFiles=fileDao.getAllFiles();
        binding= DataBindingUtil.inflate(inflater,R.layout.fragment_download,container,false);
        binding.downloadRecyclerView.setLayoutManager(new LinearLayoutManager(getContext()));


        allFiles.observe(this, new Observer<List<File>>() {
            @Override
            public void onChanged(List<File> list) {
                adapter=new MyDownloadAdapter(list);
                binding.downloadRecyclerView.setAdapter(adapter);
            }
        });

        return binding.getRoot();
//        return inflater.inflate(R.layout.fragment_download, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        // TODO: Use the ViewModel
    }

}
