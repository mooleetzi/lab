package cn.cdut.a6pan.ui.main;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import cn.cdut.a6pan.R;


public class MySettingListAdapter extends BaseAdapter {
    private static final String TAG="SETTING_ADAPTER";
    private LayoutInflater mInflater;
    private InnerClickListener listener;
    private List<HashMap> list;
    public MySettingListAdapter(Context ctx, List<HashMap> list){
        mInflater= LayoutInflater.from(ctx);
        this.list=list;
    }
    public MySettingListAdapter(Context ctx){
        mInflater= LayoutInflater.from(ctx);
    }


    @Override
    public int getCount() {
        if (list==null)
            return 0;
        return list.size();
    }

    @Override
    public Object getItem(int i) {
        if (list==null)
            return null;
        return list.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
         Holder holder = null;

        if (view == null) {
            holder = new Holder();
            view = mInflater.inflate(R.layout.setting_item, null);
            holder.rightIcon = view.findViewById(R.id.settingRightIcon);
            holder.letfIcon=view.findViewById(R.id.settingLeftIcon);
            holder.other=view.findViewById(R.id.settingOther);
            holder.setting=view.findViewById(R.id.setting);
            Map cur= (HashMap) getItem(i);
            if (cur.containsKey("rightIcon")) {
                holder.rightIcon.setVisibility(View.VISIBLE);
                holder.other.setVisibility(View.INVISIBLE);
                holder.rightIcon.setImageDrawable((Drawable) cur.get("rightIcon"));
            }
            if (cur.containsKey("other")){

                holder.other.setVisibility(View.VISIBLE);
                holder.rightIcon.setVisibility(View.INVISIBLE);
                holder.other.setText(cur.get("other").toString());
            }
            if (cur.containsKey("leftIcon")){

                holder.letfIcon.setImageDrawable((Drawable) cur.get("leftIcon"));
            }
            holder.setting.setText(cur.get("setting").toString());

            view.setTag(holder);
        }else{
            holder = (Holder) view.getTag();
        }

        return view;
    }
    public final class Holder{
        public TextView setting;
        public ImageView rightIcon;
        private ImageView letfIcon;
        public TextView other;
    }

    public void setListener(InnerClickListener listener) {
        this.listener = listener;
    }

    public interface InnerClickListener{
        void doit(View view);
    }
}
