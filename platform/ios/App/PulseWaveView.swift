import SwiftUI

struct PulseWaveView: View {
    private let normalizedX: [CGFloat] = [0.00, 0.28, 0.36, 0.44, 0.52, 0.60, 0.68, 0.76, 0.84, 1.00]
    private let normalizedY: [CGFloat] = [0.50, 0.50, 0.30, 0.70, 0.50, 0.50, 0.15, 0.85, 0.50, 0.50]

    var body: some View {
        TimelineView(.animation) { timeline in
            Canvas { context, size in
                let time = timeline.date.timeIntervalSinceReferenceDate
                let phase = CGFloat(time.truncatingRemainder(dividingBy: 3) / 3)

                let gradient = Gradient(colors: [
                    Color(red: 0.42, green: 0.36, blue: 0.91),
                    Color(red: 0.11, green: 0.06, blue: 0.21)
                ])
                context.fill(
                    Path(CGRect(origin: .zero, size: size)),
                    with: .linearGradient(gradient, startPoint: .zero, endPoint: CGPoint(x: size.width, y: size.height))
                )

                var path = Path()
                var first = true
                for cycle in -1...1 {
                    for i in 0..<normalizedX.count {
                        let x = (CGFloat(cycle) + normalizedX[i] - phase) * size.width
                        let y = normalizedY[i] * size.height
                        if first {
                            path.move(to: CGPoint(x: x, y: y))
                            first = false
                        } else {
                            path.addLine(to: CGPoint(x: x, y: y))
                        }
                    }
                }

                context.stroke(path, with: .color(.white), style: StrokeStyle(lineWidth: 4, lineCap: .round, lineJoin: .round))
            }
        }
    }
}
