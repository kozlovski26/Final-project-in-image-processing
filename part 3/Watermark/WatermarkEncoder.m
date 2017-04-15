function [ output_args ] = WatermarkEncoder( img )

orginal_image = img;
w = size(img,2);
h = size(img,1);
minValue = min(w,h);
key = [];


for i = 1 : 20000
    r = randi([1 minValue],1,4);
    key = [key ; r];
end

for i = 1 : size(key, 1)
    img(key(i,1),key(i,2)) =  img(key(i,1),key(i,2)) + 8;
    img(key(i,3),key(i,4)) =  img(key(i,3),key(i,4)) - 8;
end

imwrite(img, 'CodedImage.tiff');
dlmwrite('KeyFile.txt',key);

end
