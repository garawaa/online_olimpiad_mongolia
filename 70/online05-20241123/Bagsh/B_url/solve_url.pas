{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P+,Q+,R+,S+,T-,V-,X+,Y+}
{$M 65520,0,655360}

program url_comparing;

function norm(x: string): string;
var
    protocol, port, host, path, filename, section, element,
        tmp: string;
    i, j: longint;
    z: integer;
begin
{    writeln('----------------');
    writeln(x);
    writeln;}
    if pos('://', x) <> 0 then
    begin
        protocol := copy(x, 1, pos('://', x) - 1);
        delete(x, 1, pos('://', x) + 2);
    end else begin
        protocol := 'http';
    end;
    
    if pos(':', x) <> 0 then
    begin
        i := pos(':', x);
        j := i;
        while (j <= length(x)) and (x[j] in ['0'..'9', ':']) do
            inc(j);
        port := copy(x, i + 1, j - i - 1);
        delete(x, i, j - i);
    end else begin
        port := '80';
    end;
    
    if pos('/', x) <> 0 then
    begin
        host := copy(x, 1, pos('/', x) - 1);
        delete(x, 1, pos('/', x));
    end else begin
        host := x;
        x := '';
    end;
    
    path := '';
    while (pos('/', x) <> 0) do
    begin
        element := copy(x, 1, pos('/', x) - 1);
        delete(x, 1, pos('/', x));
        if element = '..' then
        begin
            i := length(path);
            while path[i] <> '/' do
                dec(i);
            delete(path, i, length(path) - i + 1);
        end else if element <> '.' then begin
            path := path + '/' + element;
        end;
    end;
    path := path + '/';
    
    if (x = '') then
        x := 'index.html';
    if pos('#', x) = 0 then
        x := x + '#';
    
    filename := copy(x, 1, pos('#', x) - 1);
    delete(x, 1, pos('#', x));
    
    section := x;
    
{    writeln(protocol);
    writeln(host);
    writeln(port);
    writeln(path);
    writeln(filename);
    writeln(section);
    writeln;}
    
    x := protocol + '://' + host + ':' + port + path + filename + '#' + section;
    for i := 1 to length(x) do
        x[i] := upcase(x[i]);
        
    i := 1;
    while i < length(x) do
    begin
        if (x[i] = '%') then
        begin
            tmp := x[i + 1] + x[i + 2];
            val('$' + tmp, j, z);
            delete(x, i, 3);
            insert(char(j), x, i);
        end;
        inc(i);
    end;
    
    for i := 1 to length(x) do
        x[i] := upcase(x[i]);
        
{    writeln(x);
    writeln;}
    
    norm := x;
end;

var
    url1, url2: string;

begin
    assign(input, 'input.txt');
    reset(input);
    assign(output, 'output.txt');
    rewrite(output);
    
    while not seekeof do
    begin
        readln(url1);
        readln(url2);
{        writeln(url1);
        writeln(url2);}
        url1 := norm(url1);
        url2 := norm(url2);
{        writeln(' ', url1);
        writeln(' ', url2);}
        
        if (url1 = url2) then
            writeln('YES')
        else
            writeln('NO');
    end;
    
    close(input);
    close(output);
end.