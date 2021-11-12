program Hello;

type IntArray = array of array of Integer;

procedure sum(const A,B: IntArray;const n:integer; var C: IntArray);
var i,j:integer;
begin
    setLength(C, n, n);
    for i:=0 to n-1 do
        for j:=0 to n-1 do
            C[i][j]:=A[i][j]+B[i][j];
end;

procedure sub(const A,B: IntArray;const n:integer; var C: IntArray);
var i,j:integer;
begin
    setLength(C, n, n);
    for i:=0 to n-1 do
        for j:=0 to n-1 do
            C[i][j]:=A[i][j]-B[i][j];
end;

procedure mul(const A,B: IntArray;const n:integer; var C: IntArray);
var i,j,k:integer;
begin
    setLength(C, n, n);
    for i := 0 to n-1 do
        for j := 0 to n-1 do begin
            C[i][j] := 0;
            for k := 0 to n-1 do
                C[i][j] := C[i][j] + A[i][k] * B[k][j];
        end;
end;

var n,i,j:integer;
    A,B,C,D,TMP,E:IntArray;
begin
  writeln ('n=');
  readln(n);
  
  // Задаём размерности матриц n x n
  setLength(A, n, n);
  setLength(B, n, n);
  setLength(C, n, n);
  
  writeln ('Vvedite n*n elementov matrici A:');
  for i:=0 to n-1 do
    for j:=0 to n-1 do
        read(A[i][j]);
  
  writeln ('Vvedite n*n elementov matrici B:');
  for i:=0 to n-1 do
    for j:=0 to n-1 do
        read(B[i][j]);
  
  writeln ('Vvedite n*n elementov matrici C:');
  for i:=0 to n-1 do
    for j:=0 to n-1 do
        read(C[i][j]);
  
  // Единичная матрица
  setLength(E, n, n);
  
  // Заполняем единичную матрицу размера n. Остальные элементы равны 0
  for i:=0 to n-1 do
    E[i][i]:=1;

  // A * A + (E - B * C)
  mul(A,A,n,D);
  mul(B,C,n,TMP);
  sub(E,TMP,n,TMP);
  sum(D,TMP,n,D);
  
  writeln ('result matrix D=A*A-B*C+E:');
  for i:=0 to n-1 do begin
    for j:=0 to n-1 do 
        write(D[i][j],' ');
    writeln;
  end;
  
end.

