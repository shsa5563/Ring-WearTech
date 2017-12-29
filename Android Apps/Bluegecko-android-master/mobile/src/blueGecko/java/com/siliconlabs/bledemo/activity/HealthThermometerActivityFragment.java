package com.siliconlabs.bledemo.activity;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.Fragment;
import android.support.v7.widget.SwitchCompat;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;

import com.siliconlabs.bledemo.R;
import com.siliconlabs.bledemo.models.TemperatureReading;
import com.siliconlabs.bledemo.views.TemperatureDisplay;
import com.siliconlabs.bledemo.views.ThermoGraph;

import java.util.List;

import butterknife.ButterKnife;
import butterknife.InjectView;
import butterknife.OnClick;

public class HealthThermometerActivityFragment extends Fragment {
    private TemperatureReading currentReading;
    private TemperatureReading.Type currentType;

    @InjectView(R.id.thermometer_graph)
    ThermoGraph thermoGraph;
    @InjectView(R.id.thermo_large_temperature)
    TemperatureDisplay largeTemperatureDisplay;
    @InjectView(R.id.thermo_add_graph_button)
    FloatingActionButton addToGraphButton;
    @InjectView(R.id.thermo_clear_button)
    FloatingActionButton clearButton;
    @InjectView(R.id.thermo_type_value_text)
    TextView thermoTypeText;
    @InjectView(R.id.thermo_large_time_text)
    TextView thermoTimeText;
    @InjectView(R.id.type_switch)
    SwitchCompat typeSwitch;
    @InjectView(R.id.thermometer_device_name)
    TextView deviceNameText;

    public HealthThermometerActivityFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_health_thermometer, container, false);
        ButterKnife.inject(this, v);
        setHasOptionsMenu(true);
        largeTemperatureDisplay.setFontFamily("sans-serif-thin", Typeface.NORMAL);
        thermoGraph.clear();
        typeSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                onTabClick(!isChecked);
            }
        });
        clearButton.setBackgroundTintList(ColorStateList.valueOf(Color.WHITE));
        return v;
    }

    //added by shekhar
    @OnClick(R.id.buttonActOne)
    public void onSendClick(View v) {
        //Intent sendIntent = new Intent();
        //sendIntent.setAction(Intent.ACTION_SEND);
        //sendIntent.putExtra(Intent.EXTRA_TEXT, "This is my text to send.");
        //sendIntent.setType("text/plain");
        //startActivity(sendIntent);
        //"io.github.cawfree.dtw"
    }


    //ends here
    @OnClick(R.id.thermo_clear_button)
    public void onClearClick(View v) {
        thermoGraph.clear();
    }

    @OnClick(R.id.thermo_add_graph_button)
    public void onAddClick(View v) {
        if (currentReading != null) {
            thermoGraph.addReading(currentReading);
        }
    }

    private void onTabClick(boolean fahrenheit) {
        currentType = fahrenheit ? TemperatureReading.Type.FAHRENHEIT : TemperatureReading.Type.CELSIUS;
        thermoGraph.switchDisplayMode(currentType, true);
        largeTemperatureDisplay.setCurrentType(currentType);
    }

    public void setCurrentReading(TemperatureReading temperatureReading) {
        this.currentReading = temperatureReading;
        if(temperatureReading.getTapState() ==255) {
            Toast.makeText(HealthThermometerActivityFragment.this.getActivity() , "Double Tap Detected", Toast.LENGTH_LONG).show();
        }else{
            Intent sendIntent = new Intent();
            sendIntent.setAction(Intent.ACTION_SEND);
            sendIntent.putExtra(Intent.EXTRA_TEXT, temperatureReading.getX() + "," + temperatureReading.getY() + "," + temperatureReading.getZ());
            //Toast.makeText(HealthThermometerActivityFragment.this.getActivity() , "D(X:" + String.valueOf(Math.abs(temperatureReading.getX())) + ", Y:" +  String.valueOf(Math.abs(temperatureReading.getY())) + ", Z:" +  String.valueOf(Math.abs(temperatureReading.getZ()))+":)", Toast.LENGTH_LONG).show();
            //Toast td = Toast.makeText(HealthThermometerActivityFragment.this.getActivity() , "D(X:" , Toast.LENGTH_LONG);

            sendIntent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
            sendIntent.setType("text/plain");
            startActivity(sendIntent);
            refreshUi();
        }
    }

    public void setDeviceName(String deviceName) {
        deviceNameText.setText(deviceName);
    }

    private void refreshUi() {
        if (currentReading != null && isAdded()) {
            largeTemperatureDisplay.setTemperature(currentReading);
            thermoTypeText.setText(getString(currentReading.getHtmType().getNameResId()));
            thermoTimeText.setText(currentReading.getFormattedTime());
        }
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);
        inflater.inflate(R.menu.menu_health_thermometer, menu);
    }
}
