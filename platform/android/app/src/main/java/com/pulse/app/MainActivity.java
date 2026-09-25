package com.pulse.app;

import android.app.Activity;
import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import java.util.Locale;

public class MainActivity extends Activity {

    private LinearLayout messageContainer;
    private ScrollView chatScroll;
    private EditText messageInput;
    private Button sendButton;
    private TypingIndicatorView typingIndicator;

    private final PulseResponder responder = new PulseResponder();
    private final Handler handler = new Handler(Looper.getMainLooper());

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        messageContainer = findViewById(R.id.messageContainer);
        chatScroll = findViewById(R.id.chatScroll);
        messageInput = findViewById(R.id.messageInput);
        sendButton = findViewById(R.id.sendButton);
        typingIndicator = findViewById(R.id.typingIndicator);

        sendButton.setOnClickListener(v -> onSendClicked());

        bootstrapCore();
    }

    private void onSendClicked() {
        String text = messageInput.getText().toString().trim();
        if (text.isEmpty()) {
            return;
        }

        messageInput.setText("");
        addMessage(text, true);

        typingIndicator.start();
        long delay = 500 + (long) (Math.random() * 700);
        handler.postDelayed(() -> {
            typingIndicator.stop();
            addMessage(responder.generateReply(text), false);
        }, delay);
    }

    private void bootstrapCore() {
        addMessage("Booting Pulse core...", false);

        new Thread(() -> {
            PulseBridge bridge = new PulseBridge();
            float loss = bridge.trainXor(3000);
            bridge.destroy();

            runOnUiThread(() -> addMessage(String.format(Locale.US,
                    "Pulse core ready. Training loss: %.4f. Ask me anything.", loss), false));
        }).start();
    }

    private void addMessage(String text, boolean isUser) {
        TextView bubble = new TextView(this);
        bubble.setText(text);
        bubble.setTextColor(isUser ? 0xFFFFFFFF : 0xFF1B1035);
        bubble.setTextSize(15f);
        bubble.setPadding(dp(14), dp(10), dp(14), dp(10));

        GradientDrawable background = new GradientDrawable();
        background.setCornerRadius(dp(18));
        background.setColor(isUser ? 0xFF6C5CE7 : 0xFFFFFFFF);
        bubble.setBackground(background);

        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        params.gravity = isUser ? Gravity.END : Gravity.START;
        params.topMargin = dp(6);
        params.bottomMargin = dp(6);
        params.leftMargin = isUser ? dp(60) : 0;
        params.rightMargin = isUser ? 0 : dp(60);

        bubble.setAlpha(0f);
        bubble.setTranslationY(dp(24));

        messageContainer.addView(bubble, params);

        bubble.animate()
                .alpha(1f)
                .translationY(0f)
                .setDuration(220)
                .start();

        chatScroll.post(() -> chatScroll.fullScroll(View.FOCUS_DOWN));
    }

    private int dp(int value) {
        return Math.round(value * getResources().getDisplayMetrics().density);
    }
}
