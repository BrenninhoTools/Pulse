import SwiftUI

struct ChatView: View {
    @State private var messages: [ChatMessage] = []
    @State private var inputText: String = ""
    @State private var isThinking: Bool = false

    private let responder = PulseResponder()
    private let bridge = PulseBridge()

    var body: some View {
        VStack(spacing: 0) {
            ZStack(alignment: .bottomLeading) {
                PulseWaveView()
                    .frame(height: 120)

                Text("Pulse")
                    .font(.title2)
                    .bold()
                    .foregroundColor(.white)
                    .padding(16)
            }

            ScrollViewReader { proxy in
                ScrollView {
                    LazyVStack(alignment: .leading, spacing: 8) {
                        ForEach(messages) { message in
                            MessageBubble(message: message)
                                .id(message.id)
                        }

                        if isThinking {
                            TypingIndicatorView()
                                .padding(.leading, 16)
                        }
                    }
                    .padding(16)
                }
                .onChange(of: messages.count) { _ in
                    if let last = messages.last {
                        withAnimation {
                            proxy.scrollTo(last.id, anchor: .bottom)
                        }
                    }
                }
            }

            HStack(spacing: 8) {
                TextField("Message Pulse", text: $inputText)
                    .padding(12)
                    .background(Color.white)
                    .clipShape(RoundedRectangle(cornerRadius: 24))
                    .overlay(
                        RoundedRectangle(cornerRadius: 24)
                            .stroke(Color(red: 0.88, green: 0.86, blue: 0.96))
                    )

                Button(action: send) {
                    Text("Send")
                        .foregroundColor(.white)
                        .padding(.horizontal, 20)
                        .padding(.vertical, 12)
                        .background(Color(red: 0.42, green: 0.36, blue: 0.91))
                        .clipShape(RoundedRectangle(cornerRadius: 24))
                }
            }
            .padding(12)
        }
        .background(Color(red: 0.96, green: 0.95, blue: 0.98))
        .onAppear(perform: bootstrapCore)
    }

    private func bootstrapCore() {
        addMessage(ChatMessage(text: "Booting Pulse core...", isUser: false))

        DispatchQueue.global(qos: .userInitiated).async {
            let loss = bridge.trainXor(withEpochs: 3000)
            DispatchQueue.main.async {
                addMessage(ChatMessage(
                    text: String(format: "Pulse core ready. Training loss: %.4f. Ask me anything.", loss),
                    isUser: false
                ))
            }
        }
    }

    private func send() {
        let text = inputText.trimmingCharacters(in: .whitespacesAndNewlines)
        guard !text.isEmpty else { return }

        inputText = ""
        addMessage(ChatMessage(text: text, isUser: true))

        isThinking = true
        let delay = Double.random(in: 0.5...1.2)
        DispatchQueue.main.asyncAfter(deadline: .now() + delay) {
            isThinking = false
            addMessage(ChatMessage(text: responder.generateReply(for: text), isUser: false))
        }
    }

    private func addMessage(_ message: ChatMessage) {
        messages.append(message)
    }
}

private struct MessageBubble: View {
    let message: ChatMessage

    var body: some View {
        HStack {
            if message.isUser { Spacer(minLength: 60) }

            Text(message.text)
                .foregroundColor(message.isUser ? .white : Color(red: 0.11, green: 0.06, blue: 0.21))
                .padding(.horizontal, 14)
                .padding(.vertical, 10)
                .background(message.isUser ? Color(red: 0.42, green: 0.36, blue: 0.91) : Color.white)
                .clipShape(RoundedRectangle(cornerRadius: 18))

            if !message.isUser { Spacer(minLength: 60) }
        }
    }
}
