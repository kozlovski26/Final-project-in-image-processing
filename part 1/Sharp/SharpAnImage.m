function result = sharp(A,sigma )

T=imread(A);
img=rgb2gray(T)
imshow(img);
title('original image')
G=1/6*[0 1 0;
       1 2 1;
       0 1 0;]
blurImg=conv2(img,G,'same')

sharpImg=uint8(img)-uint8(blurImg)
result=img+uint8(sigma*sharpImg)


figure,imshow(uint8(result))
title('sharpen image');

end

