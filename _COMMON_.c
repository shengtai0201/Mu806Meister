void Delay(unsigned int delay_count) {
    unsigned int delay_a, delay_b;

    for (delay_a = 0; delay_a <= delay_count; delay_a++) {
        for (delay_b = 0; delay_b <= 5000; delay_b++);
    }
}