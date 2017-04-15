function [ HistogramEqualizion ] = HistogramEqualizion( img )
    close all;
    %read the image
    figure;
    imshow(img);
    title('Original Image');

    %size of the image and number of pixels
    
    Rows = size(img,1);
    Columns =  size(img,2); 
    NumOfPixels = Rows * Columns;

    %table of frequency,probability,cumulative probability,
    frequency = zeros(256,1);
    probability = zeros(256,1);
    cdf = zeros(256,1);
    cum = zeros(256,1);
    equ = zeros(256,1);

    % Looping on each pixel of the image and Count the frequency and calculating the precentage
    for i=1:Rows
        for j=1:Columns
            value=img(i,j);
            frequency(value+1)=frequency(value+1)+1; 
            probability(value+1) = frequency(value+1) / NumOfPixels; 
        end
    end
    
    % Looping on the probability and equlizing the histogram
    sum = 0; L=255;
    for i=1:256
        sum = sum + frequency(i);
        cum(i) = sum;
        cdf(i) =  cum(i)/NumOfPixels;
        equ(i) = round(cdf(i) * L);
    end
    
    % Overwrting the original pixles with the new (contrasted) values.
    for i=1:Rows
        for j=1:Columns
            img(i,j) = equ(img(i,j) + 1);
        end
    end
    
    
    figure;
    imshow(img);
    title('Equalized Image');
    
    HistogramEqualizion = img;
    
    return
    
end

