import Foundation

final class PulseResponder {

    private let greetings = [
        "Hello. I am still learning, but I am listening.",
        "Hi. Pulse core is online and ready.",
        "Hey there. What is on your mind?"
    ]

    private let questions = [
        "That is a good question. I do not have a real answer yet, but I am getting there.",
        "I am not able to reason about that yet, my core is still just a small network.",
        "Ask me again once my brain grows a bit more."
    ]

    private let fallbacks = [
        "Noted.",
        "I hear you.",
        "Interesting. Tell me more.",
        "My core is still small, but I am paying attention."
    ]

    func generateReply(for input: String) -> String {
        let normalized = input.lowercased()

        if normalized.contains("hello") || normalized.contains("hi") || normalized.contains("oi") || normalized.contains("ola") {
            return greetings.randomElement()!
        }

        if normalized.contains("name") || normalized.contains("who are you") {
            return "I am Pulse, a small artificial intelligence being built from scratch."
        }

        if normalized.trimmingCharacters(in: .whitespaces).hasSuffix("?") {
            return questions.randomElement()!
        }

        return fallbacks.randomElement()!
    }
}
