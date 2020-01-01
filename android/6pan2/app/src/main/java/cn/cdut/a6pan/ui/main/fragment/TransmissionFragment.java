package cn.cdut.a6pan.ui.main;

import androidx.databinding.DataBindingUtil;
import androidx.lifecycle.ViewModelProviders;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.viewpager2.adapter.FragmentStateAdapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.google.android.material.tabs.TabLayout;
import com.google.android.material.tabs.TabLayoutMediator;

import cn.cdut.a6pan.R;
import cn.cdut.a6pan.databinding.TransmissionFragmentBinding;

public class TransmissionFragment extends Fragment {

    private TransmissionViewModel mViewModel;

    private TransmissionFragmentBinding binding;

    public static TransmissionFragment newInstance() {
        return new TransmissionFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        binding= DataBindingUtil.inflate(inflater,R.layout.transmission_fragment,container,false);


        binding.transmissionFragContent.setAdapter(new FragmentStateAdapter(this) {
            @NonNull
            @Override
            public Fragment createFragment(int position) {
                Fragment res=null;
                if(position==0)
                    res=new DownloadFragment();
                else if (position==1)
                    res=new UploadFragment();
                else
                    res=new OfflineFragment();
                return res;
            }
            @Override
            public int getItemCount() {
                return 3;
            }
        });
        TabLayoutMediator tabLayoutMediator=new TabLayoutMediator(binding.transmissionTab, binding.transmissionFragContent, new TabLayoutMediator.TabConfigurationStrategy() {
            @Override
            public void onConfigureTab(@NonNull TabLayout.Tab tab, int position) {
                if (position==0)
                    tab.setText("下载列表");
                else if (position==1)
                    tab.setText("上传列表");
                else tab.setText("离线列表");
            }
        });
        tabLayoutMediator.attach();

        return binding.getRoot();
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(TransmissionViewModel.class);
    }

}
