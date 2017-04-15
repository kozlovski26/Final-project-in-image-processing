function [result] = FFT(A)
   
% Load a full image
  disp('loading full image...')
  A=imread('ballon','jpg')
  figure(3)
  imshow(A);
  title('Original Image');
  
  %make any image black and white(gray)
  Abw=rgb2gray(A)
  [nx,ny]=size(Abw)
  figure(1),subplot(2,2,1),imshow(Abw);
  title('original image','Fontsize',18)
  
  %compute the FFT of our image using fft2
  disp('doing FFT analysis for sparsity check...')
  tic;
  At=fft2(Abw)
  F = log(abs(fftshift(At))+1);
  F = mat2gray(F); % Use mat2gray to scale the image between 0 and 1
figure(4)
imshow(F,[]); % Display the FFT coefficients 

% Zero out all small coefficients and inverse transform
disp('Zeroing out small Fourier coefficients...')
tic;
count_pic=2; 
for thresh=.1*[0.001 0.005 0.01] * max(max(abs(At)))
    ind = abs(At)>thresh;
    count = nx*ny-sum(sum(ind));

    Atlow = At.*ind;

    percent=100-count/(nx*ny)*100;
    Alow=uint8(ifft2(Atlow)); 
    figure(1), subplot(2,2,count_pic), imshow(Alow); count_pic=count_pic+1;
    drawnow
    title([num2str(percent) '% of FFT basis'],'FontSize',18)
end
disp(['    done. (' num2str(toc) 's)'])

%

%Anew = imresize(Abw2,.1);
%surf(double(Anew));
end