package cn.cdut.sixpan.Utils;

import android.util.Base64;
import android.util.Log;

import com.google.gson.*;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.Map;


import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSession;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;


import okhttp3.Response;

public class HttpUtils {

    private static class TrustAllCerts implements X509TrustManager {
        @Override
        public void checkClientTrusted(X509Certificate[] chain, String authType) throws CertificateException {}

        @Override
        public void checkServerTrusted(X509Certificate[] chain, String authType) throws CertificateException {}

        @Override
        public X509Certificate[] getAcceptedIssuers() {return new X509Certificate[0];}
    }

    private static class TrustAllHostnameVerifier implements HostnameVerifier {
        @Override
        public boolean verify(String hostname, SSLSession session) {
            return true;
        }
    }

    private static SSLSocketFactory createSSLSocketFactory() {
        SSLSocketFactory ssfFactory = null;

        try {
            SSLContext sc = SSLContext.getInstance("TLS");
            sc.init(null,  new TrustManager[] { new TrustAllCerts() }, new SecureRandom());

            ssfFactory = sc.getSocketFactory();
        } catch (Exception e) {
        }

        return ssfFactory;
    }


    private final static String BASE_URL="https://api.6pan.cn/v2";
    private final static String TAG="HttpUtils";
    private final static String USER_AGENT="QZCloud";
    private static HttpUtils instance=null;
    private OkHttpClient client=null;
    private String token=null;
    private Boolean login=false;
    private HttpUtils(){
        client=new OkHttpClient();
    }

    public static HttpUtils getInstance(){
        if (instance==null)
            instance=new HttpUtils();
        return instance;
    }
    public void sendRequestWithCallback(final RequestType method, final String address, final Map header,final RequestBody body, final HttpCallbackListener listener
    ) {
        final String url=BASE_URL+address;

        new Thread(new Runnable() {
            @Override
            public void run() {
                OkHttpClient.Builder mBuilder=new OkHttpClient.Builder();
                mBuilder.sslSocketFactory(createSSLSocketFactory());
                mBuilder.hostnameVerifier(new TrustAllHostnameVerifier());
                client=mBuilder.build();
                Request.Builder builder = new Request.Builder()
                        .url(url);
                if (getToken()!=null)
                    builder.addHeader("token",getToken());
                builder.addHeader("User-Agent","QZCloud");
                builder.addHeader("user-timestamp",Security.timeStamp());
                if (header!=null) {
                    for (Object key : header.keySet()) {
                        builder.addHeader(key.toString(), (String) header.get(key));
                    }
                }
                switch (method) {
                    case POST:
                        builder.post(body);
                        break;
                    case PUT:
                        builder.put(body);
                        break;
                    case DELETE:
                        builder.delete(body);
                        break;
                    default:
                        builder.get();
                        break;
                }

                Request request = builder.build();
                try {
                    //实际进行请求的代码
                    Log.i( TAG , url);
                    Response response = client.newCall(request).execute();
                    Log.e(TAG , response.toString());

                    if (response.header("qingzhen-token")!=null)
                        token=response.header("qingzhen-token");
                    if (token==null)
                        token=response.header("Qingzhen-token");
//                    Log.e(TAG,"qingzhen-token: "+response.header("qingzhen-token"));
//                    Log.e(TAG,"Qingzhen-Token: "+response.header("Qingzhen-Token"));
                    if (token == null) {
                        Log.i(TAG , "没有token使用默认token");
                    } else {
                        Log.i(TAG , "收到token：" + token);
                    }

                    String result = response.body().string();
                    if (result != null && listener != null) {
                        //当response的code大于200，小于300时，视作请求成功
                        Log.i(TAG,response.message());
                        if (response.isSuccessful()) {

                            listener.onFinish(result);
                        } else {
                            listener.onError(new ServerException(result));
                        }
                    }

                } catch (IOException e) {
                    if (listener != null) {
                        listener.onError(e);
                    }
                }
            }
        }).start();

    }

    public void post(final String address,final  Map header,RequestBody body,final HttpCallbackListener listener) {
        sendRequestWithCallback(RequestType.POST, address, header,body, listener);
    }

    public void get(String address, HttpCallbackListener listener) {
        sendRequestWithCallback(RequestType.GET, address, null,null, listener);
    }

    public void delete(String address,final  Map header, RequestBody body, HttpCallbackListener listener) {
        sendRequestWithCallback(RequestType.DELETE, address, header,body, listener);
    }

    public void put(String address, final  Map header, RequestBody body, HttpCallbackListener listener) {
        sendRequestWithCallback(RequestType.PUT, address, header,body, listener);
    }

    public String getConentMd5(){
        return "";
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token=token;
    }


    public Boolean getLogin() {
        return login;
    }

    public void setLogin(Boolean login) {
        this.login = login;
    }
}