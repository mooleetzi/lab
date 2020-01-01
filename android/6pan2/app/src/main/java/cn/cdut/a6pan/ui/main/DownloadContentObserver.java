package cn.cdut.a6pan.ui.main;

import android.database.ContentObserver;
import android.os.Handler;

public class DownloadContentObserver extends ContentObserver {
        public DownloadContentObserver(Handler handler) {
            super(handler);
        }

        @Override
        public void onChange(boolean selfChange) {

        }
}
