close all;

frequencies = [63 117 216 399 737 1361 2513 4643 8576 15842];

filters = [];
d = fdesign.lowpass('N,F3dB',4,frequencies(1),44.1e3);
filters = [filters design(d, 'butter')];

for i = 1:9
    d = fdesign.bandpass('N,F3dB1,F3dB2',4,frequencies(i),frequencies(i+1),44.1e3);
    filters = [filters design(d,'butter')];
end

d = fdesign.highpass('N,F3dB',4,frequencies(end),44.1e3);
filters = [filters design(d, 'butter')];

fvtool(filters);

for i = 1:10
    SOS_matrix = filters(i).coefficients{1,1};
    number_of_biquads = size(SOS_matrix, 1);
    fprintf('const double sos_matrix_%d[][6] = {\n', i); 
    for row = SOS_matrix.'
        fprintf('    {');
        for coeff = row
            fprintf('%.16e, ', coeff);
        end
        fprintf('},\n');
    end
    fprintf('};\n');
    gain_array = filters(i).coefficients{1,2};
    fprintf('const double gain_array_%d[] = { ', i); 
    for gain = gain_array(1:number_of_biquads)
        fprintf('%.16e, ', gain);
    end
    fprintf('};\n');
    fprintf('SOSFilter<%d> filter_%d(sos_matrix_%d, gain_array_%d);\n\n', number_of_biquads , i, i, i);
end
