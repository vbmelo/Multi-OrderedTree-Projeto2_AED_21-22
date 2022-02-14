% Plotting maxTreeDepth_Time
dic=readtable('treeDepth_time_nmec.txt')
% nMec = [990000 : 1 : 999999];
depths = table2array(dic(:,2));
index = 1;
for i=1:4:40000
    depth1(index) = depths(i,1);
    depth2(index) = depths(i+1,1);
    depth3(index) = depths(i+2,1);
    depth4(index) = depths(i+3,1);
    index=index+1;
end
binspan=(34:56);
A1 = hist(depth1,binspan);
B1 = hist(depth2,binspan);
C1 = hist(depth3,binspan);
D1 = hist(depth4,binspan);
figure(9);
x = 34:1:56;
y = [A1;B1;C1;D1];
bar(x,y,EdgeColor="none");
axis square;
grid on;
xlabel("Depth");
ylabel("Number of occurrences");
title('Depth Histogram');
legend("Name","Zip-Code","Telephone Number", "Social Security Number");


% Plotting search_time histogram
% search=readtable('search_Time_nmec.txt')
% nMec = [990000 : 1 : 999999];
% stimes = table2array(search(:,3))
% passando a table para .txt para input facilitado
% writetable((search(:,3)), 'searchTimeHistogram.txt')

stimes = dlmread('searchTimeHistogram.txt')

index = 1;
for i=1:4:40000
    search1(index) = stimes(i,1);
    search2(index) = stimes(i+1,1);
    search3(index) = stimes(i+2,1);
    search4(index) = stimes(i+3,1);
    index=index+1;
end

figure(1);
subplot(2,2,1);
line1 = histogram(search1,"BinWidth",0.00001,FaceColor="blue",EdgeColor="blue");;
title('Search Time Histogram');
xlabel("Time (s)");
ylabel("Number of occurrences");
legend("Name");
figure(2);
subplot(2,2,2);
line2 = histogram(search2,"BinWidth",0.00001,FaceColor="red",EdgeColor="red");
title('Search Time Histogram');
xlabel("Time (s)");
ylabel("Number of occurrences");
legend("Zip-Code");
figure(3);
subplot(2,2,3);
histogram(search3,"BinWidth",0.00001,FaceColor="yellow",EdgeColor="yellow");
title('Search Time Histogram');
xlabel("Time (s)");
ylabel("Number of occurrences");
legend("Telephone Number")
figure(4);
subplot(2,2,4);
histogram(search4,"BinWidth",0.00001,FaceColor="magenta",EdgeColor="magenta");
title('Search Time Histogram');
xlabel("Time (s)");
ylabel("Number of occurrences");
legend("Social Security Number");
