package cn.cdut.sixpan.Utils;

import android.text.TextUtils;
import android.util.Base64;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Date;

public class Security {
    public static String base64(String src) throws NoSuchAlgorithmException {
        byte[] byteOfMessage=src.getBytes(StandardCharsets.UTF_8);
        MessageDigest md=MessageDigest.getInstance("MD5");
        byte[] thedigist=md.digest(byteOfMessage);
        String encodedString= (String) Base64.encodeToString(thedigist,Base64.DEFAULT);
        return encodedString;
    }
    public static String md5(String string)  {
        if (TextUtils.isEmpty(string)) {
            return "";
        }
        MessageDigest md5 = null;
        try {
            md5 = MessageDigest.getInstance("MD5");
            byte[] bytes = md5.digest(string.getBytes());
            StringBuilder result = new StringBuilder();
            for (byte b : bytes) {
                String temp = Integer.toHexString(b & 0xff);
                if (temp.length() == 1) {
                    temp = "0" + temp;
                }
                result.append(temp);
            }
            return result.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return "";

    }
    public static String timeStamp(){
        Date date=new Date();
        return String.valueOf(date.getTime());
    }
}
