#!/usr/bin/env python3
import cmath

import math

__author__ = 'gorge.raccoon@gmail.com'


def generate_signal(frequency, sample_rate, duration):
    """Return a list of integers representing a sine wave. ``duration`` is measured in seconds."""
    sample_count = int(duration * sample_rate)
    sine_function = lambda t: math.sin(t * (2 * math.pi) * frequency)
    return [sine_function(s / sample_rate) for s in range(sample_count)]


def fft(data):
    """
    Calculate a Fourier Transform for of a ``chunk`` of data.

    If ``len(data)`` is not a power of two, ``ValueError`` will be raised.
    """
    length = len(data)

    def is_power_of_two(n):
        if n == 1:
            return True
        if not n == int(n):
            return False
        return is_power_of_two(n / 2)

    if not is_power_of_two(length):
        raise ValueError("Data length of {} is not a power of two.".format(length))

    if length == 1:
        return data

    even_values = data[::2]
    odd_values = data[1::2]
    new_data = fft(even_values) + fft(odd_values)
    for k in range(length // 2):
        new_data[k], new_data[k + length // 2] = (
            new_data[k] + cmath.exp(-2 * math.pi * complex('j') * k / length) * new_data[k + length // 2],
            new_data[k] - cmath.exp(-2 * math.pi * complex('j') * k / length) * new_data[k + length // 2]
        )
    return new_data


if __name__ == '__main__':
    sample_rate = 8000
    duration = 1
    samples1 = generate_signal(500, sample_rate, duration / 2)
    samples2 = generate_signal(1500, sample_rate, duration / 2)
    samples = samples1 + samples2

    chunk_size = 1024
    chunk_duration = chunk_size / sample_rate
    chunks = [samples[i:i + chunk_size] for i in range(0, len(samples), chunk_size)
              if len(samples[i:i + chunk_size]) == chunk_size]
    print("Chunk size of {} samples corresponds to {} seconds.".format(chunk_size, chunk_duration))

    for i, chunk in enumerate(chunks):
        results = fft(chunk)
        meaningful_data = [abs(x) for x in results[:chunk_size // 2]]

        max_value = max(meaningful_data[1:])
        bin_number = [x for x, y in enumerate(meaningful_data) if y == max_value][0]
        presumed_frequency = (bin_number - 0.5) * sample_rate / chunk_size

        time_from = i * chunk_size / sample_rate
        time_to = (i + 1) * chunk_size / sample_rate
        print("From {0:.2f} s to {1:.2f} --> {2:.2f} Hz".format(time_from, time_to, presumed_frequency))
