package cn.cdut.a6pan.ui.login;

import androidx.lifecycle.ViewModelProviders;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import cn.cdut.a6pan.R;

public class ModifyPwdByCode extends Fragment {

    private ModifyPwdByCodeViewModel mViewModel;

    public static ModifyPwdByCode newInstance() {
        return new ModifyPwdByCode();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.modify_pwd_by_code_fragment, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(ModifyPwdByCodeViewModel.class);
        // TODO: Use the ViewModel
    }

}
