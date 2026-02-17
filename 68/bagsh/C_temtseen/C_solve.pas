{ Командная олимпиада школьников Санкт-Петербурга 2000 года }
{ Задача: "Произведения"                                    }
{ Автор: Андрей Станкевич                                   }
{ Решение: Андрей Станкевич                                 }
{ Алгоритм: Перебор с возвратом                             }

program products;

var
  i, j, n: longint;
  { Матрица }
  a: array [0..10, 0..10] of longint;
  ok: boolean;
  x, y,  { Данные }
    nx, ny, { Количество уже поставленных чисел }
      nox, noy: { Первое число (чтобы быстрее проверять второе) }
        array [0..100] of longint;
  dx, dy: { Делители }
    array [0..10, 0..100] of longint;
  u: { Пометки об использовании }
    array [0..1000] of boolean;

{ Ищем число, которое поставим на место a[p][q] }
procedure try(p, q: longint);
var
  i, j: integer;
begin
  if q > n then
  begin
    { Все - матрица заполнена }
    for i := 1 to n do
      if ny[i] <> 2 then exit;
    { Выводим }
    for i := 1 to n do
    begin
      for j := 1 to n do
        write(a[i][j] :3, ' ');
      writeln;
    end;
    { Выходим }
    ok := true;
    exit;
  end;

  if p > n then
  begin
    { Кончился столбец }
    if ny[q] <> 2 then exit;
    try(1, q+1);
    exit;
  end;

  if (nx[p] = 2) or (ny[q] = 2) then
  begin
    { Столбец или строка насыщены - ничего ставить нельзя }
    try(p+1, q);
    exit;
  end;

  if (nx[p] = 1) then
  begin
    { Осталось поставить последнее число в эту строку }
    { Оно определяется однозначно }
    i := x[p] div nox[p];
    if y[q] mod i <> 0 then
    begin
      { Не подходит }
      try(p+1, q);
      exit;
    end;

    { Это также второе число в этом столбце }
    if ny[q] = 1 then
    begin
      if not u[i] and (noy[q] * i = y[q]) then
      begin
        { Можно ставить }
        { Поиспользовали }
        u[i] := true;
        { Поставили }
        a[p][q] := i;
        { Отметили в счетчиках }
        inc(nx[p]);
        inc(ny[q]);
        { Вызываемся рекурсивно }
        try(p+1, q);
        { Возврат }
        u[i] := false;
        a[p][q] := 0;
        dec(nx[p]);
        dec(ny[q]);
        if ok then exit;
      end;
      { Не ставим }
      try(p+1, q);
      exit;
    end;

    { ny[q] = 0 }
    { То есть первое число в столбце }
    if not u[i] and (y[q] mod i = 0) then
    begin
      { Можно ставить }
      { Поиспользовали }
      u[i] := true;
      { Поставили }
      a[p][q] := i;
      { Отметили в счетчиках }
      inc(nx[p]);
      inc(ny[q]);
      { Запомнили его }
      noy[q] := i;
      { Вызываемся рекурсивно }
      try(p+1, q);
      { Возврат }
      u[i] := false;
      a[p][q] := 0;
      dec(nx[p]);
      dec(ny[q]);
      if ok then exit;
    end;
    { Не ставим }
    try(p+1, q);
    exit;
  end;

  { nx[p] = 0; }
  { То есть первое число в строке }
  { Перебираем делители }
  for j := 1 to dx[p][0] do
  begin
    i := dx[p][j];
    if u[i] then continue;
    if x[p] mod i <> 0 then continue;
    if y[q] mod i <> 0 then continue;

    { В принципе подходит }

    { Запоминаем }
    nox[p] := i;

    { Если это второе число в столбце }
    if ny[q] = 1 then
    begin
      if noy[q] * i = y[q] then
      begin
        { См выше ;) }
        u[i] := true;
        a[p][q] := i;
        inc(nx[p]);
        inc(ny[q]);
        try(p+1, q);
        u[i] := false;
        a[p][q] := 0;
        dec(nx[p]);
        dec(ny[q]);
        if ok then exit;
      end;
      continue;
    end;

    { ny[q] = 0 }
    { Если это первое число в столбце }
    u[i] := true;
    a[p][q] := i;
    inc(nx[p]);
    inc(ny[q]);
    noy[q] := i;
    try(p+1, q);
    u[i] := false;
    a[p][q] := 0;
    dec(nx[p]);
    dec(ny[q]);
    if ok then exit;
  end;

  { Не ставим }
  try(p+1, q);
end;

begin
  assign(input, 'input.txt');
  reset(input);
  assign(output, 'output.txt');
  rewrite(output);

  { Читаем размер }
  read(n);
  { Читаем данные (здесь поменяны по смыслу x и y ) }
  for i := 1 to n do
  begin
    read(y[i]);
    { Находим делители }
    for j := 1 to y[i] do
      if y[i] mod j = 0 then
      begin
        inc(dy[i][0]);
        dy[i][dy[i][0]] := j;
      end;
  end;
  for i := 1 to n do
  begin
    read(x[i]);
    { Находим делители }
    for j := 1 to x[i] do
      if x[i] mod j = 0 then
      begin
        inc(dx[i][0]);
        dx[i][dx[i][0]] := j;
      end;
  end;

  { Перебираем }
  try(1, 1);

  close(input);
  close(output);
end.