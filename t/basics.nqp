
my $foo := 5;
$foo := $foo + 5;

sub bar() { 
  return 5 + $foo;
};

my $aa := bar(1);

say($aa);

say($aa);

class Foo {
  method get_string() {
    return 'Foo';
  }
};

my $a := Foo.new;

say($a.get_string());

grammar Stuff {
  token abc { abc }
};

sub test($arg) {
  say($arg)
}

test(3);
