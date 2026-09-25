# Pulse
A "good" artificial intelligence made by just one person.

## Structure

- `include/pulse`, `src` — core neural network engine, written in pure C++17 with no external dependencies (`Tensor`, `Layer`, `DenseLayer`, `Network`, `Trainer`).
- `platform/android` — Android app module with a JNI bridge (`PulseBridge`) exposing the core engine to Java.
- `platform/ios` — iOS static library target with an Objective-C++ bridge (`PulseBridge`) exposing the core engine to Swift/Objective-C.
- `assets/icon` — app icon source and exported PNGs.
- `.github/workflows/build.yml` — CI building Windows, Linux, macOS, Android and iOS.

## Build (desktop)

```bash
cmake -S . -B build
cmake --build build --config Release
```

## Build (Android)

```bash
cd platform/android
gradle assembleDebug
```

## Build (iOS)

```bash
cmake -S platform/ios -B build-ios -G Xcode \
  -DCMAKE_TOOLCHAIN_FILE=cmake/ios.toolchain.cmake \
  -DPULSE_IOS_PLATFORM=SIMULATORARM64
cmake --build build-ios --config Release
```

