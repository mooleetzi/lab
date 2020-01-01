package cn.cdut.a6pan.ui.main;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.google.gson.Gson;
import com.hb.dialog.myDialog.MyAlertInputDialog;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import cn.cdut.a6pan.Bean.Person;
import cn.cdut.a6pan.Bean.Result;
import cn.cdut.a6pan.Bean.ResultChangeName;
import cn.cdut.a6pan.LoginActivity;
import cn.cdut.a6pan.R;
import cn.cdut.a6pan.Utils.Code;
import cn.cdut.a6pan.Utils.HttpHelper;
import cn.cdut.a6pan.databinding.SettingFragmentBinding;
import cn.cdut.a6pan.ui.main.MySettingListAdapter;


public class SettingFragment extends Fragment implements View.OnClickListener {

    private final static String TAG = "USER_INFO";
    private MySettingListAdapter adapter = null;
    private ListView listView = null;
    private SettingFragmentBinding binding;
    private ImageView headIcon = null;
    private TextView username = null;
    private TextView phone = null;
    private List<HashMap> data = null;
    private MyHandler handler=new MyHandler(getContext());


    public static SettingFragment newInstance() {
        return new SettingFragment();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.setting_fragment, container, false);
        binding = DataBindingUtil.findBinding(view);
        headIcon = view.findViewById(R.id.headIcon);
        username = view.findViewById(R.id.username);
        phone = view.findViewById(R.id.phone);
        Person res = HttpHelper.getUser();
        if (res.getIcon().equals("default")) {
            headIcon.setImageDrawable(getResources().getDrawable(R.drawable.head_default));
        } else {//从网络加载数据

        }
        username.setText(res.getName());
        phone.setText(res.getPhone());
        listView = view.findViewById(R.id.settingsList);
        data = putData();
        adapter = new MySettingListAdapter(getActivity(), putData());
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                String name = (String) data.get(i).get("setting");
                if (name.equals("用户反馈")) {
                    feedBack();
                } else if (name.equals("隐私协议")) {
                    privacyPolicy();
                } else if (name.equals("关于")) {
                    about();
                } else if (name.equals("检查更新")) {
                    update();
                }
            }
        });
        return view;
    }


    public List<HashMap> putData() {
        List<HashMap> list = new ArrayList<>();
        HashMap<String, Object> res1 = new HashMap<>();
        HashMap<String, Object> res2 = new HashMap<>();
        HashMap<String, Object> res3 = new HashMap<>();
        HashMap<String, Object> res4 = new HashMap<>();
        res1.put("rightIcon", getResources().getDrawable(R.drawable.ic_arrow_forward_black_24dp));
        res1.put("setting", "用户反馈");
        list.add(res1);
        res2.put("rightIcon", getResources().getDrawable(R.drawable.ic_arrow_forward_black_24dp));
        res2.put("setting", "隐私协议");
        list.add(res2);
        res3.put("other", "v1.0.0");
        res3.put("setting", "关于");
        list.add(res3);
        res4.put("setting", "检查更新");
        list.add(res4);
        return list;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
//        if (context instanceof OnFragmentInteractionListener) {
//            mListener = (OnFragmentInteractionListener) context;
//        } else {
//            throw new RuntimeException(context.toString()
//                    + " must implement OnFragmentInteractionListener");
//        }
    }


    public void logout(View view) {

    }

    public void modifyPwd(View view) {
    }

    public void openDialog(View view) {
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.logout: {
                logout(view);
            }
        }
    }

    private void privacyPolicy() {
        Log.d(TAG,"隐私协议");
    }

    private void feedBack() {
        Log.d(TAG,"用户反馈");
 }

    private void update() {
    }

    private void about() {
    }

    private void modifyUsername() {
        final MyAlertInputDialog myAlertInputDialog = new MyAlertInputDialog(getContext()).builder()
                .setTitle("请输入更新用户名")
                .setEditText("");
        myAlertInputDialog.setPositiveButton("确认修改", new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String name=myAlertInputDialog.getResult();
                HashMap<String,String> params=new HashMap<>();
                params.put("name",name);
                HttpHelper.postWithJson(getString(R.string.name_change_api),new HashMap<>(),params,handler,Code.USERNAME_MODIFY_SUCCESS,Code.USERNAME_MODIFY_FAILED);
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

    static class MyHandler extends Handler{


        Context context;
        public MyHandler(Context context){
            this.context=context;
        }
        @Override
        public void handleMessage(@NonNull Message msg) {
            Gson gson=new Gson();
            String resp= (String) msg.obj;
            switch (msg.what){
                case Code.MODIFY_SUCCESS:{
                    Result res=gson.fromJson(resp,Result.class);
                    if (res.getSuccess()){
                        HttpHelper.setUser(null);
                        Intent intent=new Intent(context, LoginActivity.class);
                        Toast.makeText(context,"密码修改成功,正在跳转登录页", Toast.LENGTH_SHORT).show();
                        context.startActivity(intent);
                    }
                    else {
                        Toast.makeText(context,res.getMessage(), Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.MODIFY_FAILED:{
                    Toast.makeText(context,"密码修改失败", Toast.LENGTH_SHORT).show();
                    break;
                }
                case Code.USERNAME_MODIFY_SUCCESS:{
                    ResultChangeName res=gson.fromJson(resp,ResultChangeName.class);
                    if (res.getSuccess()){
                        Toast.makeText(context,"用户名修改成功", Toast.LENGTH_SHORT).show();
                    }
                    else {
                        Toast.makeText(context,res.getMessage(), Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case Code.USERNAME_MODIFY_FAILED:{
                    Toast.makeText(context,"用户名修改失败", Toast.LENGTH_SHORT).show();
                    break;
                }
            }
        }

    }

}
