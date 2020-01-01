package cn.cdut.sixpan.Utils;

import android.util.Log;
import java.io.IOException;
public abstract class HttpCallbackListener {

    public abstract void onFinish(String response);//正常访问之后进行的操作

    public void onError(Exception e) {//出错后进行的操作
        if (e instanceof IOException) {
            Log.e("网络错误", e.getMessage());
            return;
        }
    }
}
