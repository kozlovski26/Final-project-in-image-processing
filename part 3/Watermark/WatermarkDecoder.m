function [ out ] = WatermarkDecoder( coded_image_path, key)
    coded_image = imread(coded_image_path);


    sum = 0;
    for i = 1 : size(key,1)
        pointsMinus = int64(coded_image(key(i,1),key(i,2))) - int64(coded_image(key(i,3),key(i,4)));
        sum = sum + pointsMinus;
    end
    
    out = sum;
end

