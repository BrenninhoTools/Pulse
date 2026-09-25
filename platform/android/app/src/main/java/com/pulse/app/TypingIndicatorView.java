package com.pulse.app;

import android.animation.ObjectAnimator;
import android.content.Context;
import android.graphics.drawable.GradientDrawable;
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.View;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.widget.LinearLayout;

import java.util.ArrayList;
import java.util.List;

public class TypingIndicatorView extends LinearLayout {

    private final List<View> dots = new ArrayList<>();
    private final List<ObjectAnimator> animators = new ArrayList<>();

    public TypingIndicatorView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setOrientation(HORIZONTAL);
        setGravity(Gravity.CENTER_VERTICAL);

        int dotSize = dp(8);
        int margin = dp(4);
        for (int i = 0; i < 3; i++) {
            View dot = new View(context);
            GradientDrawable shape = new GradientDrawable();
            shape.setShape(GradientDrawable.OVAL);
            shape.setColor(0xFF6C5CE7);
            dot.setBackground(shape);

            LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(dotSize, dotSize);
            params.setMarginEnd(margin);
            addView(dot, params);
            dots.add(dot);
        }
    }

    private int dp(int value) {
        return Math.round(value * getResources().getDisplayMetrics().density);
    }

    public void start() {
        setVisibility(VISIBLE);
        for (int i = 0; i < dots.size(); i++) {
            View dot = dots.get(i);
            ObjectAnimator animator = ObjectAnimator.ofFloat(dot, "translationY", 0f, -dp(6), 0f);
            animator.setDuration(600);
            animator.setStartDelay(i * 150L);
            animator.setRepeatCount(ObjectAnimator.INFINITE);
            animator.setInterpolator(new AccelerateDecelerateInterpolator());
            animator.start();
            animators.add(animator);
        }
    }

    public void stop() {
        for (ObjectAnimator animator : animators) {
            animator.cancel();
        }
        animators.clear();
        for (View dot : dots) {
            dot.setTranslationY(0f);
        }
        setVisibility(GONE);
    }
}
