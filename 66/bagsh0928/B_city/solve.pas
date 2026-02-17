{ Командная олимпиада школьников Санкт-Петербурга 2000 года }
{ Задача: "Город"                                           }
{ Автор: Андрей Станкевич                                   }
{ Решение: Андрей Станкевич                                 }
{ Алгоритм: Очевидно ;)                                     }

program the_city;

var
  a, b: longint;
  i, j, m, n, h, v: longint;
  x, y: array [0..1000] of longint;

procedure use(x, y: longint);
begin
  if x > y then
  begin
    use(y, x);
    exit;
  end;

  { Теперь x <= y }

  { "Узкое место" ? }
  if x = 1 then
  begin
    inc(a, y);
    exit;
  end;

  { Нормальный квартал }
  inc(a, 2 * x + 2 * (y - 2));
  inc(b, (x - 2) * (y - 2));
end;

begin
  assign(input, 'input.txt');
  reset(input);
  assign(output, 'output.txt');
  rewrite(output);

  read(m, n, v, h);
  for i := 1 to v do
    read(x[i]);
  for i := 1 to h do
    read(y[i]);

  a := 0; { Количество домов }
  b := 0; { Количество парков }
  for i := 2 to v do
  begin
    for j := 2 to h do
      use(x[i] - x[i-1] - 1, y[j] - y[j-1] - 1);
  end;

  { Выводим ответ }
  writeln(a, ' ', b, ' ', m * n - a - b);
end.