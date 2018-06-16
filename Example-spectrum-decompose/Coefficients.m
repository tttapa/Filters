%% Setup

close all;

samplefreq = 44100;
filter_type = 'butter';
order = 6;
number_of_bands = 10;

min_freq = 80;
max_freq = 10000;
b = log(max_freq/min_freq)/(number_of_bands-2);
frequencies = min_freq * exp((0:number_of_bands-2).*b);

%% Filter design

filters = [];
d = fdesign.lowpass('N,F3dB',order,frequencies(1),samplefreq);
filters = [filters design(d, filter_type)];
for i = 1:number_of_bands-2
    d = fdesign.bandpass('N,F3dB1,F3dB2',order,frequencies(i),frequencies(i+1),samplefreq);
    filters = [filters design(d,filter_type)];
end
d = fdesign.highpass('N,F3dB',order,frequencies(number_of_bands-1),samplefreq);
filters = [filters design(d, filter_type)];

%% Visualize

fvtool(filters);
set(gca, 'XScale', 'log');
axis([0.02, samplefreq/2000 -60 6]);

%% Export coefficients to C/C++ header file

fileID = fopen('Coefficients.h','w');

number_of_biquads = ceil(order/2);

fprintf(fileID, '/* This is an automatically generated file, do not edit it. Edit Coefficients.m instead. */\n\n');
fprintf(fileID, 'constexpr int filterSampleRate = %d;\n\n',samplefreq);
fprintf(fileID, 'constexpr int numberOfBands = %d;\n\n',number_of_bands);
fprintf(fileID, 'constexpr int numberOfBiQuads= %d;\n\n',number_of_biquads);

number_of_biquads = ceil(order/2);
fprintf(fileID, 'const double sos_matrices[][numberOfBiQuads][6] = {\n'); 
frequencies = [0 frequencies samplefreq / 2];
for i = 1:number_of_bands
    fprintf(fileID, '    {\n');
    if (frequencies(i) >= 1000)
        fprintf(fileID, '    // %.3f - %.3f kHz\n', frequencies(i) / 1000, frequencies(i+1) / 1000); 
    else 
        fprintf(fileID, '    // %.0f - %.0f Hz\n', frequencies(i), frequencies(i+1)); 
    end
    SOS_matrix = filters(i).coefficients{1,1};
    for row = SOS_matrix.'
        fprintf(fileID, '        {');
        for coeff = row
            fprintf(fileID, '%.16e, ', coeff);
        end
        fprintf(fileID, '},\n');
    end
    fprintf(fileID, '    },\n');
end
fprintf(fileID, '};\n\n');

fprintf(fileID, 'const double gain[][numberOfBiQuads] = {\n'); 
for i = 1:number_of_bands
    fprintf(fileID, '    {');
    gain_array = filters(i).coefficients{1,2}(1:number_of_biquads);
    for gain = gain_array
        fprintf(fileID, '%.16e, ', gain);
    end
    fprintf(fileID, '},\n');
end
fprintf(fileID, '};\n\n');
