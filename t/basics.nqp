
my Int $foo := 5;
$foo = $foo + 5;

sub bar { 
  return 5 + $foo;
}

bar(1);
