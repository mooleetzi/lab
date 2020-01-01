package cn.cdut.a6pan.ui.main;

import android.app.Application;
import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.lifecycle.AndroidViewModel;
import androidx.lifecycle.LifecycleOwner;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProviders;
import androidx.paging.DataSource;
import androidx.paging.LivePagedListBuilder;
import androidx.paging.PageKeyedDataSource;
import androidx.paging.PagedList;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import com.google.gson.Gson;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;

import cn.cdut.a6pan.Bean.File;
import cn.cdut.a6pan.Bean.ResultFilePage;
import cn.cdut.a6pan.MainActivity;
import cn.cdut.a6pan.Utils.HttpCallbackListener;
import cn.cdut.a6pan.Utils.HttpUtils;
import okhttp3.MediaType;
import okhttp3.RequestBody;


public class FileViewModel extends ViewModel {
    private static final int NUM_PER_PAGE = 10;
    //第一页
    private static final int PAGE_FIRST = 1;
    //当前页码数
    private int mPage = PAGE_FIRST;
    //列表数据

    private final static String TAG="File_View_model";


    private LiveData<PagedList<File>> mLiveData;
    private LiveData<PagedList<File>> mRecycleBinData;



    private MutableLiveData<String> path;

    private MutableLiveData<Boolean> iscloseDialog;

    private HashMap<String,String>pre;

    private PageKeyedDataSource pageKeyedDataSource;


    private PageKeyedDataSource recycleBinDataSource;

    private Integer orderBy=0;

    private MutableLiveData<HashSet<Integer>> checked;


    private Context ctx;


    public void setCtx(Context ctx) {
        this.ctx = ctx;
    }

    //用来存储网络返回的信息类
    private ResultFilePage resultBean;


    public MutableLiveData<HashSet<Integer>> getChecked(){
        if (checked==null){
            checked=new MutableLiveData<>();
            checked.setValue(new HashSet<Integer>());
        }
        return checked;
    }



    public void setOrderBy(Integer i){
        orderBy=i;
    }


    public LiveData<PagedList<File>> getmRecycleBinData(){
        if (mRecycleBinData==null){
            initRecycleBinList();
        }
        return mRecycleBinData;
    }

    public LiveData<PagedList<File>> getLiveData() {
        if (mLiveData==null){
            initPagedList();
        }
            return mLiveData;
    }

    public MutableLiveData<String> getPath(){
        if (path==null){
            pre=new HashMap<>();
            path=new MutableLiveData<>();
            path.setValue("/");
        }
        return path;
    }

    public String getPrePath(String cur){
        return pre.get(cur);
    }

    public void putPrePath(String cur,String pre1){
        pre.put(cur,pre1);
    }


    private PageKeyedDataSource getRecycleBinDataSource(){
        if (recycleBinDataSource==null){
            recycleBinDataSource=new PageKeyedDataSource<Integer,File>() {
                List<File> list = new ArrayList<>();
                @Override
                public void loadInitial(@NonNull final LoadInitialParams<Integer> params, @NonNull final LoadInitialCallback<Integer, File> callback) {
                    HashMap<String,String> header=new HashMap<>();
                    HashMap<String,String> body=new HashMap<>();
                    final Gson gson=new Gson();
                    body.put("pageSize",String.valueOf(NUM_PER_PAGE));
                    header.put("Content-Type","application/json; charset=UTF-8");
                    RequestBody requestBody=RequestBody.create(MediaType.parse("application/json"),gson.toJson(body));
                    HttpUtils.getInstance().post("/trash/page", header, requestBody, new HttpCallbackListener() {
                        @Override
                        public void onFinish(String response) {
                            resultBean=gson.fromJson(response,ResultFilePage.class);
                            Log.d(TAG,"init : "+response);
                            if (resultBean.getSuccess()) {
                                list=resultBean.getResult().getList();
                                if(list==null)
                                    list=new ArrayList();
                                Integer next=null;
                                if (resultBean.getResult().getPage()!=resultBean.getResult().getTotalPage())
                                    next=resultBean.getResult().getPage()+1;
                                callback.onResult(list, 0,list.size(),null, next);
                            }
                            else {
                                Looper.prepare();
                                Toast.makeText(ctx,resultBean.getMessage(),Toast.LENGTH_SHORT).show();
                                Looper.loop();
                            }
                        }

                        @Override
                        public void onError(Exception e) {
                            Looper.prepare();
                            Toast.makeText(ctx,"检查网络状况",Toast.LENGTH_SHORT).show();
                            Looper.loop();
                            super.onError(e);
                        }
                    });
                }

                @Override
                public void loadBefore(@NonNull LoadParams<Integer> params, @NonNull LoadCallback<Integer, File> callback) {

                }

                @Override
                public void loadAfter(@NonNull LoadParams<Integer> params, @NonNull final LoadCallback<Integer, File> callback) {
                    Integer page=params.key;
                    Integer size=params.requestedLoadSize;
                    HashMap<String,String> header=new HashMap<>();
                    HashMap<String,String> body=new HashMap<>();
                    final Gson gson=new Gson();
                    body.put("pageSize",size.toString());
                    body.put("page",page.toString());
                    header.put("Content-Type","application/json; charset=UTF-8");
                    RequestBody requestBody=RequestBody.create(MediaType.parse("application/json"),gson.toJson(body));
                    HttpUtils.getInstance().post("/trash/page", header, requestBody, new HttpCallbackListener() {
                        @Override
                        public void onFinish(String response) {
                            resultBean=gson.fromJson(response,ResultFilePage.class);
                            Log.d(TAG,"after: "+response);
                            if (resultBean.getSuccess()) {
                                list=resultBean.getResult().getList();
                                if(list==null)
                                    list=new ArrayList();
                                Integer next=null;
                                if (resultBean.getResult().getPage()!=resultBean.getResult().getTotalPage())
                                    next=resultBean.getResult().getPage()+1;
                                callback.onResult(list, resultBean.getResult().getPage()+1);
                            }
                            else {
                                Looper.prepare();
                                Toast.makeText(ctx,resultBean.getMessage(),Toast.LENGTH_SHORT).show();
                                Looper.loop();
                            }
                        }

                        @Override
                        public void onError(Exception e) {
                            Looper.prepare();
                            Toast.makeText(ctx,"检查网络状况",Toast.LENGTH_SHORT).show();
                            Looper.loop();
                            super.onError(e);
                        }
                    });
                }
            };
        }
        return recycleBinDataSource;
    }


    private void initRecycleBinList(){
        mRecycleBinData=new LivePagedListBuilder(new FilePageDataSourceFactory(getRecycleBinDataSource()),NUM_PER_PAGE).build();
    }



    private PageKeyedDataSource getPageKeyedDataSource(){
        if (pageKeyedDataSource==null){
            pageKeyedDataSource = new PageKeyedDataSource<Integer, File>() {
                List<File> list = new ArrayList<>();
                @Override
                public void loadInitial(@NonNull final LoadInitialParams<Integer> params, @NonNull final LoadInitialCallback<Integer, File> callback) {
                    HashMap<String,String> header=new HashMap<>();
                    HashMap<String,String> body=new HashMap<>();
                    final Gson gson=new Gson();
                    body.put("pageSize",String.valueOf(NUM_PER_PAGE));
                    body.put("orderBy",orderBy.toString());
                    body.put("path",getPath().getValue());
                    header.put("Content-Type","application/json; charset=UTF-8");
                    RequestBody requestBody=RequestBody.create(MediaType.parse("application/json"),gson.toJson(body));
                    HttpUtils.getInstance().post("/files/page", header, requestBody, new HttpCallbackListener() {
                        @Override
                        public void onFinish(String response) {
                            resultBean=gson.fromJson(response,ResultFilePage.class);
                            Log.d(TAG,"init : "+response);
                            if (resultBean.getSuccess()) {
                                list=resultBean.getResult().getList();
                                if(list==null)
                                    list=new ArrayList();
                                Integer next=null;
                                if (resultBean.getResult().getPage()!=resultBean.getResult().getTotalPage())
                                    next=resultBean.getResult().getPage()+1;
                                callback.onResult(list, 0,list.size(),null, next);
                            }
                            else {
                                Looper.prepare();
                                Toast.makeText(ctx,resultBean.getMessage(),Toast.LENGTH_SHORT).show();
                                Looper.loop();
                            }
                        }

                        @Override
                        public void onError(Exception e) {
                            Looper.prepare();
                            Toast.makeText(ctx,"检查网络状况",Toast.LENGTH_SHORT).show();
                            Looper.loop();
                            super.onError(e);
                        }
                    });
                }

                @Override
                public void loadBefore(@NonNull LoadParams<Integer> params, @NonNull LoadCallback<Integer, File> callback) {

                }

                @Override
                public void loadAfter(@NonNull LoadParams<Integer> params, @NonNull final LoadCallback<Integer, File> callback) {
                    Integer page=params.key;
                    Integer size=params.requestedLoadSize;
                    HashMap<String,String> header=new HashMap<>();
                    HashMap<String,String> body=new HashMap<>();
                    final Gson gson=new Gson();
                    body.put("pageSize",size.toString());
                    body.put("orderBy",orderBy.toString());
                    body.put("page",page.toString());
                    body.put("path",getPath().getValue());
                    header.put("Content-Type","application/json; charset=UTF-8");
                    RequestBody requestBody=RequestBody.create(MediaType.parse("application/json"),gson.toJson(body));
                    HttpUtils.getInstance().post("/files/page", header, requestBody, new HttpCallbackListener() {
                        @Override
                        public void onFinish(String response) {
                            resultBean=gson.fromJson(response,ResultFilePage.class);
                            Log.d(TAG,"after: "+response);
                            if (resultBean.getSuccess()) {
                                list=resultBean.getResult().getList();
                                if(list==null)
                                    list=new ArrayList();
                                Integer next=null;
                                if (resultBean.getResult().getPage()!=resultBean.getResult().getTotalPage())
                                    next=resultBean.getResult().getPage()+1;
                                callback.onResult(list, resultBean.getResult().getPage()+1);
                            }
                            else {
                                Looper.prepare();
                                Toast.makeText(ctx,resultBean.getMessage(),Toast.LENGTH_SHORT).show();
                                Looper.loop();
                            }
                        }

                        @Override
                        public void onError(Exception e) {
                            Looper.prepare();
                            Toast.makeText(ctx,"检查网络状况",Toast.LENGTH_SHORT).show();
                            Looper.loop();
                            super.onError(e);
                        }
                    });
                }
            };
        }
        return pageKeyedDataSource;
    }

    public void initPagedList() {
        Log.d(TAG,"init");

        // 构建LiveData
//        mLiveData = new LivePagedListBuilder(new FilePageDataSourceFactory(pageKeyedDataSource)//自己定义
//                , new PagedList.Config.Builder().setPageSize(NUM_PER_PAGE)//每次加载的数据数量10
//                //距离本页数据几个时候开始加载下一页数据(例如现在加载10个数据,设置prefetchDistance为2,则滑到第八个数据时候开始加载下一页数据).
//                .setPrefetchDistance(1)
//                //这里设置是否设置PagedList中的占位符,如果设置为true,我们的数据数量必须固定,由于网络数据数量不固定,所以设置false.
//                .setEnablePlaceholders(false).setInitialLoadSizeHint(NUM_PER_PAGE)//10
//                .build()).build();

        mLiveData=new LivePagedListBuilder(new FilePageDataSourceFactory(getPageKeyedDataSource()),NUM_PER_PAGE).build();

    }

    public LiveData<PagedList<File>> getRefreshLiveData(){

        mLiveData = new LivePagedListBuilder(new FilePageDataSourceFactory(getPageKeyedDataSource()),NUM_PER_PAGE).build();
        return mLiveData;
    }
    public LiveData<PagedList<File>> getRecycleBinRefreshLiveData(){

        mRecycleBinData = new LivePagedListBuilder(new FilePageDataSourceFactory(getRecycleBinDataSource()),NUM_PER_PAGE).build();
        return mRecycleBinData;
    }

    public MutableLiveData<Boolean> getIsCloseDialog() {
        if (iscloseDialog==null){
            iscloseDialog=new MutableLiveData<>();
            iscloseDialog.setValue(true);
        }
        return iscloseDialog;
    }
}
