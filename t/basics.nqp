
my $foo := 5;
$foo := $foo + 5; # $foo = 10

sub bar() { 
  return 5 + $foo; # return 15
}

my $aa := bar(); # $aa = 15

say($aa);

class Foo {
  method get_string() {
    return 'Foo';
  }
}

my $a := Foo.new(); # $a = Foo object instance

say($a.get_string()); # print "Foo\n"

grammar Stuff {
  token abc { abc }
}

sub test($arg) {
  say($arg)
}

test(3); # print "3\n"

