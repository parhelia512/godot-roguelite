#pragma once

// [[signal_event]] attribute to make callback signals easy to spot/find
#define signal_event __declspec(godot_signal_event)

// [[signal_callback]] attribute to make callback signals easy to spot/find
#define signal_callback __declspec(godot_signal_callback)

// clang-format off

#define SignalConnection(signal, func_name, ...) std::pair<String, Callable>{signal, Callable(this, #func_name __VA_OPT__(,) __VA_ARGS__ )}

// clang-format on
