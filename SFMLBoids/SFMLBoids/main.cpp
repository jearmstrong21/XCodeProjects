#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    const unsigned SAMPLES = 44100;
    const unsigned SAMPLE_RATE = 44100;
    
    sf::Int16 raw[SAMPLES];
    
    sf::SoundBuffer Buffer;
    if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
        std::cerr << "Loading failed!" << std::endl;
        return 1;
    }
    
    sf::Sound Sound;
    Sound.setBuffer(Buffer);
    Sound.setLoop(true);
    Sound.play();
    while (1) {
        sf::sleep(sf::milliseconds(100));
    }
    return 0;
}
