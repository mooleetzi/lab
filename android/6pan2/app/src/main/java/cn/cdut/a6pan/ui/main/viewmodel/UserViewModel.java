package cn.cdut.a6pan.ui.main;

import android.app.Application;

import androidx.annotation.NonNull;
import androidx.lifecycle.AndroidViewModel;
import androidx.lifecycle.MutableLiveData;

import cn.cdut.a6pan.Bean.Person;
import cn.cdut.a6pan.Bean.User;

public class UserViewModel extends AndroidViewModel {

    private MutableLiveData<Person> user;
    public UserViewModel(@NonNull Application application) {
        super(application);
        user=new MutableLiveData<>();
        user.setValue(null);
    }
    public MutableLiveData<Person> getUser(){
        return user;
    }
    public void setUser(Person person){
        user.setValue(person);
    }

}
