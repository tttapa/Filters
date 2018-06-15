#include "../src/SOSFilter.h"
#include "AudioFile.h"

#include <iostream>
using namespace std;

AudioFile<double> source;
AudioFile<double> outputs[10];

const double sos_matrix_1[][6] = {
    {1.0000000000000000e+00, 2.0000000000000000e+00, 1.0000000000000000e+00, 1.0000000000000000e+00, -1.9930733999418371e+00, 9.9315369180458546e-01, },
    {1.0000000000000000e+00, 2.0000000000000000e+00, 1.0000000000000000e+00, 1.0000000000000000e+00, -1.9834712747712591e+00, 9.8355117980805484e-01, },
};
const double gain_array_1[] = { 2.0072965687071073e-05, 1.9976259198951974e-05, };
SOSFilter<2> filter_1(sos_matrix_1, gain_array_1);

const double sos_matrix_2[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9931392480963632e+00, 9.9337353463405709e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9956818916678858e+00, 9.9577693056080352e-01, },
};
const double gain_array_2[] = { 3.8364173535664048e-03, 3.8364173535664048e-03, };
SOSFilter<2> filter_2(sos_matrix_2, gain_array_2);

const double sos_matrix_3[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9871094332013195e+00, 9.8790679430340167e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9919227125801879e+00, 9.9224947717478862e-01, },
};
const double gain_array_3[] = { 7.0175883785813615e-03, 7.0175883785813615e-03, };
SOSFilter<2> filter_3(sos_matrix_3, gain_array_3);

const double sos_matrix_4[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9750520462878800e+00, 9.7775822041410199e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9846127097441471e+00, 9.8572285137416193e-01, },
};
const double gain_array_4[] = { 1.2917651060087253e-02, 1.2917651060087253e-02, };
SOSFilter<2> filter_4(sos_matrix_4, gain_array_4);

const double sos_matrix_5[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9501734538353190e+00, 9.5931635651670444e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9700156845930028e+00, 9.7378019827568829e-01, },
};
const double gain_array_5[] = { 2.3676504521485356e-02, 2.3676504521485356e-02, };
SOSFilter<2> filter_5(sos_matrix_5, gain_array_5);

const double sos_matrix_6[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.8956386374170799e+00, 9.2624566988222112e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.9393782615944464e+00, 9.5207202478769526e-01, },
};
const double gain_array_6[] = { 4.3105296527840370e-02, 4.3105296527840370e-02, };
SOSFilter<2> filter_6(sos_matrix_6, gain_array_6);

const double sos_matrix_7[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.7677428758248848e+00, 8.6842730840353266e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.8706524297989409e+00, 9.1297906123745454e-01, },
};
const double gain_array_7[] = { 7.7612892477829473e-02, 7.7612892477829473e-02, };
SOSFilter<2> filter_7(sos_matrix_7, gain_array_7);

const double sos_matrix_8[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.7051138050748977e+00, 8.4312281652415644e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.4521848100830228e+00, 7.7225474593902665e-01, },
};
const double gain_array_8[] = { 1.3733951081376508e-01, 1.3733951081376508e-01, };
SOSFilter<2> filter_8(sos_matrix_8, gain_array_8);

const double sos_matrix_9[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -1.2901297163296863e+00, 7.1787425523176140e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -6.8841585061219313e-01, 6.3197560179022561e-01, },
};
const double gain_array_9[] = { 2.3575315841864308e-01, 2.3575315841864308e-01, };
SOSFilter<2> filter_9(sos_matrix_9, gain_array_9);

const double sos_matrix_10[][6] = {
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, 8.4533149073045721e-01, 5.2412562207200453e-01, },
    {1.0000000000000000e+00, 0.0000000000000000e+00, -1.0000000000000000e+00, 1.0000000000000000e+00, -3.3630372995744928e-01, 4.6497591016459305e-01, },
};
const double gain_array_10[] = { 3.9019458704531540e-01, 3.9019458704531540e-01, };
SOSFilter<2> filter_10(sos_matrix_10, gain_array_10);

SOSFilter<2> filters[] = {
    {sos_matrix_1, gain_array_1},
    {sos_matrix_2, gain_array_2},
    {sos_matrix_3, gain_array_3},
    {sos_matrix_4, gain_array_4},
    {sos_matrix_5, gain_array_5},
    {sos_matrix_6, gain_array_6},
    {sos_matrix_7, gain_array_7},
    {sos_matrix_8, gain_array_8},
    {sos_matrix_9, gain_array_9},
    {sos_matrix_10, gain_array_10},
};

int main() {
    source.load("input.wav");
    int sampleRate = source.getSampleRate();
    assert(sampleRate == 44100);
    int numChannels = source.getNumChannels();
    int numSamples = source.getNumSamplesPerChannel();
    int bitDepth = source.getBitDepth();

    cout << "Wav loaded" << endl;

    Filter ***channelFilters = new Filter**[numChannels];
    for (int i = 0; i < numChannels; i++) {
        channelFilters[i] = new Filter*[10];
        for (int j = 0; j < 10; j++)
            channelFilters[i][j] = new SOSFilter<2>(filters[j]);
    }

    cout << "Filters created" << endl;

    for (AudioFile<double> &af : outputs) {
        af.setAudioBufferSize(numChannels, numSamples);
        af.setBitDepth(bitDepth);
        af.setSampleRate(sampleRate);
    }

    cout << "Outputs configured" << endl;

    for (int sample = 0; sample < numSamples; sample++) {
        for (int c = 0; c < numChannels; c++) {
            double currentSample = source.samples[c][sample];
            for (int f = 0; f < 10; f++) {
                outputs[f].samples[c][sample] = 
                    channelFilters[c][f]->filter(currentSample);
            }
        }
    }

    cout << "Filtered" << endl;

    for (int i = 0; i < 10; i++) {
        char name[32] = "";
        snprintf(name, 32, "output_%d.wav", i);
        AudioFile<double> &af = outputs[i];
        af.save(name);
    }

    cout << "Exported" << endl;

    return 0;
}