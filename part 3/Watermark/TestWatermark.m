function [ output_args ] = TestWatermark( img , real_key )

w = size(img, 2);
h = size(img, 1);
samples = [];

for i=1 : 10
    
    rand_key = RandomKey(w,h);
    sum = WatermarkDecoder('CodedImage.tiff', rand_key);
    samples = [samples;sum];
end

sum = WatermarkDecoder('CodedImage.tiff', real_key);
samples = [samples;sum];


for i=1 : 10
    rand_key = RandomKey(w,h);
    sum = WatermarkDecoder('CodedImage.tiff', rand_key);
    samples = [samples;sum];
end

disp(samples);
plot(samples);
end

