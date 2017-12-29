package com.siliconlabs.bledemo.activity;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.HapticFeedbackConstants;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import com.siliconlabs.bledemo.R;

import butterknife.ButterKnife;
import butterknife.InjectView;
import butterknife.OnClick;

public class LightActivityFragment extends Fragment implements LightPresenter.View {

    LightPresenter presenter;
    @InjectView(R.id.lightbulb)
    ImageButton lightbulbButton;
    @InjectView(R.id.light_status)
    TextView lightStatus;
    @InjectView(R.id.light_change_source_text)
    TextView lightSource;
    @InjectView(R.id.light_change_source_icon)
    ImageView lightIcon;

    public LightActivityFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_light, container, false);
        ButterKnife.inject(this, v);
        LightActivity activity = (LightActivity) getActivity();
        presenter = new LightPresenter(this, activity);
        return v;
    }

    @OnClick(R.id.lightbulb)
    public void onClick(View view) {
        view.performHapticFeedback(HapticFeedbackConstants.VIRTUAL_KEY);
        presenter.onLightClicked();
    }

    @Override
    public void showLightState(boolean lightOn) {
        if (lightOn) {
            lightbulbButton.setImageResource(R.drawable.light_on);
            lightStatus.setText(R.string.demo_light_on);
        } else {
            lightbulbButton.setImageResource(R.drawable.light_off);
            lightStatus.setText(R.string.demo_light_off);
        }
    }

    @Override
    public void showTriggerSource(TriggerSource source) {
        if (isAdded() && !isDetached() && !isRemoving()) {
            lightSource.setText(getString(R.string.demo_light_changed_source, getString(source.labelId)));
            lightIcon.setImageResource(source.iconId);
        }
    }
}
