# Pulse
A "good" artificial intelligence made by just one person.

## Structure

- `include/pulse`, `src` — core neural network engine, written in pure C++17 with no external dependencies (`Tensor`, `Layer`, `DenseLayer`, `Network`, `Trainer`).
- `platform/android` — Android app module with a JNI bridge (`PulseBridge`) exposing the core engine to Java, plus an animated chat home screen (`MainActivity`, `PulseWaveView`, `TypingIndicatorView`, `PulseResponder`).
- `platform/ios` — iOS static library target with an Objective-C++ bridge (`PulseBridge`), plus a SwiftUI chat home screen under `platform/ios/App` (`ChatView`, `PulseWaveView`, `TypingIndicatorView`, `PulseResponder`).
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

This only builds the static library. Xcode project files (`.xcodeproj`) are binary/generated artifacts that Xcode itself must create, so to run the chat app on iOS:

1. In Xcode, create a new iOS App project (SwiftUI, bundle id `com.pulse.app`).
2. Add all files from `platform/ios/App` to the project.
3. Add `PulseBridge.h`, `PulseBridge.mm` and the `pulse` core sources/headers to the target, and set `platform/ios/App/Pulse-Bridging-Header.h` as the target's Objective-C bridging header.
4. Replace the generated `Assets.xcassets` with `platform/ios/Assets.xcassets` and the `Info.plist` with `platform/ios/Info.plist`.
5. Build and run.

