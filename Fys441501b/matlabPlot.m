fid=fopen('text.txt')
    s = textscan(fid,'%f %f %f')
fclose(fid)

x=s{1};
y=s{2};
z=s{3};
plot(x,y,'*red')
hold on
plot(x,z,'*blue')

title(' algorithm vs real solution  for n = 10')
xlabel('x')
ylabel('y')
legend('algorithm','real solution')