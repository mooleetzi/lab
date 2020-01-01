package cn.cdut.sixpan.Dialog;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import androidx.annotation.NonNull;

import com.google.gson.Gson;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import cn.cdut.sixpan.Adapter.MyFileListDialogAdapter;
import cn.cdut.sixpan.Bean.File;
import cn.cdut.sixpan.Bean.ResultFilePage;
import cn.cdut.sixpan.R;
import cn.cdut.sixpan.Utils.HttpCallbackListener;
import cn.cdut.sixpan.Utils.HttpUtils;
import okhttp3.MediaType;
import okhttp3.RequestBody;

public class MyBottemFileChooseDialog extends Dialog implements View.OnClickListener{
    private Context context;//上下文
    private int layoutResID;//布局文件id
    private int[] listenedItem;//监听的控件id
    private ListView listView=null;
    private String path="/";
    private Handler handler=null;
    private MyFileListDialogAdapter adapter=null;
    private List<File> mdata=null;
    private static final String TAG="DIALOG";
    private  final static int GET_FILE_SUCCESS=1;
    private final static int GET_NEXT_FILE_SUCCESS=4;
    private final static int NO_MORE_DATA=2;
    private final static int DELETE_FILE_SUCCESS=3;
    private final static int GET_FILE_FROM_CACHE_SUCCESS=5;
    private final static int CHANGE_PATH=6;

    public MyBottemFileChooseDialog(Context context, int layoutResID, int[] listenedItem){
        super(context, R.style.MyBottemDialogChoose);//加载dialog的样式
        this.context = context;
        this.layoutResID = layoutResID;
        this.listenedItem = listenedItem;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //提前设置Dialog的一些样式
        Window dialogWindow = getWindow();
        dialogWindow.setGravity(Gravity.CENTER);//设置dialog显示居中
        //dialogWindow.setWindowAnimations();设置动画效果
        setContentView(layoutResID);
        WindowManager windowManager = ((Activity)context).getWindowManager();
        Display display = windowManager.getDefaultDisplay();
        listView=findViewById(R.id.dialogFileList);
        handler=new Handler(){
            @Override
            public void handleMessage(@NonNull Message msg) {
                switch (msg.what){
                    case GET_FILE_SUCCESS:{
                        Log.e(TAG,"succcess");
                        ResultFilePage cur= (ResultFilePage) msg.obj;
                        mdata=cur.getResult().getList();
                        adapter=new MyFileListDialogAdapter(getContext(),mdata);
                        listView.setAdapter(adapter);
                        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
                            @Override
                            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                                if (listener!=null)
                                    listener.clickItem(view,i,mdata.get(i));
                            }
                        });
                        break;
                    }
                }
            }
        };

        //从底部弹出
        Window window=getWindow();
        window.setGravity(Gravity.BOTTOM);
        window.setWindowAnimations(R.style.dialogBottemAnimation);
        window.getDecorView().setPadding(0, 0, 0, 300);
        WindowManager.LayoutParams lp = getWindow().getAttributes();
        getWindow().setAttributes(lp);
        lp.width = WindowManager.LayoutParams.MATCH_PARENT;
        lp.height = WindowManager.LayoutParams.WRAP_CONTENT;
        window.setAttributes(lp);
        setCanceledOnTouchOutside(true);//点击外部Dialog消失

        // Make us non-modal, so that others can receive touch events.
//        getWindow().setFlags(WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL, WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL);
//
        // ...but notify us that it happened.
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_WATCH_OUTSIDE_TOUCH, WindowManager.LayoutParams.FLAG_WATCH_OUTSIDE_TOUCH);

        //遍历控件id添加点击注册
        for(int id:listenedItem){
            findViewById(id).setOnClickListener(this);
        }
        getFile();
    }

    private void getFile(){

        final Map<String, String> params = new HashMap<>();
        params.put("path", path);
        final Gson gson = new Gson();
        RequestBody requestBody = RequestBody.create(MediaType.parse("application/json"), gson.toJson(params));
        Map<String, String> header = new HashMap<>();
        header.put("Content-Type", "application/json; charset=UTF-8");
        HttpUtils.getInstance().post("/files/list", header, requestBody, new HttpCallbackListener() {
            @Override
            public void onFinish(final String response) {
                final ResultFilePage res = gson.fromJson(response, ResultFilePage.class);

                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        Looper.prepare();
                        if (res.getSuccess()) {
                            if (res.getResult().getList() != null)
                            handler.sendMessage(handler.obtainMessage(GET_FILE_SUCCESS, res));
                        } else {
                            Toast.makeText(listView.getContext(), listView.getResources().getString(R.string.flush_failed), Toast.LENGTH_SHORT).show();
                        }
                        Looper.loop();
                    }
                }).start();

            }
            @Override
            public void onError(Exception e) {
                super.onError(e);
                Log.i(TAG, "出错了");
            }
        });
    }
    private OnCenterItemClickListener listener;
    public interface OnCenterItemClickListener {
        void OnCenterItemClick(MyBottemFileChooseDialog dialog, View view);
        void clickItem(View view,int position,File file);
    }
    public void setOnCenterItemClickListener(OnCenterItemClickListener listener) {
        this.listener = listener;
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        // If we've received a touch notification that the user has touched
        // outside the app, finish the activity.
        if (MotionEvent.ACTION_OUTSIDE == event.getAction()) {
//            dismiss();
            return true;
        }

        // Delegate everything else to Activity.
        return super.onTouchEvent(event);
    }

    @Override
    public void onClick(View v) {
        if (v.getId()==R.id.dialogFileList)
            return;
        listener.OnCenterItemClick(this,v);
    }
}

