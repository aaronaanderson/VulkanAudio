#include <cmath>
#include "DAC.hpp"
#include <vulkan/vulkan.hpp>

DeviceParameters deviceParameters (512, 48000);

double phase = 0.0;
double phaseIncrement = 440.0 * 2.0 * M_PI / static_cast<double> (deviceParameters.sampleRate);

void audioCallback(float* outputBuffer, float* inputBuffer,
                   int numFrames, int numInputChannels, int numOutputChannels) 
{
    // CPU Sine
    for (int i = 0; i < numFrames; i++)
    {
        for (int channel = 0; channel < numOutputChannels; channel++)
            outputBuffer[i * numOutputChannels + channel] = static_cast<float> (std::sin(phase) * 0.1);

        phase += phaseIncrement;
    }
}  

int main()
{  
    DAC dac (audioCallback, deviceParameters);

    std::cout << "Enter any input to quit.\n";
    std::string n;
    std::cin >> n;

    return 0;
}

