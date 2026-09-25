package com.pulse.app;

import android.animation.ValueAnimator;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Shader;
import android.util.AttributeSet;
import android.view.View;
import android.view.animation.LinearInterpolator;

public class PulseWaveView extends View {

    private static final float[] NORMALIZED_X = {0.00f, 0.28f, 0.36f, 0.44f, 0.52f, 0.60f, 0.68f, 0.76f, 0.84f, 1.00f};
    private static final float[] NORMALIZED_Y = {0.50f, 0.50f, 0.30f, 0.70f, 0.50f, 0.50f, 0.15f, 0.85f, 0.50f, 0.50f};

    private final Paint linePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint backgroundPaint = new Paint();
    private final Path path = new Path();
    private ValueAnimator animator;
    private float phase = 0f;

    public PulseWaveView(Context context, AttributeSet attrs) {
        super(context, attrs);
        linePaint.setColor(0xFFFFFFFF);
        linePaint.setStyle(Paint.Style.STROKE);
        linePaint.setStrokeWidth(dp(4));
        linePaint.setStrokeCap(Paint.Cap.ROUND);
        linePaint.setStrokeJoin(Paint.Join.ROUND);
    }

    private int dp(int value) {
        return Math.round(value * getResources().getDisplayMetrics().density);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        backgroundPaint.setShader(new LinearGradient(0, 0, w, h, 0xFF6C5CE7, 0xFF1B1035, Shader.TileMode.CLAMP));
    }

    @Override
    protected void onAttachedToWindow() {
        super.onAttachedToWindow();
        animator = ValueAnimator.ofFloat(0f, 1f);
        animator.setDuration(3000);
        animator.setRepeatCount(ValueAnimator.INFINITE);
        animator.setInterpolator(new LinearInterpolator());
        animator.addUpdateListener(animation -> {
            phase = (float) animation.getAnimatedValue();
            invalidate();
        });
        animator.start();
    }

    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        if (animator != null) {
            animator.cancel();
            animator = null;
        }
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        int width = getWidth();
        int height = getHeight();
        if (width == 0 || height == 0) {
            return;
        }

        canvas.drawRect(0, 0, width, height, backgroundPaint);

        path.reset();
        boolean first = true;
        for (int cycle = -1; cycle <= 1; cycle++) {
            for (int i = 0; i < NORMALIZED_X.length; i++) {
                float x = (cycle + NORMALIZED_X[i] - phase) * width;
                float y = NORMALIZED_Y[i] * height;
                if (first) {
                    path.moveTo(x, y);
                    first = false;
                } else {
                    path.lineTo(x, y);
                }
            }
        }

        canvas.drawPath(path, linePaint);
    }
}
