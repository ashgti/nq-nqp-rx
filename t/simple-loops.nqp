my @a := [1, 2, 3];
for @a {
  say($_ ~ " - Ok");
}

my $count := 0;
while $count != 5 {
  say(($count + 3) ~ " - Ok");
  $count := $count + 1;
}



