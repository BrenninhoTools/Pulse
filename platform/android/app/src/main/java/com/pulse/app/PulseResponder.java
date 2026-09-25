package com.pulse.app;

import java.util.Arrays;
import java.util.List;
import java.util.Locale;
import java.util.Random;

public class PulseResponder {

    private static final List<String> GREETINGS = Arrays.asList(
            "Hello. I am still learning, but I am listening.",
            "Hi. Pulse core is online and ready.",
            "Hey there. What is on your mind?"
    );

    private static final List<String> QUESTIONS = Arrays.asList(
            "That is a good question. I do not have a real answer yet, but I am getting there.",
            "I am not able to reason about that yet, my core is still just a small network.",
            "Ask me again once my brain grows a bit more."
    );

    private static final List<String> FALLBACKS = Arrays.asList(
            "Noted.",
            "I hear you.",
            "Interesting. Tell me more.",
            "My core is still small, but I am paying attention."
    );

    private final Random random = new Random();

    public String generateReply(String input) {
        String normalized = input.toLowerCase(Locale.US);

        if (normalized.contains("hello") || normalized.contains("hi") || normalized.contains("oi") || normalized.contains("ola")) {
            return pick(GREETINGS);
        }

        if (normalized.contains("name") || normalized.contains("who are you")) {
            return "I am Pulse, a small artificial intelligence being built from scratch.";
        }

        if (normalized.trim().endsWith("?")) {
            return pick(QUESTIONS);
        }

        return pick(FALLBACKS);
    }

    private String pick(List<String> options) {
        return options.get(random.nextInt(options.size()));
    }
}
