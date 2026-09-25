package com.pulse.app;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        PulseBridge bridge = new PulseBridge();
        float loss = bridge.trainXor(3000);
        float[] prediction = bridge.predict(new float[]{1.0f, 0.0f});
        bridge.destroy();

        TextView textView = new TextView(this);
        textView.setText("Pulse core loss: " + loss + "\n1 xor 0 = " + prediction[0]);
        setContentView(textView);
    }
}
