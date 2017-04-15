function [ ret ] = RandomKey( x, y )
minValue = min(x,y);
key = [];

for i = 1 : 20000
    r = randi([1 minValue],1,4);
    key = [key ; r];
end

ret = key;

end

