(*
 * II Всероссийская Командная Олимпиада Школьников по Программированию
 *
 * Задача:      Куб
 * Автор:       Денис Кузнецов
 * Решение:     Андрей Станкевич
 *)

{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P+,Q-,R-,S+,T-,V-,X+,Y+}
{$M 65520,0,655360}

program cube;

const
    maxm = 300;

var
    i, j, k, m, n, a1, a2, a3: longint;
    x, y, z: array [0..maxm] of longint;    
    
function pair(x1, y1, z1, x2, y2, z2: longint): boolean;
begin
    pair := 
        ((x1 + x2) * (y1 + y2) * (z1 + z2) <> 0) and
        (   abs(x1 - x2) * x1 * x2 +
            abs(y1 - y2) * y1 * y2 +
            abs(z1 - z2) * z1 * z2 = 0);
end;

function triple(x1, y1, z1, x2, y2, z2, x3, y3, z3: longint): boolean;
begin
    triple := 
        (x1 * x2 * x3 + y1 * y2 * y3 + z1 * z2 * z3 = 0) and
        (   abs(x1 - x2) * x1 * x2 +
            abs(x1 - x3) * x1 * x3 +
            abs(x2 - x3) * x2 * x3 +
            abs(y1 - y2) * y1 * y2 +
            abs(y1 - y3) * y1 * y3 +
            abs(y2 - y3) * y2 * y3 +
            abs(z1 - z2) * z1 * z2 +
            abs(z1 - z3) * z1 * z3 +
            abs(z2 - z3) * z2 * z3 = 0);
end;

begin
    assign(input, 'input.txt');
    reset(input);
    assign(output, 'output.txt');
    rewrite(output);
    
    read(n, m);
    for i := 1 to m do
    begin
        read(x[i], y[i], z[i]);
    end;
    
    a3 := 0;
    for i := 1 to m do
        for j := i + 1 to m do
            for k := j + 1 to m do
                if triple(
                    x[i], y[i], z[i],
                    x[j], y[j], z[j],
                    x[k], y[k], z[k]) then
                begin
{                    writeln(i, ' ', j, ' ', k, ' - ', 
                        x[i], ' ', y[i], ' ', z[i], '   ', 
                        x[j], ' ', y[j], ' ', z[j], '   ', 
                        x[k], ' ', y[k], ' ', z[k]);}
                    inc(a3);
                end;
                
    for i := 1 to m do
        for j := i + 1 to m do
            if pair(x[i], y[i], z[i], x[j], y[j], z[j]) then
                inc(a2);
                
    a2 := a2 - 3 * a3;
    a1 := m * n - 2 * a2 - 3 * a3;
    writeln(n * n * n - a1 - a2 - a3);
{    writeln(a1, ' ', a2, ' ', a3);}
    
    close(input);
    close(output);
end.