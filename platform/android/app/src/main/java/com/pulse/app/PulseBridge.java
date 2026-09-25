package com.pulse.app;

public class PulseBridge {

    static {
        System.loadLibrary("pulse_android");
    }

    private long handle;

    public PulseBridge() {
        handle = nativeCreateNetwork();
    }

    public float trainXor(int epochs) {
        return nativeTrainXor(handle, epochs);
    }

    public float[] predict(float[] input) {
        return nativePredict(handle, input);
    }

    public void destroy() {
        nativeDestroyNetwork(handle);
        handle = 0;
    }

    private native long nativeCreateNetwork();

    private native void nativeDestroyNetwork(long handle);

    private native float nativeTrainXor(long handle, int epochs);

    private native float[] nativePredict(long handle, float[] input);
}
