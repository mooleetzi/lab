package cn.cdut.sixpan.Utils;

import android.app.Activity;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class ActivityManager {

    private static Map<String, Activity> activitys = new HashMap<String, Activity>();

    public static Map<String, Activity> getActivitys()
    {
        return activitys;
    }

    public static Activity getActivity(String key)
    {
        return activitys.get(key);
    }
    public static void addActivity(String key,Activity value)
    {
        if (activitys.containsKey(key))
            return;
        activitys.put(key, value);
    }

    public static void removeActivity(String key)
    {
        activitys.remove(key);
    }

    public static void removeAllActivity()
    {
        Iterator<Activity> iterActivity = activitys.values().iterator();
        while(iterActivity.hasNext()){
            iterActivity.next().finish();
        }
        activitys.clear();
    }
}