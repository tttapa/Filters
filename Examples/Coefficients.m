close all;

samplefreq = 44100;
frequencies = [63 117 216 399 737 1361 2513 4643 8576 15842]; % 3dB corner frequencies
order = 4;

filters = [];
d = fdesign.lowpass('N,F3dB',order,frequencies(1),samplefreq);
filters = [filters design(d, 'butter')];
for i = 1:9
    d = fdesign.bandpass('N,F3dB1,F3dB2',order,frequencies(i),frequencies(i+1),samplefreq);
    filters = [filters design(d,'butter')];
end
d = fdesign.highpass('N,F3dB',order,frequencies(end),samplefreq);
filters = [filters design(d, 'butter')];

fvtool(filters);

number_of_biquads = ceil(order/2);
fprintf('const double sos_matrices[][%d][6] = {\n', number_of_biquads); 
for i = 1:10
    fprintf('    {\n');
    SOS_matrix = filters(i).coefficients{1,1};
    for row = SOS_matrix.'
        fprintf('        {');
        for coeff = row
            fprintf('%.16e, ', coeff);
        end
        fprintf('},\n');
    end
    fprintf('    },\n');
end
fprintf('};\n\n');

fprintf('const double gain[][%d] = {\n', number_of_biquads); 
for i = 1:10
    fprintf('    {');
    gain_array = filters(i).coefficients{1,2}(1:number_of_biquads);
    for gain = gain_array
        fprintf('%.16e, ', gain);
    end
    fprintf('},\n');
end
fprintf('};\n\n');
